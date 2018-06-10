#include <stdio.h>
#include "mathinterpreter.h"

int main(){
	printf("%" PRId64 "\n", mathinterpreter_eval("784+434-345+35*6-56/54"));

	return 0;
}