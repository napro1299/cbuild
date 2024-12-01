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
    LLD,
} LinkerType;

typedef enum {
    OptimizeNone = 0,
    Optimize,
    OptimizeFast,
    OptimizeSize,
} OptimizeLevel;

typedef enum {
    C89 = 1,
    C90,
    C11,
    C17,
    C18,
    C23,
} CStd;

typedef enum {
    Executable = 0,
    StaticLibrary,
    SharedLibrary,
} TargetType;

typedef struct {
    bool debug;
    bool warnings;
    CStd cstd;
    OptimizeLevel optimization;

    bool freestanding;

    const char *additional_flags;
} CompileOpts;

typedef struct {
    TargetType type;
    const char *target_name;
    const char *target_dir;

    /* Sources */
    const char *files;
    const char *include_dir;

    const char *defines;

    CompileOpts opts;
} Target;

typedef struct {
    const char *config;
} BuildArgs;

void set_compiler(CompilerType compiler_type);

void set_linker(LinkerType linker_type);

int get_config(BuildArgs args);

bool is_config(int current_config, const char *test_config);

void compile_target(Target target);

#endif