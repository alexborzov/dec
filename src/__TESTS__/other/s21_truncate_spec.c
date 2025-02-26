#include <check.h>

#include "../../s21_decimal.h"

/* Функция для выполнения теста */
void run_truncate_test(s21_decimal val, float expected) {
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(expected, fres);
}

/* Тест: Проверка округления положительного целого числа */
START_TEST(truncate_positive_integer) {
  s21_decimal val = {{7, 7, 7, 0}};
  run_truncate_test(val, 129127208515966861312.0);
}
END_TEST

/* Тест: Проверка округления отрицательного целого числа */
START_TEST(truncate_negative_integer) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  run_truncate_test(val, -2.0);
}
END_TEST

/* Тест: Проверка округления повторного отрицательного целого числа */
START_TEST(truncate_negative_integer_duplicate) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  run_truncate_test(val, -2.0);
}
END_TEST

/* Тест: Проверка округления отрицательного числа с масштабом */
START_TEST(truncate_negative_scaled) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_set_scale(&val, 5);
  run_truncate_test(val, -0.0);
}
END_TEST

/* Тест: Проверка округления положительного числа с масштабом */
START_TEST(truncate_positive_scaled) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_set_scale(&val, 1);
  run_truncate_test(val, 12.0);
}
END_TEST

/* Тест: Проверка округления нулевого значения */
START_TEST(truncate_zero_value) {
  s21_decimal val = {{0, 0, 0, 0}};
  run_truncate_test(val, 0.0);
}
END_TEST

TCase *tcase_s21_truncate(void) {
  TCase *test_cases = tcase_create("s21_truncate");
  tcase_add_test(test_cases, truncate_positive_integer);
  tcase_add_test(test_cases, truncate_negative_integer);
  tcase_add_test(test_cases, truncate_negative_integer_duplicate);
  tcase_add_test(test_cases, truncate_negative_scaled);
  tcase_add_test(test_cases, truncate_positive_scaled);
  tcase_add_test(test_cases, truncate_zero_value);
  return test_cases;
}
