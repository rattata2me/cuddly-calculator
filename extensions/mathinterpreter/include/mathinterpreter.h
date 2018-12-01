#ifndef CCALCMI_SRC_MATHINTERPRETER_H_
#define CCALCMI_SRC_MATHINTERPRETER_H_

#include "common.h"

#include <math.h>


// Character code
#define MI_NUM 'N'
#define MI_FUN 'F'
#define MI_PLUS '+'
#define MI_MINUS '-'
#define MI_MUL '*'
#define MI_DIV '/'
#define MI_POW '^'
#define MI_SUB_OPENER '('
#define MI_SUB_CLOSER ')'
#define MI_COMMA ','

// Errors
#define MI_ERR 'E'
#define MI_ERROR_SYNTAX 0x01
#define MI_ERROR_DIV_BY_ZERO 0x02
#define MI_ERROR_NONE 0x03

#define MI_OP_SIZE 6
extern const char hierarchy[MI_OP_SIZE];

//Functions, need to be defined from longest to shortest in alphabetical order
#define MI_FUN_SIN "sin"
#define MI_FUN_COS "cos"
#define MI_FUN_POW "pow"
#define MI_FUN_MOD "mod"
#define MI_FUN_PI "pi"
#define MI_FUN_X "x"
#define MI_FUN_ANS "ans"

#define MI_FUN_SIZE 7

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif

extern float MI_X;
extern char MI_USE_RADIANS;
extern char * functions[MI_FUN_SIZE];
extern const int functions_size[MI_FUN_SIZE]; // C...
extern char functions_search_bool[MI_FUN_SIZE];

typedef struct{

	char type;

	float value;

} Mi_Num_Node;

typedef struct{

	int size;
	void * args;

} Mi_Args;

typedef struct{

	char type;
	int fun_type;
	Mi_Args * args;

} Mi_Fun_Node;

typedef struct{

	char type;

	void * a;
	void * b;

} Mi_Op_Node;

typedef struct{

	char type;

	char code;

	char * error;

} Mi_Err_Node;

typedef union{

	Mi_Op_Node op;
	Mi_Num_Node num;
	Mi_Fun_Node fun;
	Mi_Err_Node err;

} Mi_Node;

int8_t mathinterpreter_eval_char(char * character);

int32_t mathinterpreter_pow(int32_t a, int x);

float mathinterpreter_solve(Mi_Node * node, Mi_Err_Node * error);

bool mathinterpreter_is_number(char * character);

char * mathinterpreterer_prepare_prediction(char * str, int startchar, int endchar);

int mathinterpreter_get_function_code(char * str, int startchar, int endchar);

Mi_Node * mathinterpreter_read_mono(char * equation, int startchar, int endchar);

float mathinterpreter_get_value_from_str(char * str, int startchar, int endchar);

Mi_Node * mathinterpreter_get_value_from_function(char * str, int startchar, int endchar);

Mi_Node * mathinterpreter_read(int hierarchy_level, char * equation, int startchar, int endchar);

float mathinterpreter_eval(char * equation, int len, Mi_Err_Node * error);

Mi_Node * mathinterpreter_error(char code, char * error);

void mathinterpreter_free(Mi_Node * node);

#endif
