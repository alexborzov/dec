#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
  if (!dst) return s21_flag_error;

  double tmp = 0;
  int exp = 0;

  /* Извлечение битов и преобразование в десятичное значение */
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(src, i) != 0) {
      tmp += pow(2, i);
    }
  }

  /* Получение масштаба */
  exp = s21_get_scale(src);
  if (exp > 0) {
    /* Делим на 10^scale */
    tmp /= pow(10, exp);
  }

  /*  Применение знака */
  if (s21_get_sign(src)) {
    tmp *= -1;
  }

  /* Проверка на переполнение */
  if (tmp < -FLT_MAX || tmp > FLT_MAX) {
    return s21_flag_error;
  }

  *dst = (float)tmp;
  return s21_flag_ok;
}
