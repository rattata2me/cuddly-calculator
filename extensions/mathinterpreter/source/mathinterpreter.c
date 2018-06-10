#include "mathinterpreter.h"

const char hierarchy[] = {
	MI_MINUS,
	MI_PLUS,
	MI_DIV,
	MI_MUL,
	MI_NUM	
};

int a = 0;

Mi_Node * mathinterpreter_read(int hierarchy_level, char * equation, int startchar, int endchar){

	a ++;
	if(a >= 50) return NULL;
	bool par = false;

	printf("Lvl: %i; Startchar: %i; Endchar: %i; ", hierarchy_level, startchar, endchar);
	for(int i = startchar; i <= endchar; i++){
		printf("%c", equation[i]);
	}
	printf("\n");

	if(hierarchy_level > 3){
		Mi_Node * this = malloc(sizeof(Mi_Node));
		this->num.type = MI_NUM;
		this->num.value = 4;
		return this;
	}
	
	for(int i = startchar; i <= endchar; i++){
		
		if(equation[i] == MI_SUB_OPENER) par = true;
		if(equation[i] == MI_SUB_CLOSER) par = false;
		
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
/*
	if(((Mi_Node * )node->op.a)->op.type == MI_NUM){
		printf("%" PRId64 "\n", ((Mi_Node * )node->op.a)->num.value);
	}else{
		read_r(node->op.a);
	}
	if(((Mi_Node * )node->op.b)->op.type == MI_NUM){
		printf("%" PRId64 "\n", ((Mi_Node * )node->op.b)->num.value);
	}else{
		read_r(node->op.b);
	}
*/
}


int64_t mathinterpreter_eval(char * equation){

	int tsize = strlen(equation);
	Mi_Node * n = mathinterpreter_read(0, equation, 0, tsize-1);
	read_r(n);
	
	return 3;
}