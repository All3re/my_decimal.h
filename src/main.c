#include "test.h"

int main(void) {
  run_tests();
  return 0;
}
void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;
  if (counter_testcase > 1)
    counter_testcase++;
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

void run_tests(void) {
  Suite *list_cases[] = {suite_s21_negate(),
                         suite_s21_truncate(),
                         suite_s21_round(),
                         suite_s21_floor(),
                         suite_s21_add(),
                         suite_s21_sub(),
                         suite_s21_mul(),
                         suite_s21_div(),
                         srunner_add_comparsion_tests(),
                         s21_from_int_to_decimal_suite(),
                         s21_from_decimal_to_int_suite(),
                         s21_from_float_to_decimal_suite(),
                         s21_from_decimal_to_float_suite(),
                         NULL};

  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}
