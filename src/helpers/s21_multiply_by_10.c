#include "../s21_decimal.h"

/* Умножение на 10 */
int s21_multiply_by_10(s21_decimal *value) {
  unsigned long long carry = 0;
  unsigned long long temp[3] = {value->bits[0], value->bits[1], value->bits[2]};

  for (int i = 0; i < 3; i++) {
    unsigned long long result = temp[i] * 10ULL + carry;
    value->bits[i] = (unsigned int)(result & 0xFFFFFFFF);
    carry = result >> 32;
  }

  if (carry != 0 || value->bits[2] > 0xFFFFFFFF) {
    return 1;
  }
  return 0;
}
