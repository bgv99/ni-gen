#include "include/ni-gen.h"

Arena arena_init(size_t arena_size) {
    Arena arena;

    if(arena_size == 0) {
        arena.failed = true;

        return arena;
    }

    arena.ptr = malloc(arena_size);

    if(!arena.ptr) {
        arena.failed = true;

        return arena;
    }

    arena.capacity = arena_size;
    arena.length = 0;
    arena.offset = 0;
    arena.failed = false;

    return arena;
}

void arena_destroy(Arena arena) {
    if(arena.failed) {
        return;
    }

    if(arena.ptr) {
        free(arena.ptr - arena.offset);
    }
}

void *arena_alloc(Arena *arena, size_t alloc_size) {
    if(!arena) {
        return NULL;
    }

    if(alloc_size == 0) {
        return NULL;
    }

    if(arena->failed) {
        return NULL;
    }

    arena->ptr += alloc_size;
    arena->offset += alloc_size;
    arena->length++;

    return arena->ptr - alloc_size;
}