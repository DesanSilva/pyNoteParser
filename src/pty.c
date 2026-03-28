#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/types.h"

void runPTY(int shell) {
    switch(shell) {
        case PYTHON: execlp("python3", "python3", (char*)NULL); break;
        case PYSPARK: execlp("pyspark", "pyspark", (char*)NULL); break;
        case MYSQL: break;  // TODO
        default: goto UNKNOWN_SHELL;
    }

UNKNOWN_SHELL:
    fprintf(stderr, "shell type undefined");
    exit(EXIT_FAILURE);
}


void log_raw_data(int fd) {

}
