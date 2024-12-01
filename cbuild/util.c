#include "util.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#ifdef __linux__
#   include <dirent.h>
#endif

#ifdef __unix__
#   include <sys/types.h>
#   include <sys/stat.h>
#   include <unistd.h>
#endif

static void cbuild_error_v(const char *msg, va_list args) {
    printf("cbuild: ");
    vprintf(msg, args);
}

void cbuild_error(const char *msg, ...) {
    va_list args;
    va_start(args, msg);

    cbuild_error_v(msg, args);

    va_end(args); 
}

void cbuild_panic(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    
    cbuild_error_v(msg, args);

    va_end(args);
    exit(1);
}

void verify_dir(const char *dir) {
#ifdef __unix__
    struct stat s;

    if (stat(dir, &s) != 0 || !S_ISDIR(s.st_mode)) {
        if (mkdir(dir, 0777) != 0) {
            cbuild_panic("failed to create %s directory\n", dir);
        }
    }
#endif
}

#define GETCWD_BUFLEN_MAX_GROW 4

Str get_current_dir() {
#ifdef __unix__
    Str dir_str = str_make_with_cap(128);
    char *buf;
    int i;
    for (i = 0; i < GETCWD_BUFLEN_MAX_GROW && !(buf = getcwd(dir_str.data, dir_str.cap)); i++) {
        str_grow(&dir_str, dir_str.cap);
    }

    assert(i != GETCWD_BUFLEN_MAX_GROW - 1 && "current path dir too long");
    assert(buf && "getcwd buf null");

    return dir_str;
#endif
}

StrList get_directories(const char *path, int *count) {
    StrList directories = strlist_make();

    struct dirent *entry;
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return directories;
    }

    *count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        int is_directory = 0;

        if (entry->d_type == DT_DIR) {
            is_directory = 1;
        }

        if (is_directory) {
            printf("%s\n", entry->d_name);
        }
    }

    return directories;
}