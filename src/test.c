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
    char res1[1000] = "0 0 0 0";
    char res2[1000] = "0 0 0 1835008";
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

START_TEST(div_test_7) {
  s21_decimal dec1, dec2, result, orig;
  int diff = 9;
  initialize_decimal(&dec1);
  initialize_decimal(&dec2);
  initialize_decimal(&result);
  initialize_decimal(&orig);

  dec1.bits[3] = 0;
  dec1.bits[2] = 0;
  dec1.bits[1] = 1568954488;
  dec1.bits[0] = 1568954488;

  dec2.bits[3] = 0;
  dec2.bits[2] = 0;
  dec2.bits[1] = 0;
  dec2.bits[0] = 1;
  set_scale(2, &dec2);

  orig.bits[3] = 0;
  orig.bits[2] = 36;
  orig.bits[1] = 2276626180;
  orig.bits[0] = 2276626144;

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
  tcase_add_test(tc_core, div_test_7);
  tcase_add_test(tc_core, div_test_8);
  tcase_add_test(tc_core, div_test_9);
  tcase_add_test(tc_core, div_test_10);
  tcase_add_test(tc_core, div_test_11);
  tcase_add_test(tc_core, div_test_12);
  tcase_add_test(tc_core, div_test_13);
  
  suite_add_tcase(s, tc_core);

  return s;
}