#ifndef common_H
#define common_H

#include <stddef.h>
#include <stdbool.h>

#ifdef _WIN32
    #define SEPARATOR "\\"
#else
    #define SEPARATOR "/"
#endif

typedef struct {
    int i, j;
} Pos;

/* Get the number of elements of a declared array (do not work with array arguments or pointer arguments)7 */
#define arrsize(array) \
    (sizeof(array) / sizeof(*array))

/* Checked malloc */
void* cmalloc(size_t size);

/* Checked calloc */
void* ccalloc(size_t num, size_t size);

/* Fatal error with message, exit. Same printf arguments */
void fatal(const char *fmt, ...);

bool inrange(int i, int minInclusive, int maxExclusive);

/* Check if unsigned number is unsigned and less than */
bool uless(int i, int maxExclusive);


/* Check if array contains the same ralue repeatedly */
bool array_repeat(int *array, int size);

int clamp(int x, int minInclusive, int maxInclusive);

#endif
