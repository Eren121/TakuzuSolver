#ifndef puzzle_H
#define puzzle_H

#include "common.h"

typedef enum {
    S_0 = 0,
    S_1 = 1,
    S_INDETERMINATED = -1
} State;

typedef enum {
    I_LINE_COLUMN,
    I_COLUMN_LINE
} Index;

State state_from_char(char c);
State state_to_char(State self);

typedef struct {

    /* Raw data of the puzzle (packed lines from top left to bottom right) */
    State *data;

    /* 2D data of the puzzle pointing to the data */
    State **lines;

    /* Size, same horizontally and vertically */
    int size;

} Puzzle;

void puzzle_init(Puzzle *self, int size);
void puzzle_init_from_file(Puzzle *self, const char *filename);
int puzzle_size(Puzzle *self);
State* puzzle_at(Puzzle *self, Index index, int i, int j);
void puzzle_display(Puzzle *self);
void puzzle_destroy(Puzzle *self);

#endif
