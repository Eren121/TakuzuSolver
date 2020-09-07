#ifndef binary_tree_H
#define binary_tree_H

#include "puzzle.h"

typedef struct {
    Puzzle *puzzle;
    Pos *undeterminateds;
    int size;

    /* Count of 0 and 1 by line/column, -1 if not set */
    int counts[2];

} Tree;

void tree_init(Tree *self, Puzzle *puzzle);
void tree_destroy(Tree *self);

void tree_reset_count(Tree *self);

void tree_solve(Puzzle* puzzle);

void tree_solve_branch(Tree *self, int i);
void tree_solve_branch_state(Tree *self, int i, State state);

#endif