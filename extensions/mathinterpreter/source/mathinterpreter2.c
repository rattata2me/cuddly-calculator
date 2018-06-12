#include "mathinterpreter.h"


// Simple pow function, more reliability than math pow? TODO: Create specific function for base 10,
int64_t mathinterpreter_pow(int64_t a, int x){
	
	int64_t val = 1;
	for(int i = 0; i < x; i++){
		val = val*a;
	}
	return val;
}


int64_t mathinterpreter_eval_mul(char * equation, int startchar, int ednchar){
	return 1;
}


int64_t mathinterpreter_eval_sum(char * equation, int startchar, int endchar){


	bool par = false;

	int last  = 0;

	char sign = 1;

	int64_t val = 0;

	for(int i = 0; i <= endchar; i++){
		if(equation[i] == MI_SUB_OPENER) par = true;
		if(equation[i] == MI_SUB_CLOSER) par = false;

		// TODO divide this into steps to track down syntax errors like open (
		if((par == false) && (((equation[i] == MI_PLUS) || (equation[i] == MI_MINUS)) || (i == endchar))){

			if(i == endchar) i++;
			val = val + (sign * mathinterpreter_eval_mul(equation, last, i-1));
			sign = (equation[i] == MI_MINUS) ? (-1) : (1);
			last = i+1;
		}

	}

	return val;
}


int64_t mathinterpreter_eval(char * equation){

	int tsize = strlen(equation);

	mathinterpreter_eval_sum(equation, 0, tsize-1);

	return 1;
}

int8_t mathinterpreter_eval_char(char * character){

	int8_t val = *character;
	val = val - 0x30;  // Ascii number offset
	return val;
}


bool mathinterpreter_is_number(char * character){
	// Check ascii values from 0 to 9
	return ((*character > 0x2F) && (*character < 0x3A));
}


int64_t mathinterpreter_get_value_from_str(char * str, int startchar, int endchar){

	int64_t val = 0;

	for(int i = startchar; i <= endchar; i++){

		// Not really needed but idk
		if(mathinterpreter_is_number(str+i)){
			val = val + ((int64_t)mathinterpreter_eval_char(str+i))*mathinterpreter_pow(0xA, endchar-i);
		}
	}

	return val;
}