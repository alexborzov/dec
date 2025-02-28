#include "../s21_decimal.h"
// ------------------------------------------------------------------------------
//  Устанавливает знак числа (bit = 1 — отрицательное, bit = 0 — положительное)
// ------------------------------------------------------------------------------
// s21_decimal *s21_set_sign(s21_decimal *value, int bit) {
//   value->bits[3] =
//       (bit) ? (value->bits[3] | (1u << 31)) : (value->bits[3] & ~(1u << 31));
//   return value;
// }

void s21_set_sign(s21_decimal* value, int sign) {
    if (sign) {
        value->bits[3] |= (1 << 31); // Установка знака
    } else {
        value->bits[3] &= ~(1 << 31); // Сброс знака
    }
}
