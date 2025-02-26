#include "../s21_decimal.h"

/* Деление мантисс */
void s21_div_mantissas(unsigned int *mantissa1, unsigned int *mantissa2,
                       unsigned int *result, unsigned int *remainder) {
  unsigned long long dividend = 0;
  for (int i = 2; i >= 0; i--) {
    dividend = (dividend << 32) | mantissa1[i];
    result[i] = (unsigned int)(dividend / mantissa2[0]);
    remainder[i] = (unsigned int)(dividend % mantissa2[0]);
  }
}
