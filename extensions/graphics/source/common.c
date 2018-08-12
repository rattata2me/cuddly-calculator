#include "common.h"

const char* endl = "\n";

const unsigned int CCALCLCDSIM_VERSION_NUMBER = ((CCALCLCDSIM_MAJOR_VERSION & 0xff) << 0xf) + ((CCALCLCDSIM_MINOR_VERSION & 0xff) << 0x8) + (CCALCLCDSIM_PATCH_VERSION & 0xff);


int sign(int x){
    return (x > 0 ? 1 : -1);
}

int str_len(char * str){
	int i = 0;
	while(str[i] != '\0') i++;
	return i;
}

char * str_new(char * str){
	
	int len = str_len(str);
	char * result = malloc(sizeof(char)*(len+1));
	memcpy(result, str, sizeof(char)*len);
	result[len] = '\0';

	return result;

}

char * str_concat(char * a, char * b){
	
	int len_a = str_len(a);
	int len_b = str_len(b);

	char * result = malloc(sizeof(char)*len_a+sizeof(char)*(len_b+1));
	memcpy(result, a, sizeof(char)*len_a);
	memcpy(result+len_a, b, sizeof(char)*len_b);
	result[len_a+len_b] = '\0';
	free(a);
	free(b);
	return result;


}

char * str_append(char * a, unsigned char b){
	int len = str_len(a);
	char * result = malloc(sizeof(char)*(len+2));
	memcpy(result, a, sizeof(char)*len);
	result[len] = b;
	result[len+1] = '\0';
	free(a);
	return result;
}

