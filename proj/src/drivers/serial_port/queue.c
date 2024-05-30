#include "queue.h"

struct queue
{
    int *buf;
    int in, out;
    unsigned int size, count;
};

static void adjust_queue(queue_t* q) {
    q->in %= q->size;
    q->out %= q->size;
}

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

void delete_queue(queue_t *q) {
    free(q->buf);
    free(q);
}

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

int pop(queue_t *q, int* n) {
    if (q->count > 0) {
        *n = q->buf[q->out];
        q->count = q->count - 1;
        adjust_queue(q);
        return 0;
    }
    return -1;
}

void clear_queue(queue_t *q) {
    int p;
    while (q->count > 0)
    {
        pop(q,&p);
    }
}

bool is_empty(queue_t *q) {
    return (q->count == 0);
}
