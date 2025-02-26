#include "../s21_decimal.h"

// /* Вычитание двух чисел */
// // int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
// {
// //   /*  Инвертируем знак второго числа и используем s21_add */
// //   s21_decimal neg_value_2 = value_2;
// //   s21_set_sign(&neg_value_2, !s21_get_sign(value_2));
// //   return s21_add(value_1, neg_value_2, result);
// // }

// /* Вычитание двух чисел */
// int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   /* Проверка на нулевой указатель */
//   if (!result) return 1;

//   // Очистка результата
//   s21_clear_decimal(result);

//   /* Проверка вычитания на ноль */
//   if (s21_check_and_set_zero(value_1, value_2, result)) return 0;

//   /* Получаем знаки */
//   int sign_1 = s21_get_sign(value_1);
//   int sign_2 = s21_get_sign(value_2);

//   /* Выравниваем масштабы */
//   int scale;
//   s21_align_scales(&value_1, &value_2, &scale);

//   /* Извлекаем мантиссы */
//   unsigned int mantissa1[3];
//   unsigned int mantissa2[3];
//   s21_extract_mantissa(value_1, mantissa1);
//   s21_extract_mantissa(value_2, mantissa2);
//   unsigned int big_result[3] = {0};

//   int overflow = 0;

//   /* Если знаки одинаковые, выполняем вычитание */
//   if (sign_1 == sign_2) {
//     if (s21_is_greater_mantissa(mantissa1, mantissa2)) {
//       s21_sub_mantissas(mantissa1, mantissa2, big_result);
//       s21_set_sign(result, sign_1);
//     } else {
//       s21_sub_mantissas(mantissa2, mantissa1, big_result);
//       s21_set_sign(result, sign_2);
//     }
//   } else {
//     // Если знаки разные, выполняем сложение
//     s21_add_mantissas(mantissa1, mantissa2, big_result, &overflow);
//     s21_set_sign(result, sign_1);  // знак остается от первого числа
//   }

//   /* Проверка переполнения */
//   if (overflow) {
//     while (overflow && scale > 0) {
//       if (big_result[0] == 0 && big_result[1] == 0 && big_result[2] == 0)
//       break; unsigned long long mantissa[3] = {big_result[0], big_result[1],
//                                         big_result[2]};
//       s21_div_mantissa_by_10(mantissa, &overflow);
//       big_result[0] = (unsigned int)mantissa[0];
//       big_result[1] = (unsigned int)mantissa[1];
//       big_result[2] = (unsigned int)mantissa[2];
//       scale--;
//     }
//     if (overflow) {
//       return sign_1 ? 2 : 1;  // Переполнение
//     }
//   }

//   /* Записываем результат */
//   s21_set_result(result, big_result, s21_get_sign(value_1), scale);

//   return 0;
// }

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  /* Проверка на нулевой указатель */
  if (!result) return 1;

  // Очистка результата
  s21_clear_decimal(result);

  /* Проверка вычитания на ноль */
  if (s21_check_and_set_zero(value_1, value_2, result)) return 0;

  /* Получаем знаки */
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);

  /* Выравниваем масштабы */
  int scale;
  s21_align_scales(&value_1, &value_2, &scale);

  /* Извлекаем мантиссы */
  unsigned int mantissa1[3];
  unsigned int mantissa2[3];
  s21_extract_mantissa(value_1, mantissa1);
  s21_extract_mantissa(value_2, mantissa2);
  unsigned int big_result[3] = {0};

  int overflow = 0;

  /* Если знаки одинаковые, выполняем вычитание */
  if (sign_1 == sign_2) {
    if (s21_is_greater_mantissa(mantissa1, mantissa2)) {
      s21_sub_mantissas(mantissa1, mantissa2, big_result);
      s21_set_sign(result, sign_1);  // сохраняем знак первого числа
    } else {
      s21_sub_mantissas(mantissa2, mantissa1, big_result);
      s21_set_sign(result, sign_2);  // сохраняем знак второго числа
    }
  } else {
    // Если знаки разные, выполняем сложение
    s21_add_mantissas(mantissa1, mantissa2, big_result, &overflow);
    s21_set_sign(result, sign_1);  // знак остается от первого числа
  }

  /* Проверка переполнения */
  if (overflow) {
    while (overflow && scale > 0) {
      if (big_result[0] == 0 && big_result[1] == 0 && big_result[2] == 0) break;
      unsigned long long mantissa[3] = {big_result[0], big_result[1],
                                        big_result[2]};
      s21_div_mantissa_by_10(mantissa, &overflow);
      big_result[0] = (unsigned int)mantissa[0];
      big_result[1] = (unsigned int)mantissa[1];
      big_result[2] = (unsigned int)mantissa[2];
      scale--;
    }
    if (overflow) {
      return sign_1 ? 2 : 1;  // Переполнение
    }
  }

  /* Записываем результат */
  s21_set_result(result, big_result, s21_get_sign(value_1), scale);

  return 0;
}
