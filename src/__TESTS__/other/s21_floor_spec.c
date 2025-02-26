#include <check.h>

#include "../../s21_decimal.h"

/* Тест: Проверка округления положительного целого числа */
START_TEST(test_floor_positive_integer) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST

/* Тест: Проверка округления отрицательного целого числа */
START_TEST(test_floor_negative_integer) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

/* Тест: Проверка округления отрицательного дробного числа */
START_TEST(test_floor_negative_fraction) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_set_scale(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-1, fres);
}
END_TEST

/* Тест: Проверка округления положительного дробного числа */
START_TEST(test_floor_positive_fraction) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_scale(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(0, fres);
}
END_TEST

TCase *tcase_s21_floor(void) {
  TCase *test_cases = tcase_create("s21_floor");
  tcase_add_test(test_cases, test_floor_positive_integer);
  tcase_add_test(test_cases, test_floor_negative_integer);
  tcase_add_test(test_cases, test_floor_negative_fraction);
  tcase_add_test(test_cases, test_floor_positive_fraction);
  return test_cases;
}
