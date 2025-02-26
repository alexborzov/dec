#include "../s21_decimal.h"

/* Выравнивание масштабов */
void s21_align_scales(s21_decimal *value_1, s21_decimal *value_2, int *scale) {
  int scale1 = s21_get_scale(*value_1);
  int scale2 = s21_get_scale(*value_2);
  *scale = (scale1 > scale2) ? scale1 : scale2;
  while (scale1 < *scale) {
    s21_multiply_mantissa_by_10(value_1->bits);
    scale1++;
  }
  while (scale2 < *scale) {
    s21_multiply_mantissa_by_10(value_2->bits);
    scale2++;
  }
}
