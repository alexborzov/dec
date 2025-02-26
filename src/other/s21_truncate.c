#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return 1;
  }

  s21_clear_decimal(result);

  if (s21_is_zero(value)) {
    s21_set_sign(result, s21_get_sign(value));
    s21_set_scale(result, 0);
    return 0;
  }

  int sign = s21_get_sign(value);
  int scale = s21_get_scale(value);

  if (scale < 0) {
    return 2;
  }

  if (scale == 0) {
    *result = value;
    return 0;
  }

  unsigned int mantissa[3] = {value.bits[0], value.bits[1], value.bits[2]};

  int overflow = 0;
  for (int i = 0; i < scale && !overflow; i++) {
    unsigned long long temp_mantissa[3] = {(unsigned long long)mantissa[0],
                                           (unsigned long long)mantissa[1],
                                           (unsigned long long)mantissa[2]};
    s21_div_mantissa_by_10_ll(temp_mantissa);
    mantissa[0] = (unsigned int)temp_mantissa[0];
    mantissa[1] = (unsigned int)temp_mantissa[1];
    mantissa[2] = (unsigned int)temp_mantissa[2];

    if (mantissa[0] == 0 && mantissa[1] == 0 && mantissa[2] == 0) {
      overflow = 1;
    }
  }

  if (mantissa[0] == 0 && mantissa[1] == 0 && mantissa[2] == 0) {
    s21_set_sign(result, sign);
    s21_set_scale(result, 0);
    return 0;
  }

  result->bits[0] = mantissa[0];
  result->bits[1] = mantissa[1];
  result->bits[2] = mantissa[2];
  s21_set_scale(result, 0);
  s21_set_sign(result, sign);

  return 0;
}
