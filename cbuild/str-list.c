#include "str-list.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

void strlist_grow(StrList *list, size_t new_size) {
    assert(new_size >= list->cap);
    list->cap = new_size;
    list->list = (char **) realloc(list->list, list->cap);
}

inline StrList strlist_make() {
    return (StrList) { 0 };
}

void strlist_add(StrList *list, const char *str) {
    if (list->size == list->cap) {
        strlist_grow(list, list->cap * 2);
    }

    size_t len = strlen(str);
    list->list[list->size++] = (char *) malloc(len + 1);
    strncpy(list->list[list->size++], str, len);
}

void strlist_add_str(StrList *list, Str str) {
    strlist_add(list, str.data);
}

void strlist_free(StrList *list) {
    if (list->list) {
        for (int i = 0; i < list->size; i++) {
            free(list->list[i]);
        }
    }
}