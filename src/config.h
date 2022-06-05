#ifndef __CONFIG_H_
#define __CONFIG_H_
    
#include <stdio.h>
#include <stdlib.h>


typedef struct{
    unsigned short ready_flag;
    int num1;
    int num2;
}num_value_t;

extern volatile num_value_t num_value;

#endif

