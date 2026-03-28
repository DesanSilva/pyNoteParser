#ifndef SETUP_H
#define SETUP_H

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>

typedef struct termios termios;
void enable_raw_mode();
void disable_raw_mode();

#endif
