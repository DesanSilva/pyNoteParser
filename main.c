#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pty.h>
#include "include/args.h"

typedef void (* parseFunc)();

programConfig handle_args(int, char**);


int main(int argc, char* argv[]) {
     
    programConfig cfg = handle_args(argc, argv);

    int masterFD;

    if (!forkpty(&masterFD, NULL, NULL, NULL)) {
        // child: runs Python on PTY (REPL)
        execlp("python", "python", NULL);
        perror("execlp");
        exit(1);
    }

    // Parent: parser
    //log_raw_data(&masterFD);

    switch(argv[1][1]) {
        default: perror("invalid argument trigger");
    }

    return 0;
}
