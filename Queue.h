#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct _Queue Queue;

Queue *new_Queue(void);

void delete_Queue(Queue *self, int free_elems);

int Queue_Empty(Queue *self);

int Queue_Count(Queue *self);

void Queue_Enqueue(Queue *self, void *data);

void *Queue_Dequeue(Queue *self);

void *Queue_Head(Queue *self);

void *Queue_Tail(Queue *self);

#endif
