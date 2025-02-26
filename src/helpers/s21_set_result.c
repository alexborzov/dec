#include "../s21_decimal.h"

/* Установка знака и масштаба результата */
void s21_set_result(s21_decimal *result, unsigned int *mantissa, int sign,
                    int scale) {
  result->bits[0] = mantissa[0];
  result->bits[1] = mantissa[1];
  result->bits[2] = mantissa[2];
  s21_set_sign(result, sign);
  s21_set_scale(result, scale);
}
