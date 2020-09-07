#ifndef solver_H
#define solver_H

#include "puzzle.h"

bool solver_is_all_valid(Puzzle *self);

/**
 * From a valid configuration, check if after modifying a single tile, at least one rule is broken.
 */
bool solver_does_move_break(Puzzle *self, int line, int column, int(*counts)[2]);

/**
 * Check if there is no more than > 2 repetition of tiles around the given tile in a center of radius 3 in
 * the same line and same column.
 */
bool solver_check_adjacent_repetition(Puzzle *self, int line, int column);

bool solver_check_count(Puzzle *self, int line, int column, const int counts[2]);

int solver_get_longest_sequence_length(Puzzle *self, Index index, int i, int minInclusive, int maxInclusive);
bool solver_is_in_duplicate(Puzzle *self, Index index, int i);


bool solver_has_indeterminated(Puzzle *self, Index index, int i);
bool solver_are_same(Puzzle *self, Index index, int i, int ii);
void solver_count(Puzzle *self, Index index, int i, int output[2]);

#endif
