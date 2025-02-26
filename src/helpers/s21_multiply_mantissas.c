#include "../s21_decimal.h"

/* Перемножение мантисс */
void s21_multiply_mantissas(unsigned int *mantissa1, unsigned int *mantissa2,
                            unsigned int *result, int *overflow) {
  *overflow = 0;
  unsigned long long temp_result[6] = {0};

  /* Перемножаем мантиссы с учетом переноса */
  for (int i = 0; i < 3; i++) {
    unsigned long long carry = 0;
    for (int j = 0; j < 3; j++) {
      unsigned long long product =
          (unsigned long long)mantissa1[i] * mantissa2[j];
      product += temp_result[i + j] + carry;
      temp_result[i + j] = product & 0xFFFFFFFF;
      carry = product >> 32;
    }
    /* Добавляем перенос в старшие разряды */
    temp_result[i + 3] += carry;
    if (carry > 0xFFFFFFFF) *overflow = 1;
  }

  /* Проверка переполнения */
  for (int i = 0; i < 6; i++) {
    /* Приводим к 32-битным значениям */
    result[i] = (unsigned int)temp_result[i];
  }

  /* Если старшие разряды не равны нулю, это означает переполнение */
  for (int i = 5; i >= 3; i--) {
    if (result[i] != 0) {
      *overflow = 1;
      break;
    }
  }
  /* Если переполнение обнаружено в процессе, возвращаем 1 (ошибка) */
  if (*overflow) return;
}
