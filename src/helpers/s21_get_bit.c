#include "../s21_decimal.h"

/* Получает бит в указанной позиции */
int s21_get_bit(s21_decimal value, int bit) {
  return !!(value.bits[bit / 32] & (1u << (bit % 32)));
}
