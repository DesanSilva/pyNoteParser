#ifndef ARGS_H
#define ARGS_H

#include <stdint.h>

typedef enum __attribute__((packed)) {
    INVALID = 0,
    PYTHON,
    PYSPARK,
    TXT,
    NOTEBOOK,
    MARKDOWN
} argTypes;

typedef struct {
    uint8_t shell;
    uint8_t output;
} programConfig;

void print_version(void);
void print_help(void);

#endif
