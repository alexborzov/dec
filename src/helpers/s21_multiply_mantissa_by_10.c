#include "../s21_decimal.h"

/* Умножение мантиссы на 10 */
void s21_multiply_mantissa_by_10(unsigned int *mantissa) {
  unsigned long long temp = 0;
  unsigned long long carry = 0;

  /* Умножаем каждый блок мантиссы на 10 с учетом переноса */
  for (int i = 0; i < 3; i++) {
    temp = (unsigned long long)mantissa[i] * 10 + carry;
    /* Нижние 32 бита */
    mantissa[i] = (unsigned int)(temp & 0xFFFFFFFF);
    /* Перенос в следующий разряд */
    carry = temp >> 32;
  }
}
