#include "s21_decimal.h"

#include "arithm.h"

work_decimal converte_to_extended(s21_decimal *a) {
  work_decimal decimal;
  for (int i = 0; i < 3; i++) {
    decimal.bits[i] = a->bits[i] & MAXBITE;
  }
  for (int i = 3; i < 7; i++) {
    decimal.bits[i] = 0;
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

void getoverflow(work_decimal *dec) {
  int overflow = 0;
  for (int i = 0; i < 7; i++) {
    dec->bits[i] += overflow;
    overflow = dec->bits[i] >> 32;
    dec->bits[i] &= MAXBITE;
  }
}

void pointleft(work_decimal *dec) {
  for (int i = 0; i < 7; i++) {
    dec->bits[i] *= 10;
  }
  getoverflow(dec);
  dec->scale++;
}

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int result = 1;

  int scale1 = (num1.bits[3] & SC) >> 16;
  int scale2 = (num2.bits[3] & SC) >> 16;
  int sign1 = get_sign(num1);
  int sign2 = get_sign(num2);
  work_decimal numw1 = converte_to_extended(&num1);
  numw1.scale = scale1;
  work_decimal numw2 = converte_to_extended(&num2);
  numw2.scale = scale2;
  if (sign1 == sign2) {
    if (scale1 > scale2) {
      while (numw1.scale != numw2.scale) {
        pointleft(&numw2);
      }
    } else if (scale1 < scale2) {
      while (numw1.scale != numw2.scale) {
        pointleft(&numw1);
      }
    }
    for (int i = 0; i < 7; i++) {
      if (numw1.bits[i] != numw2.bits[i]) {
        result = 0;
      }
    }
  } else {
    result = 0;
    if (numw1.bits[0] == 0 && numw2.bits[0] == 0 && numw1.bits[1] == 0 &&
        numw2.bits[1] == 0 && numw1.bits[2] == 0 && numw2.bits[2] == 0 &&
        numw2.bits[3] == 0 && numw1.bits[3] == 0 && numw2.bits[4] == 0 &&
        numw2.bits[4] == 0 && numw1.bits[5] == 0 && numw2.bits[5] == 0) {
      result = 1;
    }
  }

  return result;
}

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  int result = 1;

  int scale1 = (num1.bits[3] & SC) >> 16;
  int scale2 = (num2.bits[3] & SC) >> 16;
  int sign1 = get_sign(num1);
  int sign2 = get_sign(num2);
  work_decimal numw1 = converte_to_extended(&num1);
  numw1.scale = scale1;
  work_decimal numw2 = converte_to_extended(&num2);
  numw2.scale = scale2;
  if (s21_is_equal(num1, num2) == 1) {
    return 0;
  }
  if (sign1 == sign2) {
    if (scale1 > scale2) {
      while (numw1.scale != numw2.scale) {
        pointleft(&numw2);
      }
    } else if (scale1 < scale2) {
      while (numw1.scale != numw2.scale) {
        pointleft(&numw1);
      }
    }
    result = 0;
    if (sign1 == 0) {
      for (int i = 6; i >= 0; i--) {
        if (numw2.bits[i] > numw1.bits[i]) {
          result = 1;
          break;
        }
        if (numw2.bits[i] < numw1.bits[i]) {
          break;
        }
      }
    } else {
      for (int i = 6; i >= 0; i--) {
        if (numw1.bits[i] > numw2.bits[i]) {
          result = 1;
          break;
        }
        if (numw2.bits[i] > numw1.bits[i]) {
          break;
        }
      }
    }
  } else {
    if (s21_is_equal(num1, num2) != 1) {
      if (sign1 < sign2) {
        result = 0;
      }
    } else
      result = 0;
  }

  return result;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int a = s21_is_equal(value_1, value_2);
  int b = s21_is_less(value_1, value_2);
  if (a == 1 || b == 1)
    return 1;
  else
    return 0;
}
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less_or_equal(value_1, value_2);
}
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less(value_1, value_2);
}
