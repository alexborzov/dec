#include "../s21_decimal.h"

/* Устанавливает бит в указанную позицию */
s21_decimal *s21_set_bit(s21_decimal *value, int pos, int bit) {
  if (pos / 32 < 4 && bit)
    value->bits[pos / 32] |= (1u << (pos % 32));
  else if (pos / 32 < 4 && !bit)
    value->bits[pos / 32] &= ~(1u << (pos % 32));
  return value;
}
