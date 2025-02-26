#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  /* 96 бит данных + 32 бита служебной информации */
  unsigned int bits[4];
} s21_decimal;

typedef enum s21_result_conversation {
  s21_flag_ok = 0,
  s21_flag_error = 1
} s21_result_flag;

#define DECIMAL_MAX 79228162514264337593543950335.0
#define DECIMAL_MIN 1e-28
#define EPSILON 1e-6

// ------------------------------------------------------------------------------
//  HEADERS
// ------------------------------------------------------------------------------
#include "./__HEADERS__/s21_arithmetics.h"
#include "./__HEADERS__/s21_comparison.h"
#include "./__HEADERS__/s21_convertors.h"
#include "./__HEADERS__/s21_helpers.h"
#include "./__HEADERS__/s21_other.h"

#endif  //  SRC_S21_DECIMAL_H_
