#include "mathinterpreter.h"


// Overall hierarchy
const char hierarchy[] = {
	MI_PLUS,
	MI_MINUS,
	MI_MUL,
	MI_DIV,
	MI_POW,
	MI_NUM
};


// Functions, TODO Implement this in a proper way
char * functions[] = {
	MI_FUN_COS,
	MI_FUN_SIN,
	MI_FUN_MOD,
	MI_FUN_POW,
	MI_FUN_PI,
	MI_FUN_X
};
const int functions_size[] = {
	3,
	3,
	3,
	3,
	2,
	1
};

float MI_X = 1.0f;

char MI_USE_RADIANS = 0;

// This method is crappy af
char functions_search_bool[MI_FUN_SIZE];


// Slow, but with this method I avoid float errors; TODO use the 2 trick
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


// This method is essential when transforming from char array to float
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

char * mathinterpreterer_prepare_prediction(char * str, int startchar, int endchar){
	memset(functions_search_bool, 0, MI_FUN_SIZE);
	for(int i = startchar; i <= endchar; i++){
		for(int j = 0; j < MI_FUN_SIZE; j++){
			if(functions_size[j] > (i-startchar)){
				if(functions[j][i-startchar] != (str[i] | 0x20)) functions_search_bool[j] = 1;
			}else functions_search_bool[j] = 1;
		}
	}
	return functions_search_bool;
}

// Basic char * comparison
int mathinterpreter_get_function_code(char * str, int startchar, int endchar){

	int code = -1;

	mathinterpreterer_prepare_prediction(str, startchar, endchar);
	for(int i = 0; i < MI_FUN_SIZE; i++){
		if(!functions_search_bool[i] &&
			endchar-startchar == functions_size[i]-1) code = i;
		functions_search_bool[i] = 0;
	}
	return code;
}

// This function takes in the function string ex. "cos()" and returns its corresponding Mi_Node
Mi_Node * mathinterpreter_get_value_from_function(char * str, int startchar, int endchar){

	int endfun = endchar;
	for(int i = startchar; i<=endchar; i++){
		if(*(str+i) == MI_SUB_OPENER){
			endfun = i-1;
			break;
		}
	}

	// Only called if the function is just a parenthesis
	if(endfun+1 == startchar && startchar != endchar) return mathinterpreter_read(0, str, startchar+1, endchar-1);

	// Memory allocation for the function
	Mi_Node * fun = malloc(sizeof(Mi_Fun_Node));
	fun->fun.type = MI_FUN;

	//Get function code based on name string
	fun->fun.fun_type = mathinterpreter_get_function_code(str, startchar, endfun);

	//Read arguments
	Mi_Args * args = malloc(sizeof(Mi_Args));

	fun->fun.args = args; // Set function arguments

	if(endfun+2 == endchar || startchar == endchar){ // no arguments
		args->size = 0;
		return fun;
	}



	// stupid c... search comma
	int size = 0;
	for(int i = endfun+2; i <= endchar; i++){
		if(*(str+i) == MI_COMMA || i == endchar){
			size++;
		}
	}
	args->size = size;

	Mi_Node ** nodearg = malloc(sizeof(Mi_Node *)*size);
	int lc = endfun+1;
	int c = 0;
	for(int i = endfun+2; i <= endchar; i++){
		if(*(str+i) == MI_COMMA || i == endchar){
			Mi_Node * node = mathinterpreter_read(0, str, lc+1, i-1);
			nodearg[c] = node;
			c++;
			lc = i;
		}
	}
	args->args = nodearg;


	return fun;
}

Mi_Node * one(){
	Mi_Node * one = malloc(sizeof(Mi_Node));
	one->num.type = MI_NUM;
	one->num.value = 1.0f;
	return one;
}

Mi_Node * mathinterpreter_read_mono(char * equation, int startchar, int endchar){

	//Memory allocation for an empty mul
	Mi_Node * this = malloc(sizeof(Mi_Node));
	this->op.type = MI_MUL;
	this->op.a = one();
	this->op.b = one();

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
				addcurrent->op.b = one();

				current->op.b = addcurrent;
				current = addcurrent;

				li = i;


			// Only true when comming from a function to a number sin()_(here)_3
			}else if(val != 0 || ltype == -1){

				Mi_Node *  addcurrent = malloc(sizeof(Mi_Node));
				addcurrent->op.type = MI_MUL;

				addcurrent->op.a = mathinterpreter_get_value_from_function(equation, li, i-1);
				addcurrent->op.b = one();

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
#ifdef DEBUG
	printf("Lvl: %c; Startchar: %i; Endchar: %i; String ", hierarchy[hierarchy_level], startchar, endchar);
	for(int i = startchar; i <= endchar; i++){
		printf("%c", equation[i]);
	}
	printf("\n");
	//END
#endif

	// Syntax error detected, this is mostly caused by double operator
	if(startchar > endchar){

		//Negative void TODO Fix this for functions
		if(equation[startchar] == MI_MINUS && !mathinterpreter_internal_is_op(equation+startchar+1)){
			Mi_Node * this = malloc(sizeof(Mi_Node));
			this->num.type = MI_NUM;
			this->num.value = 0.0f;
			return this;
		}

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

const float epsilon = 0.0001f;
float mi_cos(float a){
	if(!MI_USE_RADIANS){
		if(a >= M_PI/2-epsilon && a <=M_PI/2+epsilon) return 0.0f;
		if(a >= (M_PI/2)*3-epsilon && a <=(M_PI/2)*3+epsilon) return 0.0f;
	}
	return cos(a);
}
float mi_sin(float a){
	if(a >= M_PI-epsilon && a <=M_PI+epsilon) return 0.0f;
	if(a >= M_PI*2-epsilon && a <=M_PI*2+epsilon) return 0.0f;
	return sin(a);
}

float mathinterpreter_solve(Mi_Node * node, Mi_Err_Node * error){


	switch(node->op.type){

		case MI_NUM:
			return node->num.value;

		case MI_FUN:
			switch(node->fun.fun_type){
				// TODO Create a better method
				case 0: // Cos
					if(node->fun.args->size == 1){
						float a = mathinterpreter_solve(*((Mi_Node**)node->fun.args->args), error);
						if(!MI_USE_RADIANS) a = (a/180)*M_PI;
						return mi_cos(a);
					}else *error = mathinterpreter_error(MI_ERROR_SYNTAX, "Invalid args")->err;
					break;

				case 1: // Sin
					if(node->fun.args->size == 1){
						float a = mathinterpreter_solve(*((Mi_Node**)node->fun.args->args), error);
						if(!MI_USE_RADIANS) a = (a/180)*M_PI;
						return mi_sin(a);
					}else *error = mathinterpreter_error(MI_ERROR_SYNTAX, "Invalid args")->err;
					break;

				case 2: // Mod %
					if(node->fun.args->size == 2){
						float a = mathinterpreter_solve(*((Mi_Node**)node->fun.args->args), error);
						float b = mathinterpreter_solve(*((Mi_Node**)node->fun.args->args+1), error);
						return (int)a%(int)b;
					}else *error = mathinterpreter_error(MI_ERROR_SYNTAX, "Invalid args")->err;
					break;

				case 3: // Pow
					if(node->fun.args->size == 2){
						float a = mathinterpreter_solve(*((Mi_Node**)node->fun.args->args), error);
						float b = mathinterpreter_solve(*((Mi_Node**)node->fun.args->args+1), error);
						if(b < 1.0f && a < 0) return 0.0f;
						return powf(a,b);
					}else *error = mathinterpreter_error(MI_ERROR_SYNTAX, "Invalid args")->err;
					break;

				case 4: // Number pi
					if(node->fun.args->size == 0){
						return M_PI;
					}else *error = mathinterpreter_error(MI_ERROR_SYNTAX, "Invalid args")->err;

				case 5: // X
					if(node->fun.args->size == 0){
						return MI_X;
					}else *error = mathinterpreter_error(MI_ERROR_SYNTAX, "Invalid args")->err;

				default:
					*error = mathinterpreter_error(MI_ERROR_SYNTAX, "Invalid function name")->err;
					return 1.0f;
			}
			break;

		float a = 0.0f;
		float b = 0.0f;

		case MI_PLUS:
			a = mathinterpreter_solve(node->op.a, error);
			b = mathinterpreter_solve(node->op.b, error);
			return a+b;

		case MI_MINUS:
			a = mathinterpreter_solve(node->op.a, error);
			b = mathinterpreter_solve(node->op.b, error);
			return a-b;

		case MI_MUL:
			a = mathinterpreter_solve(node->op.a, error);
			b = mathinterpreter_solve(node->op.b, error);
			return a*b;

		case MI_DIV:
			a = mathinterpreter_solve(node->op.a, error);
			b = mathinterpreter_solve(node->op.b, error);
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
			if(b < 1.0f && a < 0) return 0.0f;

			return powf(a, b);

		default:
			*error = node->err;
			return 0.0f;
	}

	return 0.0f;
}

void mathinterpreter_free(Mi_Node * node){
	switch(node->op.type){
		case MI_NUM:
			break;

		case MI_FUN:
			for(int i = 0; i < node->fun.args->size; i++){
				mathinterpreter_free(*((Mi_Node**)node->fun.args->args+i));
			}
			break;

		default:
			if(node->op.type == MI_PLUS || node->op.type == MI_PLUS ||
				node->op.type == MI_MUL || node->op.type == MI_DIV || node->op.type == MI_POW){
				mathinterpreter_free(node->op.a);
				mathinterpreter_free(node->op.b);
			}
	}
	free(node);
}

float mathinterpreter_eval(char * equation, int len, Mi_Err_Node * error){

	Mi_Node * node = mathinterpreter_read(0, equation, 0, len-1);

	float r = mathinterpreter_solve(node, error);
	mathinterpreter_free(node);

	return r;
}

Mi_Node * mathinterpreter_error(char code, char * error){

	Mi_Node * this = malloc(sizeof(Mi_Node));
	this->err.type = MI_ERR;
	this->err.code = code;
	this->err.error = error;

	return this;
}
