#include "../s21_decimal.h"

/* Извлечение мантисс и инициализация результата */
void s21_extract_mantissas_and_initialize(
    s21_decimal value_1, s21_decimal value_2, unsigned int mantissa1[3],
    unsigned int mantissa2[3], unsigned int big_result[6], int *overflow) {
  mantissa1[0] = value_1.bits[0];
  mantissa1[1] = value_1.bits[1];
  mantissa1[2] = value_1.bits[2];

  mantissa2[0] = value_2.bits[0];
  mantissa2[1] = value_2.bits[1];
  mantissa2[2] = value_2.bits[2];

  for (int i = 0; i < 6; i++) {
    big_result[i] = 0;
  }

  *overflow = 0;
}
