#include "mathinterpreter.h"

const char hierarchy[] = {
	MI_PLUS,
	MI_MINUS,
	MI_MUL,
	MI_DIV,
	MI_POW,
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

bool mathinterpreter_internal_is_op(char * character){
	for(int i = 0; i < MI_OP_SIZE-1; i++){
		if(hierarchy[i] == *character) return true;
	}
	return false;
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
	return (e == 0 ? (float)val : val+val2);
}

Mi_Node * mathinterpreter_get_value_from_function(char * str, int startchar, int endchar){

	Mi_Node * one = malloc(sizeof(Mi_Node));
	one->num.type = MI_NUM;
	one->num.value = 1.0f;


	int endfun = startchar;
	for(int i = startchar; i<=endchar; i++){
		if(*(str+i) == MI_SUB_OPENER){
			endfun = i;
			break;
		}
	}

	// Only called if the function is just a parenthesis
	if(endfun == startchar) return mathinterpreter_read(0, str, startchar+1, endchar-1);
	
	// Memory allocation for the function
	Mi_Node * fun = malloc(sizeof(Mi_Fun_Node));
	fun->fun.type = MI_FUN;

	//Read arguments
	Mi_Args * args = malloc(sizeof(Mi_Args));

	fun->fun.args = args; // Set function arguments

	if(endfun+1 == endchar){ // no arguments
		args->size = 0;
		return fun;
	}

	

	// stupid c...
	int size = 0;
	for(int i = endfun+1; i <= endchar; i++){
		if(*(str+i) == MI_COMMA || i == endchar){
			size++;
		}
	}
	args->size = size;

	printf("Size %i\n", size);
	
	Mi_Node ** nodearg = malloc(sizeof(Mi_Node *)*size);
	int lc = endfun;
	int c = 0;
	for(int i = endfun+1; i <= endchar; i++){
		if(*(str+i) == MI_COMMA || i == endchar){
			*(nodearg+c) = mathinterpreter_read(0, str, lc+1, i-1); 
			c++;
			for(int j = lc+1; j < i; j++){

				printf("%c", *(str+j));
			}
			printf("\n");
			lc = i;
		}
	}
	args->args = nodearg;

	
	return one;
}

Mi_Node * mathinterpreter_read_mono(char * equation, int startchar, int endchar){

	// One object
	Mi_Node * one = malloc(sizeof(Mi_Node));
	one->num.type = MI_NUM;
	one->num.value = 1.0f;

	//Memory allocation for an empty mul
	Mi_Node * this = malloc(sizeof(Mi_Node));
	this->op.type = MI_MUL;
	this->op.a = one;
	this->op.b = one;

	Mi_Node * current = this;

	char ltype = MI_NUM;
	int li = startchar;
	int par = 0;

	char ntype = 0;

	for(int i = startchar; i <= endchar+1; i++){


		// Parenthesis stuff
		if(equation[i] == MI_SUB_OPENER) par--;

		if(equation[i] == MI_SUB_CLOSER) par++;


		

		// Get the new type of character
		if(i > endchar) ntype = (ltype == MI_NUM ? MI_FUN : MI_NUM);
		else{

			if(equation[i] == MI_SUB_CLOSER && par == 0){
		
				ltype = -1; // If a parenthesis ends, there is a new function
				i++;

			}

			ntype = (mathinterpreter_is_number(equation+i) || (equation[i]) == 0x2E) ? MI_NUM : MI_FUN;
			if(par) ntype = MI_FUN;
		}
		char val = ltype - ntype; // this simplify a lot the logic

		
		printf("ltype = %c, ntype = %c, val = %i, i = %i\n", ltype, ntype, val, i);
		
		if(i!= startchar){
			

			// This is true if the program has found the start of a function,
			if(val == MI_NUM - MI_FUN){

				// Read the nummber
				
				Mi_Node *  addcurrent = malloc(sizeof(Mi_Node));
				addcurrent->op.type = MI_MUL;
					
				Mi_Node * number = malloc(sizeof(Mi_Node));
				number->num.type = MI_NUM;
				number->num.value = mathinterpreter_get_value_from_str(equation, li, i-1);

				addcurrent->op.a = number;
				addcurrent->op.b = one;

				current->op.b = addcurrent;
				current = addcurrent;

				// Debug
				printf("Number!! ");
				for(int j = li; j < i; j++){
					printf("%c", equation[j]);
				}
				printf("\n");

				li = i;

				
				
			
			// Only true when comming from a function to a number sin()_(here)_3
			}else if(val != 0 || ltype == -1){

				// Debug
				printf("Function!! ");
				for(int j = li; j < i; j++){
					printf("%c", equation[j]);
				}
				printf("\n");

				Mi_Node *  addcurrent = malloc(sizeof(Mi_Node));
				addcurrent->op.type = MI_MUL;

				addcurrent->op.a = mathinterpreter_get_value_from_function(equation, li, i-1);
				addcurrent->op.b = one;

				current->op.b = addcurrent;
				current = addcurrent;

				

				li = i;
				
				
			}
		}
		ltype = ntype; // Set the ltype to keep track of the prev. char.
	}
	return this;
}

Mi_Node * mathinterpreter_read(int hierarchy_level, char * equation, int startchar, int endchar){


	// Debug information START
	printf("Lvl: %c; Startchar: %i; Endchar: %i; String ", hierarchy[hierarchy_level], startchar, endchar);
	for(int i = startchar; i <= endchar; i++){
		printf("%c", equation[i]);
	}
	printf("\n");
	//END
	
	//Easy fix
	// if(equation[endchar] == MI_SUB_CLOSER && equation[startchar] == MI_SUB_OPENER)
	//	return mathinterpreter_read(0, equation, startchar+1, endchar-1);

	// Syntax error detected, this is mostly caused by double operator
	if(startchar > endchar){
		
		//Negative void TODO Fix this for functions
		if(equation[startchar] == MI_MINUS && !mathinterpreter_internal_is_op(equation+startchar+1)){
			Mi_Node * this = malloc(sizeof(Mi_Node));
			this->num.type = MI_NUM;
			this->num.value = 0.0f;
			return this;
		}


		printf("Error\n");
		return mathinterpreter_error(MI_ERROR_SYNTAX, "Syntax error");
	}

	// If it is a number
	if(hierarchy_level > (MI_OP_SIZE-2)){

		return mathinterpreter_read_mono(equation, startchar, endchar);

	}
	
	int par = 0;

	for(int i = endchar; i >= startchar; i--){
		
		if(equation[i] == MI_SUB_OPENER) par--;
		if(equation[i] == MI_SUB_CLOSER) par++;

		int part = par < 0 ? 0 : par;

		if((!part) && (equation[i] == hierarchy[hierarchy_level])){

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
	if(par != 0) return mathinterpreter_error(MI_ERROR_SYNTAX, "Syntax error");

	return mathinterpreter_read((hierarchy_level+1), equation, startchar, endchar);

}

float mathinterpreter_solve(Mi_Node * node, Mi_Err_Node * error){

	
	switch(node->op.type){

		case MI_NUM:
			return node->num.value;

		float a = 0.0f;
		float b = 0.0f;

		case MI_PLUS:
			a = mathinterpreter_solve(node->op.a, error);
			b = mathinterpreter_solve(node->op.b, error);
			printf("Addition a %f + b %f result = %f\n", a, b, a+b);
			return a+b;

		case MI_MINUS:
			a = mathinterpreter_solve(node->op.a, error);
			b = mathinterpreter_solve(node->op.b, error);
			printf("Substraction a %f - b %f result = %f\n", a, b, a-b);
			return a-b;

		case MI_MUL:
			a = mathinterpreter_solve(node->op.a, error);
			b = mathinterpreter_solve(node->op.b, error);
			printf("Multiplication a %f * b %f result = %f\n", a, b, a*b);
			return a*b;

		case MI_DIV:
			a = mathinterpreter_solve(node->op.a, error);
			b = mathinterpreter_solve(node->op.b, error);
			printf("Division a %f/b %f result = %f\n", a, b, a/b);
			//Division by zero
			if(b == 0.0f){
				*error = (mathinterpreter_error(MI_ERROR_DIV_BY_ZERO, 
					"Can not divide by zero")->err);
				return 0.0f;
			}
			return a/b;

		case MI_POW:
			a = mathinterpreter_solve(node->op.a, error);
			b = mathinterpreter_solve(node->op.b, error);
			printf("Power a %f ^ b %f result = %f\n", a, b, powf(a, b));
			return powf(a, b);

		default:
			*error = node->err;
			return 0.0f;
	}

	return 0.0f;
}


float mathinterpreter_eval(char * equation, int len, Mi_Err_Node * error){

	Mi_Node * n = mathinterpreter_read(0, equation, 0, len-1);

	return mathinterpreter_solve(n, error);
}

Mi_Node * mathinterpreter_error(char code, char * error){

	Mi_Node * this = malloc(sizeof(Mi_Node));
	this->err.type = MI_ERR;
	this->err.code = code;
	this->err.error = error;

	return this;
}

