/* (C) COPYRIGHT @Hust-Robocon-Team
 *    maintainer ChengJie 2019
 *       309815765@qq.com         */

#include "hust_math_lib.h"
#include "math.h"

static const float pi = 3.14159265359;
static const float pi_2 = 1.570796326795;

/* sub-function of FastTableAtan */
static float LookUpAtanTable(float tan_value) __attribute__((const));

/* atan_value for 0 ~ 1 */
static const float atan_table[101] = {
    0.00000000, 0.00999967, 0.01999733, 0.02999100, 0.03997869, 0.04995840,
    0.05992816, 0.06988600, 0.07982999, 0.08975817, 0.09966865, 0.10955953,
    0.11942893, 0.12927500, 0.13909594, 0.14888995, 0.15865526, 0.16839016,
    0.17809294, 0.18776195, 0.19739556, 0.20699219, 0.21655030, 0.22606839,
    0.23554498, 0.24497866, 0.25436806, 0.26371183, 0.27300870, 0.28225742,
    0.29145679, 0.30060567, 0.30970294, 0.31874756, 0.32773851, 0.33667482,
    0.34555558, 0.35437992, 0.36314701, 0.37185607, 0.38050638, 0.38909723,
    0.39762799, 0.40609806, 0.41450687, 0.42285393, 0.43113874, 0.43936089,
    0.44751998, 0.45561565, 0.46364761, 0.47161557, 0.47951929, 0.48735858,
    0.49513326, 0.50284321, 0.51048832, 0.51806853, 0.52558379, 0.53303411,
    0.54041950, 0.54774001, 0.55499573, 0.56218674, 0.56931319, 0.57637522,
    0.58337301, 0.59030675, 0.59717666, 0.60398298, 0.61072596, 0.61740589,
    0.62402305, 0.63057776, 0.63707033, 0.64350111, 0.64987045, 0.65617872,
    0.66242629, 0.66861357, 0.67474094, 0.68080883, 0.68681765, 0.69276784,
    0.69865982, 0.70449406, 0.71027101, 0.71599111, 0.72165485, 0.72726269,
    0.73281510, 0.73831257, 0.74375558, 0.74914462, 0.75448018, 0.75976275,
    0.76499283, 0.77017091, 0.77529750, 0.78037308, 0.78539816};

float FastTableAtan2(float y, float x) {
  if (x > 0) {
    return FastTableAtan(y / x);
  } else if (y >= 0 && x < 0) {
    return pi + FastTableAtan(y / x);
  } else if (y < 0 && x < 0) {
    return -pi + FastTableAtan(y / x);
  } else if (y > 0 && x == 0) {
    return pi_2;
  } else if (y < 0 && x == 0) {
    return -pi_2;
  } else if (y == 0 && x == 0) {
    /* undefined */
    return 0;
  }
}

float FastTableAtan2Positive(float y, float x) {
  return (NormalizeAnglePositive(FastTableAtan2(y, x)));
}

float FastTableAtan(float tan_value) {
  if (tan_value < 0) {
    if (tan_value < -1) {
      return -(pi_2 - LookUpAtanTable(-1.0f / tan_value));
    } else {
      return -(LookUpAtanTable(-tan_value));
    }
  } else {
    if (tan_value > 1) {
      return (pi_2 - LookUpAtanTable(1.0f / tan_value));
    } else {
      return LookUpAtanTable(tan_value);
    }
  }
}

float LookUpAtanTable(float tan_value) {
  if (tan_value == 1.0f) {
    return atan_table[100];
  } else {
    float tan_value_scale = tan_value * 100;
    int index = floor(tan_value_scale);
    return (atan_table[index] +
            (tan_value_scale - index) *
                (atan_table[index + 1] - atan_table[index]));
  }
}

float FastAcos(float cos_value) {
  if (fabs(cos_value) > 1) return 0.0f;
  return FastTableAtan2(sqrtf(1 - cos_value * cos_value), cos_value);
}

float NormalizeAngle(float angle_rad) {
  float angle_tmp = fmod(angle_rad + pi, 2 * pi);
  if (angle_tmp < 0) {
    angle_tmp += 2 * pi;
  }
  return angle_tmp - pi;
}

float NormalizeAnglePositive(float angle_rad) {
  float angle_tmp = fmod(angle_rad, 2*pi);
  if (angle_tmp < 0) {
    angle_tmp += 2*pi;
  }
  return angle_tmp;
}

float Clamp(float raw_data, float lowwer_bound, float upper_bound) 
{
  static float tmp = 0.0f;
  if (lowwer_bound > upper_bound) 
  {
    tmp = upper_bound;
    upper_bound = lowwer_bound;
    lowwer_bound = tmp;
  }
  if (raw_data >= upper_bound) return upper_bound;
  if (raw_data <= lowwer_bound) return lowwer_bound;
  return raw_data;
}
