cmake_minimum_required(VERSION 3.26)
project(c_projects C)

set(CMAKE_C_STANDARD 11)

add_executable(c_projects main.c
        Hangman/hangman.c
        mainheader.h
        functions.h
        functions.c)
