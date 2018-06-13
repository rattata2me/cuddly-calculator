#include <stdio.h>
#include "mathinterpreter.h"

int main(){

	char equ[50];
	printf("Enter input: ");
	fgets(equ,50,stdin);
	Mi_Err_Node * error = NULL;
	float res = mathinterpreter_eval(equ, strlen(equ)-1, error);
	printf("Response %f\n", res);
	return 0;
}