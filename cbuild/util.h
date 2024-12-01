#ifndef UTIL_H
#define UTIL_H

#include "str.h"
#include "str-list.h"

#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1

void cbuild_error(const char *msg, ...);

void cbuild_panic(const char *msg, ...);

void verify_dir(const char *dir);

Str get_current_dir();

/**
 * System agnostic function to get a list of directories.
 */
StrList get_directories(const char *path, int *count);

#endif