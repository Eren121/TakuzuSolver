#include "common.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void* cmalloc(size_t size) {
    void *ret = malloc(size);
    if(!ret) {
        fatal("Bad malloc");
    }

    return ret;
}

void* ccalloc(size_t num, size_t size) {
    void *ret = calloc(num, size);
    if(!ret) {
        fatal("Bad calloc");
    }

    return ret;
}

void fatal(const char *fmt, ...) {
    va_list list;

    va_start(list, fmt);
    vfprintf(stderr, fmt, list);
    va_end(list);

    /* Automatically append dot and newline at the end of the stream. */
    fputs(".\n", stderr);

    exit(1);
}

bool inrange(int i, int minInclusive, int maxExclusive){
    return i >= minInclusive && i < maxExclusive;
}

bool uless(int i, int maxExclusive) {
    return i >= 0 && i < maxExclusive;
}

bool array_repeat(int *array, int size) {
    bool ret = true;
    int init, i;
    if(size > 0) {
        init = array[0];
        for(i = 0; i < size && ret; ++i) {
            if(array[i] != init) {
                ret = false;
            }
        }
    }
    return ret;
}

int clamp(int x, int minInclusive, int maxInclusive) {
    int ret = x;
    if(ret < minInclusive) {
        ret = minInclusive;
    }
    else if(x > maxInclusive) {
        ret = maxInclusive;
    }
    return ret;
}