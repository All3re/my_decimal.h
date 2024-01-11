#include "test.h"

START_TEST(decimal_add_1) {
    s21_decimal x = {{4294967295, 4294967295, 0, 0b00000000000000000000000000000000}};
    s21_decimal y = {{1, 0, 0,                   0b00000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_add(x, y, &z);
    char res1[1000], res2[1000] = "0 0 1 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_add_2) {
    s21_decimal x = {{20, 1, 0, 0b10000000000000000000000000000000}};
    s21_decimal y = {{21, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_add(x, y, &z);
    char res1[1000], res2[1000] = "4294967295 0 0 2147483648";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_add_3) {
    s21_decimal x = {{20, 1, 0, 0b10000000000000000000000000000000}};
    s21_decimal y = {{21, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_add(x, y, &z);
    char res1[1000], res2[1000] = "41 1 0 2147483648";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_add_4) {
    s21_decimal x = {{20, 1, 0, 0b00000000000000000000000000000000}};
    s21_decimal y = {{21, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_add(x, y, &z);
    char res1[1000], res2[1000] = "4294967295 0 0 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_add_5) {
    s21_decimal x = {{20, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal y = {{21, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_add(x, y, &z);
    char res1[1000], res2[1000] = "1 0 0 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_add_6) {
    s21_decimal x = {{25, 1, 0, 0b10000000000000000000000000000000}};
    s21_decimal y = {{21, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_add(x, y, &z);
    char res1[1000], res2[1000] = "4 1 0 2147483648";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_add_7) {
    s21_decimal x = {{99, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal y = {{100, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_add(x, y, &z);
    char res1[1000], res2[1000] = "1 0 0 2147483648";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
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
    char res1[1000], res2[1000] = "0 0 0 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
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
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_2) {
    s21_decimal x = {{2, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal y = {{1, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_sub(x, y, &z);
    char res1[1000], res2[1000] = "1 0 0 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_3) {
    s21_decimal x = {{1, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal y = {{2, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_sub(x, y, &z);
    char res1[1000], res2[1000] = "1 0 0 2147483648";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_4) {
    s21_decimal x = {{2, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal y = {{2, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_sub(x, y, &z);
    char res1[1000], res2[1000] = "0 0 0 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_5) {
    s21_decimal x = {{1, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal y = {{2, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_sub(x, y, &z);
    char res1[1000], res2[1000] = "1 0 0 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_6) {
    s21_decimal x = {{2, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal y = {{1, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_sub(x, y, &z);
    char res1[1000], res2[1000] = "1 0 0 2147483648";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_7) {
    s21_decimal x = {{2, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal y = {{1, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_sub(x, y, &z);
    char res1[1000], res2[1000] = "3 0 0 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_sub_8) {
    s21_decimal x = {{2, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal y = {{1, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_sub(x, y, &z);
    char res1[1000], res2[1000] = "3 0 0 2147483648";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
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


START_TEST(decimal_mul_8) {
    s21_decimal x = {{0, 0, 0, 0b00000000000011110000000000000000}};
    s21_decimal y = {{0, 0, 0, 0b00000000000000100000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_mul(x, y, &z);
    char res1[1000], res2[1000] = "0 0 0 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_9) {
    s21_decimal x = {{2, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal y = {{5, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_mul(x, y, &z);
    char res1[1000], res2[1000] = "10 0 0 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_10) {
    s21_decimal x = {{2, 1, 2, 0b00000000000000000000000000000000}};
    s21_decimal y = {{5, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_mul(x, y, &z);
    char res1[1000], res2[1000] = "10 5 10 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_11) {
    s21_decimal x = {{2, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal y = {{0, 0, 10, 0b00000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_mul(x, y, &z);
    char res1[1000], res2[1000] = "0 0 20 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_12) {
    s21_decimal x = {{1000000000, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal y = {{6, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_mul(x, y, &z);
    char res1[1000], res2[1000] = "1705032704 1 0 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_13) {
    s21_decimal x = {{1000000000, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal y = {{6, 0, 0,          0b10000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_mul(x, y, &z);
    char res1[1000], res2[1000] = "1705032704 1 0 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(decimal_mul_14) {
    s21_decimal x = {{1000000000, 0, 0, 0b10000000000000000000000000000000}};
    s21_decimal y = {{6, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_mul(x, y, &z);
    char res1[1000], res2[1000] = "1705032704 1 0 2147483648";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST


START_TEST(decimal_mul_16) {
    s21_decimal x = {{1, 0, 0, 0b00000000000000000000000000000000}};
    s21_decimal y = {{165, 22, 6587456, 0b00000000000000000000000000000000}};
    s21_decimal z = {{0, 0, 0, 0}};
    s21_mul(x, y, &z);
    char res1[1000], res2[1000] = "165 22 6587456 0";
    snprintf(res1, sizeof(char)*1000, "%u %u %u %u", z.bits[0], z.bits[1], z.bits[2], z.bits[3]);
    ck_assert_str_eq(res1, res2);
}
END_TEST

Suite *suite_s21_mul(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_mul}-====\033[0m");
  tc_core = tcase_create("s21_mul_Core");

  tcase_add_test(tc_core, decimal_mul_8);
  tcase_add_test(tc_core, decimal_mul_9);
  tcase_add_test(tc_core, decimal_mul_10);
  tcase_add_test(tc_core, decimal_mul_11);
  tcase_add_test(tc_core, decimal_mul_12);
  tcase_add_test(tc_core, decimal_mul_13);
  tcase_add_test(tc_core, decimal_mul_14);
  tcase_add_test(tc_core, decimal_mul_16);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(s21_div_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_scale(&value_2, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(s21_div_both_neg) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);
  set_scale(&value_2, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_div_error) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 35;
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 1);
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);
  memset(&result, 0, sizeof(s21_decimal));
  res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(s21_div_normal2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_scale(&value_2, 1);
  int res = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_both_neg2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);
  set_scale(&value_2, 1);
  int res = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_error2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 35;
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 1);
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);

  memset(&result, 0, sizeof(s21_decimal));
  res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(part1_div_one_greater) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  s21_decimal test = {{20}};
  set_sign(&value_2, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(part1_div_one_greater2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  s21_decimal test = {{20}};
  set_sign(&value_1, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(part1_div_one_sign) {
  s21_decimal value_1 = {{150}};
  s21_decimal value_2 = {{50}};
  s21_decimal result = {0};
  s21_decimal test = {{100}};
  set_sign(&value_1, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  memset(&result, 0, sizeof(s21_decimal));
  int res = s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_sign) {
  s21_decimal value_1 = {{150}};
  s21_decimal value_2 = {{50}};
  s21_decimal result = {0};
  s21_decimal test = {{100}};
  set_sign(&value_1, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

Suite *suite_s21_div(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_div}-====\033[0m");
  tc_core = tcase_create("s21_div_Core");

  tcase_add_test(tc_core, s21_div_normal);
  tcase_add_test(tc_core, s21_div_both_neg);
  tcase_add_test(tc_core, s21_div_error);
  tcase_add_test(tc_core, s21_div_normal2);
  tcase_add_test(tc_core, s21_div_both_neg2);
  tcase_add_test(tc_core, s21_div_error2);
  tcase_add_test(tc_core, part1_div_one_greater);
  tcase_add_test(tc_core, part1_div_one_greater2);
  tcase_add_test(tc_core, part1_div_one_sign);
  tcase_add_test(tc_core, s21_div_sign);
  
  suite_add_tcase(s, tc_core);

  return s;
}