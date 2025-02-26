#include "../s21_decimal.h"

/* Деление двух чисел */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  /* Проверка на нулевой указатель */
  if (!result) return 1;

  /* Очистка результата */
  s21_clear_decimal(result);

  /* Проверка деления на ноль */
  if (s21_check_and_set_zero(value_1, value_2, result)) return 0;

  /* Получаем знаки и определяем знак результата */
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  int result_sign = sign_1 ^ sign_2;

  /* Выравниваем масштабы */
  int scale;
  s21_align_scales(&value_1, &value_2, &scale);

  /* Извлекаем мантиссы */
  unsigned int mantissa1[3];
  unsigned int mantissa2[3];
  s21_extract_mantissa(value_1, mantissa1);
  s21_extract_mantissa(value_2, mantissa2);
  unsigned int big_result[3] = {0};
  unsigned int remainder[3] = {0};

  /* Проверка деления на ноль мантисс */
  if (s21_is_mantissa_zero(mantissa2)) return 3;

  /* Выполняем деление мантисс */
  s21_div_mantissas(mantissa1, mantissa2, big_result, remainder);

  /* Проверяем остаток и увеличиваем масштаб при необходимости */
  int overflow = 0;
  while ((remainder[0] != 0 || remainder[1] != 0 || remainder[2] != 0) &&
         scale < 28) {
    s21_multiply_mantissa_by_10(big_result);
    s21_multiply_mantissa_by_10(remainder);
    s21_div_mantissas(remainder, mantissa2, big_result, remainder);
    scale++;
  }

  /* Проверяем переполнение */
  if (overflow) return result_sign ? 2 : 1;

  /* Записываем результат */
  s21_set_result(result, big_result, result_sign, scale);

  return 0;
}
