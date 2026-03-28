#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/types.h"

void run_PTY(int shell) {
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

void log_raw_data(int fdMaster) {
    fd_set fds;
    char buf[1024];
    
    FILE *logPtr = fopen("session.log", "w");
    if (!logPtr) goto FILE_READ_ERR;

    while (1) {
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(fdMaster, &fds);

        int maxfd = (fdMaster > STDIN_FILENO ? fdMaster : STDIN_FILENO) + 1;

        if (select(maxfd, &fds, NULL, NULL, NULL) < 0) goto SELECT_ERR;

        // child: stdin user input
        if (FD_ISSET(STDIN_FILENO, &fds)) {
            int bytesRead = read(STDIN_FILENO, buf, sizeof(buf));

            if (!bytesRead){
                // Ctrl+D stopped by user
                close(fdMaster);
                break;
            }

            if (bytesRead < 0) goto STDIN_READ_ERR;

            write(fdMaster, buf, bytesRead);
        }

        // python output
        if (FD_ISSET(fdMaster, &fds)) {
            int bytesRead = read(fdMaster, buf, sizeof(buf));
            if (!bytesRead) break;  // child exited
            if (bytesRead < 0) goto STDOUT_READ_ERR;

            write(STDOUT_FILENO, buf, bytesRead);
            fwrite(buf, 1, bytesRead, logPtr);
        }
    }

WRITE_ERR:
STDOUT_READ_ERR:
STDIN_READ_ERR:
SELECT_ERR: 
    fflush(logPtr);
    fclose(logPtr);
FILE_READ_ERR: return;
}
