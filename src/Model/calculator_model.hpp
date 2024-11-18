#ifndef CALCULATE_H
#define CALCULATE_H

#include <ctype.h>
#include <iso646.h>
#include <locale.h>
#include <math.h>
#include <pybind11/pybind11.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_CAPACITY 300

#define PRIORITY_ZERO 0
#define PRIORITY_ONE 1
#define PRIORITY_TWO 10
#define PRIORITY_THREE 100
#define PRIORITY_HIGHEST 9999999
#define PRIORITY_NONE -1

#define NUM_OR_X_TYPE 333
#define FUNC_TYPE 999
#define OPEN_TYPE -77777777
#define OPERATION_TYPE 2222
#define CLOSING_TYPE 666

class CalculatorModel {
 private:
  char *string_data = nullptr;
  typedef struct {
    long double value;
    int priority;
    char operation[10];
    int type;
    char printed[10];
  } lexeme;
  bool check_function_literal(int start_index, char func_literal[]);
  bool is_unary_character_operator(char c);
  bool is_binary_character_operation(char c);
  bool is_start_of_func_literal(char c);
  void delete_spaces();
  void replace_mod(char to_str[]);
  long double get_num_value(int start_index);
  bool check_leading_zeroes();
  bool check_dots_in_place();
  bool check_functions_in_place();
  bool check_operations_in_place();
  bool check_x_in_place();
  bool check_braces_in_place();
  bool check_braces_divided();
  bool check_concating_numbers();
  bool check_trash();
  bool check_value_div_with_operations();
  bool check_one_dot_per_num();
  bool check_x_in_place(int start_index, int end_index);
  long double polish_calc(lexeme pol_lexs[], int pol_size);
  void build_num_lex(int *i, long double x_value, lexeme *lex);
  void build_lexemes(lexeme lexes[], int *lexes_size, long double x_value);
  void dijkstra(lexeme lexes[], int *lexes_size, lexeme polish_lexs[],
                int *polish_size);
  void build_func_lex(int *i, lexeme *lex);

 public:
  long double calculate(long double x_value);
  bool is_valid_input();
  void set_data(char string_data[]);
  // calculator_model(/* args */);
  // ~calculator_model();
};

#endif  // CALCULATE_H
