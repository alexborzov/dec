#include <check.h>

#include "../../s21_decimal.h"

/* Тест: Проверка "больше" для одинаковых значений */
START_TEST(test_is_greater_equal_values) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

/* Тест: Проверка "больше" для значения, которое меньше в первом бите */
START_TEST(test_is_greater_smaller_first_bit) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

/* Тест: Проверка "больше" для одинаковых значений в первом бите */
START_TEST(test_is_greater_equal_bits) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

/* Тест: Проверка "больше" для значения, которое больше в первом бите */
START_TEST(test_is_greater_larger_first_bit) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

/* Тест: Проверка "больше" для значения с установленным старшим битом */
START_TEST(test_is_greater_set_high_bit) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  s21_set_bit(&val1, 127, 1);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

/* Тест: Проверка "больше" для чисел с разными масштабами, где первое число
 * меньше */
START_TEST(test_is_greater_different_scale) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_scale(&val1, 11);
  s21_set_scale(&val2, 10);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

/* Тест: Проверка "больше" для чисел с разными масштабами, где первое число
 * больше */
START_TEST(test_is_greater_different_scale_reversed) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_scale(&val1, 10);
  s21_set_scale(&val2, 11);
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

/* Тест: Проверка "больше" для чисел с установленным старшим битом */
START_TEST(test_is_greater_both_high_bits_set) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val2.bits[2] = 257;
  s21_set_bit(&val1, 127, 1);
  s21_set_bit(&val2, 127, 1);
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

/* Тест: Проверка "больше" для чисел с разными знаками */
START_TEST(test_is_greater_different_signs) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val2.bits[2] = 257;
  s21_set_bit(&val1, 127, 1);
  s21_set_bit(&val2, 127, 0);
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

TCase *tcase_s21_is_greater(void) {
  TCase *test_cases = tcase_create("s21_is_greater");
  tcase_add_test(test_cases, test_is_greater_equal_values);
  tcase_add_test(test_cases, test_is_greater_smaller_first_bit);
  tcase_add_test(test_cases, test_is_greater_equal_bits);
  tcase_add_test(test_cases, test_is_greater_larger_first_bit);
  tcase_add_test(test_cases, test_is_greater_set_high_bit);
  tcase_add_test(test_cases, test_is_greater_different_scale);
  tcase_add_test(test_cases, test_is_greater_different_scale_reversed);
  tcase_add_test(test_cases, test_is_greater_both_high_bits_set);
  tcase_add_test(test_cases, test_is_greater_different_signs);
  return test_cases;
}
