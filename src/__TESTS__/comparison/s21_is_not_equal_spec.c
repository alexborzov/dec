#include <check.h>

#include "../../s21_decimal.h"

/* Проверка на "не равно" для чисел с различиями в одном бите */
START_TEST(test_not_equal_bit_difference) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val2, 3, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

/* Проверка на "не равно" для чисел с несколькими различиями в битах */
START_TEST(test_not_equal_multiple_bit_difference) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val2, 127, 1);
  s21_set_bit(&val1, 33, 1);
  s21_set_bit(&val2, 33, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

/* Проверка на "не равно" для одинаковых значений */
START_TEST(test_not_equal_same_values) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val1, 3, 1);
  s21_set_bit(&val2, 3, 1);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

/* Проверка на "не равно" для чисел с различием в одном бите */
START_TEST(test_not_equal_single_bit_difference) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val1, 3, 1);
  s21_set_bit(&val2, 4, 1);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

/* Проверка на "не равно" для чисел с одинаковыми масштабами */
START_TEST(test_not_equal_same_scale) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_scale(&val1, 3);
  s21_set_scale(&val2, 3);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

/* Проверка на "не равно" для чисел с различиями в битах и одинаковыми
 * масштабами */
START_TEST(test_not_equal_scale_and_bit_difference) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val1, 3, 1);
  s21_set_bit(&val2, 4, 1);
  s21_set_scale(&val1, 3);
  s21_set_scale(&val2, 3);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

/* Проверка на "не равно" для чисел с различными масштабами */
START_TEST(test_not_equal_different_scales) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_scale(&val1, 3);
  s21_set_scale(&val2, 2);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

/* Проверка на "не равно" для одинаковых значений, равных нулям */
START_TEST(test_not_equal_identical_zeros) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

/* Проверка сравнения отрицательных и положительных значений */
START_TEST(test_negative_vs_positive) {
  s21_decimal val1 = {0}, val2 = {0};
  s21_set_bit(&val1, 127, 1);
  s21_set_bit(&val2, 127, 0);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

/* Проверка чисел с нулевыми значениями в разных масштабах */
START_TEST(test_zero_with_different_scales) {
  s21_decimal val1 = {0}, val2 = {0};
  s21_set_scale(&val1, 3);
  s21_set_scale(&val2, 2);
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

/* Проверка сравнения чисел с одинаковым значением, но с разными знаками */
START_TEST(test_negative_and_positive_equal_magnitude) {
  s21_decimal val1 = {0}, val2 = {0};
  s21_set_bit(&val1, 127, 1);
  s21_set_bit(&val2, 127, 0);
  s21_set_bit(&val1, 0, 10);
  s21_set_bit(&val2, 0, 10);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

/* Проверка дробных значений с разными битами и одинаковыми значениями */
START_TEST(test_fractions_with_different_bits) {
  s21_decimal val1 = {0}, val2 = {0};
  s21_set_bit(&val1, 3, 1);
  s21_set_bit(&val2, 4, 1);
  s21_set_scale(&val1, 3);
  s21_set_scale(&val2, 3);
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

TCase *tcase_s21_is_not_equal(void) {
  TCase *test_cases = tcase_create("s21_is_not_equal");
  tcase_add_test(test_cases, test_not_equal_bit_difference);
  tcase_add_test(test_cases, test_not_equal_multiple_bit_difference);
  tcase_add_test(test_cases, test_not_equal_same_values);
  tcase_add_test(test_cases, test_not_equal_single_bit_difference);
  tcase_add_test(test_cases, test_not_equal_same_scale);
  tcase_add_test(test_cases, test_not_equal_scale_and_bit_difference);
  tcase_add_test(test_cases, test_not_equal_different_scales);
  tcase_add_test(test_cases, test_not_equal_identical_zeros);
  tcase_add_test(test_cases, test_negative_vs_positive);
  tcase_add_test(test_cases, test_zero_with_different_scales);
  tcase_add_test(test_cases, test_negative_and_positive_equal_magnitude);
  tcase_add_test(test_cases, test_fractions_with_different_bits);
  return test_cases;
}
