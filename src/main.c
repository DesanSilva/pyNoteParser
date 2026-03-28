#include <pty.h>
#include "../include/main.h"

int main(int argc, char* argv[]) {
    programConfig cfg = handle_args(argc, argv);
    int fd;

    // enable signal handling and termio raw mode
    setup_PTY();

    // child: runs Python on PTY (REPL)
    if (!forkpty(&fd, NULL, NULL, NULL)) run_PTY(cfg.shell);

    // Parent: log and parse session
    log_raw_data(fd);

    parsers[cfg.output](cfg.shell);

    return 0;
}
