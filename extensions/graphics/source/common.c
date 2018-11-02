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

char * str_shorten(char * a, int amount){
	int len = str_len(a);
	if(len-amount >= 0){
		char * result = malloc(sizeof(char)*(len-amount+1));
		memcpy(result, a, sizeof(char)*(len-amount));
		result[len-amount] = '\0';
		free(a);
		return result;
	}
	return a;
}

unsigned char str_equal(char * a, char * b){
	int la = str_len(a);
	int lb = str_len(b);
	int lm = la < lb ? la : lb; // minimun length
	return memcmp(a, b, sizeof(char)*lm);
}

char ** str_divide(char * a, int cursor){
	int len = str_len(a);
	char ** result = malloc(sizeof(char*)*2);
	char * r1 = malloc(sizeof(char)*(cursor+1));
	memcpy(r1, a, cursor);
	r1[cursor] = '\0';
	char * r2 = malloc(sizeof(char)*(len-cursor+1));
	memcpy(r2, a+cursor, len-cursor);
	r2[len-cursor] = '\0';
	free(a);
	result[0] = r1;
	result[1] = r2;
	return result;
}

char * str_from_float(float value){
	char * buf = str_new("");
	sprintf (buf, "%f", (float)(value));
	return buf;
}
