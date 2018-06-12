#ifndef CCALCMI_SRC_MATHINTERPRETER_H_
#define CCALCMI_SRC_MATHINTERPRETER_H_

#include "common.h"

#define MI_NUM 'N'
#define MI_PLUS '+'
#define MI_MINUS '-'
#define MI_MUL '*'
#define MI_DIV '/'
#define MI_SUB_OPENER '('
#define MI_SUB_CLOSER ')'

#define MI_ERR 'E'
#define MI_ERROR_SYNTAX 0x01

extern const char hierarchy[5];

typedef struct{

	char type;

	float value;

} Mi_Num_Node;

typedef struct{

	char type;

	void * a;
	void * b;

} Mi_Op_Node;

typedef struct
{
	
	char type;

	char code;

	char * error;

} Mi_Err_Node;

typedef union{

	Mi_Op_Node op;
	Mi_Num_Node num;
	Mi_Err_Node err;

} Mi_Node;

int8_t mathinterpreter_eval_char(char * character);

int32_t mathinterpreter_pow(int32_t a, int x);

bool mathinterpreter_is_number(char * character);

Mi_Node * mathinterpreter_read(int hierarchy_level, char * equation, int startchar, int endchar);

int64_t mathinterpreter_eval(char * equation, int len);

Mi_Node * mathinterpreter_error(char code, char * error);

#endif