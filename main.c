#include "binary_tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char* get_puzzle_file_path(const char *argument) {
    static char tmp[100];
    const char *ret = argument;
    int id = atoi(argument);

    if(id > 0 && id < 100) {
        snprintf(tmp, sizeof(tmp), ".." SEPARATOR "assets" SEPARATOR "puzzle%d.txt", id);
        ret = tmp;
    }

    return ret;
}

int main(int argc, char *argv[]) {
    Puzzle puzzle;
    const char *filename = NULL;

    if(argc < 2) {
        fatal("Missing the puzzle's filename argument");
    }

    filename = get_puzzle_file_path(argv[1]);
    puzzle_init_from_file(&puzzle, filename);

    printf("Init:\n");
    puzzle_display(&puzzle);

    tree_solve(&puzzle);

    puzzle_destroy(&puzzle);

    return 0;
}