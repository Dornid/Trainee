#include "../Model/calculator_model.cpp"
#include "testing_header.hpp"

TEST(CoreTests, check_input) {
  CalculatorModel calcModel;
  int err = 0;
  char string[] = "1+2+3-log(6)*sqrt(10)+ln(10)";
  double answer = 0.0;
  err = calcModel.is_valid_input(string);
  if (err == 1) answer = calcModel.calculate(string, 0);
  ASSERT_EQ(1, err);

  char string_1[] = "1+2+3*ln()";
  answer = 0.0;
  err = calcModel.is_valid_input(string_1);
  if (err == 1) answer = calcModel.calculate(string, 0);
  ASSERT_EQ(0, err);

  char string_2[] = "1,123123+2mod4+(3*7)+sqrt(7)";
  answer = 0.0;
  err = calcModel.is_valid_input(string_2);
  if (err == 1) answer = calcModel.calculate(string, 0);
  ASSERT_EQ(1, err);

  char string_3[] = "1+2mod4+3*(7+1)+acos(1/2)+5^2";
  answer = 0.0;
  err = calcModel.is_valid_input(string_3);
  if (err == 1) answer = calcModel.calculate(string, 0);
  ASSERT_EQ(1, err);

  char string_4[] = "1+2mod4+3*(7+1)+asin(1/)";
  answer = 0.0;
  err = calcModel.is_valid_input(string_4);
  if (err == 1) answer = calcModel.calculate(string, 0);
  ASSERT_EQ(0, err);

  char string_5[] = "^1+2mod4+3*(7+1)+atan(1/2)";
  answer = 0.0;
  err = calcModel.is_valid_input(string_5);
  if (err == 1) answer = calcModel.calculate(string, 0);
  ASSERT_EQ(0, err);

  char string_6[] = "cos(1/2)+2mod4+3*(7+1)+sin(0)";
  answer = 0.0;
  err = calcModel.is_valid_input(string_6);
  if (err == 1) answer = calcModel.calculate(string, 0);
  ASSERT_EQ(1, err);

  char string_7[] = "tan(1/2)+2mod4+3*(7+1)+asin(0)+atan(0)";
  answer = 0.0;
  err = calcModel.is_valid_input(string_7);
  ASSERT_EQ(1, err);

  char string_8[] = "123456789+";
  answer = 0.0;
  err = calcModel.is_valid_input(string_8);
  ASSERT_EQ(0, err);

  char string_9[] = "1/2+acos(3)-log(6)+ln(8)-asin(5)+atan(3)+cos(213)^";
  answer = 0.0;
  err = calcModel.is_valid_input(string_9);
  ASSERT_EQ(0, err);

  char string_10[] = "";
  answer = 0.0;
  err = calcModel.is_valid_input(string_10);
  ASSERT_EQ(0, err);

  char string_11[] = "1+4/";
  answer = 0.0;
  err = calcModel.is_valid_input(string_11);
  ASSERT_EQ(0, err);

  char string_12[] = "1+4*";
  answer = 0.0;
  err = calcModel.is_valid_input(string_12);
  ASSERT_EQ(0, err);

  char string_13[] = "1+5-4*)";
  answer = 0.0;
  err = calcModel.is_valid_input(string_13);
  ASSERT_EQ(0, err);

  char string_14[] = "1+((5-4)/410";
  answer = 0.0;
  err = calcModel.is_valid_input(string_14);
  ASSERT_EQ(0, err);

  char string_15[] = "4mod2+(5-4)";
  answer = 0.0;
  err = calcModel.is_valid_input(string_15);
  ASSERT_EQ(1, err);

  char string_16[] = "00+(5-4)";
  answer = 0.0;
  err = calcModel.is_valid_input(string_16);
  ASSERT_EQ(0, err);
  ASSERT_NEAR(0.0, answer, 1e-8);

  char string_16_1[] = "0+(5-4)";
  answer = 0.0;
  err = calcModel.is_valid_input(string_16_1);
  ASSERT_EQ(1, err);

  char string_17[] = "*0+(5-4)";
  answer = 0.0;
  err = calcModel.is_valid_input(string_17);
  ASSERT_EQ(0, err);

  char string_18[] = "1/0+2";
  answer = 0.0;
  err = calcModel.is_valid_input(string_18);
  ASSERT_EQ(1, err);

  char string_19[] = "1+";
  answer = 0.0;
  err = calcModel.is_valid_input(string_19);
  ASSERT_EQ(0, err);

  char string_error[] = "ERROR";
  answer = 0.0;
  err = calcModel.is_valid_input(string_error);
  ASSERT_EQ(0, err);

  char string_nan[] = "nan";
  answer = 0.0;
  err = calcModel.is_valid_input(string_nan);
  ASSERT_EQ(0, err);

  char string_inf[] = "inf";
  answer = 0.0;
  err = calcModel.is_valid_input(string_inf);
  ASSERT_EQ(0, err);

  char string_20[] = "1+x";
  answer = 0.0;
  int err_x = 0;
  err = calcModel.is_valid_input(string_20);
  ASSERT_EQ(1, err);
  ASSERT_EQ(0, err_x);

  char string_21[] = "cos(x)-sin(4)";
  answer = 0.0;
  err = calcModel.is_valid_input(string_21);
  ASSERT_EQ(1, err);

  char string_22[] = "1x";
  answer = 0.0;
  err = calcModel.is_valid_input(string_22);
  ASSERT_EQ(0, err);

  char string_23[] = "x5";
  answer = 0.0;
  err = calcModel.is_valid_input(string_23);
  ASSERT_EQ(0, err);

  char string_24[] = "-mod9";
  err = calcModel.is_valid_input(string);
  answer = 0.0;
  err = calcModel.is_valid_input(string_24);
  ASSERT_EQ(0, err);

  char string_25[] = "9mod-";
  answer = 0.0;
  err = calcModel.is_valid_input(string_25);
  ASSERT_EQ(0, err);

  char string_26[] = "9.";
  answer = 0.0;
  err = calcModel.is_valid_input(string_26);
  ASSERT_EQ(0, err);

  char string_27[] = "311,312,321";
  answer = 0.0;
  err = calcModel.is_valid_input(string_27);
  ASSERT_EQ(0, err);

  char string_28[] = "9,312.321";
  answer = 0.0;
  err = calcModel.is_valid_input(string_28);
  ASSERT_EQ(0, err);

  char string_29[] = "-321.312,321";
  answer = 0.0;
  err = calcModel.is_valid_input(string_29);
  ASSERT_EQ(0, err);

  char string_30[] = "-0.0.0";
  answer = 0.0;
  err = calcModel.is_valid_input(string_30);
  ASSERT_EQ(0, err);

  char string_31[] = "-55,32";
  answer = 0.0;
  err = calcModel.is_valid_input(string_31);
  ASSERT_EQ(1, err);

  char string_32[] = "-55.32";
  answer = 0.0;
  err = calcModel.is_valid_input(string_32);
  ASSERT_EQ(1, err);

  char string_33[] = "1.1^(120)*0,01";
  answer = 0.0;
  err = calcModel.is_valid_input(string_33);
  ASSERT_EQ(1, err);
}

TEST(CoreTests, calculator) {
  CalculatorModel calcModel;
  double answer = 0.0;
  double res_original = 0.0;
  int error = 0;

  char input[300] = "(-1)*cos(1)+3";
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 0);
  res_original = -cos(1) + 3;
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error);

  char input_2[] = "-0,1+0,2";
  answer = 0.0;
  error = calcModel.is_valid_input(input_2);
  if (error == 1) answer = calcModel.calculate(input_2, 0);
  res_original = -0.1 + 0.2;
  ASSERT_EQ(1, error);
  ASSERT_NEAR(res_original, answer, 1e-8);

  strcpy(
      input,
      "15.4121212121212/(7.1-(1.1+1.1))*3-(2+(1+1))*15.4/"
      "(7-(200.1+1))*3-(2+(1+1))*(15.0/"
      "(7-(1.1+1))*3.4-(2+(1+1))+15.23456789101112/(7.5-(1+1))*3.5-(2+(1+1)))");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 0);
  res_original = 15.4121212121212 / (7.1 - (1.1 + 1.1)) * 3 -
                 (2 + (1 + 1)) * 15.4 / (7 - (200.1 + 1)) * 3 -
                 (2 + (1 + 1)) * (15.0 / (7 - (1.1 + 1)) * 3.4 - (2 + (1 + 1)) +
                                  15.23456789101112 / (7.5 - (1 + 1)) * 3.5 -
                                  (2 + (1 + 1)));
  ASSERT_EQ(1, error);
  ASSERT_NEAR(res_original, answer, 1e-8);

  strcpy(input, "2^(2.1+1)-11mod2");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 0);
  res_original = pow(2, (2.1 + 1)) - fmod(11, 2);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error);

  strcpy(input, "sin(0.5)-cos(1)+tan(0.5)+acos(0.5)-asin(1)-atan(1)");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 0);
  res_original = sin(0.5) - cos(1) + tan(0.5) + acos(0.5) - asin(1) - atan(1);
  ASSERT_EQ(1, error);
  ASSERT_NEAR(res_original, answer, 1e-8);

  strcpy(input, "sqrt(4.123456789)+3-1.12");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 0);
  res_original = sqrt(4.123456789) + 3 - 1.12;
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error);

  strcpy(input, "log(+10.2)-ln(10.2)");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 0);
  res_original = log10(10.2) - log(10.2);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error);

  strcpy(input, "11+(-2)^5");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 0);
  res_original = 11 + pow(-2, 5);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error);

  strcpy(input, "log(10.2)+ln(10.2)");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 0);
  res_original = log10(10.2) + log(10.2);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error);

  strcpy(input, "sqrt(+4+1)+(-3+1)");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 0);
  res_original = sqrt(4 + 1) + (-3 + 1);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error);

  strcpy(input, "sqrt(3+1)-(-3+1)");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 0);
  res_original = sqrt(3 + 1) - (-3 + 1);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error);

  strcpy(input, "+1.1122-(-1)");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 0);
  res_original = +1.1122 - (-1);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error);

  strcpy(input, "2^(2.1+1)+(");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 0);
  ASSERT_EQ(0, error);

  strcpy(input, "2^(2.1+1)+()");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  ASSERT_EQ(0, error);

  strcpy(input, "2^(2.1+1)+2-(3+1)");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 0);
  ASSERT_EQ(1, error);

  strcpy(input, "sqrt(+4*x+1)+(-3+1)");
  answer = 0.0;
  error = calcModel.is_valid_input(input);
  if (error == 1) answer = calcModel.calculate(input, 5.8);
  res_original = sqrt(4 * 5.8 + 1) + (-3 + 1);
  ASSERT_EQ(1, error);
  ASSERT_NEAR(res_original, answer, 1e-8);
}

TEST(CoreTests, calculation_with_unary_minus) {
  CalculatorModel calcModel;
  double answer = 0.0;
  double res_original = 0.0;
  int error2 = 0;
  char input[] = "-cos(1)+3";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input);
  if (error2 == 1) answer = calcModel.calculate(input, 0);
  res_original = -cos(1) + 3;
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error2);

  char input2[] = "-sin(1)+3+(-log(8)+9)";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input2);
  if (error2 == 1) answer = calcModel.calculate(input2, 0);
  res_original = -sin(1) + 3 + (-log10(8) + 9);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error2);

  char input3[] = "-sin(1)+3+(-log(8)+9)";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input3);
  if (error2 == 1) answer = calcModel.calculate(input3, 0);
  res_original = -sin(1) + 3 + (-log10(8) + 9);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error2);

  char input4[] = "-sqrt(-9.9)-sin(3)";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input4);
  if (error2 == 1) answer = calcModel.calculate(input4, 0);
  res_original = -sqrt(-9.9) - sin(3);
  ASSERT_EQ(1, error2);

  char input5[] = "-x+(-sin(3)-ln(99))";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input5);
  if (error2 == 1) answer = calcModel.calculate(input5, +5.6);
  res_original = -5.6 + (-sin(3) - log(99));
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error2);

  char input6[] = "-6*3+9*x";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input6);
  if (error2 == 1) answer = calcModel.calculate(input6, (-3));
  res_original = -6 * 3 + 9 * (-3);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error2);

  char input7[] = "-x";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input7);
  if (error2 == 1) answer = calcModel.calculate(input7, -3);
  res_original = 3;
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error2);
}

TEST(CoreTests, calculation_with_unary_plus) {
  CalculatorModel calcModel;
  double answer = 0.0;
  double res_original = 0.0;
  int error2 = 0;
  char input[] = "+cos(1)+3";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input);
  if (error2 == 1) answer = calcModel.calculate(input, 0);
  res_original = cos(1) + 3;
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error2);

  char input2[] = "+sin(1)+3+(+log(8)+9)";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input2);
  if (error2 == 1) answer = calcModel.calculate(input2, 0);
  res_original = sin(1) + 3 + (log10(8) + 9);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error2);

  char input3[] = "+sin(1)+3+(+log(8)+9)";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input3);
  if (error2 == 1) answer = calcModel.calculate(input3, 0);
  res_original = sin(1) + 3 + (log10(8) + 9);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error2);

  char input4[] = "+sqrt(+9.9)-sin(3)";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input4);
  if (error2 == 1) answer = calcModel.calculate(input4, 0);
  res_original = sqrt(9.9) - sin(3);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error2);

  char input5[] = "+x+(+sin(3)-ln(99))";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input5);
  if (error2 == 1) answer = calcModel.calculate(input5, 5.6);
  res_original = 5.6 + (sin(3) - log(99));
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error2);
}

TEST(CoreTests, hard_test) {
  CalculatorModel calcModel;
  double answer = 0.0;
  double res_original = 0.0;
  int error2 = 0;
  char input[] = "2^(3)^(2)";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input);
  if (error2 == 1) answer = calcModel.calculate(input, 0);
  res_original = pow(2, pow(3, 2));
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, error2);

  char input1[] = "2^(3)^(2)+)(";
  answer = 0.0;
  error2 = calcModel.is_valid_input(input1);
  if (error2 == 1) answer = calcModel.calculate(input1, 0);
  ASSERT_EQ(0, error2);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
