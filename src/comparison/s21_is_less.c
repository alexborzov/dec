#include "../s21_decimal.h"

int s21_is_less(s21_decimal a, s21_decimal b) {
  if (s21_is_zero(a) && s21_is_zero(b)) return 0;
  return s21_compare(a, b) < 0;
}
