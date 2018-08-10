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
