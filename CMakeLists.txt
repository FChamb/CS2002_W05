cmake_minimum_required(VERSION 3.27)
project(CS2002_W05 C)

set(CMAKE_C_STANDARD 11)

add_executable(CS2002_W05
        src/ttable.c
        src/ttable.h
        src/testTTable.c
        src/testTTable.h
        src/ttableFunctions.c
        src/partTwo.c)
