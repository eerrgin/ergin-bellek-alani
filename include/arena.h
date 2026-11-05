#ifndef ERGIN_ARENA_H
#define ERGIN_ARENA_H
#include <stddef.h>
typedef struct Arena Arena;
Arena *arena_create(size_t capacity);
void arena_destroy(Arena *arena);
void *arena_alloc(Arena *arena, size_t size, size_t align);
void arena_reset(Arena *arena);
size_t arena_used(const Arena *arena);
size_t arena_capacity(const Arena *arena);
char *arena_strdup(Arena *arena, const char *text);
#endif
