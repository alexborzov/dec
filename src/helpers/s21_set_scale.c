#include "../s21_decimal.h"
// ------------------------------------------------------------------------------
//  Устанавливает масштаб (количество знаков после запятой) для числа
// ------------------------------------------------------------------------------
s21_decimal *s21_set_scale(s21_decimal *value, int scale) {
  if (scale >= 0 && scale <= 28) {
    int sign = s21_get_sign(*value);
    value->bits[3] &= ~(0xFF << 16);
    value->bits[3] |= scale << 16;
    sign ? s21_set_sign(value, 1) : value;
  }
  return value;
}
