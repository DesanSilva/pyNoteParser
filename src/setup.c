#include "../include/setup.h"

void setup_PTY() {
    enable_raw_mode();
    // ensure terminal is restored on exit
    atexit(disable_raw_mode);
}

termios termOrig;
void enable_raw_mode() {
    // save original terminal settings
    tcgetattr(STDIN_FILENO, &termOrig);

    termios raw = termOrig;

    // disable echo + canonical mode
    raw.c_lflag &= ~(ECHO | ICANON); 

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &termOrig);
}
