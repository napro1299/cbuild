#include <cbuild/cbuild.h>

void build(BuildArgs args) {
    set_compiler(GCC);

    set_configurations("debug release");

    Target cbuild = { 
        .type = Executable,
        .target_name = "cbuild",
        .files = "src/**.c src/**.h",
        .configuration = "debug", // Default configuration
    };

    Target add_lib = {
        .type = StaticLibrary,
        .target_name = "add",
        .files = "func.c",
        .configuration = "debug",
    };

    int config = get_config(args);

    add_lib.opts.warnings = true;
    cbuild.opts.warnings = true;

    // Handle configs
    if (is_config(config, "debug")) {
        cbuild.opts.debug = true;
        add_lib.opts.debug = true;
    } else if (is_config(config, "release")) {
        cbuild.opts.optimization = Optimize;
        add_lib.opts.optimization = Optimize;
    }

    compile_target(cbuild);
    compile_target(add_lib);

    link(cbuild, add_lib);

    

}