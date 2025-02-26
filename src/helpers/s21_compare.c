#include "../s21_decimal.h"

int s21_compare(s21_decimal a, s21_decimal b) {
  // Если оба нули, но знаки разные, то числа не равны
  if (s21_is_zero(a) && s21_is_zero(b) && (s21_get_sign(a) != s21_get_sign(b)))
    return 1;

  int sign_a = s21_get_sign(a);
  int sign_b = s21_get_sign(b);

  if (sign_a != sign_b) {
    if (s21_is_zero(a)) return sign_b ? 1 : -1;
    if (s21_is_zero(b)) return sign_a ? -1 : 1;
    return sign_a ? -1 : 1;
  }

  /* Проверка знаков до всех остальных сравнений */
  if (sign_a && !sign_b) return -1;
  if (!sign_a && sign_b) return 1;

  if (s21_is_zero(a) && s21_is_zero(b)) return 0;

  s21_decimal temp_a = a;
  s21_decimal temp_b = b;

  if (s21_normalize(&temp_a, &temp_b) != 0) return sign_a ? -1 : 1;

  int result = 0;
  for (int i = 2; i >= 0; i--) {
    if (temp_a.bits[i] != temp_b.bits[i]) {
      result = temp_a.bits[i] > temp_b.bits[i] ? 1 : -1;
      break;
    }
  }

  return sign_a ? -result : result;
}
