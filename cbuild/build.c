#include "build.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "util.h"

static bool build_config_exists() {
    FILE *file;
    if ((file = fopen(BUILD_CONFIG_FILE, "r"))) {
        fclose(file);
        return true;
    }

    return false;
}

static void verify_build_dir() {
    struct stat s;

    if (stat(BUILD_DIR, &s) != 0 || !S_ISDIR(s.st_mode)) {
        if (mkdir(BUILD_DIR, S_IRWXG | S_IROTH | S_IWOTH | S_IXOTH) != 0) {
            cbuild_error("failed to create build directory");
        }
    }
}

void cbuild_launch_buildstrap() {
    if (!build_config_exists()) {
        cbuild_error("build.h config not found.\n");
        exit(1);
    }

    verify_build_dir();

#ifdef __unix__
    if (system("which gcc > /dev/null 2>&1")) {
        cbuild_error("failed to build project buildstrap: gcc not found.\n");
        exit(1);
    }

    

#else
#   error "Linux only supported"
#endif
}