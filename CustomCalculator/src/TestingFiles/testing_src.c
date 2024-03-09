#include "testing_header.h"

START_TEST(check_input) {
  int err = 0;
  char string[] = "1+2+3-log(6)*sqrt(10)+ln(10)";
  double answer = 0.0;
  err = is_valid_input(string);
  if (err == 1) answer = calculate(string, 0);
  ck_assert_int_eq(1, err);

  char string_1[] = "1+2+3*ln()";
  answer = 0.0;
  err = is_valid_input(string_1);
  if (err == 1) answer = calculate(string, 0);
  ck_assert_int_eq(0, err);

  char string_2[] = "1,123123+2mod4+(3*7)+sqrt(7)";
  answer = 0.0;
  err = is_valid_input(string_2);
  if (err == 1) answer = calculate(string, 0);
  ck_assert_int_eq(1, err);

  char string_3[] = "1+2mod4+3*(7+1)+acos(1/2)+5^2";
  answer = 0.0;
  err = is_valid_input(string_3);
  if (err == 1) answer = calculate(string, 0);
  ck_assert_int_eq(1, err);

  char string_4[] = "1+2mod4+3*(7+1)+asin(1/)";
  answer = 0.0;
  err = is_valid_input(string_4);
  if (err == 1) answer = calculate(string, 0);
  ck_assert_int_eq(0, err);

  char string_5[] = "^1+2mod4+3*(7+1)+atan(1/2)";
  answer = 0.0;
  err = is_valid_input(string_5);
  if (err == 1) answer = calculate(string, 0);
  ck_assert_int_eq(0, err);

  char string_6[] = "cos(1/2)+2mod4+3*(7+1)+sin(0)";
  answer = 0.0;
  err = is_valid_input(string_6);
  if (err == 1) answer = calculate(string, 0);
  ck_assert_int_eq(1, err);

  char string_7[] = "tan(1/2)+2mod4+3*(7+1)+asin(0)+atan(0)";
  answer = 0.0;
  err = is_valid_input(string_7);
  ck_assert_int_eq(1, err);

  char string_8[] = "123456789+";
  answer = 0.0;
  err = is_valid_input(string_8);
  ck_assert_int_eq(0, err);

  char string_9[] = "1/2+acos(3)-log(6)+ln(8)-asin(5)+atan(3)+cos(213)^";
  answer = 0.0;
  err = is_valid_input(string_9);
  ck_assert_int_eq(0, err);

  char string_10[] = "";
  answer = 0.0;
  err = is_valid_input(string_10);
  ck_assert_int_eq(0, err);

  char string_11[] = "1+4/";
  answer = 0.0;
  err = is_valid_input(string_11);
  ck_assert_int_eq(0, err);

  char string_12[] = "1+4*";
  answer = 0.0;
  err = is_valid_input(string_12);
  ck_assert_int_eq(0, err);

  char string_13[] = "1+5-4*)";
  answer = 0.0;
  err = is_valid_input(string_13);
  ck_assert_int_eq(0, err);

  char string_14[] = "1+((5-4)/410";
  answer = 0.0;
  err = is_valid_input(string_14);
  ck_assert_int_eq(0, err);

  char string_15[] = "4mod2+(5-4)";
  answer = 0.0;
  err = is_valid_input(string_15);
  ck_assert_int_eq(1, err);

  char string_16[] = "00+(5-4)";
  answer = 0.0;
  err = is_valid_input(string_16);
  ck_assert_int_eq(0, err);
  ck_assert_double_eq_tol(0.0, answer, 1e-8);

  char string_16_1[] = "0+(5-4)";
  answer = 0.0;
  err = is_valid_input(string_16_1);
  ck_assert_int_eq(1, err);

  char string_17[] = "*0+(5-4)";
  answer = 0.0;
  err = is_valid_input(string_17);
  ck_assert_int_eq(0, err);

  char string_18[] = "1/0+2";
  answer = 0.0;
  err = is_valid_input(string_18);
  ck_assert_int_eq(1, err);

  char string_19[] = "1+";
  answer = 0.0;
  err = is_valid_input(string_19);
  ck_assert_int_eq(0, err);

  char string_error[] = "ERROR";
  answer = 0.0;
  err = is_valid_input(string_error);
  ck_assert_int_eq(0, err);

  char string_nan[] = "nan";
  answer = 0.0;
  err = is_valid_input(string_nan);
  ck_assert_int_eq(0, err);

  char string_inf[] = "inf";
  answer = 0.0;
  err = is_valid_input(string_inf);
  ck_assert_int_eq(0, err);

  char string_20[] = "1+x";
  answer = 0.0;
  int err_x = 0;
  err = is_valid_input(string_20);
  ck_assert_int_eq(1, err);
  ck_assert_int_eq(0, err_x);

  char string_21[] = "cos(x)-sin(4)";
  answer = 0.0;
  err = is_valid_input(string_21);
  ck_assert_int_eq(1, err);

  char string_22[] = "1x";
  answer = 0.0;
  err = is_valid_input(string_22);
  ck_assert_int_eq(0, err);

  char string_23[] = "x5";
  answer = 0.0;
  err = is_valid_input(string_23);
  ck_assert_int_eq(0, err);

  char string_24[] = "-mod9";
  err = is_valid_input(string);
  answer = 0.0;
  err = is_valid_input(string_24);
  ck_assert_int_eq(0, err);

  char string_25[] = "9mod-";
  answer = 0.0;
  err = is_valid_input(string_25);
  ck_assert_int_eq(0, err);

  char string_26[] = "9.";
  answer = 0.0;
  err = is_valid_input(string_26);
  ck_assert_int_eq(0, err);

  char string_27[] = "311,312,321";
  answer = 0.0;
  err = is_valid_input(string_27);
  ck_assert_int_eq(0, err);

  char string_28[] = "9,312.321";
  answer = 0.0;
  err = is_valid_input(string_28);
  ck_assert_int_eq(0, err);

  char string_29[] = "-321.312,321";
  answer = 0.0;
  err = is_valid_input(string_29);
  ck_assert_int_eq(0, err);

  char string_30[] = "-0.0.0";
  answer = 0.0;
  err = is_valid_input(string_30);
  ck_assert_int_eq(0, err);

  char string_31[] = "-55,32";
  answer = 0.0;
  err = is_valid_input(string_31);
  ck_assert_int_eq(1, err);

  char string_32[] = "-55.32";
  answer = 0.0;
  err = is_valid_input(string_32);
  ck_assert_int_eq(1, err);

  char string_33[] = "1.1^(120)*0,01";
  answer = 0.0;
  err = is_valid_input(string_33);
  ck_assert_int_eq(1, err);
}
END_TEST

START_TEST(calculator) {
  double answer = 0.0;
  double res_original = 0.0;
  int error = 0;

  char input[300] = "(-1)*cos(1)+3";
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 0);
  res_original = -cos(1) + 3;
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error);

  char input_2[] = "-0,1+0,2";
  answer = 0.0;
  error = is_valid_input(input_2);
  if (error == 1) answer = calculate(input_2, 0);
  res_original = -0.1 + 0.2;
  ck_assert_int_eq(1, error);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);

  strcpy(
      input,
      "15.4121212121212/(7.1-(1.1+1.1))*3-(2+(1+1))*15.4/"
      "(7-(200.1+1))*3-(2+(1+1))*(15.0/"
      "(7-(1.1+1))*3.4-(2+(1+1))+15.23456789101112/(7.5-(1+1))*3.5-(2+(1+1)))");
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 0);
  res_original = 15.4121212121212 / (7.1 - (1.1 + 1.1)) * 3 -
                 (2 + (1 + 1)) * 15.4 / (7 - (200.1 + 1)) * 3 -
                 (2 + (1 + 1)) * (15.0 / (7 - (1.1 + 1)) * 3.4 - (2 + (1 + 1)) +
                                  15.23456789101112 / (7.5 - (1 + 1)) * 3.5 -
                                  (2 + (1 + 1)));
  ck_assert_int_eq(1, error);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);

  strcpy(input, "2^(2.1+1)-11mod2");
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 0);
  res_original = pow(2, (2.1 + 1)) - fmod(11, 2);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error);

  strcpy(input, "sin(0.5)-cos(1)+tan(0.5)+acos(0.5)-asin(1)-atan(1)");
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 0);
  res_original = sin(0.5) - cos(1) + tan(0.5) + acos(0.5) - asin(1) - atan(1);
  ck_assert_int_eq(1, error);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);

  strcpy(input, "sqrt(4.123456789)+3-1.12");
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 0);
  res_original = sqrt(4.123456789) + 3 - 1.12;
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error);

  strcpy(input, "log(+10.2)-ln(10.2)");
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 0);
  res_original = log10(10.2) - log(10.2);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error);

  strcpy(input, "11+(-2)^5");
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 0);
  res_original = 11 + pow(-2, 5);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error);

  strcpy(input, "log(10.2)+ln(10.2)");
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 0);
  res_original = log10(10.2) + log(10.2);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error);

  strcpy(input, "sqrt(+4+1)+(-3+1)");
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 0);
  res_original = sqrt(4 + 1) + (-3 + 1);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error);

  strcpy(input, "sqrt(3+1)-(-3+1)");
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 0);
  res_original = sqrt(3 + 1) - (-3 + 1);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error);

  strcpy(input, "+1.1122-(-1)");
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 0);
  res_original = +1.1122 - (-1);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error);

  strcpy(input, "2^(2.1+1)+(");
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 0);
  ck_assert_int_eq(0, error);

  strcpy(input, "2^(2.1+1)+()");
  answer = 0.0;
  error = is_valid_input(input);
  ck_assert_int_eq(0, error);

  strcpy(input, "2^(2.1+1)+2-(3+1)");
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 0);
  ck_assert_int_eq(1, error);

  strcpy(input, "sqrt(+4*x+1)+(-3+1)");
  answer = 0.0;
  error = is_valid_input(input);
  if (error == 1) answer = calculate(input, 5.8);
  res_original = sqrt(4 * 5.8 + 1) + (-3 + 1);
  ck_assert_int_eq(1, error);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
}
END_TEST

START_TEST(calculation_with_unary_minus) {
  double answer = 0.0;
  double res_original = 0.0;
  int error2 = 0;
  char input[] = "-cos(1)+3";
  answer = 0.0;
  error2 = is_valid_input(input);
  if (error2 == 1) answer = calculate(input, 0);
  res_original = -cos(1) + 3;
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error2);

  char input2[] = "-sin(1)+3+(-log(8)+9)";
  answer = 0.0;
  error2 = is_valid_input(input2);
  if (error2 == 1) answer = calculate(input2, 0);
  res_original = -sin(1) + 3 + (-log10(8) + 9);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error2);

  char input3[] = "-sin(1)+3+(-log(8)+9)";
  answer = 0.0;
  error2 = is_valid_input(input3);
  if (error2 == 1) answer = calculate(input3, 0);
  res_original = -sin(1) + 3 + (-log10(8) + 9);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error2);

  char input4[] = "-sqrt(-9.9)-sin(3)";
  answer = 0.0;
  error2 = is_valid_input(input4);
  if (error2 == 1) answer = calculate(input4, 0);
  res_original = -sqrt(-9.9) - sin(3);
  ck_assert_msg(res_original != res_original, "Error!\n");
  ck_assert_msg(answer != answer, "Error!\n");
  ck_assert_int_eq(1, error2);

  char input5[] = "-x+(-sin(3)-ln(99))";
  answer = 0.0;
  error2 = is_valid_input(input5);
  if (error2 == 1) answer = calculate(input5, +5.6);
  res_original = -5.6 + (-sin(3) - log(99));
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error2);

  char input6[] = "-6*3+9*x";
  answer = 0.0;
  error2 = is_valid_input(input6);
  if (error2 == 1) answer = calculate(input6, (-3));
  res_original = -6 * 3 + 9 * (-3);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error2);

  char input7[] = "-x";
  answer = 0.0;
  error2 = is_valid_input(input7);
  if (error2 == 1) answer = calculate(input7, -3);
  res_original = 3;
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error2);
}

START_TEST(calculation_with_unary_plus) {
  double answer = 0.0;
  double res_original = 0.0;
  int error2 = 0;
  char input[] = "+cos(1)+3";
  answer = 0.0;
  error2 = is_valid_input(input);
  if (error2 == 1) answer = calculate(input, 0);
  res_original = cos(1) + 3;
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error2);

  char input2[] = "+sin(1)+3+(+log(8)+9)";
  answer = 0.0;
  error2 = is_valid_input(input2);
  if (error2 == 1) answer = calculate(input2, 0);
  res_original = sin(1) + 3 + (log10(8) + 9);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error2);

  char input3[] = "+sin(1)+3+(+log(8)+9)";
  answer = 0.0;
  error2 = is_valid_input(input3);
  if (error2 == 1) answer = calculate(input3, 0);
  res_original = sin(1) + 3 + (log10(8) + 9);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error2);

  char input4[] = "+sqrt(+9.9)-sin(3)";
  answer = 0.0;
  error2 = is_valid_input(input4);
  if (error2 == 1) answer = calculate(input4, 0);
  res_original = sqrt(9.9) - sin(3);
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error2);

  char input5[] = "+x+(+sin(3)-ln(99))";
  answer = 0.0;
  error2 = is_valid_input(input5);
  if (error2 == 1) answer = calculate(input5, 5.6);
  res_original = 5.6 + (sin(3) - log(99));
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error2);
}

START_TEST(hard_test) {
  double answer = 0.0;
  double res_original = 0.0;
  int error2 = 0;
  char input[] = "2^(3)^(2)";
  answer = 0.0;
  error2 = is_valid_input(input);
  if (error2 == 1) answer = calculate(input, 0);
  res_original = pow(2, pow(3, 2));
  ck_assert_double_eq_tol(res_original, answer, 1e-8);
  ck_assert_int_eq(1, error2);

  char input1[] = "2^(3)^(2)+)(";
  answer = 0.0;
  error2 = is_valid_input(input1);
  if (error2 == 1) answer = calculate(input1, 0);
  ck_assert_int_eq(0, error2);
}

Suite *s21_SmartCalc_tests_create() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("suite_s21_SmartCalc");
  tc_core = tcase_create("tcase_tests");
  tcase_add_test(tc_core, check_input);
  tcase_add_test(tc_core, calculator);
  tcase_add_test(tc_core, calculation_with_unary_minus);
  tcase_add_test(tc_core, calculation_with_unary_plus);
  tcase_add_test(tc_core, hard_test);
  suite_add_tcase(s, tc_core);
  return s;
}
int main() {
  Suite *s = s21_SmartCalc_tests_create();
  SRunner *s21_SmartCalc_runner = srunner_create(s);
  int number_failed;
  srunner_run_all(s21_SmartCalc_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(s21_SmartCalc_runner);
  srunner_free(s21_SmartCalc_runner);

  return number_failed == 0 ? 0 : 1;
}
