#include "str.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MALLOC_STR(sz) ((char *) malloc(sizeof(char) * (sz) + 1))

Str str_make() {
    Str str;
    str.cap = 16;
    str.size = 0;
    str.data = MALLOC_STR(str.cap);

    return str;
}

Str str_make_from(const char *from) {
    Str str;
    str.cap = strlen(from);
    str.size = str.cap;
    str.data = MALLOC_STR(str.cap);
    assert(str.data && "malloc retured null");
    memcpy(str.data, from, str.cap);
    
    str.data[str.size] = '\0';

    return str;
}

Str str_make_from_len(const char *from, size_t n) {
    Str str;
    str.cap = n;
    str.size = str.cap;
    str.data = MALLOC_STR(str.cap);
    assert(str.data && "malloc retured null");
    memcpy(str.data, from, n);
 
    str.data[str.size] = '\0';

    return str;
}

Str str_make_with_cap(size_t size) {
    assert(size != 0 && "size is 0");

    Str str;
    str.cap = size;
    str.size = 0;
    str.data = MALLOC_STR(size);

    assert(str.data && "malloc retured null");

    return str;
}

void str_append(Str *str, const char *other) {
    assert(other && "other string null");

    size_t other_size = strlen(other);

    if (str->size + other_size > str->cap) {
        // Add other size + half of size 
        str->cap = str->cap + (other_size + (other_size >> 1)) + 1;
        str->data = (char *) realloc(str->data, str->cap);
        assert(str->data && "realloc retured null");
    }

    memcpy(&str->data[str->size], other, other_size);
    str->size += other_size;

    str->data[str->size] = '\0';
}

void str_grow(Str *str, size_t size) {
    str->cap += size;
    str->data = (char *) realloc(str->data, str->cap + 1);
    assert(str->data && "realloc retured null");
}

void str_free(Str *str) {
    free(str->data);
}