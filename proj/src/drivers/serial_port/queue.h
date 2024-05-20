#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

struct queue;
typedef struct queue queue_t;

queue_t *new_queue();

void delete_queue(queue_t *q);

int push(queue_t *q, int n);

int pop(queue_t *q, int* n);

void clear_queue(queue_t *q);

bool is_empty(queue_t *q);

#endif /* _QUEUE_H_ */

