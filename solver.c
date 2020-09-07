#include "solver.h"
#include <string.h>

bool solver_is_all_valid(Puzzle *self) {
    bool ret = true;
    int i, j;

    for(i = 0; i < puzzle_size(self) && ret; ++i) {
        for(j = 0; j < puzzle_size(self) && ret; ++j) {
            ret &= !solver_does_move_break(self, i, j, NULL);
        }
    }

    return ret;
}

bool solver_does_move_break(Puzzle *self, int line, int column, int(*counts)[2]) {
    int tmp[2];
    bool ret = false;

    if(!solver_check_adjacent_repetition(self, line, column)) {
        ret = true;
    }
    else if(solver_is_in_duplicate(self, I_LINE_COLUMN, line)) {
        ret = true;
    }
    else if(solver_is_in_duplicate(self, I_COLUMN_LINE, column)) {
        ret = true;
    }
    else if(counts && !solver_check_count(self, line, column, *counts)) {
        ret = true;
    }

    return ret;

}

bool solver_check_adjacent_repetition(Puzzle *self, int line, int column) {
    bool ret = true;

    if(solver_get_longest_sequence_length(self, I_LINE_COLUMN, line,
            clamp(column - 2, 0, self->size - 1),
            clamp(column + 2, 0, self->size - 1)) > 2) {
        ret = false;
    }
    else if(solver_get_longest_sequence_length(self, I_COLUMN_LINE, column,
            clamp(line - 2, 0, self->size - 1),
            clamp(line + 2, 0, self->size - 1)) > 2) {
        ret = false;
    }

    return ret;
}

bool solver_check_count(Puzzle *self, int line, int column, const int counts[2]) {
    bool ret = true;
    int current[2];
    int i;

    if(!solver_has_indeterminated(self, I_LINE_COLUMN, line)) {
        solver_count(self, I_LINE_COLUMN, line, current);
        if (memcmp(current, counts, sizeof(current)) != 0) {
            ret = false;
        }
    }

    if(ret && !solver_has_indeterminated(self, I_COLUMN_LINE, column)) {
        solver_count(self, I_COLUMN_LINE, column, current);
        if (memcmp(current, counts, sizeof(current)) != 0) {
            ret = false;
        }
    }

    return ret;
}


int solver_get_longest_sequence_length(Puzzle *self, Index index, int i, int minInclusive, int maxInclusive) {
    int count = 0, ret = 0;
    State current, state;
    int j;

    current = S_INDETERMINATED;
    for(j = minInclusive; j <= maxInclusive; ++j) {
        state = *puzzle_at(self, index, i, j);

        if(state != S_INDETERMINATED && state == current) {
            ++count;
            if(count > ret) {
                ret = count;
            }
        }
        else {
            current = state;
            count = 1;
        }
    }

    return ret;
}

bool solver_is_in_duplicate(Puzzle *self, Index index, int i) {
    bool ret = false;
    int ii;

    if(!solver_has_indeterminated(self, index, i)) {
        for(ii = 0; ii < puzzle_size(self) && !ret; ++ii) {
            if(i != ii && solver_are_same(self, index, i, ii)) {
                ret = true;
            }
        }
    }

    return ret;
}

bool solver_has_indeterminated(Puzzle *self, Index index, int i) {
    bool ret = false;
    int j;

    for(j = 0; j < puzzle_size(self) && !ret; ++j) {
        if(*puzzle_at(self, index, i, j) == S_INDETERMINATED) {
            ret = true;
        }
    }

    return ret;
}

bool solver_are_same(Puzzle *self, Index index, int i, int ii) {
    int j;
    bool ret = true;

    for(j = 0; j < puzzle_size(self) && ret; ++j) {
        if(*puzzle_at(self, index, i, j) != *puzzle_at(self, index, ii, j)) {
            ret = false;
        }
    }

    return ret;
}

void solver_count(Puzzle *self, Index index, int i, int output[2]) {
    int j;

    memset(output, 0, sizeof(*output) * 2);

    for(j = 0; j < puzzle_size(self); ++j) {
        ++output[*puzzle_at(self, index, i, j)];
    }
}