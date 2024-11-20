#include "calculator_model.hpp"

// func_literal should contain '(' for good working!
bool CalculatorModel::check_function_literal(int start_index,
                                             char func_literal[]) {
  bool is_ok = true;
  if (strlen(func_literal) + 1 + start_index >= strlen(string_data)) {
    is_ok = false;
  }
  for (int i = 0; is_ok and i < strlen(func_literal); i++) {
    if (string_data[start_index + i] != func_literal[i]) {
      is_ok = false;
    }
  }
  return is_ok;
}

bool CalculatorModel::is_unary_character_operator(char c) {
  return c == '+' or c == '-';
}

bool CalculatorModel::is_binary_character_operation(char c) {
  return c == '*' or c == '/' or c == '^' or c == '%';
}

bool CalculatorModel::is_start_of_func_literal(char c) {
  return c == 'c' or c == 's' or c == 't' or c == 'a' or c == 'l';
}

// Check whether string is valid beforehand!
void CalculatorModel::delete_spaces() {
  char buff_str[MAXLENGTH] = "";
  int next_index = 0;
  for (int i = 0; i < strlen(string_data); i++) {
    if (string_data[i] != ' ') {
      buff_str[next_index] = string_data[i];
      next_index++;
    }
  }
  strcpy(string_data, buff_str);
}

void CalculatorModel::replace_mod(char to_str[]) {
  char buff_str[300] = "";
  int next_index = 0;
  int i = 0;
  for (; i < strlen(string_data) - 2; i++) {
    if (string_data[i] == 'm' and string_data[i + 1] == 'o' and
        string_data[i + 2] == 'd') {
      buff_str[next_index] = '%';
      next_index++;
      i += 2;
    } else {
      buff_str[next_index] = string_data[i];
      next_index++;
    }
  }
  while (i < strlen(string_data)) {
    buff_str[next_index] = string_data[i];
    next_index++;
    i++;
  }
  strcpy(to_str, buff_str);
}

long double CalculatorModel::get_num_value(int start_index) {
  long double res = 0;
  int i = start_index;
  while (isdigit(string_data[i])) {
    res *= 10;
    res += string_data[i] - '0';
    i++;
  }
  if (string_data[i] == '.' or string_data[i] == ',') {
    int j = 1;
    i++;
    while (isdigit(string_data[i])) {
      res += (string_data[i] - '0') / pow(10, j);
      j++;
      i++;
    }
  }
  return res;
}

bool CalculatorModel::check_leading_zeroes() {
  const int length = strlen(string_data);
  bool is_leading_zeros_in_place = true;
  bool has_non_zero_before = false;
  for (int i = 0; i < length; i++) {
    char c = string_data[i];
    if (isdigit(c) and c != '0' or c == '.' or c == ',') {
      has_non_zero_before = true;
    } else if (not isdigit(c)) {
      has_non_zero_before = false;
    } else if (c == '0' and not has_non_zero_before and
               not((i - 1 < 0 or not isdigit(string_data[i - 1])) and
                   (i + 1 >= length or not isdigit(string_data[i + 1])))) {
      is_leading_zeros_in_place = false;
    }
  }
  return is_leading_zeros_in_place;
}

bool CalculatorModel::check_dots_in_place() {
  bool is_dots_in_place = true;
  for (int i = 0; i < strlen(string_data); i++) {
    char c = tolower(string_data[i]);
    if (c == '.' or c == ',') {  // c == ',' or
      if (not(i + 1 < strlen(string_data) and isdigit(string_data[i + 1]) and
              i - 1 >= 0 and isdigit(string_data[i - 1]))) {
        is_dots_in_place = false;
      }
    }
  }
  return is_dots_in_place;
}

bool CalculatorModel::check_functions_in_place() {
  bool is_functions_in_place = true;
  for (int i = 0; i < strlen(string_data); i++) {
    char c = tolower(string_data[i]);
    if (isalpha(c) and c != 'x') {
      char literals[][10] = {"sin(",  "cos(",  "tan(", "acos(", "asin(",
                             "atan(", "sqrt(", "ln(",  "log("};
      int literal_size = 9;
      bool found_literal = false;
      int correct_literal_index = -1;
      for (int j = 0; j < literal_size; j++) {
        if (check_function_literal(i, literals[j])) {
          found_literal = true;
          correct_literal_index = j;
        }
      }
      if (found_literal) {
        i += strlen(literals[correct_literal_index]) - 1;
      } else {
        is_functions_in_place = false;
      }
    }
  }
  return is_functions_in_place;
}

bool CalculatorModel::check_operations_in_place() {
  const int length = strlen(string_data);
  bool is_operation_in_place = true;
  for (int i = 0; i < length; i++) {
    if (is_binary_character_operation(string_data[i])) {
      if (i - 1 < 0 or
          string_data[i - 1] != 'x' and not isdigit(string_data[i - 1]) and
              string_data[i - 1] != '(' and string_data[i - 1] != ')')
        is_operation_in_place = false;
      if (i + 1 >= length or
          string_data[i + 1] != 'x' and
              not is_start_of_func_literal(string_data[i + 1]) and
              not isdigit(string_data[i + 1]) and string_data[i + 1] != '(')
        is_operation_in_place = false;
    }
    if (is_unary_character_operator(string_data[i])) {
      if (i + 1 >= length or
          string_data[i + 1] != 'x' and
              not is_start_of_func_literal(string_data[i + 1]) and
              not isdigit(string_data[i + 1]) and string_data[i + 1] != '(' and
              string_data[i + 1] != ')') {
        is_operation_in_place = false;
      }
    }
  }
  return is_operation_in_place;
}

bool CalculatorModel::check_x_in_place() {
  const int length = strlen(string_data);
  bool is_x_in_place = true;
  for (int i = 0; i < length; i++) {
    if (string_data[i] == 'x') {
      if (i - 1 >= 0 and not is_unary_character_operator(string_data[i - 1]) and
          not is_binary_character_operation(string_data[i - 1]) and
          string_data[i - 1] != '(' and string_data[i - 1] != ')')
        is_x_in_place = false;
      if (i + 1 < length and
          not is_unary_character_operator(string_data[i + 1]) and
          not is_binary_character_operation(string_data[i + 1]) and
          string_data[i + 1] != '(' and string_data[i + 1] != ')')
        is_x_in_place = false;
    }
  }
  return is_x_in_place;
}

bool CalculatorModel::check_braces_in_place() {
  int braces_cnt = 0;
  const int length = strlen(string_data);
  bool is_braces_in_place = true;
  for (int i = 0; i < length; i++) {
    char c = string_data[i];
    if (c == '(') braces_cnt++;
    if (c == ')') {
      braces_cnt--;
      if (i > 0 and string_data[i - 1] == '(') {
        is_braces_in_place = false;
      }
    }
    if (braces_cnt < 0) {
      is_braces_in_place = false;
    }
  }
  is_braces_in_place = is_braces_in_place and braces_cnt == 0;
  return is_braces_in_place;
}

bool CalculatorModel::check_braces_divided() {
  bool is_braces_devided_with_operations_or_funcs = true;
  for (int i = 1; i < strlen(string_data); i++) {
    if (string_data[i] == '(' and string_data[i - 1] != '(' and
        not isalpha(string_data[i - 1]) and
        not is_unary_character_operator(string_data[i - 1]) and
        not is_binary_character_operation(string_data[i - 1])) {
      is_braces_devided_with_operations_or_funcs = false;
    }
    if (string_data[i] == ')' and i < strlen(string_data) - 1 and
        string_data[i + 1] != ')' and
        not is_unary_character_operator(string_data[i + 1]) and
        not is_binary_character_operation(string_data[i + 1])) {
      is_braces_devided_with_operations_or_funcs = false;
    }
  }
  return is_braces_devided_with_operations_or_funcs;
}

bool CalculatorModel::check_concating_numbers() {
  bool is_concating_numbers_in_place = true;
  for (int i = 0; i < strlen(string_data); i++) {
    if (string_data[i] == ' ') {
      int j = i;
      while (j >= 0 and string_data[j] == ' ') {
        j--;
      }
      bool is_x_or_num_left =
          j >= 0 and (string_data[j] == 'x' or isdigit(string_data[j]));
      j = i;
      while (j < strlen(string_data) and string_data[j] == ' ') {
        j++;
      }
      bool is_x_or_num_right =
          j < strlen(string_data) and
          (string_data[j] == 'x' or isdigit(string_data[j]));
      if (is_x_or_num_left and is_x_or_num_right) {
        is_concating_numbers_in_place = false;
      }
    }
  }
  return is_concating_numbers_in_place;
}

bool CalculatorModel::check_trash() {
  bool is_trash_symbols_in_place = true;
  for (int i = 0; i < strlen(string_data); i++) {
    if (not isalpha(string_data[i]) and not isdigit(string_data[i]) and
        string_data[i] != 'x' and
        not is_binary_character_operation(string_data[i]) and
        not is_unary_character_operator(string_data[i]) and
        string_data[i] != '(' and string_data[i] != ')' and
        string_data[i] != ',' and string_data[i] != '.') {
      is_trash_symbols_in_place = false;
    }
  }
  return is_trash_symbols_in_place;
}

bool CalculatorModel::check_one_dot_per_num() {
  bool is_one_dot_per_num = true;
  for (int i = 0; i < strlen(string_data); i++) {
    if (isdigit(string_data[i])) {
      int j = i;
      int cnt_dots = 0;
      while (j < strlen(string_data) and
             (isdigit(string_data[j]) or string_data[j] == '.' or
              string_data[j] == ',')) {
        cnt_dots += string_data[j] == '.' or string_data[j] == ',';
        j++;
      }
      if (cnt_dots > 1) {
        is_one_dot_per_num = false;
      }
    }
  }
  return is_one_dot_per_num;
}

bool CalculatorModel::check_value_div_with_operations() {
  bool is_value_divided_with_operations = true;
  for (int i = 1; i < strlen(string_data); i++) {
    if (isalpha(string_data[i]) and isdigit(string_data[i - 1]) or
        isdigit(string_data[i]) and isalpha(string_data[i - 1])) {
      is_value_divided_with_operations = false;
    }
  }
  return is_value_divided_with_operations;
}

#include <iostream>
using namespace std;

bool CalculatorModel::is_valid_input() {
  char string_init[MAXLENGTH] = "";
  strncpy(string_init, string_data, MAXLENGTH);

  if (strcmp(string_data, "") == 0) return false;
  if (strlen(string_data) > 255) return false;
  for (int i = 0; i < strlen(string_data); i++) {
    if (string_data[i] == '%') return false;
  }
  // char string_data[MAXLENGTH] = "";
  replace_mod(string_data);
  bool is_concating_numbers_in_place = check_concating_numbers();

  bool is_one_dot_per_num = check_one_dot_per_num();
  delete_spaces();
  bool is_value_divided_with_operations = check_value_div_with_operations();
  int cnt_x_or_vals = 0;
  for (int i = 0; i < strlen(string_data); i++) {
    cnt_x_or_vals += isdigit(string_data[i]) or string_data[i] == 'x';
  }
  bool at_least_one_val = cnt_x_or_vals > 0;
  bool is_trash_symbols_in_place = check_trash();
  bool is_braces_devided_with_operations_or_funcs = check_braces_divided();
  const int length = strlen(string_data);
  for (int i = 0; i < length; i++) {
    string_data[i] = tolower(string_data[i]);
  }
  bool is_braces_in_place = check_braces_in_place();
  bool is_x_in_place = check_x_in_place();
  bool is_operation_in_place = check_operations_in_place();
  bool is_functions_in_place = check_functions_in_place();
  bool is_dots_in_place = check_dots_in_place();
  bool is_leading_zeros_in_place = check_leading_zeroes();

  set_data(string_init);

  return is_braces_in_place and is_dots_in_place and is_functions_in_place and
         is_x_in_place and is_operation_in_place and
         is_leading_zeros_in_place and is_value_divided_with_operations and
         is_trash_symbols_in_place and
         is_braces_devided_with_operations_or_funcs and
         is_concating_numbers_in_place and is_one_dot_per_num and
         at_least_one_val;
}

void CalculatorModel::build_num_lex(int *i, long double x_value, lexeme *lex) {
  const int length = strlen(string_data);
  char c = string_data[*i];
  long double value = 0;
  if (c == 'x') {
    value = x_value;
    if (*i - 1 >= 0 and string_data[*i - 1] == '-' and
        (*i - 2 < 0 or string_data[*i - 2] == '(')) {
      value = -value;
    }
  } else {
    value = get_num_value(*i);
    if (*i - 1 >= 0 and string_data[*i - 1] == '-' and
        (*i - 2 < 0 or string_data[*i - 2] == '(')) {
      value = -value;
    }
    while (*i < length and (isdigit(string_data[*i]) or
                            string_data[*i] == ',' or string_data[*i] == '.')) {
      (*i) = (*i) + 1;
    }
    (*i) = (*i) - 1;
  }

  lex->priority = PRIORITY_ZERO;
  lex->type = NUM_OR_X_TYPE;
  lex->value = value;
  sprintf(lex->printed, "%Lf", value);
}

void CalculatorModel::build_func_lex(int *i, lexeme *lex) {
  lex->priority = PRIORITY_HIGHEST;
  lex->type = FUNC_TYPE;
  int j = 0;
  int unary_sign = 0;
  if (*i - 1 >= 0 and string_data[*i - 1] == '-' and
      (*i - 2 < 0 or string_data[*i - 2] == '(')) {
    lex->printed[0] = '-';
    unary_sign = 1;
  }
  while (string_data[*i + j] != '(') {
    lex->printed[j + unary_sign] = string_data[*i + j];
    lex->operation[j] = string_data[*i + j];
    j++;
  }
  lex->printed[*i + j + unary_sign] = '\0';
  (*i) += j - 1;
}

void CalculatorModel::build_lexemes(lexeme *out_lexes, int *out_lexes_size,
                                    long double x_value) {
  const int length = strlen(string_data);
  lexeme lexes[MAXLENGTH];
  int size_lexes = 0;
  for (int i = 0; i < length; i++) {
    char c = string_data[i];
    lexeme lex;
    strcpy(lex.printed, "not_set");
    if (isdigit(c) or c == 'x') {
      build_num_lex(&i, x_value, &lex);
    } else if (isalpha(c) and c != 'x') {
      build_func_lex(&i, &lex);
    } else if (c == '(') {
      lex.priority = PRIORITY_NONE;
      lex.type = OPEN_TYPE;
      lex.printed[0] = '(';
      lex.printed[1] = '\0';
    } else if (c == ')') {
      lex.priority = PRIORITY_NONE;
      lex.type = CLOSING_TYPE;
      lex.printed[0] = ')';
      lex.printed[1] = '\0';
    } else if (is_unary_character_operator(c) and i > 0 and
               string_data[i - 1] != '(') {
      lex.priority = PRIORITY_ONE;
      lex.type = OPERATION_TYPE;
      lex.operation[0] = c;
      lex.printed[0] = c;
      lex.printed[1] = '\0';
    } else if (is_binary_character_operation(c) and c != '^') {
      lex.priority = PRIORITY_TWO;
      lex.type = OPERATION_TYPE;
      lex.printed[0] = c;
      lex.printed[1] = '\0';
      lex.operation[0] = c;
    } else if (c == '^') {
      lex.priority = PRIORITY_THREE;
      lex.type = OPERATION_TYPE;
      lex.printed[0] = c;
      lex.printed[1] = '\0';
      lex.operation[0] = c;
    }
    if (strcmp(lex.printed, "not_set") != 0) {
      lexes[size_lexes] = lex;
      size_lexes++;
    }
  }
  *out_lexes_size = size_lexes;
  for (int i = 0; i < size_lexes; i++) {
    out_lexes[i] = lexes[i];
  }
}

void CalculatorModel::dijkstra(lexeme in_lexes[], int *in_size,
                               lexeme out_lexes[], int *out_size) {
  lexeme stack[MAXLENGTH];
  int stack_size = 0;

  for (int i = 0; i < *in_size; i++) {
    lexeme cur_lex = in_lexes[i];
    if (cur_lex.type == NUM_OR_X_TYPE) {
      out_lexes[*out_size] = cur_lex;
      *out_size += 1;
    } else if (cur_lex.type == FUNC_TYPE or cur_lex.type == OPEN_TYPE) {
      stack[stack_size] = cur_lex;
      stack_size++;
    } else if (cur_lex.type == OPERATION_TYPE) {
      lexeme on_top = {0};
      if (stack_size > 0) {
        on_top = stack[stack_size - 1];
      }
      while (
          stack_size > 0 and on_top.type == OPERATION_TYPE and
          (on_top.priority > cur_lex.priority or
           on_top.priority == cur_lex.priority and cur_lex.printed[0] != '^')) {
        out_lexes[*out_size] = on_top;
        *out_size += 1;
        stack_size -= 1;
        if (stack_size > 0) {
          on_top = stack[stack_size - 1];
        }
      }
      stack[stack_size] = cur_lex;
      stack_size += 1;
    } else if (cur_lex.type == CLOSING_TYPE) {
      lexeme on_top = {0};
      if (stack_size > 0) {
        on_top = stack[stack_size - 1];
      }
      while (stack_size > 0 and on_top.type != OPEN_TYPE) {
        out_lexes[*out_size] = on_top;
        *out_size += 1;
        stack_size -= 1;
        if (stack_size > 0) on_top = stack[stack_size - 1];
      }
      stack_size -= 1;
      if (stack_size > 0 and stack[stack_size - 1].type == FUNC_TYPE) {
        out_lexes[*out_size] = stack[stack_size - 1];
        stack_size -= 1;
        *out_size += 1;
      }
    }
  }

  while (stack_size > 0) {
    out_lexes[*out_size] = stack[stack_size - 1];
    stack_size -= 1;
    *out_size += 1;
  }
}

long double CalculatorModel::polish_calc(lexeme pol_lexs[], int pol_size) {
  long double nums_stack[MAXLENGTH];
  int stack_size = 0;
  for (int i = 0; i < pol_size; i++) {
    lexeme cur_dah_tah_tah_lex = pol_lexs[i];
    if (cur_dah_tah_tah_lex.type == NUM_OR_X_TYPE) {
      long double next_val = 0;
      if (cur_dah_tah_tah_lex.printed[0] == 'x') {
        next_val = 1;
      } else {
        next_val = cur_dah_tah_tah_lex.value;
      }
      nums_stack[stack_size] = next_val;
      stack_size++;
    } else if (cur_dah_tah_tah_lex.type == OPERATION_TYPE) {
      long double val_1 = nums_stack[stack_size - 1];
      long double val_2 = nums_stack[stack_size - 2];
      long double res_of_oper = 0;
      if (cur_dah_tah_tah_lex.printed[0] == '+')
        res_of_oper = val_1 + (long double)(0.0) + val_2;
      if (cur_dah_tah_tah_lex.printed[0] == '-') res_of_oper = val_2 - val_1;
      if (cur_dah_tah_tah_lex.printed[0] == '*') res_of_oper = val_1 * val_2;
      if (cur_dah_tah_tah_lex.printed[0] == '/') res_of_oper = val_2 / val_1;
      if (cur_dah_tah_tah_lex.printed[0] == '%')
        res_of_oper = fmod(val_2, val_1);
      if (cur_dah_tah_tah_lex.printed[0] == '^')
        res_of_oper = pow(val_2, val_1);
      stack_size -= 1;
      nums_stack[stack_size - 1] = res_of_oper;
    } else {
      long double res_of_oper = 0;
      long double val = nums_stack[stack_size - 1];
      char *start_pos = cur_dah_tah_tah_lex.printed;
      int sign = 1;
      if (start_pos[0] == '-') {
        sign = -1;
        start_pos++;
      }
      if (start_pos[0] == 'c') res_of_oper = cos(val);
      if (strncmp(start_pos, "si", 2) == 0) res_of_oper = sin(val);
      if (start_pos[0] == 't') res_of_oper = tan(val);
      if (strncmp(start_pos, "ac", 2) == 0) res_of_oper = acos(val);
      if (strncmp(start_pos, "as", 2) == 0) res_of_oper = asin(val);
      if (strncmp(start_pos, "at", 2) == 0) res_of_oper = atan(val);
      if (strncmp(start_pos, "sq", 2) == 0) res_of_oper = sqrt(val);
      if (strncmp(start_pos, "ln", 2) == 0) res_of_oper = log(val);
      if (strncmp(start_pos, "lo", 2) == 0) res_of_oper = log10(val);
      nums_stack[stack_size - 1] = sign * res_of_oper;
    }
  }
  return nums_stack[0];
}

long double CalculatorModel::calculate(long double x_value) {
  char string_buff[MAXLENGTH] = "";
  strcpy(string_buff, string_data);
  if (not is_valid_input()) {
    // cout << ": " <<  << "\n";
    printf("\n|DEBUG:| string_data is : %s\n", this->string_data);
    printf("\n|Crush because of calculation on invalid string!|\n");
    return -123456789.0;
  }
  set_data(string_buff);
  replace_mod(string_data);

  delete_spaces();

  lexeme lexes[MAXLENGTH];
  int lexes_size = 0;
  build_lexemes(lexes, &lexes_size, x_value);

  lexeme polish_lexs[MAXLENGTH];
  int polish_size = 0;
  dijkstra(lexes, &lexes_size, polish_lexs, &polish_size);

  return polish_calc(polish_lexs, polish_size);
}

void CalculatorModel::set_data(char string_data[]) {
  strcpy(this->string_data, string_data);
  // strncpy(this->string_data, string_data, MAXLENGTH);
}

PYBIND11_MODULE(libcalculate, m) {
  pybind11::class_<CalculatorModel>(m, "CalculatorModel")
      .def(pybind11::init())
      .def("is_valid_input", &CalculatorModel::is_valid_input)
      .def("calculate", &CalculatorModel::calculate)
      .def("set_data", &CalculatorModel::set_data);
}
