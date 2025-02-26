#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return 1;
  }

  s21_clear_decimal(result);

  *result = value;

  int sign = s21_get_sign(value);

  int new_sign = sign ? 0 : 1;
  s21_set_sign(result, new_sign);

  return 0;
}
