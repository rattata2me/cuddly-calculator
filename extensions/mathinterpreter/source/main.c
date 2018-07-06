#include <stdio.h>
#include "mathinterpreter.h"

int main(){

	while(1){
		char equ[50];
		printf("Enter input: ");
		fgets(equ,50,stdin);
		Mi_Err_Node error;
		error = mathinterpreter_error(MI_ERROR_NONE, "")->err;
		float res = mathinterpreter_eval(equ, strlen(equ)-1, &error);
		if(error.code == MI_ERROR_NONE){
			printf("Response %f\n", res);
		}else{
			printf("ERROR: %s\n", error.error);
		}
	}
	return 0;
}