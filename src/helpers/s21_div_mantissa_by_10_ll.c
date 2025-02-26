#include "../s21_decimal.h"

/* Деление мантиссы на 10 */
void s21_div_mantissa_by_10_ll(unsigned long long *mantissa) {
  unsigned long long remainder = 0;
  for (int i = 2; i >= 0; i--) {
    unsigned long long temp = (remainder << 32) | mantissa[i];
    mantissa[i] = temp / 10;
    remainder = temp % 10;
  }
}
