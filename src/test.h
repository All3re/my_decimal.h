#ifndef SRC_MATH_SUITECASES_H_
#define SRC_MATH_SUITECASES_H_

#include <check.h>
#include <math.h>

#include "arithm.h"

Suite *suite_s21_add(void);
Suite *suite_s21_sub(void);
Suite *suite_s21_mul(void);
Suite *suite_s21_div(void);

void run_tests(void);
void run_testcase(Suite *testcase);

#endif  // SRC_MATH_SUITECASES_H_