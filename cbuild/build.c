#include "build.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifdef __unix__
#   include <sys/types.h>
#   include <sys/stat.h>
#else
#   error "Linux is only supported"
#endif

#include "util.h"
#include "str.h"

static bool build_config_exists() {
    FILE *file;
    if ((file = fopen(BUILD_CONFIG_FILE, "r"))) {
        fclose(file);
        return true;
    }

    return false;
}

void cbuild_build_buildstrap(BuildOpts opts) {
    if (!build_config_exists()) {
        cbuild_panic("build.h config not found.\n");
    }
    verify_dir(BUILD_DIR);

#ifdef __unix__
    if (system("which gcc > /dev/null 2>&1")) {
        cbuild_panic("failed to build project buildstrap: gcc not found.\n");
    }

    Str build_buildstrap_command = str_make_from("gcc " CBUILD_BUILDSTRAP_SOURCES_DIR "/buildstrap.c " CBUILD_INCLUDE_DIR "/str.c " CBUILD_INCLUDE_DIR "/util.c -include " CBUILD_INCLUDE_DIR "/cbuild.h -I. -o build/build");
    int failed;

    if (opts.config) {
        str_append(&build_buildstrap_command, " -D");
        str_append(&build_buildstrap_command, opts.config);
    }

    if (opts.verbose) {
        printf(">> %s\n", build_buildstrap_command.data);
        failed = system(build_buildstrap_command.data);
    } else {
        Str build_buildstrap_command_silent = str_make_from(build_buildstrap_command.data);
        str_append(&build_buildstrap_command_silent, " > /dev/null 2>&1");

        failed = system(build_buildstrap_command_silent.data);
    }

    if (failed) {
        printf("=== Buildstrap build FAILED ===\n");
        return;
    } else {
        printf("=== Buildstrap build SUCCESS ===\n");
    }

    failed = execl("./build/build", "./build/build", NULL);
    if (failed) {
        perror("Failed to run buildstrap.\n");
        return;
    } else {
        printf("Building...\n");
    }

#endif
}