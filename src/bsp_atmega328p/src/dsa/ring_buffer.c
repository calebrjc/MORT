#include "bsp/dsa/ring_buffer.h"

void rb_init(ring_buffer *rb, uint8_t *buffer, size_t size) {
    rb->buffer = buffer;
    rb->size   = size;
    rb->head   = 0;
    rb->tail   = 0;
}

void rb_enqueue(ring_buffer *rb, uint8_t data) {
    rb->buffer[rb->head] = data;

    // Chase the tail
    rb->head = (rb->head + 1) % rb->size;
}

uint8_t rb_dequeue(ring_buffer *rb) {
    uint8_t data = rb->buffer[rb->tail];

    // Run from the head
    rb->tail = (rb->tail + 1) % rb->size;

    return data;
}

uint8_t rb_peek(ring_buffer *rb) {
    return rb->buffer[rb->tail];
}

size_t rb_size(const ring_buffer *rb) {
    return (rb->head - rb->tail) % rb->size;
}

size_t rb_capacity(const ring_buffer *rb) {
    return rb->size - 1;
}

bool rb_is_empty(const ring_buffer *rb) {
    return rb->head == rb->tail;
}

bool rb_is_full(const ring_buffer *rb) {
    return (rb->head + 1) % rb->size == rb->tail;
}
