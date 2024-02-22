#ifndef CONVERTERS_H
#define CONVERTERS_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "arithm.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float num, s21_decimal *dec);
int s21_from_decimal_to_float(s21_decimal dec, float *num);

void s21_set_decimal_zero(s21_decimal *dst);
unsigned int s21_get_exp(s21_decimal src);
void normal_set_sign(s21_decimal *res);

unsigned int s21_set_mask(int index);

int s21_significant_count(unsigned int int_num);
s21_decimal from_char_to_decimal(char digit);
void s21_string_to_decimal(char *formated_float, s21_decimal *dec);

#endif