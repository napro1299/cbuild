#ifndef STR_H
#define STR_H

#include <stddef.h>

/* Dynamic string type */
typedef struct {
    size_t size;
    size_t cap;
    char *data;
} Str;

Str str_make();
Str str_make_from(const char *from);
Str str_make_from_len(const char *from, size_t n);
Str str_make_with_cap(size_t size);
void str_append(Str *str, const char *other);
void str_grow(Str *str, size_t size);
void str_free(Str *str);

#endif