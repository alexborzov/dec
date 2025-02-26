#include <check.h>

#include "../../s21_decimal.h"

// Проверка преобразования положительного значения из decimal в float с
// масштабом 5
START_TEST(test_from_decimal_to_float_positive) {
  s21_decimal value = {{123456789, 0, 0, 0}};
  s21_set_scale(&value, 5);

  float expected = 1234.56789;
  float result = 0.0;

  s21_from_decimal_to_float(value, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// Проверка преобразования отрицательного значения из decimal в float с
// масштабом 5
START_TEST(test_from_decimal_to_float_negative) {
  s21_decimal value = {{123456789, 0, 0, 0}};
  s21_set_bit(&value, 127, 1);  // Отрицательное значение
  s21_set_scale(&value, 5);

  float expected = -1234.56789;
  float result = 0.0;

  s21_from_decimal_to_float(value, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// Проверка преобразования нулевого значения из decimal в float
START_TEST(test_from_decimal_to_float_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_set_scale(&value, 5);

  float expected = 0.0;
  float result = 0.0;

  s21_from_decimal_to_float(value, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// Проверка преобразования большого значения из decimal в float с масштабом 0
START_TEST(test_from_decimal_to_float_large_value) {
  s21_decimal value = {{1234567890, 0, 0, 0}};
  s21_set_scale(&value, 0);

  float expected = 1234567890.0;
  float result = 0.0;

  s21_from_decimal_to_float(value, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

TCase *tcase_s21_from_decimal_to_float(void) {
  TCase *test_cases = tcase_create("s21_from_decimal_to_float");
  tcase_add_test(test_cases, test_from_decimal_to_float_positive);
  tcase_add_test(test_cases, test_from_decimal_to_float_negative);
  tcase_add_test(test_cases, test_from_decimal_to_float_zero);
  tcase_add_test(test_cases, test_from_decimal_to_float_large_value);
  return test_cases;
}
