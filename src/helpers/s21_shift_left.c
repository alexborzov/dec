#include "../s21_decimal.h"

/* Сдвиг влево */
int s21_shift_left(s21_decimal *value, int shift) {
  if (shift <= 0) return 0;

  unsigned int carry = 0;
  unsigned int new_carry;

  for (int i = 0; i < shift; i++) {
    new_carry = value->bits[2] >> 31;
    value->bits[2] = (value->bits[2] << 1) | (value->bits[1] >> 31);
    value->bits[1] = (value->bits[1] << 1) | (value->bits[0] >> 31);
    value->bits[0] = value->bits[0] << 1;
    carry = new_carry;
  }

  return carry;
}
