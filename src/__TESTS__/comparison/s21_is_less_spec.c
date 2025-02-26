#include <check.h>

#include "../../s21_decimal.h"

/* Тест: Проверка на "меньше" для одинаковых значений */
START_TEST(test_is_less_equal_values) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше" для значения, которое меньше по первому биту */
START_TEST(test_is_less_smaller_first_bit) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше" для одинаковых значений по битам */
START_TEST(test_is_less_equal_bits) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше" для значения, которое больше по первому биту */
START_TEST(test_is_less_larger_first_bit) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше" для установленных старших битов */
START_TEST(test_is_less_set_high_bit) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  s21_set_bit(&val1, 127, 1);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше" для чисел с разными масштабами, где первое число
 * меньше */
START_TEST(test_is_less_different_scale) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_scale(&val1, 11);
  s21_set_scale(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше" для чисел с разными масштабами, где первое число
 * больше */
START_TEST(test_is_less_different_scale_reversed) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_scale(&val1, 10);
  s21_set_scale(&val2, 11);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше" для чисел с установленными старшими битами */
START_TEST(test_is_less_both_high_bits_set) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val2.bits[2] = 257;
  s21_set_bit(&val1, 127, 1);
  s21_set_bit(&val2, 127, 1);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше" для чисел с разными знаками и масштабами */
START_TEST(test_is_less_different_signs_scale) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  s21_set_bit(&val1, 127, 1);
  s21_set_bit(&val2, 127, 1);
  s21_set_bit(&val1, 83, 1);
  s21_set_scale(&val1, 12);
  s21_set_scale(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше" для чисел с одинаковыми знаками, но разными
 * масштабами */
START_TEST(test_is_less_equal_signs_different_scale) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  s21_set_bit(&val1, 127, 1);
  s21_set_bit(&val2, 127, 1);
  s21_set_bit(&val1, 83, 1);
  s21_set_bit(&val2, 83, 1);
  s21_set_scale(&val1, 10);
  s21_set_scale(&val2, 11);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше" для чисел с одинаковыми масштабами */
START_TEST(test_is_less_equal_scale) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  s21_set_bit(&val1, 127, 1);
  s21_set_bit(&val2, 127, 1);
  s21_set_bit(&val1, 83, 1);
  s21_set_scale(&val1, 10);
  s21_set_scale(&val2, 10);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше" для отрицательного числа по сравнению с
 * положительным */
START_TEST(test_is_less_negative_vs_positive) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  s21_set_bit(&val1, 127, 1);
  s21_set_bit(&val2, 127, 0);
  s21_set_bit(&val1, 83, 1);
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше" для отрицательного числа по сравнению с
 * положительным с установленным старшим битом */
START_TEST(test_is_less_negative_vs_positive_high_bit) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  s21_set_bit(&val1, 127, 1);
  s21_set_bit(&val2, 127, 0);
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

TCase *tcase_s21_is_less(void) {
  TCase *test_cases = tcase_create("s21_is_less");
  tcase_add_test(test_cases, test_is_less_equal_values);
  tcase_add_test(test_cases, test_is_less_smaller_first_bit);
  tcase_add_test(test_cases, test_is_less_equal_bits);
  tcase_add_test(test_cases, test_is_less_larger_first_bit);
  tcase_add_test(test_cases, test_is_less_set_high_bit);
  tcase_add_test(test_cases, test_is_less_different_scale);
  tcase_add_test(test_cases, test_is_less_different_scale_reversed);
  tcase_add_test(test_cases, test_is_less_both_high_bits_set);
  tcase_add_test(test_cases, test_is_less_different_signs_scale);
  tcase_add_test(test_cases, test_is_less_equal_signs_different_scale);
  tcase_add_test(test_cases, test_is_less_equal_scale);
  tcase_add_test(test_cases, test_is_less_negative_vs_positive);
  tcase_add_test(test_cases, test_is_less_negative_vs_positive_high_bit);
  return test_cases;
}
