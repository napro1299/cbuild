#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "build.h"

static void print_usage() {
    printf("cbuild: no command specified (e.g. 'cbuild build'). 'cbuild help' for commands.\n");
}

static void unknown_command(char *command) {
    printf("cbuild: unknown command '%s'. 'cbuild help' for commands.\n", command);
}

static void unrecognized_argument(const char *command, int argc, char **argv) {
    printf("'cbuild %s ", command);

    for (int i = 0; i < argc; i++) {
        if (i == argc - 1)
            printf("%s", argv[i]);
        else 
            printf("%s ", argv[i]);
    }

    printf("': unrecognized arguments. 'cbuild help %s' for help.\n", command);
}

static void help_command(int argc, char **argv) {
    if (argc == 0) {
        printf(
            "Cbuild is a build manager for C.\n"
            "Usage:\n   cbuild <command> [options]\n\n"
            "Commands:\n"
            "   build, b        compile the project\n"
            "   run, r          compile and run C program\n"
            "   help            display help information\n"
            "\n"
            "Use 'cbuild help <command>' for more information about a command.\n"
            "\n"
        );
        return;
    } else if (argc == 1) {
        if (strcmp(argv[1], "build") == 0) {
            printf(
                "usage: cbuild build [config=...]\n\n"
                "Build compiles the project in the current directory\n"
                "specified by the 'build.h' configuration.\n\n"
                "A config for the build can be set with 'config=...'. E.g. 'go build config=release'\n\n"
                "Build files will be stored in a build directory at the project root directory.\n"
            );
            return;
        } else if (strcmp(argv[1], "run") == 0) {
            printf(
                "usage: cbuild run\n\n"
                "Run compiles and runs the resulting project executable.\n"
            );
            return;
        }
    }
    
    char **unknown_args = &argv[1];

    printf("'cbuild help ");
    for (int i = 0; i < argc; i++) {
        if (i == argc - 1)
            printf("%s", unknown_args[i]);
        else
            printf("%s ", unknown_args[i]);
    }
    
    printf("': unknown help command. Run 'cbuild help'.\n");
}

static void build_command(int argc, char **argv) {
    if (argc == 0) {
        cbuild_launch_buildstrap();
    } else if (argc == 1) {
        cbuild_launch_buildstrap();
        // cbuild_verify_config_args();
    } else {
        unrecognized_argument("build", argc, &argv[1]);
    }
}

static void run_command(int argc, char **argv) {
    printf("RUNNN\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        print_usage();
        exit(1);
    }

    char *command = argv[1];

    if (strcmp(command, "build") == 0 || strcmp(command, "b") == 0) {
        build_command(argc - 2, &argv[1]);
    } else if (strcmp(command, "run") == 0 || strcmp(command, "r") == 0) {
        run_command(argc - 2, &argv[1]);
    } else if (strcmp(command, "help") == 0) {
        help_command(argc - 2, &argv[1]);
    } else {
        unknown_command(command);
    }
}