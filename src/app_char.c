#include "app_char.h"

app_char_t app_ch;



int user_char_open(){
    app_ch.fd = open(CHAR_DEVICE_NODE,O_RDWR);
    if(app_ch.fd < 0){
        printf("Open %s Failed!\n",CHAR_DEVICE_NODE);
    	return 0;
    }
    return 1;
}

int user_char_read(){
    app_ch.retval = read(app_ch.fd,app_ch.data_buf,16);
    if(app_ch.retval < 0){
        printf("Read %s Failed!\n",CHAR_DEVICE_NODE);
    	return 0;
    }
    return 1;
}

/*
void user_char_write(char[] str){
    app_ch.retval = write(app_ch.fd,str,);    
}


void user_char_lseek(){
    app_ch.retval = lseek(fd,0,0);
}

*/

int user_char_ioctl(){
    app_ch.retval = ioctl(app_ch.fd,COMMAND_A,0);
    if(app_ch.retval < 0){
    	printf("Ioctl %s Failed!\n",CHAR_DEVICE_NODE);
	    return 0;
    }
    return 1;
}



