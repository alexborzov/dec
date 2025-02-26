#include "../s21_decimal.h"

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  if (s21_is_zero(a) && s21_is_zero(b)) return 1;
  return s21_compare(a, b) <= 0;
}
