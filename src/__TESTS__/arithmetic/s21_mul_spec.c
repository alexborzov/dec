#include <check.h>

#include "../../s21_decimal.h"

/** Тест: Проверка умножения двух положительных чисел (результат положительный)
 */
START_TEST(test_mul_two_positive_numbers) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{3, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

/** Тест: Проверка умножения двух отрицательных чисел (результат положительный)
 */
START_TEST(test_mul_two_negative_numbers) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{3, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

/** Тест: Проверка умножения положительного числа на отрицательное (результат
 * отрицательный) */
START_TEST(test_mul_positive_and_negative) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{3, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

/** Тест: Проверка умножения на ноль (результат должен быть ноль) */
START_TEST(test_mul_by_zero) {
  s21_decimal val1 = {{5, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

/** Тест: Проверка переполнения при умножении двух положительных чисел */
START_TEST(test_mul_positive_overflow) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

/** Тест: Проверка переполнения при умножении двух отрицательных чисел */
START_TEST(test_mul_negative_overflow) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

/** Тест: Проверка переполнения при умножении максимальных мантисс (очень
 * большие числа) */
START_TEST(test_mul_max_value_overflow) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

/** Тест: Проверка правильности результата умножения чисел с разными масштабами
 */
START_TEST(test_mul_with_scaling) {
  s21_decimal val1 = {{10, 0, 0, 0}};
  s21_decimal val2 = {{5, 0, 0, 1}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

/** Тест: Проверка переполнения с очень маленькими значениями мантиссы */
START_TEST(test_mul_small_mantissa_overflow) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

TCase *tcase_s21_mul(void) {
  TCase *test_cases = tcase_create("s21_mul");
  tcase_add_test(test_cases, test_mul_two_positive_numbers);
  tcase_add_test(test_cases, test_mul_two_negative_numbers);
  tcase_add_test(test_cases, test_mul_positive_and_negative);
  tcase_add_test(test_cases, test_mul_by_zero);
  tcase_add_test(test_cases, test_mul_positive_overflow);
  tcase_add_test(test_cases, test_mul_negative_overflow);
  tcase_add_test(test_cases, test_mul_max_value_overflow);
  tcase_add_test(test_cases, test_mul_with_scaling);
  tcase_add_test(test_cases, test_mul_small_mantissa_overflow);
  return test_cases;
}
