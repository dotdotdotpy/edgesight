#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>
#include <malloc.h>

#define STACK_MAGIC 0xDEADBEEF

// === PAYLOAD: Executed after hijack ===
void ghost_message() {
    printf("[GHOST] Entered ghost_message()\n");
    fflush(stdout);

    MessageBoxA(NULL, "HIJACK CONFIRMED", "StackGhost", MB_OK | MB_ICONINFORMATION);
    printf("[GHOST] MessageBoxA triggered.\n");
    fflush(stdout);

    FILE *f = fopen("hijack_success.txt", "w");
    if (f) {
        fputs("Payload ran.\n", f);
        fclose(f);
        printf("[GHOST] File written successfully.\n");
    } else {
        printf("[GHOST] Failed to open file.\n");
    }

    fflush(stdout);
    Beep(1000, 300);
    ExitProcess(0);
}

// === DUMP HELPER ===
void dump_memory_region(uint8_t *start, size_t len) {
    printf("[DEBUG] Dumping %zu bytes starting at %p:\n", len, (void*)start);
    for (size_t i = 0; i < len; i++) {
        if (i % 16 == 0) printf("\n%p : ", (void*)(start + i));
        printf("%02X ", start[i]);
    }
    printf("\n\n");
    fflush(stdout);
}

// === COMBINED FUNCTION: plant + scan within same frame ===
void plant_and_scan_locked() {
    printf("[DEBUG] Planting + scanning in same stack frame to preserve memory layout.\n");

    uintptr_t marker = STACK_MAGIC;
    void *payload = (void*)&ghost_message;

    size_t block_size = sizeof(uintptr_t) + sizeof(void*);
    uint8_t *buf = (uint8_t *)_alloca(block_size);

    // Write the marker + payload pointer to stack
    memcpy(buf, &marker, sizeof(uintptr_t));
    memcpy(buf + sizeof(uintptr_t), &payload, sizeof(void*));

    uintptr_t expected_payload_ptr = (uintptr_t)payload;
    uint8_t *expected_marker_addr = buf;

    // Force retention
    volatile uintptr_t *keep_alive = (volatile uintptr_t *)buf;
    printf("[DEBUG] Live marker check: 0x%08X at %p\n", keep_alive[0], (void*)buf);
    fflush(stdout);

    // Dump surrounding memory
    dump_memory_region(buf - 48, 96);

    // Now scan the region (bytewise, locked to exact address)
    printf("[DEBUG] Scanning memory around %p...\n", (void*)buf);
    size_t steps = 0;
    uintptr_t candidate;

    for (uint8_t *p = buf - 96; p < buf + 96; p++, steps++) {
        if (p == expected_marker_addr) {
            memcpy(&candidate, p, sizeof(uintptr_t));

            if (candidate == STACK_MAGIC) {
                uintptr_t payload_ptr;
                memcpy(&payload_ptr, p + sizeof(uintptr_t), sizeof(void*));

                if (payload_ptr == expected_payload_ptr) {
                    printf("[!] LOCKED marker found at %p\n", (void*)p);
                    printf("[!] Executing ghost payload at %p...\n", (void*)payload_ptr);
                    fflush(stdout);

                    ((void (*)())payload_ptr)();
                    return;
                } else {
                    printf("[✘] Payload mismatch at %p: found %p, expected %p\n",
                           (void*)p, (void*)payload_ptr, (void*)expected_payload_ptr);
                }
            } else {
                printf("[✘] Marker mismatch at locked address %p: found 0x%08X\n", (void*)p, (unsigned int)candidate);
            }
        }

        if (steps % 16 == 0)
            printf("[trace] Step %zu: %p -> 0x%p\n", steps, (void*)p, (void*)(uintptr_t)candidate);
    }

    printf("[stackghost] No valid marker found. Memory clean.\n");
    fflush(stdout);
}

// === MAIN ===
int main() {
    printf("StackGhost activated. Architecture: %zu-bit\n", sizeof(void*) * 8);
    fflush(stdout);

    plant_and_scan_locked();

    printf("[✘] Hijack did not trigger. This is a fallback line.\n");
    fflush(stdout);
    return 0;
}
