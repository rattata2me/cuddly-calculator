#include <stdio.h>
#include "mathinterpreter.h"

int main(){

	char equ[50];
	printf("Enter input: ");
	fgets(equ,50,stdin);
	printf("Response %" PRId64 "\n", mathinterpreter_eval(equ, strlen(equ)-1));
	return 0;
}