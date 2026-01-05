cmake_minimum_required(VERSION 3.20)

project(ni-gen)

add_executable(ni-gen src/main.c src/word.c src/arena.c)

target_compile_options(ni-gen PUBLIC -std=c99 -Wall -Werror -Wextra -g)
