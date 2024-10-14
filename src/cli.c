#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void 
print_usage() {
    printf("cbuild: no command specified (e.g. 'cbuild build'). 'cbuild help' for commands.\n");
}

static void  
unknown_command(char *command) {
    printf("cbuild: unknown command '%s'. 'cbuild help' for commands.\n", command);
}

static void 
help_command() {
    printf(
        "Cbuild is a build manager for C.\n"
        "Usage:\n   cbuild <command> [options]\n\n"
        "Commands:\n"
        "   build, b        compile the project\n"
        "   run, r          compile and run C program\n"
        "   help            display help information\n"
        "\n"
        "Use \"cbuild help <command>\" for more information about a command.\n"
        "\n"
    );
}

static void 
build_command(int argc, char **argv) {
    if (argc == 0) {
        // Assume current directory
        cbuild_build(".");
    }
}

static void
run_command(int argc, char **argv) {
    
}

int
main(int argc, char **argv) {
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
        help_command();
    } else {
        unknown_command(command);
    }
}