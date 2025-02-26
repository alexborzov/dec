#include "../s21_decimal.h"

/* Вычитание мантисс */
void s21_sub_mantissas(unsigned int *mantissa1, unsigned int *mantissa2,
                       unsigned int *result) {
  unsigned long long borrow = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long diff =
        (unsigned long long)mantissa1[i] - mantissa2[i] - borrow;
    result[i] = (unsigned int)(diff & 0xFFFFFFFF);
    borrow = (diff >> 32) & 1;
  }
}
