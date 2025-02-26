#include <check.h>

#include "../../s21_decimal.h"

// Тест: Проверка вычитания одинаковых положительных чисел (результат 0)
START_TEST(test_sub_same_positive_values) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

// Тест: Проверка вычитания одинаковых отрицательных чисел (результат 0)
START_TEST(test_sub_same_negative_values) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

// Тест: Проверка вычитания положительного числа и отрицательного (результат
// положительный)
START_TEST(test_sub_positive_minus_negative) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

// Тест: Проверка вычитания отрицательного числа и положительного (результат
// отрицательный)
START_TEST(test_sub_negative_minus_positive) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

// Тест: Проверка вычитания большего числа из меньшего (результат отрицательный)
START_TEST(test_sub_larger_minus_smaller) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

// Тест: Проверка вычитания меньшего числа из большего (результат отрицательный)
START_TEST(test_sub_smaller_minus_larger) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

// Тест: Проверка вычитания на границах значений (максимальное значение - малое
// положительное)
START_TEST(test_sub_max_value_minus_small) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

// Тест: Проверка переполнения при вычитании с отрицательным числом
START_TEST(test_sub_max_negative_overflow) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

TCase *tcase_s21_sub(void) {
  TCase *test_cases = tcase_create("s21_sub");
  tcase_add_test(test_cases, test_sub_same_positive_values);
  tcase_add_test(test_cases, test_sub_same_negative_values);
  tcase_add_test(test_cases, test_sub_positive_minus_negative);
  tcase_add_test(test_cases, test_sub_negative_minus_positive);
  tcase_add_test(test_cases, test_sub_larger_minus_smaller);
  tcase_add_test(test_cases, test_sub_smaller_minus_larger);
  tcase_add_test(test_cases, test_sub_max_value_minus_small);
  tcase_add_test(test_cases, test_sub_max_negative_overflow);
  return test_cases;
}
