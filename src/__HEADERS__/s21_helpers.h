#ifndef SRC_S21_HELPERS_H_
#define SRC_S21_HELPERS_H_

// ------------------------------------------------------------------------------
//  Helpers for arithmetic shared
// ------------------------------------------------------------------------------
void s21_clear_decimal(s21_decimal *decimal);
int s21_is_mantissa_zero(unsigned int *mantissa);
int s21_check_and_set_zero(s21_decimal value_1, s21_decimal value_2,
                           s21_decimal *result);
int s21_is_mantissa_too_large(unsigned int *mantissa, int scale,
                              int initial_overflow);
int s21_combined_check_overflow(unsigned int *mantissa);
void s21_set_result(s21_decimal *result, unsigned int *mantissa, int sign,
                    int scale);
void s21_align_scales(s21_decimal *value_1, s21_decimal *value_2, int *scale);
void s21_extract_mantissas_and_initialize(
    s21_decimal value_1, s21_decimal value_2, unsigned int mantissa1[3],
    unsigned int mantissa2[3], unsigned int big_result[6], int *overflow);
void s21_extract_mantissa(s21_decimal value, unsigned int *mantissa);
int s21_is_greater_mantissa(unsigned int *mantissa1, unsigned int *mantissa2);
// ------------------------------------------------------------------------------
//  Helpers for arithmetic [s21_mul]
// ------------------------------------------------------------------------------
void s21_multiply_mantissas(unsigned int *mantissa1, unsigned int *mantissa2,
                            unsigned int *result, int *overflow);
void s21_multiply_mantissa_by_10(unsigned int *mantissa);
int s21_multiply_by_10(s21_decimal *value);
// ------------------------------------------------------------------------------
//  Helpers for arithmetic [s21_div]
// ------------------------------------------------------------------------------
void s21_div_mantissas(unsigned int *mantissa1, unsigned int *mantissa2,
                       unsigned int *result, unsigned int *remainder);
void s21_div_mantissa_by_10(unsigned long long *mantissa, int *overflow);
// ------------------------------------------------------------------------------
//  Helpers for arithmetic (s21_add)
// ------------------------------------------------------------------------------
void s21_add_mantissas(unsigned int *mantissa1, unsigned int *mantissa2,
                       unsigned int *result, int *overflow);
// ------------------------------------------------------------------------------
//  Helpers for arithmetic (s21_sub)
// ------------------------------------------------------------------------------
void s21_sub_mantissas(unsigned int *mantissa1, unsigned int *mantissa2,
                       unsigned int *result);
// ------------------------------------------------------------------------------
//  Helpers for comparison
// ------------------------------------------------------------------------------
int s21_compare(s21_decimal a, s21_decimal b);
int s21_normalize(s21_decimal *a, s21_decimal *b);
// ------------------------------------------------------------------------------
//  Helpers for other
// ------------------------------------------------------------------------------
void s21_div_mantissa_by_10_ll(unsigned long long *mantissa);
// ------------------------------------------------------------------------------
//  Shared for s21_decimal
// ------------------------------------------------------------------------------
int s21_get_sign(s21_decimal value);
// s21_decimal *s21_set_sign(s21_decimal *value, int bit);
void s21_set_sign(s21_decimal* value, int sign);
s21_decimal *s21_set_scale(s21_decimal *value, int scale);
int s21_get_scale(s21_decimal value);
int s21_shift_left(s21_decimal *value, int shift);
int s21_get_bit(s21_decimal value, int bit);
s21_decimal *s21_set_bit(s21_decimal *value, int pos, int bit);
int s21_is_zero(s21_decimal value);

#endif  //  SRC_S21_HELPERS_H_
