/* Объединенная проверка для мантиссы и проверки переполнения в одном */
int s21_combined_check_overflow(unsigned int *mantissa) {
  /* Проверка переполнения, если мантисса больше чем 96 бит */
  if (mantissa[5] != 0 || mantissa[4] != 0 || mantissa[3] != 0) {
    return 1;
  }

  /* Дополнительная проверка старшего бита мантиссы */
  if (mantissa[2] & 0x80000000) {
    return 1;
  }

  /* Проверка на максимальное значение 96 бит */
  if (mantissa[2] > 0x7FFFFFFF) {
    return 1;
  }

  return 0;
}
