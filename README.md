# CBuild

CBuild is a build system for C, written in C. It is designed to address the unnecessary complexity of modern build systems like CMake. The driving philosophy of CBuild is in order to build C, you only need to know C. It is centered around `build.h` where the build process can be configured. It has a simple C API which allows for simple creation of targets and configurations. More features are yet to come.

There are two components to the build system:
- The CLI utility `cbuild` which allows for initialization, building, and running of projects
- The build executable `build` which is created to compile the project based on options specified from `cbuild build`

A new project can be created with `cbuild init` which initializes an empty build config header.

`cbuild build` builds the project, and `--config=<config>` can be passed for the current configuration. The `-v, --verbose` flag enables all messages.

Example build.h
---
```c
#include <cbuild/cbuild.h>

void build() {
    Target app = {
        .type = Executable,
        .target_name = "app",
        .files = "src/**.c",
        .include_dir = "include",
    };

    app.opts.warnings = true; // Enable warnings
	
    // Handle configurations with macro defines `cbuild build --config=DEBUG`
#ifdef DEBUG
    app.opts.debug = true; // Enable debug flag
#elif RELEASE
    app.opts.optimization = Optimize; // Enable optimizations
#endif

    compile_target(app);
}
```
