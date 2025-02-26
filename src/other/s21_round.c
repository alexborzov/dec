#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
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

  s21_decimal truncated;
  s21_clear_decimal(&truncated);
  int truncate_result = s21_truncate(value, &truncated);
  if (truncate_result != 0) {
    return truncate_result;
  }

  s21_decimal fraction;
  s21_clear_decimal(&fraction);
  int sub_result = s21_sub(value, truncated, &fraction);
  if (sub_result != 0) {
    return sub_result;
  }

  s21_set_scale(&fraction, scale);

  s21_decimal half = {{5, 0, 0, 0}};
  s21_set_scale(&half, 1);
  s21_set_sign(&half, 0);

  int need_round_up = 0;
  if (sign) {
    if (s21_is_greater_or_equal(fraction, half)) {
      need_round_up = 1;
    }
  } else {
    if (s21_is_greater_or_equal(fraction, half)) {
      need_round_up = 1;
    }
  }

  if (need_round_up) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_set_scale(&one, 0);
    s21_set_sign(&one, 0);

    if (sign) {
      sub_result = s21_sub(truncated, one, result);
    } else {
      sub_result = s21_add(truncated, one, result);
    }
    if (sub_result != 0) {
      return sub_result;
    }
  } else {
    *result = truncated;
  }

  s21_set_sign(result, sign);
  return 0;
}
