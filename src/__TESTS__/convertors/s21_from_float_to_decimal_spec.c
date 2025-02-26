#include <check.h>

#include "../../s21_decimal.h"

// Проверка преобразования отрицательного значения из float в decimal и обратно
START_TEST(test_from_float_to_decimal_negative) {
  float input = -1234.56789;
  s21_decimal decimal_value = {{0, 0, 0, 0}};
  float result = 0.0;

  s21_from_float_to_decimal(input, &decimal_value);

  s21_from_decimal_to_float(decimal_value, &result);

  ck_assert_float_eq(result, input);
}
END_TEST

// Проверка преобразования положительного значения из float в decimal и обратно
START_TEST(test_from_float_to_decimal_positive) {
  float input = 1234.56789;
  s21_decimal decimal_value = {{0, 0, 0, 0}};
  float result = 0.0;

  s21_from_float_to_decimal(input, &decimal_value);

  s21_from_decimal_to_float(decimal_value, &result);

  ck_assert_float_eq(result, input);
}
END_TEST

// Проверка преобразования нулевого значения из float в decimal и обратно
START_TEST(test_from_float_to_decimal_zero) {
  float input = 0.0;
  s21_decimal decimal_value = {{0, 0, 0, 0}};
  float result = 0.0;

  s21_from_float_to_decimal(input, &decimal_value);

  s21_from_decimal_to_float(decimal_value, &result);

  ck_assert_float_eq(result, input);
}
END_TEST

// Проверка преобразования большого значения из float в decimal и обратно
START_TEST(test_from_float_to_decimal_large_value) {
  float input = 1234567.89;
  s21_decimal decimal_value = {{0, 0, 0, 0}};
  float result = 0.0;

  s21_from_float_to_decimal(input, &decimal_value);

  s21_from_decimal_to_float(decimal_value, &result);

  ck_assert_float_eq(result, input);
}
END_TEST

// Проверка возможной потери точности при преобразовании float в decimal
START_TEST(test_from_float_to_decimal_precision_loss) {
  float input = 0.0001234;
  s21_decimal decimal_value = {{0, 0, 0, 0}};
  float result = 0.0;

  s21_from_float_to_decimal(input, &decimal_value);

  s21_from_decimal_to_float(decimal_value, &result);

  ck_assert_float_eq(result, input);  // Точность должна быть сохранена
}
END_TEST

START_TEST(test_from_float_to_decimal_overflow) {
  s21_decimal result;

  // Тест переполнения (слишком большое число)
  float src = FLT_MAX * 10.0f;
  int status = s21_from_float_to_decimal(src, &result);
  ck_assert_int_eq(status, s21_flag_error);
}
END_TEST

START_TEST(test_from_float_to_decimal_nan) {
  s21_decimal result;

  // Тест NAN
  float src = NAN;
  int status = s21_from_float_to_decimal(src, &result);
  ck_assert_int_eq(status, s21_flag_error);
}
END_TEST

START_TEST(test_from_float_to_decimal_inf) {
  s21_decimal result;

  // Тест бесконечности
  float src = INFINITY;
  int status = s21_from_float_to_decimal(src, &result);
  ck_assert_int_eq(status, s21_flag_error);
}
END_TEST

START_TEST(test_from_float_to_decimal_null_pointer) {
  // Передаем NULL в dst
  float src = 123.45f;
  int status = s21_from_float_to_decimal(src, NULL);
  ck_assert_int_eq(status, s21_flag_error);
}
END_TEST

TCase *tcase_s21_from_float_to_decimal(void) {
  TCase *test_cases = tcase_create("s21_from_float_to_decimal");
  tcase_add_test(test_cases, test_from_float_to_decimal_positive);
  tcase_add_test(test_cases, test_from_float_to_decimal_negative);
  tcase_add_test(test_cases, test_from_float_to_decimal_zero);
  tcase_add_test(test_cases, test_from_float_to_decimal_large_value);
  tcase_add_test(test_cases, test_from_float_to_decimal_precision_loss);
  tcase_add_test(test_cases, test_from_float_to_decimal_overflow);
  tcase_add_test(test_cases, test_from_float_to_decimal_nan);
  tcase_add_test(test_cases, test_from_float_to_decimal_inf);
  tcase_add_test(test_cases, test_from_float_to_decimal_null_pointer);
  return test_cases;
}
