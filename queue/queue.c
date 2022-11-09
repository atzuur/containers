#include "queue.h"

void q_init(Queue* self, size_t item_size, size_t capacity) {

    assert(item_size > 0);
    assert(capacity > 0);

    self->items = calloc(item_size, capacity);
    self->item_size = item_size;

    self->capacity = capacity;
    self->length = 0;

    self->front = self->items;
    self->back = self->items;
}

void q_add(Queue* self, void* items, size_t count) {

    assert(count > 0);

    size_t tot_size = count * self->item_size;
    void* last_addr = self->length == 0 ? self->back : self->back + self->item_size;

    if (self->length + count > self->capacity) {
        // shift everything except the last COUNT items to the front
        memmove(self->front, self->items + tot_size, (self->length - count) * self->item_size);
        // copy the last COUNT items to the back
        memmove(self->back - tot_size + self->item_size, items, count * self->item_size);

    } else {
        memmove(last_addr, items, tot_size);
        self->length += count;
    }

    self->front = self->items;
    self->back = self->items + (self->length - 1) * self->item_size;
}

void q_pop(Queue* self, size_t count) {

    assert(count > 0);

    if (count >= self->length)
        return q_clear(self);

    size_t tot_size = count * self->item_size;

    // shift items to the front
    memmove(self->front, self->items + tot_size, (self->length - count) * self->item_size);
    // set remaining items to 0
    memset(self->back - count * self->item_size, 0, count * self->item_size);

    self->length -= count;
    self->front = self->items;
    self->back = self->items + (self->length - 1) * self->item_size;
}

void* q_get_ptr(Queue* self, long index) {

    if (index > 0 && (unsigned)index >= self->length)
        return NULL;

    if (index < 0)
        index += self->length;

    return self->items + index * self->item_size;
}

void q_set_capacity(Queue* self, size_t new_capacity) {

    assert(new_capacity > 0);
    if (new_capacity == self->capacity)
        return;

    self->items = realloc(self->items, new_capacity * self->item_size);
    self->capacity = new_capacity;
    self->front = self->items;
    self->back = self->items + (self->length - 1) * self->item_size;
}

void q_clear(Queue* self) {

    memset(self->items, 0, self->length * self->item_size);

    self->length = 0;
    self->front = self->items;
    self->back = self->items;
}

void q_free(Queue* self) {

    assert(self->items);

    q_clear(self);
    free(self->items);

    self->items = NULL;
    self->item_size = 0;
    self->capacity = 0;
}

bool q_empty(Queue* self) {
    return self->length == 0 || self->items == NULL || self->capacity == 0;
}
