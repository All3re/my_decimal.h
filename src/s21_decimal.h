#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#define MAXBITE 0xffffffff
#define MINUS 0x80000000
#define SC 0x00ff0000
#define NM 0x0f00ffff
#include <stdint.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[16];
} s21_big_decimal;

typedef struct {
  uint64_t bits[7];
  uint16_t scale;
  uint32_t sign;
} work_decimal;

work_decimal converte_to_extended(s21_decimal *a);
void converte_to_base(s21_decimal *a, work_decimal *b);

int s21_negate(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
uint64_t pointright(work_decimal *a);
void getoverflow(work_decimal *dec);
void pointleft(work_decimal *dec);
void get_zero_decimal(s21_decimal *a);
int check_dec(s21_decimal dec);
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);
#endif
