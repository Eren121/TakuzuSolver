cmake_minimum_required(VERSION 3.13)
project(TakuzuSolver C)

set(CMAKE_C_FLAGS "-ansi")

add_executable(TakuzuSolver
    main.c
    puzzle.c puzzle.h
    common.c common.h solver.c solver.h binary_tree.c binary_tree.h)