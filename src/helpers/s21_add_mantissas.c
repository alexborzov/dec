#include "../s21_decimal.h"

/* Сложение мантисс */
void s21_add_mantissas(unsigned int *mantissa1, unsigned int *mantissa2,
                       unsigned int *result, int *overflow) {
  unsigned long long carry = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long sum =
        (unsigned long long)mantissa1[i] + mantissa2[i] + carry;
    result[i] = (unsigned int)(sum & 0xFFFFFFFF);
    carry = sum >> 32;
  }
  *overflow = carry != 0;
}
