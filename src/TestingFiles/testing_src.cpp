#include "../Model/calculator_model.cpp"
#include "testing_header.hpp"

using namespace s21;

TEST(CoreTests, check_input) {
  CalculatorModel calcModel;
  int is_valid = 0;
  char string[] = "1+2+3-log(6)*sqrt(10)+ln(10)";
  calcModel.set_data(string);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(1, is_valid);
  char string_1[] = "1+2+3*ln()";
  calcModel.set_data(string_1);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_2[] = "1,123123+2mod4+(3*7)+sqrt(7)";
  calcModel.set_data(string_2);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(1, is_valid);

  char string_3[] = "1+2mod4+3*(7+1)+acos(1/2)+5^2";
  calcModel.set_data(string_3);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(1, is_valid);

  char string_4[] = "1+2mod4+3*(7+1)+asin(1/)";
  calcModel.set_data(string_4);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_5[] = "^1+2mod4+3*(7+1)+atan(1/2)";
  calcModel.set_data(string_5);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_6[] = "cos(1/2)+2mod4+3*(7+1)+sin(0)";
  calcModel.set_data(string_6);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(1, is_valid);

  char string_7[] = "tan(1/2)+2mod4+3*(7+1)+asin(0)+atan(0)";
  calcModel.set_data(string_7);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(1, is_valid);

  char string_8[] = "123456789+";
  calcModel.set_data(string_8);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_9[] = "1/2+acos(3)-log(6)+ln(8)-asin(5)+atan(3)+cos(213)^";
  calcModel.set_data(string_9);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_10[] = "";
  calcModel.set_data(string_10);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_11[] = "1+4/";
  calcModel.set_data(string_11);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_12[] = "1+4*";
  calcModel.set_data(string_12);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_13[] = "1+5-4*)";
  calcModel.set_data(string_13);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_14[] = "1+((5-4)/410";
  calcModel.set_data(string_14);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_15[] = "4mod2+(5-4)";
  calcModel.set_data(string_15);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(1, is_valid);

  char string_16[] = "00+(5-4)";
  calcModel.set_data(string_16);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_16_1[] = "0+(5-4)";
  calcModel.set_data(string_16_1);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(1, is_valid);

  char string_17[] = "*0+(5-4)";
  calcModel.set_data(string_17);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_18[] = "1/0+2";
  calcModel.set_data(string_18);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(1, is_valid);

  char string_19[] = "1+";
  calcModel.set_data(string_19);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_error[] = "ERROR";
  calcModel.set_data(string_error);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_nan[] = "nan";
  calcModel.set_data(string_nan);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_inf[] = "inf";
  calcModel.set_data(string_inf);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_20[] = "1+x";
  calcModel.set_data(string_20);
  int err_x = 0;
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(1, is_valid);
  ASSERT_EQ(0, err_x);

  char string_21[] = "cos(x)-sin(4)";
  calcModel.set_data(string_21);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(1, is_valid);

  char string_22[] = "1x";
  calcModel.set_data(string_22);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_23[] = "x5";
  calcModel.set_data(string_23);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_24[] = "-mod9";
  calcModel.set_data(string_24);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_25[] = "9mod-";
  calcModel.set_data(string_25);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_26[] = "9.";
  calcModel.set_data(string_26);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_27[] = "311,312,321";
  calcModel.set_data(string_27);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_28[] = "9,312.321";
  calcModel.set_data(string_28);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_29[] = "-321.312,321";
  calcModel.set_data(string_29);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_30[] = "-0.0.0";
  calcModel.set_data(string_30);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  char string_31[] = "-55,32";
  calcModel.set_data(string_31);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(1, is_valid);

  char string_32[] = "-55.32";
  calcModel.set_data(string_32);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(1, is_valid);

  char string_33[] = "1.1^(120)*0,01";
  calcModel.set_data(string_33);
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(1, is_valid);
}

TEST(CoreTests, calculator) {
  CalculatorModel calcModel;
  double answer = 0.0;
  double res_original = 0.0;
  int is_valid = 0;

  char input[300] = "(-1)*cos(1)+3";
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  res_original = -cos(1) + 3;
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid);

  char input_2[] = "-0,1+0,2";
  calcModel.set_data(input_2);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  res_original = -0.1 + 0.2;
  ASSERT_EQ(1, is_valid);
  ASSERT_NEAR(res_original, answer, 1e-8);

  strcpy(
      input,
      "15.4121212121212/(7.1-(1.1+1.1))*3-(2+(1+1))*15.4/"
      "(7-(200.1+1))*3-(2+(1+1))*(15.0/"
      "(7-(1.1+1))*3.4-(2+(1+1))+15.23456789101112/(7.5-(1+1))*3.5-(2+(1+1)))");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  res_original = 15.4121212121212 / (7.1 - (1.1 + 1.1)) * 3 -
                 (2 + (1 + 1)) * 15.4 / (7 - (200.1 + 1)) * 3 -
                 (2 + (1 + 1)) * (15.0 / (7 - (1.1 + 1)) * 3.4 - (2 + (1 + 1)) +
                                  15.23456789101112 / (7.5 - (1 + 1)) * 3.5 -
                                  (2 + (1 + 1)));
  ASSERT_EQ(1, is_valid);
  ASSERT_NEAR(res_original, answer, 1e-8);

  strcpy(input, "2^(2.1+1)-11mod2");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  res_original = pow(2, (2.1 + 1)) - fmod(11, 2);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid);

  strcpy(input, "sin(0.5)-cos(1)+tan(0.5)+acos(0.5)-asin(1)-atan(1)");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  res_original = sin(0.5) - cos(1) + tan(0.5) + acos(0.5) - asin(1) - atan(1);
  ASSERT_EQ(1, is_valid);
  ASSERT_NEAR(res_original, answer, 1e-8);

  strcpy(input, "sqrt(4.123456789)+3-1.12");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  res_original = sqrt(4.123456789) + 3 - 1.12;
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid);

  strcpy(input, "log(+10.2)-ln(10.2)");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  res_original = log10(10.2) - log(10.2);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid);

  strcpy(input, "11+(-2)^5");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  res_original = 11 + pow(-2, 5);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid);

  strcpy(input, "log(10.2)+ln(10.2)");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  res_original = log10(10.2) + log(10.2);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid);

  strcpy(input, "sqrt(+4+1)+(-3+1)");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  res_original = sqrt(4 + 1) + (-3 + 1);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid);

  strcpy(input, "sqrt(3+1)-(-3+1)");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  res_original = sqrt(3 + 1) - (-3 + 1);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid);

  strcpy(input, "+1.1122-(-1)");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  res_original = +1.1122 - (-1);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid);

  strcpy(input, "2^(2.1+1)+(");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  ASSERT_EQ(0, is_valid);

  strcpy(input, "2^(2.1+1)+()");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  ASSERT_EQ(0, is_valid);

  strcpy(input, "2^(2.1+1)+2-(3+1)");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(0);
  ASSERT_EQ(1, is_valid);

  strcpy(input, "sqrt(+4*x+1)+(-3+1)");
  calcModel.set_data(input);
  answer = 0.0;
  is_valid = calcModel.is_valid_input();
  if (is_valid == 1) answer = calcModel.calculate(5.8);
  res_original = sqrt(4 * 5.8 + 1) + (-3 + 1);
  ASSERT_EQ(1, is_valid);
  ASSERT_NEAR(res_original, answer, 1e-8);
}
TEST(CoreTests, calculation_with_unary_minus) {
  CalculatorModel calcModel;
  double answer = 0.0;
  double res_original = 0.0;
  int is_valid_2 = 0;

  char input[] = "-cos(1)+3";
  calcModel.set_data(input);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate(0);
  res_original = -cos(1) + 3;
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid_2);

  char input2[] = "-sin(1)+3+(-log(8)+9)";
  calcModel.set_data(input2);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate(0);
  res_original = -sin(1) + 3 + (-log10(8) + 9);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid_2);

  char input3[] = "-sin(1)+3+(-log(8)+9)";
  calcModel.set_data(input3);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate(0);
  res_original = -sin(1) + 3 + (-log10(8) + 9);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid_2);

  char input4[] = "-sqrt(-9.9)-sin(3)";
  calcModel.set_data(input4);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate(0);
  res_original = -sqrt(-9.9) - sin(3);
  ASSERT_EQ(1, is_valid_2);

  char input5[] = "-x+(-sin(3)-ln(99))";
  calcModel.set_data(input5);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate(+5.6);
  res_original = -5.6 + (-sin(3) - log(99));
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid_2);

  char input6[] = "-6*3+9*x";
  calcModel.set_data(input6);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate((-3));
  res_original = -6 * 3 + 9 * (-3);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid_2);

  char input7[] = "-x";
  calcModel.set_data(input7);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate(-3);
  res_original = 3;
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid_2);
}

TEST(CoreTests, calculation_with_unary_plus) {
  CalculatorModel calcModel;
  double answer = 0.0;
  double res_original = 0.0;
  int is_valid_2 = 0;

  char input[] = "+cos(1)+3";
  calcModel.set_data(input);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate(0);
  res_original = cos(1) + 3;
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid_2);

  char input2[] = "+sin(1)+3+(+log(8)+9)";
  calcModel.set_data(input2);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate(0);
  res_original = sin(1) + 3 + (log10(8) + 9);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid_2);

  char input3[] = "+sin(1)+3+(+log(8)+9)";
  calcModel.set_data(input3);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate(0);
  res_original = sin(1) + 3 + (log10(8) + 9);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid_2);

  char input4[] = "+sqrt(+9.9)-sin(3)";
  calcModel.set_data(input4);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate(0);
  res_original = sqrt(9.9) - sin(3);
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid_2);

  char input5[] = "+x+(+sin(3)-ln(99))";
  calcModel.set_data(input5);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate(5.6);
  res_original = 5.6 + (sin(3) - log(99));
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid_2);
}

TEST(CoreTests, hard_test) {
  CalculatorModel calcModel;
  double answer = 0.0;
  double res_original = 0.0;
  int is_valid_2 = 0;

  char input[] = "2^(3)^(2)";
  calcModel.set_data(input);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate(0);
  res_original = pow(2, pow(3, 2));
  ASSERT_NEAR(res_original, answer, 1e-8);
  ASSERT_EQ(1, is_valid_2);

  char input1[] = "2^(3)^(2)+)(";
  calcModel.set_data(input1);
  answer = 0.0;
  is_valid_2 = calcModel.is_valid_input();
  if (is_valid_2 == 1) answer = calcModel.calculate(0);
  ASSERT_EQ(0, is_valid_2);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
