#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include "types.h"
#define NULL 0

programConfig handle_args(int, char**);
void runPTY(uint8_t);
void log_raw_data(int);

typedef void (* parseFunc)(uint8_t);
void parse_txt(uint8_t);
void parse_notebook(uint8_t);
void parse_markdown(uint8_t);

static parseFunc parsers[] = {parse_txt, parse_notebook, parse_markdown};

#endif
