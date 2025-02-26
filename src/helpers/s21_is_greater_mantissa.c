#include "../s21_decimal.h"

/* Проверка больше ли одна мантисса другой */
int s21_is_greater_mantissa(unsigned int *mantissa1, unsigned int *mantissa2) {
  for (int i = 2; i >= 0; i--) {
    if (mantissa1[i] != mantissa2[i]) {
      return mantissa1[i] > mantissa2[i];
    }
  }
  return 0;
}
