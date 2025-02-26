#include "../s21_decimal.h"

/* Нормализация десятичного числа */
int s21_normalize(s21_decimal *a, s21_decimal *b) {
  if (s21_is_zero(*a) && s21_is_zero(*b)) {
    s21_set_scale(a, 0);
    s21_set_scale(b, 0);
    return 0;
  }

  int scale_a = s21_get_scale(*a);
  int scale_b = s21_get_scale(*b);

  if (scale_a == scale_b) return 0;

  s21_decimal *smaller_scale = scale_a > scale_b ? b : a;
  int diff = abs(scale_a - scale_b);

  while (diff > 0) {
    s21_decimal temp = *smaller_scale;
    if (s21_multiply_by_10(&temp) != 0) {
      return 1;
    }
    *smaller_scale = temp;
    s21_set_scale(smaller_scale, s21_get_scale(*smaller_scale) + 1);
    diff--;
  }

  if (s21_get_scale(*a) != s21_get_scale(*b)) {
    return 1;
  }
  return 0;
}
