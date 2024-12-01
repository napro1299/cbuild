#include <string.h>

#ifdef __unix__
#   include <sys/types.h>
#   include <sys/stat.h>
#endif

#include "../cbuild/str.h"
#include "../cbuild/util.h"

#include "build.h"

#define TARGET_DIR "targets"

static Str build_exec_path;

static void compile_executable(Target target) {
    
    int num;
    get_directories(".", &num);

    printf("num: %d\n", num);
} 

void compile_target(Target target) {
    Str target_dir = str_make_from(build_exec_path.data);
    str_append(&target_dir, "/" TARGET_DIR);
    printf("Verifying targets directory: %s\n", target_dir.data);
    verify_dir(target_dir.data);

    switch (target.type)
    {   
    case Executable:
        compile_executable(target);
        break;
    case StaticLibrary:
        // compile_static_lib(target);
        break;
    case SharedLibrary:
        // compile_shared_lib(target);
        break;
    default:
        break;
    }

    str_free(&target_dir);
}

int main(int argc, char **argv) {
    printf("%s\n", argv[0]);
    char *last_slash = strrchr(argv[0], '/');

    if (!last_slash)
        cbuild_panic("failed to get own path\n");
    
    build_exec_path = str_make_from_len(argv[0], last_slash - argv[0]);

    build();

    str_free(&build_exec_path);
}