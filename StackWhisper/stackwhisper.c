#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define STACK_MAGIC 0xDEADBEEF
#define STACK_STRUCT_SIZE sizeof(struct StackMarker)

struct StackMarker {
    uint32_t magic;
    char filler[12];
};

void scan_stack_for_magic(void *start, void *end) {
    uintptr_t *p = (uintptr_t*)start;
    uintptr_t *limit = (uintptr_t*)end;

    if (p > limit) {
        uintptr_t *tmp = p;
        p = limit;
        limit = tmp;
    }

    printf("[stackwhisper] Scanning stack region: %p - %p\n\n", (void*)p, (void*)limit);
    int total = 0, found = 0;

    for (; p < limit; p++) {
        total++;
        if (*p == STACK_MAGIC) {
            printf("Found STACK_MAGIC at: %p\n", (void*)p);
            found++;
        }
    }

    printf("\nChecked %d memory words, found %d marker(s).\n", total, found);
    if (found == 0) {
        printf("No markers detected. Stack may be optimized or corrupted.\n");
    } else if (found < 3) {
        printf("Partial match. Possible overwrite or movement.\n");
    } else {
        printf("All markers found. Stack region appears intact.\n");
    }
}

void place_stack_markers() {
    struct StackMarker a = { STACK_MAGIC, "A1" };
    struct StackMarker b = { STACK_MAGIC, "B2" };
    struct StackMarker c = { STACK_MAGIC, "C3" };

    volatile struct StackMarker *refs[] = { &a, &b, &c };
    for (int i = 0; i < 3; i++) {
        printf("Marker placed at: %p\n", (void*)refs[i]);
    }

    scan_stack_for_magic((void*)&a, (void*)&c);
}

int main() {
    printf("=== stackwhisper ===\n\n");
    place_stack_markers();
    return 0;
}
