#include "../s21_decimal.h"

/* Преобразование float в decimal */
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_result_flag flag = s21_flag_ok;

  if (!dst) return s21_flag_error;

  if (isnan(src)) return s21_flag_error;

  /* Обработка нулевого значения */
  if (src == 0.0f) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    return flag;
  }

  /* Проверка на переполнение или бесконечность */
  if (isinf(src) || fabs(src) > DECIMAL_MAX) {
    return s21_flag_error;
  }

  /* Учет знака */
  int sign = (src < 0) ? 1 : 0;
  src = fabs(src);

  /* Определение масштаба */
  int scale = 0;
  while (src != floor(src) && scale < 28) {
    src *= 10;
    scale++;
  }

  /* Преобразование во множество бит */
  unsigned int integer_value = (unsigned int)src;
  if (integer_value > INT_MAX) {
    return s21_flag_error;
  }

  dst->bits[0] = integer_value;
  dst->bits[1] = 0;
  dst->bits[2] = 0;

  /* Установка масштаба и знака */
  dst->bits[3] = (scale << 16) | (sign << 31);

  return flag;
}
