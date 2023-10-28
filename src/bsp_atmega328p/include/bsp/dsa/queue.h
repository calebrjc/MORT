#ifndef _CALEBRJC_BSP_DSA_QUEUE_H_
#define _CALEBRJC_BSP_DSA_QUEUE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/// Note:
/// I'm not sure if my use of the volatile keyword is the best here. I'm using it because I want to
/// be able to use the queue in an interrupt handler, and I don't want the compiler to
/// optimize away the reads and writes to the queue. I'm not sure if this is the best way to
/// do this, but it seems to work.
///
/// I came up with three ways to use the keyword in such a way that the compiler doesn't complain,
/// and that seems to work as I expect in interrupt-driven code:
/// - typedef volatile struct { ... } queue;
/// - typedef struct { volatile T ..., volatile T ... } queue;
/// - declare the queue as volatile in the function signatures that I deem necessary (mostly
///   accessor and status functions e.g. q_size, q_is_empty, q_is_full)
///
/// I'm not sure which of these is the best, but I'm going to go with my first approach for now.
///
/// (It could also be that I don't need to use the volatile keyword at all, and that I just need to
/// use some synchronization primitive e.g. condition variable, but I don't have access to those
/// yet, so I'm going to stick with volatile for now.)

/// @brief Queue data structure, implemented as a circular buffer.
typedef volatile struct {
    /// @brief The queue's data storage.
    uint8_t *data;

    /// @brief The size of the queue's data storage.
    size_t size;

    /// @brief The index of the front of the queue.
    size_t head;

    /// @brief The index of the back of the queue.
    size_t tail;

    /// @brief True if the queue is full, and false otherwise.
    bool is_full;
} queue;

/// @brief Initialize a queue.
/// @param q The queue to initialize.
/// @param buffer The buffer to use for the queue.
/// @param size The size of the buffer.
void q_init(queue *q, uint8_t *buffer, size_t size);

/// @brief Enqueue data into the queue, or do nothing if the queue is full.
/// @param q The queue to enqueue data into.
/// @param data The data to enqueue.
void q_enqueue(queue *q, uint8_t data);

/// @brief Pop and return the data at the front of the queue, or 0 if the queue is empty.
/// @param q The queue to dequeue data from.
/// @return The data at the front of the queue, or 0 if the queue is empty.
uint8_t q_dequeue(queue *q);

/// @brief Return the data at the front of the queue without removing it, or 0 if the queue is
/// empty.
/// @param q The queue to peek at.
/// @return The data at the front of the queue, or 0 if the queue is empty.
uint8_t q_peek(queue *q);

/// @brief Return the number of elements in the queue.
/// @param q The queue to get the size of.
/// @return The number of elements in the queue.
size_t q_size(const queue *q);

/// @brief Return true if the queue is empty, and false otherwise.
/// @param q The queue to check.
/// @return True if the queue is empty, and false otherwise.
bool q_is_empty(const queue *q);

/// @brief Return true if the queue is full, and false otherwise.
/// @param q The queue to check.
/// @return True if the queue is full, and false otherwise.
bool q_is_full(const queue *q);

#endif  // _CALEBRJC_BSP_DSA_QUEUE_H_
