#include <stdlib.h>
#include <pthread.h>
#include "Queue.h"

// Pthread Queue

typedef struct _Item Item;
struct _Item {
      Item *next;
      void *data;
};

struct _Queue {
      Item *head;
      Item *tail;
      int count;
      pthread_mutex_t lock;
};

Queue *new_Queue()
{
      Queue *self = (Queue*)malloc(sizeof(Queue));
      self->head = NULL;
      self->tail = NULL;
      self->count = 0;
      pthread_mutex_init(&self->lock, NULL);
      return self;
}

void delete_Queue(Queue *self, int free_elems)
{
      for(Item *iter = self->head; iter->next != NULL; iter = iter->next)
      {
            if(free_elems)
                  free(iter->data);
            free(iter);
      }
      pthread_mutex_destroy(&self->lock);
      free(self);
}

int Queue_Empty(Queue *self)
{
      return self->head == NULL;
}

int Queue_Count(Queue *self)
{
      return self->count;
}

void Queue_Enqueue(Queue *self, void *data)
{
      Item *item = (Item*)malloc(sizeof(Item));
      item->data = data;
      item->next = NULL;
      pthread_mutex_lock(&self->lock);
      if(self->head == NULL)
      {
            self->head = item;
            self->tail = self->head;
      }
      else
      {
            self->tail->next = item;
            self->tail = self->tail->next;
      }
      ++self->count;
      pthread_mutex_unlock(&self->lock);
}

void *Queue_Dequeue(Queue *self)
{
      if(self->head == NULL)
            return NULL;
      Item *head; 
      pthread_mutex_lock(&self->lock);
      head = self->head;
      self->head = self->head->next;
      --self->count;
      pthread_mutex_unlock(&self->lock);
      void *data = head->data;
      free(head);
      return data;
}

void *Queue_Head(Queue *self)
{
      void *data;
      pthread_mutex_lock(&self->lock);
      data = self->head->data;
      pthread_mutex_unlock(&self->lock);
      return data;
}

void *Queue_Tail(Queue *self)
{
      void *data;
      pthread_mutex_lock(&self->lock);
      data = self->tail->data;
      pthread_mutex_unlock(&self->lock);
      return data;
}

