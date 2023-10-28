#include "bsp/dsa/queue.h"

void q_init(queue *q, uint8_t *buffer, size_t size) {
    // Sanity check arguments
    if (!q || !buffer || size == 0) return;

    q->data    = buffer;
    q->size    = size;
    q->head    = 0;
    q->tail    = 0;
    q->is_full = false;
}

void q_enqueue(queue *q, uint8_t data) {
    // If the queue is full, do nothing
    if (!q || q_is_full(q)) return;

    // Enqueue the data
    q->data[q->head] = data;

    // Wrap around if the head is at the end of the queue
    q->head = (q->head + 1 == q->size) ? 0 : q->head + 1;

    // If the head is equal to the tail, the queue is full
    if (q->head == q->tail) q->is_full = true;
}

uint8_t q_dequeue(queue *q) {
    // If the queue is empty, return 0
    if (!q || q_is_empty(q)) return 0;

    // Dequeue the data
    uint8_t data = q->data[q->tail];

    // Wrap around if the tail is at the end of the queue
    q->tail = (q->tail + 1 == q->size) ? 0 : q->tail + 1;

    // If the head is not equal to the tail, the queue is not full
    if (q->head != q->tail) q->is_full = false;

    return data;
}

uint8_t q_peek(queue *q) {
    // If the queue is empty, return 0
    if (!q || q_is_empty(q)) return 0;

    return q->data[q->tail];
}

size_t q_size(const volatile queue *q) {
    if (!q) return 0;

    if (q->is_full) return q->size;

    if (q->head >= q->tail) return q->head - q->tail;

    return q->size - q->tail + q->head;
}

bool q_is_empty(const volatile queue *q) {
    if (!q) return true;

    return q->head == q->tail && !q->is_full;
}

bool q_is_full(const volatile queue *q) {
    if (!q) return false;

    return q->is_full;
}
