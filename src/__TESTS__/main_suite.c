#include <check.h>

// ------------------------------------------------------------------------------
//  ARITHMETICS IMPORT
// ------------------------------------------------------------------------------
#include "./arithmetic/s21_add_spec.c"
#include "./arithmetic/s21_div_spec.c"
#include "./arithmetic/s21_mul_spec.c"
#include "./arithmetic/s21_sub_spec.c"
// ------------------------------------------------------------------------------
//  COMPARISON IMPORT
// ------------------------------------------------------------------------------
#include "./comparison/s21_is_equal_spec.c"
#include "./comparison/s21_is_greater_or_equal_spec.c"
#include "./comparison/s21_is_greater_spec.c"
#include "./comparison/s21_is_less_or_equal_spec.c"
#include "./comparison/s21_is_less_spec.c"
#include "./comparison/s21_is_not_equal_spec.c"
// ------------------------------------------------------------------------------
//  CONVERTORS IMPORT
// ------------------------------------------------------------------------------
#include "./convertors/s21_from_decimal_to_float_spec.c"
#include "./convertors/s21_from_decimal_to_int_spec.c"
#include "./convertors/s21_from_float_to_decimal_spec.c"
#include "./convertors/s21_from_int_to_decimal_spec.c"

// ------------------------------------------------------------------------------
//  OTHER IMPORT
// ------------------------------------------------------------------------------
#include "./other/s21_floor_spec.c"
#include "./other/s21_negate_spec.c"
#include "./other/s21_round_spec.c"
#include "./other/s21_truncate_spec.c"

// ------------------------------------------------------------------------------
//  ARITHMETICS SUITE
// ------------------------------------------------------------------------------
Suite *arithmetic_suite(void) {
  Suite *arithm_suite = suite_create("arithmetic_suite");
  suite_add_tcase(arithm_suite, tcase_s21_add());
  suite_add_tcase(arithm_suite, tcase_s21_div());
  suite_add_tcase(arithm_suite, tcase_s21_mul());
  suite_add_tcase(arithm_suite, tcase_s21_sub());
  return arithm_suite;
}

// ------------------------------------------------------------------------------
//  COMPARISON SUITE
// ------------------------------------------------------------------------------
Suite *comparison_suite(void) {
  Suite *comprm_suite = suite_create("comparison_suite");
  suite_add_tcase(comprm_suite, tcase_s21_is_equal());
  suite_add_tcase(comprm_suite, tcase_s21_is_greater_or_equal());
  suite_add_tcase(comprm_suite, tcase_s21_is_greater());
  suite_add_tcase(comprm_suite, tcase_s21_is_less());
  suite_add_tcase(comprm_suite, tcase_s21_is_less_or_equal());
  suite_add_tcase(comprm_suite, tcase_s21_is_not_equal());
  return comprm_suite;
}

// ------------------------------------------------------------------------------
//  CONVERTORS SUITE
// ------------------------------------------------------------------------------
Suite *convertors_suite(void) {
  Suite *convert_suite = suite_create("convertors_suite");
  suite_add_tcase(convert_suite, tcase_s21_from_decimal_to_float());
  suite_add_tcase(convert_suite, tcase_s21_from_decimal_to_int());
  suite_add_tcase(convert_suite, tcase_s21_from_float_to_decimal());
  suite_add_tcase(convert_suite, tcase_s21_from_int_to_decimal());
  return convert_suite;
}

// ------------------------------------------------------------------------------
//  OTHER SUITE
// ------------------------------------------------------------------------------
Suite *other_suite(void) {
  Suite *othr_suite = suite_create("other_suite");
  suite_add_tcase(othr_suite, tcase_s21_truncate());
  suite_add_tcase(othr_suite, tcase_s21_floor());
  suite_add_tcase(othr_suite, tcase_s21_round());
  suite_add_tcase(othr_suite, tcase_s21_negate());
  return othr_suite;
}

int main(void) {
  int failed_count = 0;
  // ------------------------------------------------------------------------------
  //  ARITHMETICS RUNNER
  // ------------------------------------------------------------------------------
  Suite *arithm = arithmetic_suite();
  SRunner *runner_arithm = srunner_create(arithm);

  srunner_run_all(runner_arithm, CK_NORMAL);
  failed_count += srunner_ntests_failed(runner_arithm);
  srunner_free(runner_arithm);

  // ------------------------------------------------------------------------------
  //  COMPARISON RUNNER
  // ------------------------------------------------------------------------------
  Suite *comprm = comparison_suite();
  SRunner *runner_comprm = srunner_create(comprm);

  srunner_run_all(runner_comprm, CK_NORMAL);
  failed_count += srunner_ntests_failed(runner_comprm);
  srunner_free(runner_comprm);
  // ------------------------------------------------------------------------------
  //  CONVERTORS RUNNER
  // ------------------------------------------------------------------------------
  Suite *convert = convertors_suite();
  SRunner *runner_convert = srunner_create(convert);

  srunner_run_all(runner_convert, CK_NORMAL);
  failed_count += srunner_ntests_failed(runner_convert);
  srunner_free(runner_convert);
  // ------------------------------------------------------------------------------
  //  OTHER RUNNER
  // ------------------------------------------------------------------------------
  Suite *othr = other_suite();
  SRunner *runner_othr = srunner_create(othr);

  srunner_run_all(runner_othr, CK_NORMAL);
  failed_count += srunner_ntests_failed(runner_othr);
  srunner_free(runner_othr);

  return failed_count == 0 ? 0 : 1;
}
