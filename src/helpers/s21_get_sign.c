#include "../s21_decimal.h"

/* Получение знака */
int s21_get_sign(s21_decimal value) { return (value.bits[3] >> 31) & 1; }
// (value.bits[3] >> 31) & 1
