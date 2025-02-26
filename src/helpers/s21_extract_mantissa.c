#include "../s21_decimal.h"

/* Извлечение мантиссы из s21_decimal */
void s21_extract_mantissa(s21_decimal value, unsigned int *mantissa) {
  mantissa[0] = value.bits[0];
  mantissa[1] = value.bits[1];
  mantissa[2] = value.bits[2];
}
