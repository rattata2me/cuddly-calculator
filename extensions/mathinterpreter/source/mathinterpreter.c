#include "mathinterpreter.h"

const char hierarchy[] = {
	MI_MINUS,
	MI_PLUS,
	MI_DIV,
	MI_MUL,
	MI_NUM	
};

// Slow, but with this method I avoid float errors;
int32_t mathinterpreter_pow(int32_t a, int x){
	
	int32_t val = 1;
	for(int i = 0; i < x; i++){
		val = val*a;
	}
	return val;
}

bool mathinterpreter_is_number(char * character){
	// Check ascii values from 0 to 9
	return ((*character > 0x2F) && (*character < 0x3A));
}

int8_t mathinterpreter_eval_char(char * character){

	int8_t val = *character;
	val = val - 0x30;  // Ascii number offset
	return val;
}

float mathinterpreter_get_value_from_str(char * str, int startchar, int endchar){
	
	//Comma position
	int e = 0;

	endchar = ((endchar-startchar) > 6 ? startchar+6 : endchar);

	// TODO: limit number of commas and check for illegal characters
	for(int i = startchar; (i <= endchar); i++){
		if(*(str+i) == 0x2E){
			e = i;
		}
	}

	int32_t val = 0;
	float val2 = 0;

	int exp = 0;
	int l = endchar - startchar - (e == 0 ? 0 : 1);
	for(int i = startchar; (i <= endchar); i++){
		if(mathinterpreter_is_number(str+i)){
			if(exp < (e-startchar) || e == 0) val = val + 
				mathinterpreter_eval_char(str+i)*mathinterpreter_pow(0xA,l-exp-(e == 0 ? 0 : endchar-e));
			else val2 = val2 + 
				mathinterpreter_eval_char(str+i)*(1.0f/mathinterpreter_pow(0xA,exp-(e-startchar)+1));
			exp++;
		}
	}
	printf("Number %f\n" , (e == 0 ? (float)val : val+val2));
	return (e == 0 ? (float)val : val+val2);
}

/*
// TODO FIX THIS
float mathinterpreter_get_value_from_str(char * str, int startchar, int endchar){

	int32_t val = 0;
	int e = 0;
	for(int i = startchar; (i <= endchar) && (startchar+10); i++){
		if(*(str+i) == 0x2E){
			e = i;
		}
	}
	for(int i = startchar; (i <= endchar) && (i < (startchar+10)); i++){
		// Not really needed but idk
		char t = i-((i >= e) && (e > 0) ? 1 : 0);
		if(mathinterpreter_is_number(str+i)){
			val = val + ((int32_t)mathinterpreter_eval_char(str+i))
				*mathinterpreter_pow(0xA, (endchar-(e == 0 ? 0 : 1))-t);
		}
	}
	float r = ((float)val/mathinterpreter_pow(0xA, (e > 0 ? endchar-e : 0)));
	printf("Number: %f\n", r);
	return r;
}
*/


Mi_Node * mathinterpreter_read(int hierarchy_level, char * equation, int startchar, int endchar){

	int par = 0;

	

	// Debug information START
	printf("Lvl: %c; Startchar: %i; Endchar: %i; String ", hierarchy[hierarchy_level], startchar, endchar);
	for(int i = startchar; i <= endchar; i++){
		printf("%c", equation[i]);
	}
	printf("\n");

	if((equation[startchar] == MI_SUB_OPENER) && (equation[endchar] == MI_SUB_CLOSER)){
		return mathinterpreter_read(0, equation, startchar+1, endchar-1);
	}
	//END



	// Syntax error detected, this is mostly caused by double operator
	if(startchar > endchar){
		printf("Error\n");
		return mathinterpreter_error(MI_ERR, "Syntax error");
	}

	// If it is a number
	if(hierarchy_level > 3){

		Mi_Node * this = malloc(sizeof(Mi_Node));
		this->num.type = MI_NUM;
		this->num.value = 4;
		mathinterpreter_get_value_from_str(equation, startchar, endchar);
		return this;

	}
	
	for(int i = startchar; i <= endchar; i++){
		
		if(equation[i] == MI_SUB_OPENER) par++;
		if(equation[i] == MI_SUB_CLOSER) par--;
		
		if((!par) && (equation[i] == hierarchy[hierarchy_level])){

			// TODO Add syntax error handlers

			Mi_Node * a = mathinterpreter_read(hierarchy_level, equation, startchar, (i-1));
			Mi_Node * b = mathinterpreter_read(hierarchy_level, equation, (i+1), endchar);

			Mi_Node * this = malloc(sizeof(Mi_Node));
			this->op.type = hierarchy[hierarchy_level];
			this->op.a = a;
			this->op.b = b;
			return this; 

		}
	}

	return mathinterpreter_read((hierarchy_level+1), equation, startchar, endchar);

}

void read_r(Mi_Node * node){



}


int64_t mathinterpreter_eval(char * equation, int len){

	Mi_Node * n = mathinterpreter_read(0, equation, 0, len-1);
	read_r(n);
	
	return 3;
}

Mi_Node * mathinterpreter_error(char code, char * error){

	Mi_Node * this = malloc(sizeof(Mi_Node));
	this->err.type = MI_ERR;
	this->err.code = code;
	this->err.error = error;

	return this;
}

