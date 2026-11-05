#include "arena.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
static int fails;
#define CHECK(cond) do { if (!(cond)) { fprintf(stderr, "fail %s:%d %s\n", __FILE__, __LINE__, #cond); fails++; } } while (0)
int main(void) {
    Arena *a = arena_create(64);
    char *s;
    void *p, *q;
    unsigned char *b1, *b2;
    CHECK(a != NULL);
    CHECK(arena_alloc(NULL, 8, 8) == NULL);
    CHECK(arena_alloc(a, 0, 8) == NULL);
    CHECK(arena_alloc(a, 8, 3) == NULL);
    p = arena_alloc(a, 1, 8);
    CHECK(p != NULL);
    CHECK(((uintptr_t)p % 8) == 0);
    q = arena_alloc(a, 80, 8);
    CHECK(q == NULL);
    CHECK(arena_used(a) < 64);
    s = arena_strdup(a, "iz");
    CHECK(s && strcmp(s, "iz") == 0);
    arena_reset(a);
    CHECK(arena_used(a) == 0);
    b1 = arena_alloc(a, 4, 1);
    memset(b1, 0xAB, 4);
    arena_reset(a);
    b2 = arena_alloc(a, 4, 1);
    CHECK(b1 == b2);
    arena_destroy(a);
    arena_destroy(NULL);
    CHECK(arena_create(0) == NULL);
    if (fails) { fprintf(stderr, "%d assertion failed\n", fails); return 1; }
    puts("ok");
    return 0;
}
