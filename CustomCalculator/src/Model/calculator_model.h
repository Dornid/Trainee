#ifndef CALCULATE_H
#define CALCULATE_H

#include <ctype.h>
#include <iso646.h>
#include <locale.h>
#include <math.h>
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

long double calculate(char string[], long double x_value);
bool is_valid_input(char string[]);

typedef struct {
  long double value;
  int priority;
  char operation[10];
  int type;
  char printed[10];
} lexeme;

#endif  // CALCULATE_H
