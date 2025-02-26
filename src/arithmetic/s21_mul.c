#include "../s21_decimal.h"

/* Произведение двух чисел */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  /* Проверка на нулевой указатель */
  if (!result) return 1;

  /* Очистка результата */
  s21_clear_decimal(result);

  /* Проверка умножения на ноль */
  if (s21_check_and_set_zero(value_1, value_2, result)) return 0;

  /* Получаем знаки и определяем масштаб */
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  int scale = s21_get_scale(value_1) + s21_get_scale(value_2);

  /* Извлекаем мантиссы и инициализируем big_result и overflow */
  unsigned int mantissa1[3], mantissa2[3], big_result[6] = {0};
  int overflow = 0;
  s21_extract_mantissas_and_initialize(value_1, value_2, mantissa1, mantissa2,
                                       big_result, &overflow);

  /* Выполняем умножение мантисс */
  s21_multiply_mantissas(mantissa1, mantissa2, big_result, &overflow);

  /* Проверка на переполнение после умножения */
  if (overflow || s21_combined_check_overflow(big_result)) return 1;

  int initial_overflow = s21_combined_check_overflow(big_result);

  /* Если переполнение, корректируем масштаб */
  while (s21_combined_check_overflow(big_result) && scale < 28) {
    unsigned long long temp_mantissa[6] = {0};
    for (int i = 0; i < 6; i++) temp_mantissa[i] = big_result[i];
    s21_div_mantissa_by_10(temp_mantissa, &overflow);
    for (int i = 0; i < 6; i++) big_result[i] = (unsigned int)temp_mantissa[i];
    scale++;
  }

  /* Еще раз проверяем переполнение */
  while (s21_combined_check_overflow(big_result) && scale >= 28) {
    unsigned long long temp_mantissa[6] = {0};
    for (int i = 0; i < 6; i++) temp_mantissa[i] = big_result[i];
    s21_div_mantissa_by_10(temp_mantissa, &overflow);
    for (int i = 0; i < 6; i++) big_result[i] = (unsigned int)temp_mantissa[i];
    scale--;
  }

  /* Проверка на переполнение после масштабирования */
  if (initial_overflow &&
      s21_is_mantissa_too_large(big_result, scale, initial_overflow))
    return (sign_1 ^ sign_2) ? 2 : 1;

  /* Записываем результат */
  s21_set_result(result, big_result, sign_1 ^ sign_2, scale);

  return 0;
}
