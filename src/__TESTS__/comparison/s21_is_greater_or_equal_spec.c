#include <check.h>

#include "../../s21_decimal.h"

/* Тест: Проверка "больше или равно" для одинаковых значений */
START_TEST(test_greater_or_equal_same_values) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка "больше или равно" для значения, которое меньше */
START_TEST(test_greater_or_equal_less) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка "больше или равно" для одинаковых значений */
START_TEST(test_greater_or_equal_equal_values) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка "больше или равно" для значения, которое больше */
START_TEST(test_greater_or_equal_greater) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка "больше или равно" для значения с установленным старшим битом
 */
START_TEST(test_greater_or_equal_high_bit) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_set_bit(&val1, 127, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка "больше или равно" для чисел с разными масштабами, где первое
 * число меньше */
START_TEST(test_greater_or_equal_different_scale_less) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_scale(&val1, 11);
  s21_set_scale(&val2, 10);
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка "больше или равно" для чисел с разными масштабами, где первое
 * число больше */
START_TEST(test_greater_or_equal_different_scale_greater) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  s21_set_scale(&val1, 10);
  s21_set_scale(&val2, 11);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

/* Тест: Проверка "больше или равно" для чисел с установленным старшим битом и
 * разными значениями */
START_TEST(test_greater_or_equal_high_bit_set) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  val2.bits[2] = 257;
  s21_set_bit(&val1, 127, 1);
  s21_set_bit(&val2, 127, 1);
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

TCase *tcase_s21_is_greater_or_equal(void) {
  TCase *test_cases = tcase_create("s21_is_greater_or_equal");
  tcase_add_test(test_cases, test_greater_or_equal_same_values);
  tcase_add_test(test_cases, test_greater_or_equal_less);
  tcase_add_test(test_cases, test_greater_or_equal_equal_values);
  tcase_add_test(test_cases, test_greater_or_equal_greater);
  tcase_add_test(test_cases, test_greater_or_equal_high_bit);
  tcase_add_test(test_cases, test_greater_or_equal_different_scale_less);
  tcase_add_test(test_cases, test_greater_or_equal_different_scale_greater);
  tcase_add_test(test_cases, test_greater_or_equal_high_bit_set);
  return test_cases;
}
