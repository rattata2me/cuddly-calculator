#ifndef CCALCLCDSIM_SRC_COMMON_H_
#define CCALCLCDSIM_SRC_COMMON_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

extern const char* endl;

#define CCALCLCDSIM_MAJOR_VERSION 0
#define CCALCLCDSIM_MINOR_VERSION 1
#define CCALCLCDSIM_PATCH_VERSION 1

extern const unsigned int CCALCLCDSIM_VERSION_NUMBER;

int sign(int x);

int str_len(char * str);

char * str_new(char * str);

char * str_concat(char * a, char * b);

char * str_append(char * a, unsigned char b);

char * str_shorten(char * a, int amount);

#endif

