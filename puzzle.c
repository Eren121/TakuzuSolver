#include "puzzle.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

State state_from_char(char c) {
    State ret;

    switch(c) {

        case '0':
            ret = S_0;
            break;

        case '1':
            ret = S_1;
            break;

        case '*':
            ret = S_INDETERMINATED;
            break;

        default:
            fatal("Unknown State character '%c'", c);
    }

    return ret;
}

State state_to_char(State self) {
    char ret;

    switch(self) {

        case S_0:
            ret = '0';
            break;

        case S_1:
            ret = '1';
            break;

        case S_INDETERMINATED:
            ret = '*';
            break;

        default:
            fatal("Unknown State '%d'", self);
    }

    return ret;
}

void puzzle_init(Puzzle *self, int size) {
    int i;

    self->data = cmalloc(sizeof(*self->data) * size * size);
    self->lines = ccalloc(size, sizeof(*self->lines));
    self->size = size;

    for(i = 0; i < size * size; ++i) {
        self->data[i] = S_INDETERMINATED;
    }

    for(i = 0; i < size; ++i) {
        self->lines[i] = &self->data[i * size];
    }
}


void puzzle_init_from_file(Puzzle *self, const char *filename) {
    int dimension = 0, line = 0, column = 0, c;
    State state;
    FILE* file = fopen(filename, "r");

    if(!file) {
        fatal("Can't open file '%s'", filename);
    }

    /* Read first the size */
    while(c = fgetc(file), c != '\n' && c != EOF) {
        ++dimension;
    }

    /* Check if the file is empty (non supporting empty file because not very useful and no tests are made later) */
    if(dimension == 0) {
        fatal("The file '%s' is empty", filename);
    }

    puzzle_init(self, dimension);

    /* Then read the data */
    fseek(file, SEEK_SET, 0);

    while((c = fgetc(file)) != EOF) {
        if(c == '\n') {

            if(column != dimension) {
                fatal("In file '%s', missing character before end of line (line %d)", line + 1);
            }

            ++line;
            column = 0;

            if(line >= dimension) {
                fatal("In file '%s', too many lines (more than %d)", filename, dimension);
            }
        }
        else {
            state = state_from_char((char)c);

            if(column >= dimension) {
                fatal("In file '%s', line %d has invalid size (%d characters instead of %d)",
                        filename, line + 1, column + 1, dimension);
            }

            *puzzle_at(self, I_LINE_COLUMN, line, column) = state;

            ++column;
        }
    }

    if(column != dimension) {
        fatal("In file '%s', missing character before end of line (line %d)", line + 1);
    }

    if(line + 1 != dimension) {
        fatal("In file '%s' missing lines (%d lines instead of %d)", filename, line + 1, dimension);
    }

    fclose(file);
    file = NULL;
}

int puzzle_size(Puzzle *self) {
    return self->size;
}

State* puzzle_at(Puzzle *self, Index index, int i, int j) {
    State *ret = NULL;

    assert(uless(i, self->size) && uless(j, self->size));

    if(index == I_LINE_COLUMN) {
        ret = &self->lines[i][j];
    }
    else {
        ret = &self->lines[j][i];
    }

    return ret;
}

void puzzle_display(Puzzle *self) {
    int line, column, color;
    State state;

    for(line = 0; line < self->size; ++line) {
        for(column = 0; column < self->size; ++column) {
            state = *puzzle_at(self, I_LINE_COLUMN, line, column);

            switch(state) {
                case S_0:
                    color = 31;
                    break;

                case S_1:
                    color = 32;
                    break;

                case S_INDETERMINATED:
                    color = 33;
                    break;
            }

            printf("\033[0;%dm", color);
            putchar(state_to_char(state));

            /* Reset ansi color */
            printf("\033[0;0m");
        }
        putchar('\n');
    }
}

void puzzle_destroy(Puzzle *self) {
    free(self->data);
    self->data = NULL;

    free(self->lines);
    self->lines = NULL;

    self->size = 0;
}
