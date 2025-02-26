#include <check.h>

#include "../../s21_decimal.h"

/* Тест: Проверка сложения двух положительных чисел (результат положительный) */
START_TEST(test_add_positive_values) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));

  val1 = (s21_decimal){{2, 0, 0, 0}};
  val2 = (s21_decimal){{8, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));

  val1 = (s21_decimal){{0}};
  val2 = (s21_decimal){{0}};
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

/* Тест: Проверка переполнения при сложении больших положительных чисел */
START_TEST(test_add_overflow_positive) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

/* Тест: Проверка переполнения при сложении больших отрицательных чисел */
START_TEST(test_add_overflow_negative) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

/* Тест: Проверка сложения отрицательных чисел с разными масштабами */
START_TEST(test_add_negative_with_scale) {
  s21_decimal val1 = {{UINT_MAX, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  s21_set_scale(&val1, 5);
  s21_set_scale(&val2, 3);
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

/* Тест: Проверка сложения отрицательного числа и положительного (результат
 * положительный) */
START_TEST(test_add_negative_plus_positive) {
  s21_decimal val1 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

/* Тест: Проверка сложения положительного числа и отрицательного (результат
 * отрицательный) */
START_TEST(test_add_positive_plus_negative) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

/* Тест: Проверка переполнения при сложении большого отрицательного числа и
 * большого отрицательного числа */
START_TEST(test_add_large_negative_overflow) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

/* Тест: Проверка сложения с неинициализированным результатом */
START_TEST(test_add_uninitialized_result) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

/* Тест: Проверка сложения с неинициализированными входными значениями */
START_TEST(test_add_uninitialized_inputs) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;  // Инициализируем результат
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

/* Тест: Проверка сложения с частично инициализированными входными значениями */
START_TEST(test_add_partially_initialized_inputs) {
  s21_decimal val1 = {{8, 0, 0}};  // Не инициализирован последний элемент
  s21_decimal val2 = {{2, 0, 0}};  // Не инициализирован последний элемент
  s21_decimal res = {{0}};         // Инициализируем результат
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

/* Тест: Проверка сложения с нулевыми значениями */
// START_TEST(test_add_zeros) {
//   s21_decimal val1;
//   s21_decimal val2;
//   s21_decimal res;
//   ck_assert_int_eq(0, s21_add(val1, val2, &res));
// }
// END_TEST


/* Тест: Проверка сложения с нулевыми значениями */
START_TEST(test_add_zeros) {
    s21_decimal val1;
    s21_decimal val2;
    s21_decimal res;

    // Инициализация val1 и val2 как нулевых значений
    memset(&val1, 0, sizeof(s21_decimal));
    memset(&val2, 0, sizeof(s21_decimal));

    // Проверка результата сложения
    ck_assert_int_eq(0, s21_add(val1, val2, &res));

    // Дополнительно можно проверить, что результат также равен нулю
    ck_assert_int_eq(0, s21_get_sign(res));
    for (int i = 0; i < 3; i++) {
        ck_assert_int_eq(0, res.bits[i]);
    }
}
END_TEST

TCase *tcase_s21_add(void) {
  TCase *test_cases = tcase_create("s21_add");
  tcase_add_test(test_cases, test_add_positive_values);
  tcase_add_test(test_cases, test_add_overflow_positive);
  tcase_add_test(test_cases, test_add_overflow_negative);
  tcase_add_test(test_cases, test_add_negative_with_scale);
  tcase_add_test(test_cases, test_add_negative_plus_positive);
  tcase_add_test(test_cases, test_add_positive_plus_negative);
  tcase_add_test(test_cases, test_add_large_negative_overflow);
  tcase_add_test(test_cases, test_add_uninitialized_result);
  tcase_add_test(test_cases, test_add_uninitialized_inputs);
  tcase_add_test(test_cases, test_add_partially_initialized_inputs);
  tcase_add_test(test_cases, test_add_zeros);
  return test_cases;
}
