#include "arena.h"
#include <stdio.h>
#include <string.h>
/* Gece boyunca acik kalan yerel bir gunluk toplayicisi icin sabit bellek.
   Her tur arena_reset ile geri alinir; heap parcalanmasi birikmez. */
#define BATCH 4096
int main(void) {
    Arena *arena = arena_create(BATCH);
    const char *lines[] = {
        "samatya gece vardiyasi acildi",
        "yerel gunluk satiri 1",
        "yerel gunluk satiri 2"
    };
    size_t i, kept = 0;
    if (!arena) return 1;
    for (i = 0; i < 3; i++) {
        if (arena_strdup(arena, lines[i])) kept++;
    }
    printf("tutulan=%zu kullanilan=%zu kapasite=%zu\n", kept, arena_used(arena), arena_capacity(arena));
    arena_reset(arena);
    printf("sifirdan_sonra=%zu\n", arena_used(arena));
    arena_destroy(arena);
    return kept == 3 ? 0 : 2;
}
