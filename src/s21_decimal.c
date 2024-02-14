#include "s21_decimal.h"

#include "arithm.h"

work_decimal converte_to_extended(s21_decimal *a) {
  work_decimal decimal;
  for (int i = 0; i < 3; i++) {
    decimal.bits[i] = a->bits[i] & MAXBITE;
  }
  decimal.scale = (a->bits[3] & SC) >> 16;
  decimal.sign = get_sign(*a);
  return decimal;
}

void converte_to_base(s21_decimal *a, work_decimal *b) {
  for (int i = 0; i < 3; i++) {
    a->bits[i] = b->bits[i] & MAXBITE;
  }
  a->bits[3] |= (b->sign << 31);
  a->bits[3] |= (b->scale << 16) & SC;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (!result) {
    error = 1;
  } else {
    if (check_dec(value) == 1) {
      error = 1;
    } else {
      *result = value;
      result->bits[3] ^= MINUS;
    }
  }
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (!result) {
    error = 1;
  } else {
    if (check_dec(value) == 1) {
      error = 1;
    } else {
      work_decimal decimal = converte_to_extended(&value);
      get_zero_decimal(result);
      for (; decimal.scale != 0;) {
        pointright(&decimal);
      }
      converte_to_base(result, &decimal);
    }
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (!result) {
    error = 1;
  } else {
    if (check_dec(value) == 1) {
      error = 1;
    } else {
      work_decimal decimal = converte_to_extended(&value);
      int flag = 0;
      uint64_t remainder = 0;
      get_zero_decimal(result);
      for (; decimal.scale != 0;) {
        if ((remainder = pointright(&decimal)) != 0 && decimal.scale > 1) {
          flag = 1;
        }
      }
      if (remainder == 5 && flag == 0) {
        if ((decimal.bits[0] % 2) != 0) {
          decimal.bits[0] += 1;
        }
      } else if (remainder == 5 && flag == 1) {
        decimal.bits[0] += 1;
      }
      converte_to_base(result, &decimal);
    }
  }
  return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (!result) {
    error = 1;
  } else {
    if (check_dec(value) == 1) {
      error = 1;
    } else {
      work_decimal decimal = converte_to_extended(&value);
      int flag = 0;
      uint64_t remainder = 0;
      get_zero_decimal(result);
      for (; decimal.scale != 0;) {
        if ((remainder = pointright(&decimal)) != 0) {
          flag = 1;
        }
      }
      if ((remainder > 0 && decimal.sign == 1) ||
          (flag == 1 && decimal.sign == 1)) {
        decimal.bits[0] += 1;
      }
      converte_to_base(result, &decimal);
    }
  }
  return error;
}

uint64_t pointright(work_decimal *a) {
  uint64_t remainder = 0;
  for (int i = 2; i >= 0; i--) {
    a->bits[i] += remainder << 32;
    remainder = a->bits[i] % 10;
    a->bits[i] /= 10;
  }
  a->scale--;
  return remainder;
}

void get_zero_decimal(s21_decimal *a) {
  a->bits[0] = 0;
  a->bits[1] = 0;
  a->bits[2] = 0;
  a->bits[3] = 0;
}

int check_dec(s21_decimal dec) {
  int check = 0;
  if ((dec.bits[3] & NM) != 0 || ((dec.bits[3] & SC) >> 16) > 28) {
    check = 1;
  }
  return check;
}

int compareInt(unsigned int a, unsigned int b) {
  return a > b ? 1 : (a < b ? -1 : 0);
}

int decimal_compare(s21_decimal num1, s21_decimal num2) {
  int sign1 = (num1.bits[3] >> 31) & 1;
  int sign2 = (num2.bits[3] >> 31) & 1;

  if (sign1 != sign2) {
    return sign1 ? -1 : 1;
  }

  unsigned long long int1 =
      ((unsigned long long)num1.bits[2] << 32) | num1.bits[1];
  unsigned long long int2 =
      ((unsigned long long)num2.bits[2] << 32) | num2.bits[1];

  unsigned long long frac1 =
      ((unsigned long long)num1.bits[0] << 32) | num1.bits[0];
  unsigned long long frac2 =
      ((unsigned long long)num2.bits[0] << 32) | num2.bits[0];

  int scale1 = (num1.bits[3] >> 16) & 0xFF;
  int scale2 = (num2.bits[3] >> 16) & 0xFF;

  if (scale1 > scale2) {
    frac2 *= (unsigned long long)pow(10, scale1 - scale2);
  } else if (scale2 > scale1) {
    frac1 *= (unsigned long long)pow(10, scale2 - scale1);
  }

  unsigned long long num1_val =
      int1 * (unsigned long long)pow(10, scale1) + frac1;
  unsigned long long num2_val =
      int2 * (unsigned long long)pow(10, scale2) + frac2;

  return (sign1 ? -compareInt(num1_val, num2_val)
                : compareInt(num1_val, num2_val));
}

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  return decimal_compare(num1, num2) == 0;
}

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  return decimal_compare(num1, num2) < 0;
}

int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  return decimal_compare(num1, num2) <= 0;
}

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  return !s21_is_equal(num1, num2);
}

int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  return decimal_compare(num1, num2) >= 0;
}

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  return decimal_compare(num1, num2) > 0;
}