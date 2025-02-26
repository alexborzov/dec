#include "../s21_decimal.h"

/* Проверка, является ли мантисса слишком большой для представления в
 * s21_decimal */
int s21_is_mantissa_too_large(unsigned int *mantissa, int scale,
                              int initial_overflow) {
  if (s21_combined_check_overflow(mantissa)) return 1;
  if (initial_overflow) {
    if (scale < 0) return 1;
    if (scale > 28) return 1;
    if (s21_is_mantissa_zero(mantissa)) return 1;
  }
  return 0;
}
