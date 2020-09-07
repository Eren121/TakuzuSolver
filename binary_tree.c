#include "binary_tree.h"
#include "solver.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void tree_init(Tree *self, Puzzle *puzzle) {
    int size = 0, i, j;
    Pos *positions = cmalloc(sizeof(int) * puzzle_size(puzzle) * puzzle_size(puzzle));

    for(i = 0; i < puzzle_size(puzzle); ++i) {
        for(j = 0; j < puzzle_size(puzzle); ++j) {
            if(*puzzle_at(puzzle, I_LINE_COLUMN, i, j) == S_INDETERMINATED) {
                positions[size].i = i;
                positions[size].j = j;

                ++size;
            }
        }
    }

    self->undeterminateds = positions;
    self->puzzle = puzzle;
    self->size = size;

    tree_reset_count(self);
}

void tree_reset_count(Tree *self) {
    int i;

    for(i = 0; i < 2; ++i) {
        self->counts[i] = -1;
    }
}

void tree_destroy(Tree *self) {
    free(self->undeterminateds);
    self->undeterminateds = NULL;

    self->puzzle = NULL;

    self->size = 0;

    tree_reset_count(self);
}

void tree_solve(Puzzle* puzzle) {
    Tree tree;

    if(!solver_is_all_valid(puzzle)) {
        printf("Erreur: le puzzle n'est pas possible de base.\n");
    }
    else {
        tree_init(&tree, puzzle);
        tree_solve_branch(&tree, 0);
        tree_destroy(&tree);
    }
}

void tree_solve_branch(Tree *self, int i) {
    Pos pos;
    State *state = NULL;

    /* If out-of-bounds of number of underminated, then the puzzle is solved */
    if(i == self->size) {
        printf("Solved:\n");
        puzzle_display(self->puzzle);
        printf("--------------\n");
    }
    else {
        pos = self->undeterminateds[i];
        state = puzzle_at(self->puzzle, I_LINE_COLUMN, pos.i, pos.j);

        tree_solve_branch_state(self, i, S_0);
        tree_solve_branch_state(self, i, S_1);

        *state = S_INDETERMINATED;
    }
}

void tree_solve_branch_state(Tree *self, int i, State state) {
    bool hasSetCount = false;
    Pos pos = self->undeterminateds[i];
    *puzzle_at(self->puzzle, I_LINE_COLUMN, pos.i, pos.j) = state;

    if(self->counts[0] == -1) {

        if(!solver_has_indeterminated(self->puzzle, I_LINE_COLUMN, pos.i)) {
            solver_count(self->puzzle, I_LINE_COLUMN, pos.i, self->counts);
            hasSetCount = true;
        }
        else if(!solver_has_indeterminated(self->puzzle, I_COLUMN_LINE, pos.j)) {
            solver_count(self->puzzle, I_COLUMN_LINE, pos.j, self->counts);
            hasSetCount = true;
        }

        if(!hasSetCount || solver_check_count(self->puzzle, pos.i, pos.j, self->counts)) {
            if (!solver_does_move_break(self->puzzle, pos.i, pos.j, NULL)) {
                tree_solve_branch(self, i + 1);
            }
        }
    }
    else {
        if (!solver_does_move_break(self->puzzle, pos.i, pos.j, &self->counts)) {
            tree_solve_branch(self, i + 1);
        }
    }

    if(hasSetCount) {
        tree_reset_count(self);
    }
}