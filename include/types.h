#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef enum __attribute__((packed)) {
    INVALID = 0,
    PYTHON,
    PYSPARK,
    MYSQL,      // TODO
    TXT,
    NOTEBOOK,
    MARKDOWN
} argTypes;

typedef struct programConfig {
    uint8_t shell;
    uint8_t output;
} programConfig;

#endif
