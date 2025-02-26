#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return 1;
  }

  s21_clear_decimal(result);

  int sign = s21_get_sign(value);
  int scale = s21_get_scale(value);

  if (scale == 0) {
    *result = value;
    return 0;
  }

  int truncate_result = s21_truncate(value, result);
  if (truncate_result != 0) {
    return truncate_result;
  }

  if (sign) {
    s21_decimal truncated = *result;
    s21_decimal temp = value;
    int has_fractional_part = 0;

    s21_set_scale(&temp, 0);
    if (s21_compare(temp, truncated) != 0) {
      has_fractional_part = 1;
    }

    if (has_fractional_part) {
      s21_decimal one = {{1, 0, 0, 0}};
      s21_set_scale(&one, 0);
      s21_set_sign(&one, 0);

      int sub_result = s21_sub(*result, one, result);
      if (sub_result != 0) {
        return sub_result;
      }
    }
  }

  s21_set_sign(result, sign);
  return 0;
}
