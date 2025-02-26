#include <check.h>

#include "../../s21_decimal.h"

// Проверка преобразования положительного значения из int в decimal и обратно
START_TEST(test_from_int_to_decimal_positive) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int expected_value = 123456789;

  s21_from_int_to_decimal(expected_value, &val);

  s21_from_decimal_to_int(val, &res);

  ck_assert_int_eq(res, expected_value);
}
END_TEST

// Проверка преобразования отрицательного значения из int в decimal и обратно
START_TEST(test_from_int_to_decimal_negative) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int expected_value = -123456789;

  s21_from_int_to_decimal(expected_value, &val);

  s21_from_decimal_to_int(val, &res);

  ck_assert_int_eq(res, expected_value);
}
END_TEST

// Проверка преобразования нулевого значения из int в decimal и обратно
START_TEST(test_from_int_to_decimal_zero) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int expected_value = 0;

  s21_from_int_to_decimal(expected_value, &val);

  s21_from_decimal_to_int(val, &res);

  ck_assert_int_eq(res, expected_value);
}
END_TEST

// Проверка преобразования большого значения из int в decimal и обратно
START_TEST(test_from_int_to_decimal_large_value) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int expected_value = 2147483647;  // максимальное значение для int

  s21_from_int_to_decimal(expected_value, &val);

  s21_from_decimal_to_int(val, &res);

  ck_assert_int_eq(res, expected_value);
}
END_TEST

TCase *tcase_s21_from_int_to_decimal(void) {
  TCase *test_cases = tcase_create("s21_from_int_to_decimal");
  tcase_add_test(test_cases, test_from_int_to_decimal_positive);
  tcase_add_test(test_cases, test_from_int_to_decimal_negative);
  tcase_add_test(test_cases, test_from_int_to_decimal_zero);
  tcase_add_test(test_cases, test_from_int_to_decimal_large_value);
  return test_cases;
}
