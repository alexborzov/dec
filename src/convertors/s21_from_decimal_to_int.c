#include "../s21_decimal.h"

/* Преобразование decimal в int */
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst) return s21_flag_error;

  /*  Инициализируем результат */
  *dst = 0;
  int sign = s21_get_sign(src);
  int scale = s21_get_scale(src);

  /* Проверка на слишком большой масштаб или ненулевые старшие части */
  if ((scale > 28) || (src.bits[1] || src.bits[2])) {
    return s21_flag_error;
  }

  // Извлечение значения из младшего бита
  unsigned long long value = src.bits[0];

  /* Делим на 10^scale для получения целого значения */
  for (int i = 0; i < scale; i++) {
    value /= 10;
  }

  /* Проверка на переполнение */
  if (value > INT_MAX) {
    return s21_flag_error;
  }

  /* Применяем знак */
  *dst = (sign == 1) ? -(int)value : (int)value;
  return s21_flag_ok;
}
