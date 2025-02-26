#include "../s21_decimal.h"

/* Проверяет, являются ли оба числа нулями, и устанавливает результат в 0, если
 это так Возвращает 1, если оба числа нули, иначе 0 */
int s21_check_and_set_zero(s21_decimal value_1, s21_decimal value_2,
                           s21_decimal *result) {
  if (s21_is_zero(value_1) && s21_is_zero(value_2)) {
    s21_clear_decimal(result);
    s21_set_sign(result, 0);
    s21_set_scale(result, 0);
    return 1;
  }
  return 0;
}
