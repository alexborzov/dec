#include "../s21_decimal.h"

/* Проверка на нули */
int s21_is_zero(s21_decimal value) {
  if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0) return 1;
  return 0;
}
