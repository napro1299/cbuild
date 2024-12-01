#include <cbuild/cbuild.h>

void build() {
    // set_compiler(GCC);

    Target cbuild = { 
        .type = Executable,
        .target_name = "cbuild",
        .files = "cbuild/**.c",
        .include_dir = "cbuild"
    };

    Target add_lib = {
        .type = StaticLibrary,
        .target_name = "add",
        .files = "func.c",
    };

    add_lib.opts.warnings = true;
    cbuild.opts.warnings = true;

// Configuration handling
#ifdef DEBUG
    printf("Compiling for DEBUG...\n");
    cbuild.opts.debug = true;
    add_lib.opts.debug = true;
#elif RELEASE
    printf("Compiling for RELEASE...\n");
    cbuild.opts.optimization = Optimize;
    add_lib.opts.optimization = Optimize;
#endif

    compile_target(cbuild);
    // compile_target(add_lib);

    // link(cbuild, add_lib);
}