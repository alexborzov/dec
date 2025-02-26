
// int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//     if (!result) return 1;

//     // Инициализация структуры результата
//     for (int x = 0; x < 4; x += 1) result->bits[x] = 0;

//     /* Проверка сложения на ноль */
//     if (s21_check_and_set_zero(value_1, value_2, result)) return 0;

//     /* Получаем знаки */
//     int sign_1 = s21_get_sign(value_1);
//     int sign_2 = s21_get_sign(value_2);

//     /* Выравниваем масштабы */
//     int scale = 0;
//     s21_align_scales(&value_1, &value_2, &scale);

//     /* Извлекаем мантиссы */
//     unsigned int mantissa1[3] = {0};
//     unsigned int mantissa2[3] = {0};
//     unsigned int big_result[3] = {0};

//     s21_extract_mantissa(value_1, mantissa1);
//     s21_extract_mantissa(value_2, mantissa2);

//     int overflow = 0;

//     if (sign_1 == sign_2) {
//       s21_add_mantissas(mantissa1, mantissa2, big_result, &overflow);
//       s21_set_sign(result, sign_1);
//     } else {
//       if (s21_is_greater_mantissa(mantissa1, mantissa2)) {
//         s21_sub_mantissas(mantissa1, mantissa2, big_result);
//         s21_set_sign(result, sign_1);
//       } else {
//         s21_sub_mantissas(mantissa2, mantissa1, big_result);
//         s21_set_sign(result, sign_2);
//       }
//     }

//     if (overflow) {
//       while (overflow && scale > 0) {
//         if (big_result[0] == 0 && big_result[1] == 0 && big_result[2] == 0) break;
//         unsigned long long mantissa[3] = {big_result[0], big_result[1],
//                                           big_result[2]};
//         s21_div_mantissa_by_10(mantissa, &overflow);
//         big_result[0] = (unsigned int)mantissa[0];
//         big_result[1] = (unsigned int)mantissa[1];
//         big_result[2] = (unsigned int)mantissa[2];
//         scale--;
//       }
//       if (overflow) {
//         return sign_1 ? 2 : 1;
//       }
//     }

//     /* Записываем результат */
//     s21_set_result(result, big_result, sign_1, scale);

//     return 0;
//   }

#include "../s21_decimal.h"

// int getSign(s21_decimal value) {
//     return (value.bits[3] >> 31) & 1; // Получение знака числа
// }

// void setSign(s21_decimal* value, int sign) {
//     if (sign) {
//         value->bits[3] |= (1 << 31); // Установка знака
//     } else {
//         value->bits[3] &= ~(1 << 31); // Сброс знака
//     }
// }

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
    // Обнуление результата
    for (int i = 0; i < 4; i++) {
        result->bits[i] = 0;
    }

    int sign_1 = s21_get_sign(value_1);
    int sign_2 = s21_get_sign(value_2);

    if (sign_1 == sign_2) {
        // Сложение двух положительных или двух отрицательных чисел
        unsigned long long carry = 0; // Перенос
        for (int i = 0; i < 3; i++) {
            unsigned long long sum = (unsigned long long)value_1.bits[i] + value_2.bits[i] + carry;
            result->bits[i] = (unsigned int)(sum & 0xFFFFFFFF);
            carry = sum >> 32; // Обновление переноса
        }
        // Установка знака результата
        s21_set_sign(result, sign_1);
        return 0; // Успешное выполнение
    } else {
        // Здесь можно реализовать логику для сложения с разными знаками (вычитание)
        // Для упрощения не реализовано
        return -1; // Ошибка: разные знаки
    }
}
