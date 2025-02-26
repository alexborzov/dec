#include <check.h>

#include "../../s21_decimal.h"

/* Тест: Проверка на равенство значений */
START_TEST(test_equal_values) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше или равно" для значения, которое меньше */
START_TEST(test_less_than_value) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше или равно" для одинаковых ненулевых значений */
START_TEST(test_equal_nonzero_values) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше или равно" для значения, которое больше */
START_TEST(test_greater_than_value) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше или равно" для отрицательного числа по сравнению с
 * нулём */
START_TEST(test_negative_value_vs_zero) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  s21_set_bit(&val1, 127, 1);
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше или равно" для чисел с разными масштабами, где
 * первое число меньше */
START_TEST(test_different_scales_less) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_scale(&val1, 11);
  s21_set_scale(&val2, 10);
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше или равно" для чисел с разными масштабами, где
 * первое число больше */
START_TEST(test_different_scales_greater) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_scale(&val1, 10);
  s21_set_scale(&val2, 11);
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка на "меньше или равно" для отрицательных значений */
START_TEST(test_negative_values_comparison) {
  s21_decimal val1 = {{0, 0, 0, 0}}, val2 = {{0, 0, 0, 0}};
  val2.bits[2] = 257;
  s21_set_bit(&val1, 127, 1);
  s21_set_bit(&val2, 127, 1);
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

TCase *tcase_s21_is_less_or_equal(void) {
  TCase *test_cases = tcase_create("s21_is_less_or_equal");
  tcase_add_test(test_cases, test_equal_values);
  tcase_add_test(test_cases, test_less_than_value);
  tcase_add_test(test_cases, test_equal_nonzero_values);
  tcase_add_test(test_cases, test_greater_than_value);
  tcase_add_test(test_cases, test_negative_value_vs_zero);
  tcase_add_test(test_cases, test_different_scales_less);
  tcase_add_test(test_cases, test_different_scales_greater);
  tcase_add_test(test_cases, test_negative_values_comparison);
  return test_cases;
}
