#include "arithm.h"

int get_sign(s21_decimal src) {
  int result = get_bit(src, 127);
  return result;
}

void set_sign(s21_decimal *src, int sign_value) {
  set_bit(src, 127, sign_value);
}

void set_scale(int src, s21_decimal *dst) {
  for (int i = 112; i <= 119; i++) {
    if (get_bit_int(src, i - 112) == 1) {
      set_bit(dst, i, 1);
    } else {
      set_bit(dst, i, 0);
    }
  }
}

int get_scale(s21_decimal src) {
  int result = 0;
  for (int i = 112; i <= 119; i++) {
    if (get_bit(src, i) == 1) {
      result = (result | (1 << (i - 112)));
    } else {
      result = (result & ~(1 << (i - 112)));
    }
  }
  if (result > 28) {
    result = 28;
  }
  return result;
}

int get_bit(const s21_decimal src, int n) {
  int result = 0;
  if (((src.bits[n / 32] & (1 << (n % 32))) != 0)) {
    result = 1;
  }
  return result;
}

void set_bit(s21_decimal *src, int n, int sign_value) {
  if (sign_value == 1) {
    src->bits[n / 32] = (src->bits[n / 32] | (1 << (n % 32)));
  } else {
    src->bits[n / 32] = (src->bits[n / 32] & ~(1 << (n % 32)));
  }
}

void shift_left_decimal(s21_decimal *src) {
  for (int i = 95; i >= 0; i--) {
    set_bit(src, i + 1, get_bit(*src, i));
  }
  set_bit(src, 0, 0);
}

void shift_right_decimal(s21_decimal *src) {
  for (int i = 0; i <= 96; i++) {
    set_bit(src, i, get_bit(*src, i + 1));
  }
  set_bit(src, 96, 0);
}

void initialize_decimal(s21_decimal *src) {
  for (int i = 0; i < 128; i++) {
    set_bit(src, i, 0);
  }
}

int get_bit_int(const int src, int n) {
  int result = 0;
  if (((src & (1 << n)) != 0)) {
    result = 1;
  }
  return result;
}

void degree_alignment(s21_decimal *d_a, s21_decimal *d_b) {
  int scale_a = get_scale(*d_a);
  int scale_b = get_scale(*d_b);
  set_scale(0, d_a);
  set_scale(0, d_b);
  int sign_a = get_sign(*d_a);
  int sign_b = get_sign(*d_b);
  int multiplier = 10;
  s21_decimal d_multiplier;
  initialize_decimal(&d_multiplier);
  s21_from_int_to_decimal(multiplier, &d_multiplier);
  while (scale_a > scale_b) {
    if ((get_bit(*d_b, 95) == 0) && (get_bit(*d_b, 94) == 0) &&
        (get_bit(*d_b, 93) == 0) && (get_bit(*d_b, 92) == 0)) {
      mullt(*d_b, d_multiplier, d_b);
      scale_b++;
    } else {
      divid(*d_a, d_multiplier, d_a);
      scale_a--;
    }
  }
  while (scale_a < scale_b) {
    if ((get_bit(*d_a, 95) == 0) && (get_bit(*d_a, 94) == 0) &&
        (get_bit(*d_a, 93) == 0) && (get_bit(*d_a, 92) == 0)) {
      mullt(*d_a, d_multiplier, d_a);
      scale_a++;
    } else {
      divid(*d_b, d_multiplier, d_b);
      scale_b--;
    }
  }
  set_scale(scale_a, d_a);
  set_scale(scale_b, d_b);
  set_sign(d_a, sign_a);
  set_sign(d_b, sign_b);
}

void shift_left_bigdecimal(s21_big_decimal *src) {
  for (int i = 510; i >= 0; i--) {
    set_bit_bigdecimal(src, i + 1, get_bit_bigdecimal(*src, i));
  }
  set_bit_bigdecimal(src, 0, 0);
}

void set_bit_bigdecimal(s21_big_decimal *src, int n, int sign_value) {
  if (sign_value == 1) {
    src->bits[n / 32] = (src->bits[n / 32] | (1 << (n % 32)));
  } else {
    src->bits[n / 32] = (src->bits[n / 32] & ~(1 << (n % 32)));
  }
}

void initialize_bigdec(s21_big_decimal *src) {
  for (int i = 0; i < 512; i++) {
    set_bit_bigdecimal(src, i, 0);
  }
}

int get_bit_bigdecimal(const s21_big_decimal src, int n) {
  int result = 0;
  if (((src.bits[n / 32] & (1 << (n % 32))) != 0)) {
    result = 1;
  }
  return result;
}

void shift_right_bigdecimal(s21_big_decimal *src) {
  for (int i = 0; i < 511; i++) {
    set_bit_bigdecimal(src, i, get_bit_bigdecimal(*src, i + 1));
  }
  set_bit_bigdecimal(src, 511, 0);
}

void bank_rounding(s21_big_decimal *result, s21_big_decimal *temp) {
  s21_big_decimal multiplier;
  initialize_bigdec(&multiplier);
  multiplier.bits[0] = 10;
  s21_big_decimal result_buff;
  initialize_bigdec(&result_buff);
  mullt_bigdec(*result, multiplier, &result_buff);
  subt_bigdec(*temp, result_buff, temp);
  initialize_bigdec(&result_buff);
  result_buff.bits[0] = 1;

  if (temp->bits[0] > 5) {
    addit_bigdec(*result, result_buff, result);
  }
  if (temp->bits[0] == 5) {
    result_buff = *result;
    divid_bigdec(result_buff, multiplier, &result_buff);
    mullt_bigdec(result_buff, multiplier, &result_buff);
    subt_bigdec(*result, result_buff, temp);
    if (temp->bits[0] % 2 != 0) {
      initialize_bigdec(&result_buff);
      result_buff.bits[0] = 1;
      addit_bigdec(*result, result_buff, result);
    }
  }
}

int divid(s21_decimal d_a, s21_decimal d_b, s21_decimal *result) {
  initialize_decimal(result);
  int sign_a = get_sign(d_a);
  int sign_b = get_sign(d_b);
  set_sign(&d_a, 0);
  set_sign(&d_b, 0);
  s21_decimal d_buff_1;
  initialize_decimal(&d_buff_1);
  d_buff_1.bits[0] = d_a.bits[0];
  d_buff_1.bits[1] = d_a.bits[1];
  d_buff_1.bits[2] = d_a.bits[2];
  d_buff_1.bits[3] = d_a.bits[3];
  initialize_decimal(result);
  s21_decimal zero;
  initialize_decimal(&zero);
  int max_bit_a = 0;
  int max_bit_b = 0;
  for (int i = 0; i < 96; i++) {
    if (get_bit(d_a, i) == 1) {
      max_bit_a = i;
    }
    if (get_bit(d_b, i) == 1) {
      max_bit_b = i;
    }
  }
  int k = max_bit_b;
  for (int i = 0; i < max_bit_a - max_bit_b; i++) {
    shift_left_decimal(&d_b);
  }
  if (s21_is_less_simple(d_a, d_b)) {
    shift_right_decimal(&d_b);
    k++;
  }
  while (k <= max_bit_a) {
    if (s21_is_not_equal(d_a, zero)) {
      subt(d_a, d_b, &d_a);
      if (s21_is_not_equal(*result, zero)) {
        shift_left_decimal(result);
        set_bit(result, 0, 1);
      } else {
        set_bit(result, 0, 1);
      }
    }
    shift_left_decimal(&d_a);
    k++;

    while (s21_is_less_simple(d_a, d_b) && (k <= max_bit_a)) {
      if (get_bit(d_a, 95) != 1) {
        shift_left_decimal(&d_a);
        shift_left_decimal(result);
      } else {
        shift_right_decimal(&d_b);
        shift_left_decimal(result);
      }
      k++;
    }
  }
  s21_decimal d_buff_2;
  initialize_decimal(&d_buff_2);
  d_buff_2 = *result;
  s21_decimal temp;
  initialize_decimal(&temp);
  temp.bits[0] = 10;
  mullt(d_buff_2, temp, &d_buff_2);
  s21_decimal tmp;
  initialize_decimal(&tmp);
  subt(d_buff_1, d_buff_2, &tmp);
  if (tmp.bits[0] > 5) {
    initialize_decimal(&d_buff_2);
    d_buff_2.bits[0] = 1;
    addit(d_buff_2, *result, result);
  }
  if (tmp.bits[0] == 5) {
    div_no_rounding(d_buff_2, temp, &d_buff_2);
    div_no_rounding(d_buff_2, temp, &d_buff_2);
    mullt(d_buff_2, temp, &d_buff_2);
    mullt(d_buff_2, temp, &d_buff_2);
    subt(d_buff_1, d_buff_2, &d_buff_1);
    subt(d_buff_1, tmp, &d_buff_1);
    div_no_rounding(d_buff_1, temp, &d_buff_1);
    if (d_buff_1.bits[0] % 2 != 0) {
      initialize_decimal(&d_buff_2);
      d_buff_2.bits[0] = 1;
      addit(d_buff_2, *result, result);
    }
  }
  if (sign_a != sign_b) {
    set_sign(result, 1);
  }
  return 0;
}

int div_no_rounding(s21_decimal d_a, s21_decimal d_b,
                               s21_decimal *result) {
  initialize_decimal(result);
  int sign_a = get_sign(d_a);
  int sign_b = get_sign(d_b);
  set_sign(&d_a, 0);
  set_sign(&d_b, 0);
  initialize_decimal(result);
  s21_decimal zero;
  initialize_decimal(&zero);
  int max_bit_a = 0;
  int max_bit_b = 0;
  for (int i = 0; i < 96; i++) {
    if (get_bit(d_a, i) == 1) {
      max_bit_a = i;
    }
    if (get_bit(d_b, i) == 1) {
      max_bit_b = i;
    }
  }
  int k = max_bit_b;
  for (int i = 0; i < max_bit_a - max_bit_b; i++) {
    shift_left_decimal(&d_b);
  }
  if (s21_is_less_simple(d_a, d_b)) {
    shift_right_decimal(&d_b);
    k++;
  }
  while (k <= max_bit_a) {
    if (s21_is_not_equal(d_a, zero)) {
      subt(d_a, d_b, &d_a);
      if (s21_is_not_equal(*result, zero)) {
        shift_left_decimal(result);
        set_bit(result, 0, 1);
      } else {
        set_bit(result, 0, 1);
      }
    }
    shift_left_decimal(&d_a);
    k++;

    while (s21_is_less_simple(d_a, d_b) && (k <= max_bit_a)) {
      if (get_bit(d_a, 95) != 1) {
        shift_left_decimal(&d_a);
        shift_left_decimal(result);
      } else {
        shift_right_decimal(&d_b);
        shift_left_decimal(result);
      }
      k++;
    }
  }

  if (sign_a != sign_b) {
    set_sign(result, 1);
  }
  return 0;
}

int divid_bigdec(s21_big_decimal d_a, s21_big_decimal d_b, s21_big_decimal *result) {
  initialize_bigdec(result);
  s21_big_decimal zero;
  initialize_bigdec(&zero);
  int max_bit_a = 0;
  int max_bit_b = 0;
  for (int i = 0; i < 512; i++) {
    if (get_bit_bigdecimal(d_a, i) == 1) {
      max_bit_a = i;
    }
    if (get_bit_bigdecimal(d_b, i) == 1) {
      max_bit_b = i;
    }
  }
  int k = max_bit_b;
  for (int i = 0; i < max_bit_a - max_bit_b; i++) {
    shift_left_bigdecimal(&d_b);
  }
  if (s21_is_less_bigdec(
          d_a, d_b)) {
    shift_right_bigdecimal(&d_b);
    k++;
  }
  s21_big_decimal d_buff_1;
  initialize_bigdec(&d_buff_1);
  s21_big_decimal d_buff_2;
  initialize_bigdec(&d_buff_2);
  while (k <= max_bit_a) {
    if (s21_is_not_equal_bigdec(d_a, zero)) {
      subt_bigdec(d_a, d_b, &d_a);
      if (s21_is_not_equal_bigdec(*result, zero)) {
        shift_left_bigdecimal(result);
        set_bit_bigdecimal(result, 0, 1);
      } else {
        set_bit_bigdecimal(result, 0, 1);
      }
    }
    shift_left_bigdecimal(&d_a);
    k++;

    while (s21_is_less_bigdec(d_a, d_b) && (k <= max_bit_a)) {
      shift_left_bigdecimal(&d_a);
      k++;
      shift_left_bigdecimal(result);
    }
  }
  return 0;
}

int mullt(s21_decimal a, s21_decimal b, s21_decimal *result) {
  initialize_decimal(result);
  for (int i = 0; i < 96; i++) {
    if (get_bit(b, i) == 1) {
      addit(*result, a, result);
    }
    shift_left_decimal(&a);
  }
  return 0;
}

int mullt_bigdec(s21_big_decimal a, s21_big_decimal b,
                            s21_big_decimal *result) {
  initialize_bigdec(result);
  for (int i = 0; i < 512; i++) {
    if (get_bit_bigdecimal(b, i) == 1) {
      addit_bigdec(*result, a, result);
    }
    shift_left_bigdecimal(&a);
  }
  return 0;
}

int addit(s21_decimal a, s21_decimal b, s21_decimal *result) {
  initialize_decimal(result);
  int temp = 0;
  for (int i = 0; i < 96; i++) {
    int res;
    res = get_bit(a, i) + get_bit(b, i) + temp;
    if (res == 3) {
      set_bit(result, i, 1);
      temp = 1;
    } else if (res == 2) {
      set_bit(result, i, 0);
      temp = 1;
    } else {
      set_bit(result, i, get_bit(a, i) + get_bit(b, i) + temp);
      temp = 0;
    }
    if ((i == 95) && (temp != 0)) {
      initialize_decimal(result);
      if (get_sign(a) == 0) {
        return 1;
      } else {
        return 2;
      }
    }
  }
  return 0;
}

int func_for_sub(s21_decimal a, s21_decimal b, s21_decimal *result) {
  initialize_decimal(result);
  int temp = 0;
  for (int i = 0; i < 96; i++) {
    int res;
    res = get_bit(a, i) + get_bit(b, i) + temp;
    if (res == 3) {
      set_bit(result, i, 1);
      temp = 1;
    } else if (res == 2) {
      set_bit(result, i, 0);
      temp = 1;
    } else {
      set_bit(result, i, get_bit(a, i) + get_bit(b, i) + temp);
      temp = 0;
    }
  }
  return 0;
}

int addit_bigdec(s21_big_decimal a, s21_big_decimal b,
                            s21_big_decimal *result) {
  initialize_bigdec(result);
  int temp = 0;
  for (int i = 0; i < 512; i++) {
    int res;
    res = get_bit_bigdecimal(a, i) + get_bit_bigdecimal(b, i) + temp;
    if (res == 3) {
      set_bit_bigdecimal(result, i, 1);
      temp = 1;
    } else if (res == 2) {
      set_bit_bigdecimal(result, i, 0);
      temp = 1;
    } else {
      set_bit_bigdecimal(
          result, i, get_bit_bigdecimal(a, i) + get_bit_bigdecimal(b, i) + temp);
      temp = 0;
    }
  }
  return 0;
}

int subt(s21_decimal a, s21_decimal b, s21_decimal *result) {
  initialize_decimal(result);
  s21_decimal buff;
  initialize_decimal(&buff);
  int sign = 0;
  if (s21_is_less_simple(a, b)) {
    buff = b;
    b = a;
    a = buff;
    sign = 1;
  }
  for (int i = 0; i < 3; i++) {
    b.bits[i] = ~(b.bits[i]);
  }
  s21_decimal tmp;
  initialize_decimal(&tmp);
  tmp.bits[0] = 1;
  addit(tmp, b, &b);
  func_for_sub(a, b, result);
  set_sign(result, sign);
  return 0;
}

int subt_bigdec(s21_big_decimal a, s21_big_decimal b, s21_big_decimal *result) {
  initialize_bigdec(result);
  s21_big_decimal buff;
  initialize_bigdec(&buff);
  for (int i = 0; i < 16; i++) {
    b.bits[i] = ~(b.bits[i]);
  }
  s21_big_decimal temp;
  initialize_bigdec(&temp);
  temp.bits[0] = 1;
  addit_bigdec(b, temp, &b);
  addit_bigdec(a, b, result);
  return 0;
}

int s21_is_less_simple(s21_decimal a, s21_decimal b) {
  int result = 0;
  s21_decimal d_a = a;
  s21_decimal d_b = b;
  if (get_sign(d_a) > get_sign(d_b)) {
    result = 1;
  } else {
    for (int i = 95; i >= 0; i--) {
      if (get_bit(d_a, i) < get_bit(d_b, i)) {
        result = 1;
        break;
      }
      if (get_bit(d_a, i) > get_bit(d_b, i)) {
        result = 0;
        break;
      }
    }
  }
  return result;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  initialize_decimal(result);
  int sign_a = get_sign(value_1);
  int sign_b = get_sign(value_2);
  int res = 0;
  s21_decimal d_a = value_1;
  s21_decimal d_b = value_2;
  degree_alignment(&d_a, &d_b);
  if (sign_a == sign_b) {
    res = addit(d_a, d_b, result);
    set_sign(result, get_sign(d_a));
  } else if (sign_b > sign_a) {
    set_sign(&d_b, 0);
    res = subt(d_a, d_b, result);
  } else {
    set_sign(&d_a, 0);
    res = subt(d_b, d_a, result);
  }
  set_scale(get_scale(d_a), result);
  return res;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  initialize_decimal(result);
  int res = 0;
  s21_decimal d_a;
  s21_decimal d_b;
  d_a = value_1;
  d_b = value_2;
  degree_alignment(&d_a, &d_b);
  int sign_a = get_sign(value_1);
  int sign_b = get_sign(value_2);
  if (sign_b > sign_a) {
    set_sign(&d_b, 0);
    res = addit(d_a, d_b, result);
  } else if (sign_a > sign_b) {
    res = addit(d_a, d_b, result);
    set_sign(result, 1);
  } else if (sign_a == 0) {
    res = subt(d_a, d_b, result);
  } else if (sign_a == 1) {
    res = subt(d_b, d_a, result);
  }
  set_scale(get_scale(d_a), result);
  return res;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  initialize_decimal(result);
  int sign_a = get_sign(value_1);
  int sign_b = get_sign(value_2);
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  int scale_a = get_scale(value_1);
  int scale_b = get_scale(value_2);
  set_scale(0, &value_1);
  set_scale(0, &value_2);
  s21_big_decimal zero_ex;
  initialize_bigdec(&zero_ex);
  s21_decimal zero;
  initialize_decimal(&zero);
  if (s21_is_equal(value_2, zero)) {
    return 3;
  }
  if (s21_is_equal(value_1, zero)) {
    initialize_decimal(result);
    return 0;
  }
  int max_bit_a = 0;
  int max_bit_b = 0;
  for (int i = 0; i < 96; i++) {
    if (get_bit(value_1, i) == 1) {
      max_bit_a = i;
    }
    if (get_bit(value_2, i) == 1) {
      max_bit_b = i;
    }
  }
  int k = 0;
  int is_less = 0;
  if (s21_is_less_simple(value_2, value_1)) {
    k = max_bit_b;
    for (int i = 0; i < max_bit_a - max_bit_b; i++) {
      shift_left_decimal(&value_2);
    }
    if (s21_is_less_simple(value_1, value_2)) {
      shift_right_decimal(&value_2);
      k++;
    }
  } else {
    is_less = 1;
    while (s21_is_less_simple(value_1, value_2)) {
      if (get_bit(value_1, 95) != 1) {
        shift_left_decimal(&value_1);
      } else {
        shift_right_decimal(&value_2);
      }
      k++;
    }
  }
  s21_big_decimal d_buff_1;
  initialize_bigdec(&d_buff_1);
  s21_big_decimal d_buff_2;
  initialize_bigdec(&d_buff_2);
  int param = 96 + k;
  while (k <= param) {
    if (s21_is_not_equal(value_1, zero)) {
      subt(value_1, value_2, &value_1);
      if (s21_is_not_equal_bigdec(d_buff_2, zero_ex)) {
        shift_left_bigdecimal(&d_buff_2);
        set_bit_bigdecimal(&d_buff_2, 0, 1);
      } else {
        set_bit_bigdecimal(&d_buff_2, 0, 1);
      }
      shift_left_decimal(&value_1);
      k++;
    }
    if (s21_is_equal(value_1, zero) && (k > max_bit_a)) {
      break;
    }
    while (s21_is_less_simple(value_1, value_2) && (k <= param)) {
      if (get_bit(value_1, 95) != 1) {
        shift_left_decimal(&value_1);
        shift_left_bigdecimal(&d_buff_2);
      } else {
        shift_right_decimal(&value_2);
        shift_left_bigdecimal(&d_buff_2);
      }
      k++;
    }
  }
  int fractional_part_max_index = 0;
  if (is_less) {
    fractional_part_max_index = k - 1;
  } else {
    fractional_part_max_index = k - max_bit_a - 1;
  }
  if (fractional_part_max_index + scale_a - scale_b < 200) {
    int scale = 0;
    if (fractional_part_max_index > 0) {
      s21_big_decimal temp_ext;
      initialize_bigdec(&temp_ext);
      temp_ext = d_buff_2;
      d_buff_1.bits[0] = 5;
      for (int i = 0; i < fractional_part_max_index; i++) {
        mullt_bigdec(d_buff_2, d_buff_1, &d_buff_2);
      }
      initialize_bigdec(&d_buff_1);
      d_buff_1.bits[0] = 10;
      s21_big_decimal d_buff_4;
      initialize_bigdec(&d_buff_4);
      int a = 0;
      while ((d_buff_2.bits[3] != 0) || (d_buff_2.bits[4] != 0) ||
             (d_buff_2.bits[5] != 0) || (d_buff_2.bits[6] != 0) ||
             (d_buff_2.bits[7] != 0) || (d_buff_2.bits[8] != 0) ||
             (d_buff_2.bits[9] != 0) || (d_buff_2.bits[10] != 0)) {
        d_buff_4 = d_buff_2;
        divid_bigdec(d_buff_2, d_buff_1, &d_buff_2);
        a++;
      }
      s21_big_decimal d_buff_3;
      initialize_bigdec(&d_buff_3);
      mullt_bigdec(d_buff_2, d_buff_1, &d_buff_3);
      subt_bigdec(d_buff_4, d_buff_3, &d_buff_3);
      scale = fractional_part_max_index - a + scale_a - scale_b;
    } else {
      scale = scale_a - scale_b;
    }
    s21_big_decimal d_buff_3;
    initialize_bigdec(&d_buff_3);
    d_buff_3.bits[0] = 10;
    while (scale < 0) {
      if ((get_bit_bigdecimal(d_buff_2, 95) == 0) &&
          (get_bit_bigdecimal(d_buff_2, 94) == 0) &&
          (get_bit_bigdecimal(d_buff_2, 93) == 0) &&
          (get_bit_bigdecimal(d_buff_2, 92) == 0)) {
        mullt_bigdec(d_buff_2, d_buff_3, &d_buff_2);
        scale++;
      } else {
        if (sign_a == sign_b) {
          return 1;
        } else {
          return 2;
        }
      }
    }
    result->bits[0] = d_buff_2.bits[0];
    result->bits[1] = d_buff_2.bits[1];
    result->bits[2] = d_buff_2.bits[2];
    result->bits[3] = d_buff_2.bits[3];
    while (scale > 28) {
      s21_decimal temp;
      initialize_decimal(&temp);
      temp.bits[0] = 10;
      divid(*result, temp, result);
      scale--;
    }
    set_scale(scale, result);
    if (sign_a == sign_b) {
      set_sign(result, 0);
    } else {
      set_sign(result, 1);
    }
  } else {
    initialize_decimal(result);
  }
  return 0;
}

int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result) {
  initialize_decimal(result);
  int sign = 0;
  if (get_sign(a) == get_sign(b)) {
    sign = 0;
  } else {
    sign = 1;
  }
  int scale = get_scale(a) + get_scale(b);
  int res = 0;
  s21_big_decimal result_ext;
  s21_big_decimal a_ext;
  s21_big_decimal b_ext;
  initialize_bigdec(&result_ext);
  initialize_bigdec(&a_ext);
  initialize_bigdec(&b_ext);
  a_ext.bits[0] = a.bits[0];
  a_ext.bits[1] = a.bits[1];
  a_ext.bits[2] = a.bits[2];
  b_ext.bits[0] = b.bits[0];
  b_ext.bits[1] = b.bits[1];
  b_ext.bits[2] = b.bits[2];
  for (int i = 0; i < 96; i++) {
    if (get_bit_bigdecimal(b_ext, i) == 1) {
      addit_bigdec(result_ext, a_ext, &result_ext);
    }
    shift_left_bigdecimal(&a_ext);
  }
  s21_big_decimal multiplier;
  initialize_bigdec(&multiplier);
  multiplier.bits[0] = 10;
  s21_big_decimal temp;
  initialize_bigdec(&temp);
  s21_big_decimal result_buff;
  initialize_bigdec(&result_buff);
  if ((result_ext.bits[3] != 0) || (result_ext.bits[4] != 0) ||
      (result_ext.bits[5] != 0) || (result_ext.bits[6] != 0) ||
      (result_ext.bits[7] != 0) || (result_ext.bits[8] != 0) ||
      (result_ext.bits[9] != 0) || (result_ext.bits[10] != 0)) {
    while ((result_ext.bits[3] != 0) || (result_ext.bits[4] != 0) ||
           (result_ext.bits[5] != 0) || (result_ext.bits[6] != 0) ||
           (result_ext.bits[7] != 0) || (result_ext.bits[8] != 0) ||
           (result_ext.bits[9] != 0) || (result_ext.bits[10] != 0)) {
      temp = result_ext;
      divid_bigdec(result_ext, multiplier, &result_ext);
      scale--;
      if (scale < 0) {
        if (sign == 1) {
          res = 2;
        } else {
          res = 1;
        }
      }
    }
    bank_rounding(&result_ext, &temp);
  }
  if (scale > 28) {
    while (scale > 28) {
      temp = result_ext;
      divid_bigdec(result_ext, multiplier, &result_ext);
      scale--;
    }
    bank_rounding(&result_ext, &temp);
  }
  result->bits[0] = result_ext.bits[0];
  result->bits[1] = result_ext.bits[1];
  result->bits[2] = result_ext.bits[2];

  set_sign(result, sign);
  set_scale(scale, result);
  return res;
}

int s21_is_less_bigdec(s21_big_decimal a,
                                s21_big_decimal b) {
  int result = 0;
  s21_big_decimal d_a = a;
  s21_big_decimal d_b = b;
  for (int i = 511; i >= 0; i--) {
    if (get_bit_bigdecimal(d_a, i) < get_bit_bigdecimal(d_b, i)) {
      result = 1;
      break;
    }
    if (get_bit_bigdecimal(d_a, i) > get_bit_bigdecimal(d_b, i)) {
      result = 0;
      break;
    }
  }

  return result;
}

int s21_is_not_equal_bigdec(s21_big_decimal a, s21_big_decimal b) {
  int result = 0;
  s21_big_decimal d_a = a;
  s21_big_decimal d_b = b;
  for (int i = 511; i >= 0; i--) {
    if (get_bit_bigdecimal(d_a, i) != get_bit_bigdecimal(d_b, i)) {
      result = 1;
      break;
    }
  }

  return result;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) { // надо было не мое
  int result = 0;
  s21_decimal d_a = a;
  s21_decimal d_b = b;
  degree_alignment(&d_a, &d_b);
  if (get_sign(d_a) != get_sign(d_b)) {
    result = 1;
  } else {
    for (int i = 95; i >= 0; i--) {
      if (get_bit(d_a, i) != get_bit(d_b, i)) {
        result = 1;
        break;
      }
    }
  }
  if ((a.bits[0] == 0) && (a.bits[1] == 0) && (a.bits[2] == 0) &&
      (b.bits[0] == 0) && (b.bits[1] == 0) && (b.bits[2] == 0)) {
    result = 0;
  }
  return result;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) { // надо было не мое
  initialize_decimal(dst);
  if (src < 0) {
    set_sign(dst, 1);
    src = -src;
  }
  dst->bits[0] = src;
  return 0;
}

int s21_is_equal(s21_decimal a, s21_decimal b) { // надо было не мое
  int result = 1;
  s21_decimal d_a = a;
  s21_decimal d_b = b;
  degree_alignment(&d_a, &d_b);
  if (get_sign(d_a) != get_sign(d_b)) {
    result = 0;
  } else {
    for (int i = 95; i >= 0; i--) {
      if (get_bit(d_a, i) != get_bit(d_b, i)) {
        result = 0;
        break;
      }
    }
  }
  if ((a.bits[0] == 0) && (a.bits[1] == 0) && (a.bits[2] == 0) &&
      (b.bits[0] == 0) && (b.bits[1] == 0) && (b.bits[2] == 0)) {
    result = 1;
  }
  return result;
}

int get_exp_from_float(float src) { // надо было не мое
  unsigned int buff = *(unsigned int *)&src;
  int scale = 0;
  int k = 0;
  for (unsigned int i = 8388608; i != 2147483648; i = i << 1) {
    if (!!(buff & i) == 1) {
      scale += pow(2, k);
    }
    k++;
  }
  scale = scale - 127;
  return scale;
}

int get_mantissa_min_index(float src) { // надо было не мое
  int mantissa_min_index = 0;
  int k = 0;
  unsigned int buff = *(unsigned int *)&src;
  for (unsigned int i = 1; i != 8388608; i = i << 1) {
    if (!!(buff & i) == 1) {
      mantissa_min_index = 23 - k;
      break;
    }
    k++;
  }
  return mantissa_min_index;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) { // надо было не мое
  initialize_decimal(dst);
  int scale = get_exp_from_float(src);
  int mantissa_min_index = -get_mantissa_min_index(src);
  if (scale > 95) {
    return 1;
  }
  if (scale < -94) {
    return 1;
  }
  s21_big_decimal d_buff_1;
  initialize_bigdec(&d_buff_1);
  int multiplier = 0;
  multiplier = scale + mantissa_min_index;
  s21_big_decimal mantissa_buffer;
  initialize_bigdec(&mantissa_buffer);
  mantissa_buffer.bits[0] = 1;
  for (int i = 0; i < scale - multiplier; i++) {
    shift_left_bigdecimal(&mantissa_buffer);
  }
  unsigned int j = 8388608;
  unsigned int buff = *(unsigned int *)&src;
  for (int i = -1; i >= -23; i--) {
    j = j >> 1;
    if (!!(buff & j) == 1) {
      d_buff_1.bits[0] = 1;
      for (int k = 0; k < i + scale - multiplier; k++) {
        shift_left_bigdecimal(&d_buff_1);
      }
      addit_bigdec(mantissa_buffer, d_buff_1, &mantissa_buffer);
      initialize_bigdec(&d_buff_1);
    }
  }
  initialize_bigdec(&d_buff_1);
  s21_big_decimal d_buff_2;
  initialize_bigdec(&d_buff_2);
  s21_decimal result;
  initialize_decimal(&result);
  /////////////////////////////////////////////////
  if (multiplier >= 0) {
    for (int i = 0; i < multiplier; i++) {
      shift_left_bigdecimal(&mantissa_buffer);
    }
    result.bits[0] = mantissa_buffer.bits[0];
    result.bits[1] = mantissa_buffer.bits[1];
    result.bits[2] = mantissa_buffer.bits[2];
    result.bits[3] = mantissa_buffer.bits[3];
    *dst = result;  ///////////////////////
  } else {
    d_buff_2 = mantissa_buffer;
    initialize_bigdec(&d_buff_1);
    d_buff_1.bits[0] = 5;
    for (int i = 0; i < -multiplier; i++) {
      mullt_bigdec(d_buff_1, d_buff_2, &d_buff_2);
    }
    initialize_bigdec(&d_buff_1);
    s21_big_decimal d_buff_3;
    initialize_bigdec(&d_buff_3);
    d_buff_1.bits[0] = 10;
    d_buff_3.bits[0] = 1;
    for (int i = 0; i < -multiplier - 28; i++) {
      mullt_bigdec(d_buff_1, d_buff_3, &d_buff_3);
    }
    if (-multiplier - 28 > 0) {
      divid_bigdec(d_buff_2, d_buff_3, &d_buff_2);
    }
    result.bits[0] = d_buff_2.bits[0];
    result.bits[1] = d_buff_2.bits[1];
    result.bits[2] = d_buff_2.bits[2];
    result.bits[3] = d_buff_2.bits[3];
    if (multiplier < -28) {
      scale = 28;
    } else {
      scale = -multiplier;
    }
    s21_decimal temp;
    initialize_decimal(&temp);
    temp.bits[0] = 10;
    set_scale(scale, &result);
  }
  if (src < 0) {
    set_sign(&result, 1);
  }
  *dst = result;
  return 0;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) { // надо было не мое
  *dst = 0;
  int sign = get_sign(src);
  int exp = get_scale(src);
  long double result = 0;
  for (int i = 0; i < 96; i++) {
    if (get_bit(src, i) == 1) {
      result += pow(2, i);
    }
  }
  result /= pow(10, exp);
  if (sign == 1) {
    result = -result;
  }
  *dst = (float)result;
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) { // надо было не мое
  *dst = 0;
  int sign = get_sign(src);
  int exp = get_scale(src);
  s21_decimal src_buff;
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
    }
  }
  if ((src_buff.bits[1] != 0) || (src_buff.bits[2] != 0)) {
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