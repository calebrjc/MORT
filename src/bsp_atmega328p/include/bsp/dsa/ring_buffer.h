#ifndef _CALEBRJC_BSP_DSA_RINGBUFFER_RINGBUFFER_H_
#define _CALEBRJC_BSP_DSA_RINGBUFFER_RINGBUFFER_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/// @brief Ring buffer data structure.
typedef struct ring_buffer {
    /// @brief The buffer.
    uint8_t *buffer;

    /// @brief The size of the buffer.
    size_t size;

    /// @brief The index of the front of the buffer.
    size_t head;

    /// @brief The index of the back of the buffer.
    size_t tail;
} ring_buffer;

/// @brief Initialize a ring buffer.
/// @param rb The ring buffer to initialize.
/// @param buffer The buffer to use for the ring buffer.
/// @param size The size of the buffer.
void rb_init(ring_buffer *rb, uint8_t *buffer, size_t size);

/// @brief Enqueue data into the ring buffer.
/// @param rb The ring buffer to enqueue data into.
/// @param data The data to enqueue.
void rb_enqueue(ring_buffer *rb, uint8_t data);

/// @brief Pop and return the data at the front of the ring buffer.
/// @param rb The ring buffer to dequeue data from.
/// @return The data at the front of the ring buffer.
uint8_t rb_dequeue(ring_buffer *rb);

/// @brief Return the data at the front of the ring buffer without removing it.
/// @param rb The ring buffer to peek at.
/// @return The data at the front of the ring buffer.
uint8_t rb_peek(ring_buffer *rb);

/// @brief Return the number of elements in the ring buffer.
/// @param rb The ring buffer to get the size of.
/// @return The number of elements in the ring buffer.
size_t rb_size(const ring_buffer *rb);

/// @brief Return the capacity of the ring buffer.
/// @param rb The ring buffer to get the capacity of.
/// @return The capacity of the ring buffer.
size_t rb_capacity(const ring_buffer *rb);

/// @brief Return true if the ring buffer is empty, and false otherwise.
/// @param rb The ring buffer to check.
/// @return True if the ring buffer is empty, and false otherwise.
bool rb_is_empty(const ring_buffer *rb);

/// @brief Return true if the ring buffer is full, and false otherwise.
/// @param rb The ring buffer to check.
/// @return True if the ring buffer is full, and false otherwise.
bool rb_is_full(const ring_buffer *rb);

#endif  // _CALEBRJC_BSP_DSA_RINGBUFFER_RINGBUFFER_H_
