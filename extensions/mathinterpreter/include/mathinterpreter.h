#ifndef CCALCMI_SRC_MATHINTERPRETER_H_
#define CCALCMI_SRC_MATHINTERPRETER_H_

#include "common.h"
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#define MI_NUM 'N'
#define MI_PLUS '+'
#define MI_MINUS '-'
#define MI_MUL '*'
#define MI_DIV '/'
#define MI_SUB_OPENER '('
#define MI_SUB_CLOSER ')'

extern const char hierarchy[5];

typedef struct{

	char type;

	int64_t value;

} Mi_Num_Node;

typedef struct{

	char type;

	void * a;
	void * b;

} Mi_Op_Node;

typedef union{

	Mi_Op_Node op;
	Mi_Num_Node num;

} Mi_Node;

int64_t mathinterpreter_eval(char * equation);

#endif