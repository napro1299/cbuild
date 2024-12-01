#ifndef CLI_H
#define CLI_H

#include <stdbool.h>

typedef struct {
    bool verbose;
    const char *config;
} BuildOpts;

#endif