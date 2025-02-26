#include "../s21_decimal.h"

/* Проверка, является ли мантисса нулевой */
int s21_is_mantissa_zero(unsigned int *mantissa) {
  for (int i = 0; i < 6; i++) {
    if (mantissa[i] != 0) return 0;
  }
  return 1;
}
