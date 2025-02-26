#include <check.h>

#include "../../s21_decimal.h"

/* Тест: Проверка деления двух положительных чисел (результат положительный) */
START_TEST(test_div_two_positive_numbers) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

/*  Тест: Проверка деления двух отрицательных чисел (результат положительный) */
START_TEST(test_div_two_negative_numbers) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

/* Тест: Проверка деления положительного числа на отрицательное (результат
 * отрицательный) */
START_TEST(test_div_positive_by_negative) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

/* Тест: Проверка деления отрицательного числа на положительное (результат
 * отрицательный) */
START_TEST(test_div_negative_by_positive) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

/* Тест: Проверка деления с простым дробным результатом (0.5) */
START_TEST(test_div_fractional_result_simple) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

/* Тест: Проверка деления с периодическим дробным результатом (0.333...) */
START_TEST(test_div_fractional_result_periodic) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal val2 = {{3, 0, 0, 0}};
  s21_decimal res = {{0}};
  int status = s21_div(val1, val2, &res);
  ck_assert_int_eq(0, status);
}
END_TEST

TCase *tcase_s21_div(void) {
  TCase *test_cases = tcase_create("s21_div");
  tcase_add_test(test_cases, test_div_two_positive_numbers);
  tcase_add_test(test_cases, test_div_two_negative_numbers);
  tcase_add_test(test_cases, test_div_positive_by_negative);
  tcase_add_test(test_cases, test_div_negative_by_positive);
  tcase_add_test(test_cases, test_div_fractional_result_simple);
  tcase_add_test(test_cases, test_div_fractional_result_periodic);
  return test_cases;
}
