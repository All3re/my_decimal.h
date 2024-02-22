#define SCALE_MASK 0b11111111 << 16
#define MAX_FLOAT_TO_CONVERT 79228162514264337593543950335.0
#define MIN_FLOAT_TO_CONVERT \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f

#include "converters.h"

#include "arithm.h"

unsigned int s21_set_mask(int index) { return 1u << (index % 32); }

int s21_significant_count(unsigned int int_num) {
  int count = 0;
  while (int_num > 0) {
    int_num /= 10;
    count++;
  }
  return count;
}

void s21_set_decimal_zero(s21_decimal *dst) {
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
}

int s21_get_scale_from_string(char *formated_float) {
  int scale = 0;
  char *ptr = formated_float;
  while (ptr) {
    if (*ptr == 'E') {
      ptr++;
      scale = strtol(ptr, NULL, 10);
      break;
    }
    ptr++;
  }
  // for (; formated_float[i] != '\0'; i++) {
  //   scale = scale * 10 + (formated_float[i] - 48);
  // }
  // if (formated_float[9] == '-' || formated_float[10] == '-') {
  //   scale = -scale;
  // }

  return scale;
}

unsigned int s21_get_exp(s21_decimal src) {
  return (src.bits[3] & SCALE_MASK) >> 16;
}

int is_decimal_correct(s21_decimal src) {
  int exit_code = 1;
  for (int i = 0; i <= 15 || (i >= 24 && i <= 30); i++) {
    if (src.bits[3] & (1 << (i))) {
      exit_code = 0;
    }
  }
  return exit_code;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_set_decimal_zero(dst);
  int exit_code = 0;
  if (!dst || src > INT_MAX || src < INT_MIN) {
    exit_code = 1;
  } else {
    unsigned int sign;
    unsigned int unsigned_src;
    if (src < 0) {
      sign = 1u;
      if (src != INT_MIN) {
        unsigned_src = -src;
      } else {
        unsigned_src = (unsigned int)INT_MAX + 1u;
      }
    } else {
      sign = 0u;
      unsigned_src = src;
    }
    dst->bits[0] = unsigned_src;
    set_sign(dst, sign);
  }
  return exit_code;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  *dst = 0;
  int sign = get_sign(src);
  int exp = s21_get_exp(src);
  s21_decimal src_buff;
  if (exp > 28) {
    return 1;
  }
  initialize_decimal(&src_buff);
  src_buff.bits[0] = src.bits[0];
  src_buff.bits[1] = src.bits[1];
  src_buff.bits[2] = src.bits[2];
  src_buff.bits[3] = src.bits[3];
  if ((exp > 0) && ((src.bits[1] != 0) || (src.bits[2] != 0))) {
    int k = 0;
    s21_decimal d_multiplier;
    initialize_decimal(&d_multiplier);
    d_multiplier.bits[0] = 10;
    while (((src_buff.bits[1] != 0) || (src_buff.bits[2] != 0))) {
      div_no_rounding(src_buff, d_multiplier, &src_buff);
      exp--;
      set_scale(exp, &src_buff);
      k++;
      if (exp < 0) {
        return 1;
      }
      k = k;
    }
  }
  if (src_buff.bits[1] != 0 || src_buff.bits[2] != 0 || src.bits[0] > INT_MAX ||
      is_decimal_correct(src_buff) == 0) {
    return 1;
  }
  unsigned int result = src_buff.bits[0];
  exp = get_scale(src_buff);
  result /= pow(10, exp);
  if (sign == 1) {
    result = -result;
  }
  *dst = (unsigned int)result;
  return 0;
}

s21_decimal from_char_to_decimal(char digit) {
  s21_decimal dec;
  s21_set_decimal_zero(&dec);

  switch (digit) {
    case '0':
      s21_from_int_to_decimal(0, &dec);
      break;
    case '1':
      s21_from_int_to_decimal(1, &dec);
      break;
    case '2':
      s21_from_int_to_decimal(2, &dec);
      break;
    case '3':
      s21_from_int_to_decimal(3, &dec);
      break;
    case '4':
      s21_from_int_to_decimal(4, &dec);
      break;
    case '5':
      s21_from_int_to_decimal(5, &dec);
      break;
    case '6':
      s21_from_int_to_decimal(6, &dec);
      break;
    case '7':
      s21_from_int_to_decimal(7, &dec);
      break;
    case '8':
      s21_from_int_to_decimal(8, &dec);
      break;
    case '9':
      s21_from_int_to_decimal(9, &dec);
      break;
  }
  return dec;
}

void s21_string_to_decimal(char *formated_float, s21_decimal *dec) {
  int scale = s21_get_scale_from_string(formated_float);
  s21_decimal result = {0};
  s21_decimal ten = {{10, 0, 0, 0}};
  int max_scale = 28;
  int i;
  i = formated_float[0] == '-' ? 1 : 0;
  result = from_char_to_decimal(formated_float[i]);
  for (i = formated_float[i + 1] == '.' ? i + 2 : i + 1;
       formated_float[i] != 'E'; i++) {
    s21_mul(result, ten, &result);
    s21_add(result, from_char_to_decimal(formated_float[i]), &result);
  }
  scale -= 6;
  if (scale > 0) {
    while (scale > 0) {
      s21_mul(result, ten, &result);
      scale--;
    }
  } else if (scale < 0) {
    while (scale < 0 && result.bits[0] % 10 == 0) {
      result.bits[0] /= 10;
      max_scale--;
      scale++;
    }
    if (scale <= -28) {
      scale = max_scale;
    }
    set_scale(abs(scale), &result);
  }
  *dec = result;
}

int s21_from_float_to_decimal(float num, s21_decimal *dec) {
  if (dec) {
    s21_set_decimal_zero(dec);
  }
  int exit_code = 0;
  if (!dec) {
    exit_code = 1;
  } else if (fabsf(num) > MAX_FLOAT_TO_CONVERT) {
    exit_code = 1;
  } else if (fabsf(num) < MIN_FLOAT_TO_CONVERT && fabsf(num) != 0.0) {
    exit_code = 1;
  } else if (isnan(num) || isinf(num)) {
    exit_code = 1;
  } else if (num == 0.0) {
    s21_set_decimal_zero(dec);
    if (*(unsigned int *)&num & (1 << 31)) {
      set_sign(dec, 1);
    }
  } else {
    s21_set_decimal_zero(dec);
    char formated[30];
    sprintf(formated, "%.6E", num);

    int scale = s21_get_scale_from_string(formated);

    if (scale <= -23) {
      int new_scale = scale + 28;
      sprintf(formated, "%.*E", new_scale, fabsf(num));
    }
    s21_string_to_decimal(formated, dec);
    if (num < 0) {
      set_sign(dec, 1);
    }
  }
  return exit_code;
}

int s21_is_set_bit(int number, int index) { return !!(number & (1U << index)); }

int s21_decimal_is_set_bit(s21_decimal decimal, int index) {
  return s21_is_set_bit(decimal.bits[index / 32], index % 32);
}

int s21_from_decimal_to_float(s21_decimal dec, float *num) {
  int exit_code = 0;
  int scale = s21_get_exp(dec);
  if (!(num) || scale > 28 || !is_decimal_correct(dec)) {
    exit_code = 1;
  } else {
    *num = 0.0;
    double tmp = 0.0;
    int sign = get_sign(dec);
    int power = s21_get_exp(dec);

    for (int i = 0; i < 96; i++) {
      if (s21_decimal_is_set_bit(dec, i) != 0) {
        tmp += pow(2.0, i);
      }
    }

    double powerten = pow(10, power);
    tmp /= powerten;

    if (sign == 1) {
      tmp *= -1.0;
    }
    *num = (float)tmp;
  }

  return exit_code;
}
