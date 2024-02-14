#ifndef TEST_H
#define TEST_H

#include <check.h>
#include <math.h>

#include "arithm.h"
#include "converters.h"
#include "s21_decimal.h"

Suite *suite_s21_negate(void);
Suite *suite_s21_truncate(void);
Suite *suite_s21_round(void);
Suite *suite_s21_floor(void);
Suite *suite_s21_add(void);
Suite *suite_s21_sub(void);
Suite *suite_s21_mul(void);
Suite *suite_s21_div(void);
Suite *srunner_add_comparsion_tests(void);
Suite *s21_from_decimal_to_float_suite(void);
Suite *s21_from_float_to_decimal_suite(void);
Suite *s21_from_decimal_to_int_suite(void);
Suite *s21_from_int_to_decimal_suite(void);
void run_tests(void);
void run_testcase(Suite *testcase);

#endif
