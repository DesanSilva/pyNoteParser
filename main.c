#include <pty.h>
#include "include/main.h"

int main(int argc, char* argv[]) {
    programConfig cfg = handle_args(argc, argv);
    int fd;

    // child: runs Python on PTY (REPL)
    if (!forkpty(&fd, NULL, NULL, NULL)) runPTY(cfg.shell);

    // Parent: log and parse session
    log_raw_data(fd);

    parsers[cfg.output](cfg.shell);

    return 0;
}
