#include <check.h>

#include "../../s21_decimal.h"

/* Тест: Проверка равенства нуля и отрицательного нуля */
START_TEST(test_zero_and_negative_zero_equivalence) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_set_sign(&val2, 1);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

/* Тест: Проверка идентичности битов в разных позициях */
START_TEST(test_different_bit_positions) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val2, 3, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

/* Тест: Проверка идентичности битов в разных позициях */
START_TEST(test_different_bits_high_position) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val2, 127, 1);
  s21_set_bit(&val1, 33, 1);
  s21_set_bit(&val2, 33, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

/* Тест: Проверка идентичности битов */
START_TEST(test_identical_bits) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val1, 3, 1);
  s21_set_bit(&val2, 3, 1);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

/* Тест: Проверка различия смежных битов */
START_TEST(test_adjacent_bits_difference) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val1, 3, 1);
  s21_set_bit(&val2, 4, 1);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

/* Тест: Проверка равенства чисел с одинаковым масштабом */
START_TEST(test_same_scale_values) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_scale(&val1, 3);
  s21_set_scale(&val2, 3);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

/* Тест: Проверка равенства чисел с разными битами и одинаковым масштабом */
START_TEST(test_different_bits_with_same_scale) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_bit(&val1, 3, 1);
  s21_set_bit(&val2, 4, 1);
  s21_set_scale(&val1, 3);
  s21_set_scale(&val2, 3);
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

/* Тест: Проверка равенства чисел при разных масштабах */
START_TEST(test_different_scales_with_equal_values) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_set_scale(&val1, 3);
  s21_set_scale(&val2, 2);
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

/* Тест: Проверка равенства двух нулевых значений */
START_TEST(test_two_zero_values_equivalence) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

TCase *tcase_s21_is_equal(void) {
  TCase *test_cases = tcase_create("s21_is_equal");
  tcase_add_test(test_cases, test_zero_and_negative_zero_equivalence);
  tcase_add_test(test_cases, test_different_bit_positions);
  tcase_add_test(test_cases, test_different_bits_high_position);
  tcase_add_test(test_cases, test_identical_bits);
  tcase_add_test(test_cases, test_adjacent_bits_difference);
  tcase_add_test(test_cases, test_same_scale_values);
  tcase_add_test(test_cases, test_different_bits_with_same_scale);
  tcase_add_test(test_cases, test_different_scales_with_equal_values);
  tcase_add_test(test_cases, test_two_zero_values_equivalence);
  return test_cases;
}
