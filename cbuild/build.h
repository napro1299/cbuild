#ifndef BUILD_H
#define BUILD_H

#include <stdbool.h>

#include "cli.h"

#define BUILD_CONFIG_FILE   "build.h"
#define BUILD_DIR           "build"

#ifdef __unix__
#   define CBUILD_BUILDSTRAP_SOURCES_DIR    "./buildstrap"
#   define CBUILD_INCLUDE_DIR               "./cbuild"
#endif

void cbuild_build_buildstrap(BuildOpts opts);

#endif