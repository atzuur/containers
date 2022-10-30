#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Queue {
    char* items;
    size_t item_size;

    size_t length;
    size_t capacity;

    void* front;
    void* back;
} Queue;

void q_init(Queue* self, size_t item_size, size_t capacity);

void q_add(Queue* self, void* items, size_t count);
void q_pop(Queue* self, size_t count);

void* q_get_ptr(Queue* self, long index);

// cleaner way of getting a value
#define q_get(T, S, I) (*(T*)q_get_ptr(S, I))

void q_set_capacity(Queue* self, size_t capacity);

void q_clear(Queue* self);
void q_free(Queue* self);

bool q_empty(Queue* self);
