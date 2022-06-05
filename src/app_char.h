#ifndef __APP_CHAR_H_
#define __APP_CHAR_H_

#include "config.h"
#include <fcntl.h>

#define CHAR_DEVICE_NODE "/dev/demo_control"
#define BUF_SIZE    256
#define COMMAND_A 'a'
#define COMMAND_B 'b'


typedef struct {
    int fd;
    int retval;
    char data_buf[BUF_SIZE];
}app_char_t;

int user_char_open(void);
int user_char_read(void);
int user_char_ioctl(void);

#endif
