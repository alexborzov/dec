#include <check.h>

#include "../../s21_decimal.h"

/* Тест: Инверсия знака положительного числа */
START_TEST(test_negate_positive_integer) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  int sign_before = s21_get_sign(val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign(res);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

/* Тест: Инверсия знака отрицательного числа */
START_TEST(test_negate_negative_integer) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  int sign_before = s21_get_sign(val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign(res);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

/* Тест: Инверсия знака у нуля с отрицательным знаком */
START_TEST(test_negate_negative_zero) {
  s21_decimal val = {{0, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  int sign_before = s21_get_sign(val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign(res);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

/* Тест: Инверсия знака у нуля с положительным знаком */
START_TEST(test_negate_positive_zero) {
  s21_decimal val = {0};
  s21_decimal res = {0};
  int sign_before = s21_get_sign(val);
  s21_negate(val, &res);
  int sign_after = s21_get_sign(res);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

TCase *tcase_s21_negate(void) {
  TCase *test_cases = tcase_create("s21_negate");
  tcase_add_test(test_cases, test_negate_positive_integer);
  tcase_add_test(test_cases, test_negate_negative_integer);
  tcase_add_test(test_cases, test_negate_negative_zero);
  tcase_add_test(test_cases, test_negate_positive_zero);
  return test_cases;
}
