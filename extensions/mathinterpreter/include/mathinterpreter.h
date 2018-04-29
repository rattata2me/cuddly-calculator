#ifndef CCALCMI_SRC_MATHINTERPRETER_H_
#define CCALCMI_SRC_MATHINTERPRETER_H_

#include "common.h"
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

const static char MI_PLUS = '+';
const static char MI_MINUS = '-';
const static char MI_MUL = '*';
const static char MI_DIV = '/';
const static char MI_SUB_OPENER  = '(';
const static char MI_SUB_CLOSER = ')';

int64_t mathinterpreter_eval(char * equation);
int64_t mathinterpreter_eval_sum(char * equation, int startchar, int endchar);
int64_t mathinterpreter_eval_mul(char * equation, int startchar, int ednchar);
bool mathinterpreter_is_number(char * character);
int8_t mathinterpreter_eval_char(char * character);
int64_t mathinterpreter_get_value_from_str(char * str, int startchar, int endchar);

#endif