#ifndef CALCULATE_H
#define CALCULATE_H

#include <ctype.h>
#include <iso646.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define STACK_CAPACITY 300

// delete it!
#include <stdio.h>

#define STACK_CAPACITY 300
// #define CLOSE_BRACKET_TYPE 1
// #define CLOSE_BRACKET_PROIRITY 0
// #define OPEN_BRACKET_TYPE 2
// #define OPEN_BRACKET_PROIRITY 0
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

// #define X_TYPE 3
// #define PLUS_TYPE 4
// #define MINUS_TYPE 5
// #define MUL_TYPE 6
// #define DIV_TYPE 7
// #define MOD_TYPE 8
// #define POW_TYPE 9

long double calculate(char string[], long double x_value);
bool is_valid_input(char string[]);
// struct stack
// {
//     /* data */
// };

typedef struct {
  long double value;
  int priority;
  char operation[10];
  int type;
  char printed[10];
} lexeme;

// typedef struct {
//   lexeme lexemes[STACK_CAPACITY];
//   int size;
// } stack_t;

// lexeme pop(stack_t *stack);
// lexeme peek(stack_t *stack);
// void push(stack_t *stack, lexeme *lex);
// void create_stack(stack_t *stack);
// int size(stack_t *stack);

#endif  // CALCULATE_H
