#ifndef _ARITHM_H
#define _ARITHM_H

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

int get_sign(s21_decimal src);
void set_sign(s21_decimal *src, int sign_value);
void set_scale(int src, s21_decimal *dst);
int get_scale(s21_decimal src);
int get_bit(const s21_decimal src, int n);
void set_bit(s21_decimal *src, int n, int sign_value);
void shift_left_decimal(s21_decimal *src);
void shift_right_decimal(s21_decimal *src);
void initialize_decimal(s21_decimal *src);
int get_bit_int(const int src, int n);
void degree_alignment(s21_decimal *d_a, s21_decimal *d_b);
void shift_left_bigdecimal(s21_big_decimal *src);
void set_bit_bigdecimal(s21_big_decimal *src, int n, int sign_value);
void initialize_bigdec(s21_big_decimal *src);
int get_bit_bigdecimal(const s21_big_decimal src, int n);
void shift_right_bigdecimal(s21_big_decimal *src);
void bank_rounding(s21_big_decimal *result, s21_big_decimal *temp);
int divid(s21_decimal d_a, s21_decimal d_b, s21_decimal *result);
int div_no_rounding(s21_decimal d_a, s21_decimal d_b, s21_decimal *result);
int divid_bigdec(s21_big_decimal d_a, s21_big_decimal d_b,
                 s21_big_decimal *result);
int mullt(s21_decimal a, s21_decimal b, s21_decimal *result);
int mullt_bigdec(s21_big_decimal a, s21_big_decimal b, s21_big_decimal *result);
int addit(s21_decimal a, s21_decimal b, s21_decimal *result);
int func_for_sub(s21_decimal a, s21_decimal b, s21_decimal *result);
int addit_bigdec(s21_big_decimal a, s21_big_decimal b, s21_big_decimal *result);
int subt(s21_decimal a, s21_decimal b, s21_decimal *result);
int subt_bigdec(s21_big_decimal a, s21_big_decimal b, s21_big_decimal *result);
int s21_is_less_simple(s21_decimal a, s21_decimal b);
int s21_is_not_equal_bigdec(s21_big_decimal a, s21_big_decimal b);
int s21_is_less_bigdec(s21_big_decimal a, s21_big_decimal b);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int equal_arithm(s21_decimal a, s21_decimal b);
#endif
