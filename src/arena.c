#include "arena.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
struct Arena {
    unsigned char *base;
    size_t capacity;
    size_t used;
};
static size_t align_up(size_t value, size_t align) {
    size_t mask;
    if (align == 0 || (align & (align - 1)) != 0) return value;
    mask = align - 1;
    if (value > SIZE_MAX - mask) return SIZE_MAX;
    return (value + mask) & ~mask;
}
Arena *arena_create(size_t capacity) {
    Arena *arena;
    if (capacity == 0) return NULL;
    arena = calloc(1, sizeof *arena);
    if (!arena) return NULL;
    arena->base = malloc(capacity);
    if (!arena->base) { free(arena); return NULL; }
    arena->capacity = capacity;
    return arena;
}
void arena_destroy(Arena *arena) {
    if (!arena) return;
    free(arena->base);
    free(arena);
}
void arena_reset(Arena *arena) {
    if (arena) arena->used = 0;
}
size_t arena_used(const Arena *arena) { return arena ? arena->used : 0; }
size_t arena_capacity(const Arena *arena) { return arena ? arena->capacity : 0; }
void *arena_alloc(Arena *arena, size_t size, size_t align) {
    size_t start, next;
    if (!arena || size == 0 || align == 0 || (align & (align - 1)) != 0) return NULL;
    start = align_up(arena->used, align);
    if (start == SIZE_MAX || size > arena->capacity || start > arena->capacity - size) return NULL;
    next = start + size;
    arena->used = next;
    return arena->base + start;
}
char *arena_strdup(Arena *arena, const char *text) {
    size_t n;
    char *copy;
    if (!text) return NULL;
    n = strlen(text) + 1;
    copy = arena_alloc(arena, n, 1);
    if (!copy) return NULL;
    memcpy(copy, text, n);
    return copy;
}
