#include <cbuild.h>

void build() {
    set_compiler(GCC);

    // Options can be optional too
    add_executable((SourcesInfo) {
        .name = "test",
        .include_paths = "./include",
        .files = "**.c"
    }, (ExecutableOptions) {
        .debug = true,
        .enable_warnings = true,
    });
}