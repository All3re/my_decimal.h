#include "test.h"

START_TEST(negate_1_fail) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_negate(decimal, NULL);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(negate_2_fail) {
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(negate_3_fail) {
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(negate_4_fail) {
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(negate_5_fail) {
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(negate_6_fail) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_negate_ok1) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result;
  int code = s21_negate(decimal, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_negate_ok2) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  s21_decimal result;
  int code = s21_negate(decimal, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_negate_ok3) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  s21_decimal result;
  int code = s21_negate(decimal, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

Suite *suite_s21_negate(void) {
  Suite *s1;
  TCase *tc1;
  s1 = suite_create("s21_negate");

  tc1 = tcase_create("case_negate");

  tcase_add_test(tc1, negate_1_fail);
  tcase_add_test(tc1, negate_2_fail);
  tcase_add_test(tc1, negate_3_fail);
  tcase_add_test(tc1, negate_4_fail);
  tcase_add_test(tc1, negate_5_fail);
  tcase_add_test(tc1, negate_6_fail);
  tcase_add_test(tc1, test_negate_ok1);
  tcase_add_test(tc1, test_negate_ok2);
  tcase_add_test(tc1, test_negate_ok3);

  suite_add_tcase(s1, tc1);
  return s1;
}

START_TEST(truncate_1_fail) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_truncate(decimal, NULL);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(truncate_2_fail) {
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(truncate_3_fail) {
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(truncate_4_fail) {
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(truncate_5_fail) {
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(truncate_6_fail) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_truncate_ok1) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  s21_decimal decimal_check = {
      {0x99999999, 0x99999999, 0x19999999, 0x80000000}};

  s21_decimal result;
  int code = s21_truncate(decimal, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_truncate_ok2) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};

  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

  s21_decimal result;
  int code = s21_truncate(decimal, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

Suite *suite_s21_truncate(void) {
  Suite *s2;
  TCase *tc2;
  s2 = suite_create("s21_truncate");
  tc2 = tcase_create("case_truncate");

  tcase_add_test(tc2, truncate_1_fail);
  tcase_add_test(tc2, truncate_2_fail);
  tcase_add_test(tc2, truncate_3_fail);
  tcase_add_test(tc2, truncate_4_fail);
  tcase_add_test(tc2, truncate_5_fail);
  tcase_add_test(tc2, truncate_6_fail);
  tcase_add_test(tc2, test_truncate_ok1);
  tcase_add_test(tc2, test_truncate_ok2);

  suite_add_tcase(s2, tc2);
  return s2;
}

START_TEST(round_1_fail) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_round(decimal, NULL);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(round_2_fail) {
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(round_3_fail) {
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(round_4_fail) {
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(round_5_fail) {
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(round_6_fail) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_round_ok1) {
  // -79228162514264337.593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
  // -79228162514264338
  s21_decimal decimal_check = {{0x12DEA112, 0x1197998, 0x0, 0x80000000}};

  s21_decimal result;
  int code = s21_round(decimal, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok2) {
  // 792281625142643.37593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // 792281625142643
  s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x0}};

  s21_decimal result;
  int code = s21_round(decimal, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_round_ok3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395034
  s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  s21_decimal result;
  int code = s21_round(decimal, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

Suite *suite_s21_round(void) {
  Suite *s3;
  TCase *tc3;
  s3 = suite_create("s21_round");
  tc3 = tcase_create("case_round");

  tcase_add_test(tc3, round_1_fail);
  tcase_add_test(tc3, round_2_fail);
  tcase_add_test(tc3, round_3_fail);
  tcase_add_test(tc3, round_4_fail);
  tcase_add_test(tc3, round_5_fail);
  tcase_add_test(tc3, round_6_fail);
  tcase_add_test(tc3, test_round_ok1);
  tcase_add_test(tc3, test_round_ok2);
  tcase_add_test(tc3, test_round_ok3);

  suite_add_tcase(s3, tc3);
  return s3;
}

START_TEST(floor_1_fail) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_floor(decimal, NULL);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(floor_2_fail) {
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(floor_3_fail) {
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(floor_4_fail) {
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(floor_5_fail) {
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(floor_6_fail) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;

  int code = s21_floor(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_floor_ok1) {
  // -5281877500950955.8392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};
  // -5281877500950956
  s21_decimal decimal_check = {{0xF030F9AC, 0x12C3D6, 0x0, 0x80000000}};

  s21_decimal result;
  int code = s21_floor(decimal, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}
END_TEST
START_TEST(test_floor_ok2) {
  // -5.2818775009509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
  // -6
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

  s21_decimal result;
  int code = s21_floor(decimal, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}
END_TEST
START_TEST(test_floor_ok3) {
  // 52818774997211729016086244010
  s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};
  // 52818774997211729016086244010
  s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};

  s21_decimal result;
  int code = s21_floor(decimal, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(test_floor_ok4) {
  // -0.00000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800E0000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  s21_decimal result;
  int code = s21_floor(decimal, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(decimal_add_1) {
  s21_decimal x = {
      {4294967295, 4294967295, 0, 0b00000000000000000000000000000000}};
  s21_decimal y = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "0 0 1 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_add_2) {
  s21_decimal x = {{20, 1, 0, 0b10000000000000000000000000000000}};
  s21_decimal y = {{21, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "4294967295 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_add_3) {
  s21_decimal x = {{20, 1, 0, 0b10000000000000000000000000000000}};
  s21_decimal y = {{21, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "41 1 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_add_4) {
  s21_decimal x = {{20, 1, 0, 0b00000000000000000000000000000000}};
  s21_decimal y = {{21, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "4294967295 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_add_5) {
  s21_decimal x = {{20, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal y = {{21, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_add_6) {
  s21_decimal x = {{25, 1, 0, 0b10000000000000000000000000000000}};
  s21_decimal y = {{21, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "4 1 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_add_7) {
  s21_decimal x = {{99, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal y = {{100, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_add_9) {
  s21_decimal x = {{0, 0, 3000000000, 0}};
  s21_decimal y = {{0, 0, 3000000000, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 1);
}
END_TEST

START_TEST(decimal_add_10) {
  s21_decimal x = {{1, 0, 0, 1835008}};
  s21_decimal y = {{1, 0, 0, 2149318656}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char res1[1000] = "0 0 0 0";
  char res2[1000] = "0 0 0 1835008";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

Suite *suite_s21_add(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_add_suite}-====\033[0m");
  tc_core = tcase_create("Add_Core");

  tcase_add_test(tc_core, decimal_add_1);
  tcase_add_test(tc_core, decimal_add_2);
  tcase_add_test(tc_core, decimal_add_3);
  tcase_add_test(tc_core, decimal_add_4);
  tcase_add_test(tc_core, decimal_add_5);
  tcase_add_test(tc_core, decimal_add_6);
  tcase_add_test(tc_core, decimal_add_7);
  tcase_add_test(tc_core, decimal_add_9);
  tcase_add_test(tc_core, decimal_add_10);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(decimal_sub_1) {
  s21_decimal x = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal y = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_2) {
  s21_decimal x = {{2, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal y = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_3) {
  s21_decimal x = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal y = {{2, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_4) {
  s21_decimal x = {{2, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal y = {{2, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_5) {
  s21_decimal x = {{1, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal y = {{2, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_6) {
  s21_decimal x = {{2, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal y = {{1, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_7) {
  s21_decimal x = {{2, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal y = {{1, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "3 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_8) {
  s21_decimal x = {{2, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal y = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_sub(x, y, &z);
  char res1[1000], res2[1000] = "3 0 0 2147483648";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

Suite *suite_s21_sub(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_sub_suite}-====\033[0m");
  tc_core = tcase_create("Sub_Core");

  tcase_add_test(tc_core, decimal_sub_1);
  tcase_add_test(tc_core, decimal_sub_2);
  tcase_add_test(tc_core, decimal_sub_3);
  tcase_add_test(tc_core, decimal_sub_4);
  tcase_add_test(tc_core, decimal_sub_5);
  tcase_add_test(tc_core, decimal_sub_6);
  tcase_add_test(tc_core, decimal_sub_7);
  tcase_add_test(tc_core, decimal_sub_8);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_mul_1) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403.0e2;
  int b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = 189940600;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_mul_2) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403.0e2;
  float b = 9403.0e2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 884164090000;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_mul_3) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = 9403;
  float b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 1899406;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_mul_4) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -32768;
  float b = 2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -65536;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_mul_5) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float a = -32768;
  float b = 32768;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1073741824;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_mul_6) {
  s21_decimal src1 = {{0, 1, 0, 0}};
  s21_decimal src2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  float res_our_dec = 0.0;
  float res_origin = 4294967296;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_mul_7) {
  s21_decimal src1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_mul_8) {
  s21_decimal src1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(test_mul_9) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  float n1 = -5.6e-15;
  float n2 = 1.5e-15;
  s21_from_float_to_decimal(n1, &val1);
  s21_from_float_to_decimal(n2, &val2);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
}
END_TEST

Suite *suite_s21_mul(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_mul}-====\033[0m");
  tc_core = tcase_create("s21_mul_Core");

  tcase_add_test(tc_core, test_mul_1);
  tcase_add_test(tc_core, test_mul_2);
  tcase_add_test(tc_core, test_mul_3);
  tcase_add_test(tc_core, test_mul_4);
  tcase_add_test(tc_core, test_mul_5);
  tcase_add_test(tc_core, test_mul_6);
  tcase_add_test(tc_core, test_mul_7);
  tcase_add_test(tc_core, test_mul_8);
  tcase_add_test(tc_core, test_mul_9);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(div_test_1) {
  int num1 = 100;
  int num2 = 50;
  int res_origin = 2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_test_2) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -16384;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_test_3) {
  int num1 = 2;
  int num2 = 2;
  int res_origin = 1;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_test_4) {
  int num1 = 0;
  int num2 = 5;
  int res_origin = num1 / num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_test_5) {
  s21_decimal dec1, dec2, result;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);

  dec1.bits[3] = 0;
  dec1.bits[2] = 1568954488;
  dec1.bits[1] = 1568954488;
  dec1.bits[0] = 1568954488;

  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 0;
  dec2.bits[0] = 0;

  diff = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(diff, 3);
}
END_TEST

START_TEST(div_test_6) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);

  dec1.bits[3] = 0;
  dec1.bits[2] = 1568954488;
  dec1.bits[1] = 1568954488;
  dec1.bits[0] = 1568954488;

  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 0;
  dec2.bits[0] = 1;

  orig.bits[3] = 0;
  orig.bits[2] = 1568954488;
  orig.bits[1] = 1568954488;
  orig.bits[0] = 1568954488;

  s21_div(dec1, dec2, &result);
  diff = s21_is_equal(result, orig);
  ck_assert_int_eq(diff, 1);
}
END_TEST

START_TEST(div_test_8) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);
  // 4949341991908698119347372159
  dec1.bits[3] = 0;
  dec1.bits[2] = 0b1111111111011111111111101111;
  dec1.bits[1] = 0b111100000000000000;
  dec1.bits[0] = 0b0000000000000001111111;
  // 31
  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 0;
  dec2.bits[0] = 0b000000011111;
  set_scale(2, &dec2);
  // 15965619328737735868862490835.4838709677419355
  orig.bits[3] = 0;
  orig.bits[2] = 0b00110011100101100111001101100110;
  orig.bits[1] = 0b00010000100100000011100111001110;
  orig.bits[0] = 0b01110011100111001110100011010011;

  s21_div(dec1, dec2, &result);

  diff = s21_is_equal(result, orig);
  ck_assert_int_eq(diff, 1);
}
END_TEST

START_TEST(div_test_9) {
  s21_decimal src1 = {{25, 0, 0, 0}};
  s21_decimal src2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  float a = 25;
  float b = 5;
  float c = 0;
  s21_from_decimal_to_float(result, &c);
  ck_assert_float_eq(c, a / b);
}
END_TEST

START_TEST(div_test_10) {
  s21_decimal src1 = {{25, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_div(src1, src2, &result);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(div_test_11) {
  s21_decimal src1 = {{0, 1, 0, 0}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);

  s21_decimal result_expected;
  initialize_decimal(&result_expected);
  result_expected.bits[0] = 2147483648;
  float a = 0;
  float b = 0;
  s21_from_decimal_to_float(result, &a);
  s21_from_decimal_to_float(result_expected, &b);

  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(div_test_12) {
  s21_decimal src1 = {{1000, 0, 0, 65536}};
  s21_decimal src2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);
  s21_decimal result_expected;
  initialize_decimal(&result_expected);
  result_expected.bits[0] = 50;
  float a = 0;
  float b = 0;
  s21_from_decimal_to_float(result, &a);
  s21_from_decimal_to_float(result_expected, &b);

  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(div_test_13) {
  s21_decimal src1 = {{1000, 0, 0, 0}};
  s21_decimal src2 = {{5, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(src1, src2, &result);

  s21_decimal result_expected;
  initialize_decimal(&result_expected);
  result_expected.bits[0] = 2000;
  float a = 0;
  float b = 0;
  s21_from_decimal_to_float(result, &a);
  s21_from_decimal_to_float(result_expected, &b);

  ck_assert_float_eq(a, b);
}
END_TEST
Suite *suite_s21_div(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_div}-====\033[0m");
  tc_core = tcase_create("s21_div_Core");

  tcase_add_test(tc_core, div_test_1);
  tcase_add_test(tc_core, div_test_2);
  tcase_add_test(tc_core, div_test_3);
  tcase_add_test(tc_core, div_test_4);
  tcase_add_test(tc_core, div_test_5);
  tcase_add_test(tc_core, div_test_6);
  tcase_add_test(tc_core, div_test_8);
  tcase_add_test(tc_core, div_test_9);
  tcase_add_test(tc_core, div_test_10);
  tcase_add_test(tc_core, div_test_11);
  tcase_add_test(tc_core, div_test_12);
  tcase_add_test(tc_core, div_test_13);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *suite_s21_floor(void) {
  Suite *s4;
  TCase *tc4;
  s4 = suite_create("s21_floor");
  tc4 = tcase_create("case_floor");

  tcase_add_test(tc4, floor_1_fail);
  tcase_add_test(tc4, floor_2_fail);
  tcase_add_test(tc4, floor_3_fail);
  tcase_add_test(tc4, floor_4_fail);
  tcase_add_test(tc4, floor_5_fail);
  tcase_add_test(tc4, floor_6_fail);
  tcase_add_test(tc4, test_floor_ok1);
  tcase_add_test(tc4, test_floor_ok2);
  tcase_add_test(tc4, test_floor_ok3);
  tcase_add_test(tc4, test_floor_ok4);
  suite_add_tcase(s4, tc4);
  return s4;
}

START_TEST(s21_less_1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 0);
}
END_TEST

START_TEST(s21_less_2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 0);
}
END_TEST

START_TEST(s21_less_3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 0);
}
END_TEST

START_TEST(s21_less_4) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 1);
}
END_TEST

START_TEST(s21_less_5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 0);
}
END_TEST

START_TEST(s21_less_6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 0);
}
END_TEST

START_TEST(s21_less_7) {
  // 1.0
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 1);
}
END_TEST

START_TEST(s21_less_8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 0);
}
END_TEST

START_TEST(s21_less_9) {
  // 0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 1);
}
END_TEST

START_TEST(s21_less_10) {
  // 1431655764.999999999999999999
  s21_decimal decimal1 = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x120000}};
  // 0.00000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0xE0000}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 0);
}
END_TEST

START_TEST(s21_less_11) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 52818775009509558395695966891
  s21_decimal decimal2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 1);
}
END_TEST

START_TEST(s21_less_12) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 1);
}
END_TEST

START_TEST(s21_less_13) {
  // -1.2297829382473034409
  s21_decimal decimal1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 0);
}
END_TEST

START_TEST(s21_less_14) {
  // 1.2297829382473034411
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0x0, 0x130000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 0);
}
END_TEST
START_TEST(s21_less_15) {
  // -1.2297829382473034411
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0x0, 0x80130000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_less(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_is_equal_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_is_equal_ok2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_equal_ok3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok4) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 52818775009509558395695966890
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok6) {
  // 52818775009509558395695966890
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -52818775009509558395695966890
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok8) {
  // -52818775009509558395695966890
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 52818775009509558395695966891
  s21_decimal decimal2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok10) {
  // 52818775009509558395695966891
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_is_equal_ok12) {
  // -52818775009509558395695966891
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5.281877500950955839569596690
  s21_decimal decimal2 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok14) {
  // 5.281877500950955839569596690
  s21_decimal decimal1 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5.281877500950955839569596690
  s21_decimal decimal2 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok16) {
  // -5.281877500950955839569596690
  s21_decimal decimal1 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5281877500950955839569596689
  s21_decimal decimal2 = {{0x11111111, 0x11111111, 0x11111111, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok18) {
  // 5281877500950955839569596689
  s21_decimal decimal1 = {{0x11111111, 0x11111111, 0x11111111, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5281877500950955839569596689
  s21_decimal decimal2 = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok20) {
  // -5281877500950955839569596689
  s21_decimal decimal1 = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_equal_ok21) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5281877500950955839569596689.0
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok22) {
  // 5281877500950955839569596689.0
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok23) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5281877500950955839569596689.0
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok24) {
  // -5281877500950955839569596689.0
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok25) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok26) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_equal_ok27) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok28) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok29) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok30) {
  // 7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok31) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok32) {
  // -7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.2297829382473034409
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_equal_ok34) {
  // 1.2297829382473034409
  s21_decimal decimal1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x130000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_equal_ok35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.2297829382473034409
  s21_decimal decimal2 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_is_not_equal_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_not_equal_ok2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_not_equal_ok3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok4) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 52818775009509558395695966890
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok6) {
  // 52818775009509558395695966890
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -52818775009509558395695966890
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok8) {
  // -52818775009509558395695966890
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 52818775009509558395695966891
  s21_decimal decimal2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok10) {
  // 52818775009509558395695966891
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -52818775009509558395695966891
  s21_decimal decimal2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok12) {
  // -52818775009509558395695966891
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5.281877500950955839569596690
  s21_decimal decimal2 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok14) {
  // 5.281877500950955839569596690
  s21_decimal decimal1 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5.281877500950955839569596690
  s21_decimal decimal2 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok16) {
  // -5.281877500950955839569596690
  s21_decimal decimal1 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5281877500950955839569596689
  s21_decimal decimal2 = {{0x11111111, 0x11111111, 0x11111111, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok18) {
  // 5281877500950955839569596689
  s21_decimal decimal1 = {{0x11111111, 0x11111111, 0x11111111, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5281877500950955839569596689
  s21_decimal decimal2 = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok20) {
  // -5281877500950955839569596689
  s21_decimal decimal1 = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok21) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5281877500950955839569596689.0
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok22) {
  // 5281877500950955839569596689.0
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok23) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5281877500950955839569596689.0
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok24) {
  // -5281877500950955839569596689.0
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok25) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok26) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok27) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok28) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok29) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok30) {
  // 7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok31) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok32) {
  // -7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.2297829382473034409
  s21_decimal decimal2 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x130000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok34) {
  // 1.2297829382473034409
  s21_decimal decimal1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x130000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_not_equal_ok35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};
  // -1.2297829382473034409
  s21_decimal decimal2 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_not_equal_ok36) {
  // -1.2297829382473034409
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_is_greater_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok4) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 52818775009509558395695966890
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok6) {
  // 52818775009509558395695966890
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -52818775009509558395695966890
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok8) {
  // -52818775009509558395695966890
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 52818775009509558395695966891
  s21_decimal decimal2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok10) {
  // 52818775009509558395695966891
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -52818775009509558395695966891
  s21_decimal decimal2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok12) {
  // -52818775009509558395695966891
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5.281877500950955839569596690
  s21_decimal decimal2 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok14) {
  // 5.281877500950955839569596690
  s21_decimal decimal1 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5.281877500950955839569596690
  s21_decimal decimal2 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok16) {
  // -5.281877500950955839569596690
  s21_decimal decimal1 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5281877500950955839569596689
  s21_decimal decimal2 = {{0x11111111, 0x11111111, 0x11111111, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok18) {
  // 5281877500950955839569596689
  s21_decimal decimal1 = {{0x11111111, 0x11111111, 0x11111111, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5281877500950955839569596689
  s21_decimal decimal2 = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok20) {
  // -5281877500950955839569596689
  s21_decimal decimal1 = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok21) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5281877500950955839569596689.0
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok22) {
  // 5281877500950955839569596689.0
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok23) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5281877500950955839569596689.0
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok24) {
  // -5281877500950955839569596689.0
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok25) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok26) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok27) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok28) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok29) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok30) {
  // 7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok31) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok32) {
  // -7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.2297829382473034409
  s21_decimal decimal2 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x130000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok34) {
  // 1.2297829382473034409
  s21_decimal decimal1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x130000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_ok35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.2297829382473034409
  s21_decimal decimal2 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_ok36) {
  // -1.2297829382473034409
  s21_decimal decimal1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_is_greater_or_equal_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok4) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 52818775009509558395695966890
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok6) {
  // 52818775009509558395695966890
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -52818775009509558395695966890
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok8) {
  // -52818775009509558395695966890
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 52818775009509558395695966891
  s21_decimal decimal2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok10) {
  // 52818775009509558395695966891
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -52818775009509558395695966891
  s21_decimal decimal2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok12) {
  // -52818775009509558395695966891
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5.281877500950955839569596690
  s21_decimal decimal2 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok14) {
  // 5.281877500950955839569596690
  s21_decimal decimal1 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5.281877500950955839569596690
  s21_decimal decimal2 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok16) {
  // -5.281877500950955839569596690
  s21_decimal decimal1 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5281877500950955839569596689
  s21_decimal decimal2 = {{0x11111111, 0x11111111, 0x11111111, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok18) {
  // 5281877500950955839569596689
  s21_decimal decimal1 = {{0x11111111, 0x11111111, 0x11111111, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5281877500950955839569596689
  s21_decimal decimal2 = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok20) {
  // -5281877500950955839569596689
  s21_decimal decimal1 = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok21) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5281877500950955839569596689.0
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok22) {
  // 5281877500950955839569596689.0
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok23) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5281877500950955839569596689.0
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok24) {
  // -5281877500950955839569596689.0
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok25) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok26) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok27) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok28) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok29) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok30) {
  // 7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok31) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok32) {
  // -7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.2297829382473034409
  s21_decimal decimal2 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x130000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok34) {
  // 1.2297829382473034409
  s21_decimal decimal1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x130000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.2297829382473034409
  s21_decimal decimal2 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 1);
}
END_TEST
START_TEST(test_is_greater_or_equal_ok36) {
  // -1.2297829382473034409
  s21_decimal decimal1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal1, decimal2), 0);
}
END_TEST

Suite *srunner_add_comparsion_tests(void) {
  Suite *s1 = suite_create("compare");
  TCase *tc1_1 = tcase_create("compare");
  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_is_equal_ok1);
  tcase_add_test(tc1_1, test_is_equal_ok2);
  tcase_add_test(tc1_1, test_is_equal_ok3);
  tcase_add_test(tc1_1, test_is_equal_ok4);
  tcase_add_test(tc1_1, test_is_equal_ok5);
  tcase_add_test(tc1_1, test_is_equal_ok6);
  tcase_add_test(tc1_1, test_is_equal_ok7);
  tcase_add_test(tc1_1, test_is_equal_ok8);
  tcase_add_test(tc1_1, test_is_equal_ok9);
  tcase_add_test(tc1_1, test_is_equal_ok10);
  tcase_add_test(tc1_1, test_is_equal_ok12);
  tcase_add_test(tc1_1, test_is_equal_ok13);
  tcase_add_test(tc1_1, test_is_equal_ok14);
  tcase_add_test(tc1_1, test_is_equal_ok15);
  tcase_add_test(tc1_1, test_is_equal_ok16);
  tcase_add_test(tc1_1, test_is_equal_ok17);
  tcase_add_test(tc1_1, test_is_equal_ok18);
  tcase_add_test(tc1_1, test_is_equal_ok19);
  tcase_add_test(tc1_1, test_is_equal_ok20);
  tcase_add_test(tc1_1, test_is_equal_ok21);
  tcase_add_test(tc1_1, test_is_equal_ok22);
  tcase_add_test(tc1_1, test_is_equal_ok23);
  tcase_add_test(tc1_1, test_is_equal_ok24);
  tcase_add_test(tc1_1, test_is_equal_ok25);
  tcase_add_test(tc1_1, test_is_equal_ok26);
  tcase_add_test(tc1_1, test_is_equal_ok27);
  tcase_add_test(tc1_1, test_is_equal_ok28);
  tcase_add_test(tc1_1, test_is_equal_ok29);
  tcase_add_test(tc1_1, test_is_equal_ok30);
  tcase_add_test(tc1_1, test_is_equal_ok31);
  tcase_add_test(tc1_1, test_is_equal_ok32);
  tcase_add_test(tc1_1, test_is_equal_ok33);
  tcase_add_test(tc1_1, test_is_equal_ok34);
  tcase_add_test(tc1_1, test_is_equal_ok35);
  tcase_add_test(tc1_1, test_is_not_equal_ok1);
  tcase_add_test(tc1_1, test_is_not_equal_ok2);
  tcase_add_test(tc1_1, test_is_not_equal_ok3);
  tcase_add_test(tc1_1, test_is_not_equal_ok4);
  tcase_add_test(tc1_1, test_is_not_equal_ok5);
  tcase_add_test(tc1_1, test_is_not_equal_ok6);
  tcase_add_test(tc1_1, test_is_not_equal_ok7);
  tcase_add_test(tc1_1, test_is_not_equal_ok8);
  tcase_add_test(tc1_1, test_is_not_equal_ok9);
  tcase_add_test(tc1_1, test_is_not_equal_ok10);
  tcase_add_test(tc1_1, test_is_not_equal_ok11);
  tcase_add_test(tc1_1, test_is_not_equal_ok12);
  tcase_add_test(tc1_1, test_is_not_equal_ok13);
  tcase_add_test(tc1_1, test_is_not_equal_ok14);
  tcase_add_test(tc1_1, test_is_not_equal_ok15);
  tcase_add_test(tc1_1, test_is_not_equal_ok16);
  tcase_add_test(tc1_1, test_is_not_equal_ok17);
  tcase_add_test(tc1_1, test_is_not_equal_ok18);
  tcase_add_test(tc1_1, test_is_not_equal_ok19);
  tcase_add_test(tc1_1, test_is_not_equal_ok20);
  tcase_add_test(tc1_1, test_is_not_equal_ok21);
  tcase_add_test(tc1_1, test_is_not_equal_ok22);
  tcase_add_test(tc1_1, test_is_not_equal_ok23);
  tcase_add_test(tc1_1, test_is_not_equal_ok24);
  tcase_add_test(tc1_1, test_is_not_equal_ok25);
  tcase_add_test(tc1_1, test_is_not_equal_ok26);
  tcase_add_test(tc1_1, test_is_not_equal_ok27);
  tcase_add_test(tc1_1, test_is_not_equal_ok28);
  tcase_add_test(tc1_1, test_is_not_equal_ok29);
  tcase_add_test(tc1_1, test_is_not_equal_ok30);
  tcase_add_test(tc1_1, test_is_not_equal_ok31);
  tcase_add_test(tc1_1, test_is_not_equal_ok32);
  tcase_add_test(tc1_1, test_is_not_equal_ok33);
  tcase_add_test(tc1_1, test_is_not_equal_ok34);
  tcase_add_test(tc1_1, test_is_not_equal_ok35);
  tcase_add_test(tc1_1, test_is_not_equal_ok36);
  tcase_add_test(tc1_1, s21_less_1);
  tcase_add_test(tc1_1, s21_less_2);
  tcase_add_test(tc1_1, s21_less_3);
  tcase_add_test(tc1_1, s21_less_4);
  tcase_add_test(tc1_1, s21_less_5);
  tcase_add_test(tc1_1, s21_less_6);
  tcase_add_test(tc1_1, s21_less_7);
  tcase_add_test(tc1_1, s21_less_8);
  tcase_add_test(tc1_1, s21_less_9);
  tcase_add_test(tc1_1, s21_less_10);
  tcase_add_test(tc1_1, s21_less_11);
  tcase_add_test(tc1_1, s21_less_12);
  tcase_add_test(tc1_1, s21_less_13);
  tcase_add_test(tc1_1, s21_less_14);
  tcase_add_test(tc1_1, s21_less_15);
  tcase_add_test(tc1_1, test_is_greater_ok1);
  tcase_add_test(tc1_1, test_is_greater_ok2);
  tcase_add_test(tc1_1, test_is_greater_ok3);
  tcase_add_test(tc1_1, test_is_greater_ok4);
  tcase_add_test(tc1_1, test_is_greater_ok5);
  tcase_add_test(tc1_1, test_is_greater_ok6);
  tcase_add_test(tc1_1, test_is_greater_ok7);
  tcase_add_test(tc1_1, test_is_greater_ok8);
  tcase_add_test(tc1_1, test_is_greater_ok9);
  tcase_add_test(tc1_1, test_is_greater_ok10);
  tcase_add_test(tc1_1, test_is_greater_ok11);
  tcase_add_test(tc1_1, test_is_greater_ok12);
  tcase_add_test(tc1_1, test_is_greater_ok13);
  tcase_add_test(tc1_1, test_is_greater_ok14);
  tcase_add_test(tc1_1, test_is_greater_ok15);
  tcase_add_test(tc1_1, test_is_greater_ok16);
  tcase_add_test(tc1_1, test_is_greater_ok17);
  tcase_add_test(tc1_1, test_is_greater_ok18);
  tcase_add_test(tc1_1, test_is_greater_ok19);
  tcase_add_test(tc1_1, test_is_greater_ok20);
  tcase_add_test(tc1_1, test_is_greater_ok21);
  tcase_add_test(tc1_1, test_is_greater_ok22);
  tcase_add_test(tc1_1, test_is_greater_ok23);
  tcase_add_test(tc1_1, test_is_greater_ok24);
  tcase_add_test(tc1_1, test_is_greater_ok25);
  tcase_add_test(tc1_1, test_is_greater_ok26);
  tcase_add_test(tc1_1, test_is_greater_ok27);
  tcase_add_test(tc1_1, test_is_greater_ok28);
  tcase_add_test(tc1_1, test_is_greater_ok29);
  tcase_add_test(tc1_1, test_is_greater_ok30);
  tcase_add_test(tc1_1, test_is_greater_ok31);
  tcase_add_test(tc1_1, test_is_greater_ok32);
  tcase_add_test(tc1_1, test_is_greater_ok33);
  tcase_add_test(tc1_1, test_is_greater_ok34);
  tcase_add_test(tc1_1, test_is_greater_ok35);
  tcase_add_test(tc1_1, test_is_greater_ok36);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok1);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok2);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok3);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok4);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok5);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok6);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok7);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok8);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok9);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok10);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok11);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok12);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok13);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok14);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok15);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok16);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok17);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok18);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok19);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok20);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok21);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok22);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok23);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok24);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok25);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok26);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok27);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok28);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok29);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok30);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok31);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok32);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok33);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok34);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok35);
  tcase_add_test(tc1_1, test_is_greater_or_equal_ok36);
  return s1;
}

START_TEST(test_int_to_decimal_ok1) {
  int src = 2147483647;
  s21_decimal res;
  s21_set_decimal_zero(&res);
  int exit_code = s21_from_int_to_decimal(src, &res);
  int expected_exit_code = 0;
  s21_decimal expected_dec = {{2147483647, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_mem_eq(&expected_dec, &res, 4 * sizeof(uint32_t));
}

START_TEST(test_int_to_decimal_ok2) {
  int src = -489;
  s21_decimal res;
  s21_set_decimal_zero(&res);
  int exit_code = s21_from_int_to_decimal(src, &res);
  int expected_exit_code = 0;
  s21_decimal expected_dec = {{0x000001e9, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_mem_eq(&expected_dec, &res, 4 * sizeof(uint32_t));
}

START_TEST(test_int_to_decimal_ok3) {
  int src = -419;
  s21_decimal res;
  s21_set_decimal_zero(&res);
  int exit_code = s21_from_int_to_decimal(src, &res);
  int expected_exit_code = 0;
  s21_decimal expected_dec = {{0x000001a3, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_mem_eq(&expected_dec, &res, 4 * sizeof(uint32_t));
}

START_TEST(test_int_to_decimal_ok4) {
  int src = 0;
  s21_decimal res;
  s21_set_decimal_zero(&res);
  int exit_code = s21_from_int_to_decimal(src, &res);
  int expected_exit_code = 0;
  s21_decimal expected_dec = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_mem_eq(&expected_dec, &res, 4 * sizeof(uint32_t));
}

START_TEST(test_int_to_decimal_ok5) {
  int src = INT_MIN;
  s21_decimal res;
  s21_set_decimal_zero(&res);
  int exit_code = s21_from_int_to_decimal(src, &res);
  int expected_exit_code = 0;
  s21_decimal expected_dec = {{0x80000000, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_mem_eq(&expected_dec, &res, 4 * sizeof(uint32_t));
}

//---------------------s21_decimal to int-----------------------//

START_TEST(test_decimal_to_int_ok1) {
  s21_decimal src = {{0x2F394219, 0x00000000, 0x00000000, 0x00000000}};
  int res;
  int exit_code = s21_from_decimal_to_int(src, &res);
  int expected_exit_code = 0;
  int expected_res = 792281625;
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_int_eq(expected_res, res);
}

START_TEST(test_decimal_to_int_bad1) {
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int res;
  int exit_code = s21_from_decimal_to_int(src, &res);
  int expected_exit_code = 1;
  ck_assert_int_eq(exit_code, expected_exit_code);
}

START_TEST(test_decimal_to_int_bad2) {
  s21_decimal src = {{1, 0, 0, 1000000000}}; // слишком большая степень
  int res;
  int exit_code = s21_from_decimal_to_int(src, &res);
  int expected_exit_code = 1;
  ck_assert_int_eq(exit_code, expected_exit_code);
}

START_TEST(test_decimal_to_int_bad3) {
  s21_decimal src = {{-1, 0, 0, 0x1D0000}}; // слишком большая степень
  int res;
  int exit_code = s21_from_decimal_to_int(src, &res);
  int expected_exit_code = 1;
  ck_assert_int_eq(exit_code, expected_exit_code);
}

START_TEST(test_decimal_to_int_bad4) {
  s21_decimal src = {{0, 0, 0, 0x1D0000}}; // слишком большая степень
  int res;
  int exit_code = s21_from_decimal_to_int(src, &res);
  int expected_exit_code = 1;
  ck_assert_int_eq(exit_code, expected_exit_code);
}

START_TEST(test_decimal_to_int_bad5) {
  s21_decimal src = {{-1, 0, 0, 0x1C0001}}; // слишком большая степень
  int res;
  int exit_code = s21_from_decimal_to_int(src, &res);
  int expected_exit_code = 1;
  ck_assert_int_eq(exit_code, expected_exit_code);
}

START_TEST(test_decimal_to_int_bad6) {
  s21_decimal src = {{-1, 0, 0, 0x11C0000}}; // слишком большая степень
  int res;
  int exit_code = s21_from_decimal_to_int(src, &res);
  int expected_exit_code = 1;
  ck_assert_int_eq(exit_code, expected_exit_code);
}

START_TEST(test_decimal_to_int_bad7) {
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                      0xFFFFFFFF}}; // слишком большая степень
  int res;
  int exit_code = s21_from_decimal_to_int(src, &res);
  int expected_exit_code = 1;
  ck_assert_int_eq(exit_code, expected_exit_code);
}

//---------------------float to decimal-----------------------//
START_TEST(test_float_to_decimal_ok1) {
  float src = 56.986;
  s21_decimal res;
  s21_set_decimal_zero(&res);
  int exit_code = s21_from_float_to_decimal(src, &res);
  int expected_exit_code = 0;
  s21_decimal expected_dec = {{0xDE9A, 0, 0, 0x30000}};

  ck_assert_uint_eq(exit_code, expected_exit_code);
  ck_assert_mem_eq(&expected_dec, &res, 4 * sizeof(uint32_t));
}

START_TEST(test_float_to_decimal_ok2) {
  float src = -1.596;
  s21_decimal res;
  s21_set_decimal_zero(&res);
  int exit_code = s21_from_float_to_decimal(src, &res);
  int expected_exit_code = 0;
  s21_decimal expected_dec = {{1596, 0, 0, 2147680256}};

  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_mem_eq(&expected_dec, &res, 4 * sizeof(uint32_t));
}

START_TEST(test_float_to_decimal_ok3) {
  float src = (46237.42332 / 12712.37834);
  s21_decimal res;
  s21_set_decimal_zero(&res);
  int exit_code = s21_from_float_to_decimal(src, &res);
  int expected_exit_code = 0;
  s21_decimal expected_dec = {{3637197, 0, 0, 393216}};

  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_mem_eq(&expected_dec, &res, 4 * sizeof(uint32_t));
}

START_TEST(test_float_to_decimal_ok4) {
  float src = 0.0000000000000000002284016;
  s21_decimal res;
  s21_set_decimal_zero(&res);
  int exit_code = s21_from_float_to_decimal(src, &res);
  int expected_exit_code = 0;
  s21_decimal expected_dec = {{0x22D9F0, 0x0, 0x0, 0x190000}};

  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_mem_eq(&expected_dec, &res, 4 * sizeof(uint32_t));
}

START_TEST(test_float_to_decimal_ok5) {
  float src = -0.0000000000000000002284016;
  s21_decimal res;
  s21_set_decimal_zero(&res);
  int exit_code = s21_from_float_to_decimal(src, &res);
  int expected_exit_code = 0;
  s21_decimal expected_dec = {{0x22D9F0, 0x0, 0x0, 0x80190000}};

  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_mem_eq(&expected_dec, &res, 4 * sizeof(uint32_t));
}

START_TEST(test_float_to_decimal_ok6) {
  float src = 2.1349025E-18;
  s21_decimal res;
  s21_set_decimal_zero(&res);
  int exit_code = s21_from_float_to_decimal(src, &res);
  int expected_exit_code = 0;
  s21_decimal expected_dec = {{0x209376, 0x0, 0x0, 0x180000}};

  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_mem_eq(&expected_dec, &res, 4 * sizeof(uint32_t));
}
// printf("\n%x %x %x %x\n\n", res.bits[0], res.bits[1], res.bits[2],
// res.bits[3]);
START_TEST(test_float_to_decimal_ok7) {
  float src = 7.91617864E+11;
  s21_decimal res;
  s21_set_decimal_zero(&res);
  int exit_code = s21_from_float_to_decimal(src, &res);
  int expected_exit_code = 0;
  s21_decimal expected_dec = {{0x501A8DE0, 0xB8, 0x0, 0x0}};

  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_mem_eq(&expected_dec, &res, 4 * sizeof(uint32_t));
}

START_TEST(test_float_to_decimal_bad1) {
  float src = 1.0 / 0.0;
  s21_decimal res;
  s21_set_decimal_zero(&res);
  int exit_code = s21_from_float_to_decimal(src, &res);
  int expected_exit_code = 1;
  s21_decimal expected_dec = {{0, 0, 0, 0}};

  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_mem_eq(&expected_dec, &res, 4 * sizeof(uint32_t));
}

//---------------------s21_decimal to float-----------------------//
START_TEST(test_decimal_to_float_ok1) {
  s21_decimal src = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  float res;
  int exit_code = s21_from_decimal_to_float(src, &res);
  int expected_exit_code = 0;
  float expected_float = 0.0;
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_float_eq(expected_float, res);
}

START_TEST(test_decimal_to_float_ok2) {
  s21_decimal src = {{1234, 0, 0, 0}};
  set_scale(6, &src);
  float res;
  int exit_code = s21_from_decimal_to_float(src, &res);
  int expected_exit_code = 0;
  float expected_float = 0.001234;
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_float_eq(expected_float, res);
}

START_TEST(test_decimal_to_float_ok3) {
  s21_decimal src, value_1, value_2;
  s21_set_decimal_zero(&src);
  s21_set_decimal_zero(&value_1);
  s21_set_decimal_zero(&value_2);
  s21_from_int_to_decimal(1994214, &value_1);
  s21_from_int_to_decimal(77443333, &value_2);
  s21_sub(value_1, value_2, &src);
  float res;
  int exit_code = s21_from_decimal_to_float(src, &res);
  int expected_exit_code = 0;
  float expected_float = 1994214 - 77443333;
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_float_eq(expected_float, res);
}

START_TEST(test_decimal_to_float_ok4) {
  s21_decimal src, value_1, value_2;
  s21_set_decimal_zero(&src);
  s21_set_decimal_zero(&value_1);
  s21_set_decimal_zero(&value_2);
  s21_from_int_to_decimal(1994214, &value_1);
  s21_from_int_to_decimal(77443333, &value_2);
  s21_div(value_1, value_2, &src);
  float res;
  int exit_code = s21_from_decimal_to_float(src, &res);
  int expected_exit_code = 0;
  double expected_float = 1994214.0 / 77443333.0;
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_float_eq(expected_float, res);
}

START_TEST(test_decimal_to_float_ok5) {
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  float res;
  int exit_code = s21_from_decimal_to_float(src, &res);
  int expected_exit_code = 0;
  float expected_float = 792281625.14264337593543950335;
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_float_eq(expected_float, res);
}

START_TEST(test_decimal_to_float_ok6) {
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  float res;
  int exit_code = s21_from_decimal_to_float(src, &res);
  int expected_exit_code = 0;
  float expected_float = -792281625142643375935439503.35;
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_float_eq(expected_float, res);
}

START_TEST(test_decimal_to_float_ok7) {
  s21_decimal src = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80010000}};
  float res;
  int exit_code = s21_from_decimal_to_float(src, &res);
  int expected_exit_code = 0;
  float expected_float = -2099546306628004946228914683.9;
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_float_eq(expected_float, res);
}

START_TEST(test_decimal_to_float_ok8) {
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
  float res;
  int exit_code = s21_from_decimal_to_float(src, &res);
  int expected_exit_code = 0;
  float expected_float = 7922816251426433759.3543950335;
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_float_eq(expected_float, res);
}

START_TEST(test_decimal_to_float_ok9) {
  s21_decimal src = {{0xD0D5C09E, 0xF5C86D50, 0xC07CEE69, 0xD0000}};
  float res;
  int exit_code = s21_from_decimal_to_float(src, &res);
  int expected_exit_code = 0;
  float expected_float = 5957215456517204.3656388264094;
  ck_assert_int_eq(exit_code, expected_exit_code);
  ck_assert_float_eq(expected_float, res);
}

START_TEST(test_decimal_to_float_bad1) {
  s21_decimal src = {{0, 0, 0, 1000000000}};
  float res;
  int exit_code = s21_from_decimal_to_float(src, &res);
  int expected_exit_code = 1;
  ck_assert_int_eq(exit_code, expected_exit_code);
}

START_TEST(test_decimal_to_float_bad2) {
  s21_decimal src = {{-1, 0, 0, 0x1D0000}};
  float res;
  int exit_code = s21_from_decimal_to_float(src, &res);
  int expected_exit_code = 1;
  ck_assert_int_eq(exit_code, expected_exit_code);
}

Suite *s21_from_int_to_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_from_int_to_decimal}-====\033[0m");
  tc_core = tcase_create("s21_from_int_to_decimal_Core");
  tcase_add_test(tc_core, test_int_to_decimal_ok1);
  tcase_add_test(tc_core, test_int_to_decimal_ok2);
  tcase_add_test(tc_core, test_int_to_decimal_ok3);
  tcase_add_test(tc_core, test_int_to_decimal_ok4);
  tcase_add_test(tc_core, test_int_to_decimal_ok5);

  //---------------------s21_decimal to float-----------------------//
  tcase_add_test(tc_core, test_decimal_to_float_ok1);
  tcase_add_test(tc_core, test_decimal_to_float_ok2);
  tcase_add_test(tc_core, test_decimal_to_float_ok3);
  tcase_add_test(tc_core, test_decimal_to_float_ok4);

  tcase_add_test(tc_core, test_decimal_to_float_bad1);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_from_decimal_to_int_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_from_decimal_to_int}-====\033[0m");
  tc_core = tcase_create("s21_from_decimal_to_int_Core");

  tcase_add_test(tc_core, test_float_to_decimal_ok1);
  tcase_add_test(tc_core, test_float_to_decimal_ok2);
  tcase_add_test(tc_core, test_float_to_decimal_ok3);
  tcase_add_test(tc_core, test_float_to_decimal_ok4);
  tcase_add_test(tc_core, test_float_to_decimal_ok5);
  tcase_add_test(tc_core, test_float_to_decimal_ok6);
  tcase_add_test(tc_core, test_float_to_decimal_ok7);

  tcase_add_test(tc_core, test_float_to_decimal_bad1);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_from_float_to_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_from_float_to_decimal}-====\033[0m");
  tc_core = tcase_create("s21_from_float_to_decimal_Core");

  tcase_add_test(tc_core, test_decimal_to_int_ok1);

  tcase_add_test(tc_core, test_decimal_to_int_bad1);
  tcase_add_test(tc_core, test_decimal_to_int_bad2);
  tcase_add_test(tc_core, test_decimal_to_int_bad3);
  tcase_add_test(tc_core, test_decimal_to_int_bad4);
  tcase_add_test(tc_core, test_decimal_to_int_bad5);
  tcase_add_test(tc_core, test_decimal_to_int_bad6);
  tcase_add_test(tc_core, test_decimal_to_int_bad7);

  suite_add_tcase(s, tc_core);

  return s;
}

Suite *s21_from_decimal_to_float_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_from_decimal_to_float}-====\033[0m");
  tc_core = tcase_create("s21_from_decimal_to_float_Core");

  tcase_add_test(tc_core, test_decimal_to_float_ok1);
  tcase_add_test(tc_core, test_decimal_to_float_ok2);
  tcase_add_test(tc_core, test_decimal_to_float_ok3);
  tcase_add_test(tc_core, test_decimal_to_float_ok4);
  tcase_add_test(tc_core, test_decimal_to_float_ok5);
  tcase_add_test(tc_core, test_decimal_to_float_ok6);
  tcase_add_test(tc_core, test_decimal_to_float_ok7);
  tcase_add_test(tc_core, test_decimal_to_float_ok8);
  tcase_add_test(tc_core, test_decimal_to_float_ok9);

  tcase_add_test(tc_core, test_decimal_to_float_bad1);
  tcase_add_test(tc_core, test_decimal_to_float_bad2);

  suite_add_tcase(s, tc_core);

  return s;
}