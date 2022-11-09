#include "queue.h"
#include <stdio.h>

int main(void) {

    Queue q = {0};
    q_init(&q, sizeof(int), 5);
    assert(q.front == q.back);
    assert(q.capacity == 5);
    assert(q.length == 0);
    assert(q.item_size == sizeof(int));
    puts("q_init() test passed");

    q_add(&q, &(int[]) {1, 2, 3, 4, 5}, 5);
    assert(q.length == 5);
    assert(q.front != q.back);
    assert(q.back == q.front + 4 * sizeof(int)); // arr[4] = 5th
    puts("q_add() test passed");

    q_add(&q, &(int[]) {6, 7, 8, 9, 10}, 5);
    assert(q.length == 5);
    assert(q.front != q.back);
    assert(q.back == q.front + 4 * sizeof(int));
    puts("q_add() while full test passed");

    q_pop(&q, 3);
    assert(q.length == 2);
    assert(q.front != q.back);
    assert(q.back == q.front + 1 * sizeof(int));
    puts("q_pop() test passed");

    q_clear(&q);
    assert(q.length == 0);
    assert(q.front == q.back);
    puts("q_clear() test passed");

    q_add(&q, &(int[]) {1, 2, 3, 4, 5}, 5);
    puts("q_add() after q_clear() test passed");

    assert(q_get(int, &q, 0) == 1);
    assert(q_get(int, &q, 3) == 4);
    puts("q_get() with positive index test passed");

    assert(q_get(int, &q, -1) == 5);
    assert(q_get(int, &q, -4) == 2);
    puts("q_get() with negative index test passed");

    assert(q_get_ptr(&q, 0) == q.front);
    assert(q_get_ptr(&q, -1) == q.back);
    puts("q_get() test passed");

    q_set_capacity(&q, 10);
    assert(q.capacity == 10);
    assert(q.length == 5);
    assert(q.front == q.items);
    assert(q.back == q.front + 4 * sizeof(int));

    q_add(&q, &(int[]) {6, 7, 8, 9, 10}, 5);
    assert(q.length == 10);
    assert(q.back == q.front + 9 * sizeof(int));
    puts("q_set_capacity() test passed");

    q_clear(&q);
    assert(q_empty(&q));

    puts("q_empty() test passed");

    q_free(&q);

    puts("All tests passed");

    return 0;
}
