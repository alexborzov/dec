#include "../s21_decimal.h"

/* Функция для очистки результата (устанавливает все биты в 0) */
void s21_clear_decimal(s21_decimal *value) {
  for (int i = 0; i < 3; i++) {
    /* Обнуляем мантиссу */
    value->bits[i] = 0;
  }
  /*  Очищаем бит знака */
  value->bits[3] &= ~(1 << 31);
}
