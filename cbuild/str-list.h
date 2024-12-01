#ifndef STR_LIST_H
#define STR_LIST_H

#include <stddef.h>

#include "str.h"

typedef struct {
    char **list;
    size_t cap;
    size_t size;
} StrList;

StrList strlist_make();
void strlist_add(StrList *list, const char *str);
void strlist_add_str(StrList *list, Str str);
void strlist_free(StrList *list);

#endif