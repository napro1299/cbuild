#ifndef CBUILD_H
#define CBUILD_H

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    GCC,
    CLANG,
    MSVC,
} CompilerType;

typedef enum {
    LD,
    LDD,
} LinkerType;

typedef struct {
    const char *name;

    /**
     * Space deliminated string of include paths.
     * 
     * Example: "./include ./lib/include"
     * 
     * Default: current directory
     */
    const char *include_paths;

    /**
     * 
     */
    const char *files;
} SourcesInfo;

typedef struct {
    bool debug;
    bool enable_warnings;
    bool freestanding;
} ExecutableOptions;

typedef struct {

} Executable;

void set_compiler(CompilerType compiler_type);

void set_linker(LinkerType linker_type);

Executable add_executable(SourcesInfo sources, ExecutableOptions executable_opts);


#endif