#include "queue.h"
/**
 * @defgroup Queue Queue
 * 
 */


/*!
 * @ingroup Queue Queue
 * @brief Structure representing a queue.
 */
struct queue
{
    int *buf;
    int in, out;
    unsigned int size, count;
};

/*!
 * @ingroup Queue Queue
 * @brief Adjusts the queue indices to wrap around when they reach the end of the buffer.
 * 
 * @param q Pointer to the queue structure.
 */
static void adjust_queue(queue_t* q) {
    q->in %= q->size;
    q->out %= q->size;
}

/*!
 * @ingroup Queue Queue
 * @brief Resizes the queue buffer to double its current size.
 * 
 * @param q Pointer to the queue structure.
 * @return int Returns 0 upon success and -1 upon failure.
 */
static int resize_queue(queue_t *q) {
    int *p = (int *)realloc(q->buf, 2 * (q->size) * sizeof(int));

    int i;
    if (p == NULL) {
        return -1;
    }

    q->buf = p;
    for (i = 0; i < q->in; i++) {
        q->buf[q->size + i] = q->buf[i];
    }
    q->in += q->size;
    q->size *= 2;
    return 0;
}

/*!
 * @ingroup Queue Queue
 * @brief Creates a new queue.
 * 
 * @return queue_t* Pointer to the newly created queue, or NULL if memory allocation fails.
 */
queue_t *new_queue() {

    queue_t *q = (queue_t *)malloc(sizeof(queue_t));
    if (q == NULL)
        return NULL;

    q->size = 100;
    q->count = q->in = q->out = 0;

    q->buf = (int *)malloc(q->size * sizeof(int));
    if (q == NULL) {
        free(q);
        return NULL;
    }

    return q;
}

/*!
 * @ingroup Queue Queue
 * @brief Deletes a queue and frees its memory.
 * 
 * @param q Pointer to the queue structure.
 */
void delete_queue(queue_t *q) {
    free(q->buf);
    free(q);
}

/*!
 * @ingroup Queue Queue
 * @brief Adds an element to the queue.
 * 
 * @param q Pointer to the queue structure.
 * @param n The element to be added.
 * @return int Returns 0 upon success and 1 upon failure.
 */
int push(queue_t *q, int n) {
    if (q->count == q->size) {
        if (resize_queue(q))
            return 1;
    }

    q->buf[q->in++] = n;
    q->count++;
    adjust_queue(q);
    return 0;
}

/*!
 * @ingroup Queue Queue
 * @brief Removes an element from the queue.
 * 
 * @param q Pointer to the queue structure.
 * @param n Pointer to the variable where the removed element will be stored.
 * @return int Returns 0 upon success and -1 if the queue is empty.
 */
int pop(queue_t *q, int* n) {
    if (q->count > 0) {
        *n = q->buf[q->out];
        q->count = q->count - 1;
        adjust_queue(q);
        return 0;
    }
    return -1;
}

/*!
 * @ingroup Queue Queue
 * @brief Clears all elements from the queue.
 * 
 * @param q Pointer to the queue structure.
 */
void clear_queue(queue_t *q) {
    int p;
    while (q->count > 0)
    {
        pop(q,&p);
    }
}

/*!
 * @ingroup Queue Queue
 * @brief Checks if the queue is empty.
 * 
 * @param q Pointer to the queue structure.
 * @return bool Returns true if the queue is empty, otherwise false.
 */
bool is_empty(queue_t *q) {
    return (q->count == 0);
}
