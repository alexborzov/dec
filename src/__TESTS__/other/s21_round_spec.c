#include <check.h>

#include "../../s21_decimal.h"

/* Тест: Округление положительного большого целого числа */
START_TEST(test_round_positive_large_integer) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res = {0};
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

/* Тест: Округление отрицательного большого целого числа */
START_TEST(test_round_negative_large_integer) {
  s21_decimal val = {{3, 3, 3, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

/* Тест: Округление положительного дробного числа */
START_TEST(test_round_positive_fraction) {
  s21_decimal val = {{3, 3, 3, 0}};
  s21_decimal res = {0};
  s21_set_scale(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

/* Тест: Округление отрицательного дробного числа */
START_TEST(test_round_negative_fraction) {
  s21_decimal val = {{7, 7, 7, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_set_scale(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

/* Тест: Округление отрицательного числа с масштабом 1 */
START_TEST(test_round_negative_scale_1) {
  s21_decimal val = {{25, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

/* Тест: Округление положительного числа с масштабом 1 */
START_TEST(test_round_positive_scale_1) {
  s21_decimal val = {{26, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

/* Тест: Округление числа 11.5 до ближайшего целого */
START_TEST(test_round_11_5_to_12) {
  s21_decimal val = {{115, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

/* Тест: Округление числа 11.8 до ближайшего целого */
START_TEST(test_round_11_8_to_12) {
  s21_decimal val = {{118, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

/* Тест: Округление числа 12.5 до ближайшего чётного */
START_TEST(test_round_12_5_to_12) {
  s21_decimal val = {{125, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_scale(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

/* Тест: Округление числа 12.8 до 13 */
START_TEST(test_round_12_8_to_13) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_scale(&val, 1);
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 13;
  ck_assert_float_eq(need, fres);
}
END_TEST

TCase *tcase_s21_round(void) {
  TCase *test_cases = tcase_create("s21_round");
  tcase_add_test(test_cases, test_round_positive_large_integer);
  tcase_add_test(test_cases, test_round_negative_large_integer);
  tcase_add_test(test_cases, test_round_positive_fraction);
  tcase_add_test(test_cases, test_round_negative_fraction);
  tcase_add_test(test_cases, test_round_negative_scale_1);
  tcase_add_test(test_cases, test_round_positive_scale_1);
  tcase_add_test(test_cases, test_round_11_5_to_12);
  tcase_add_test(test_cases, test_round_11_8_to_12);
  tcase_add_test(test_cases, test_round_12_5_to_12);
  tcase_add_test(test_cases, test_round_12_8_to_13);
  return test_cases;
}
