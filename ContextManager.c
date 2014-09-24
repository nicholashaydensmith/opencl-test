#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <CL/cl.h>
#include "ContextManager.h"
#include "Platform.h"
#include "Context.h"
#include "Queue.h"
#include "Util.h"

struct _ContextManager
{
      Platform **platforms;
      int num_platforms;
	  Queue *incoming_queue;
	  Queue *outgoing_queue;
	  pthread_t threads[MAX_THREADS]; // Thread 0 and 1 are consumer / producer threads respectively
                                      //  > 1 are context threads
      int num_threads;
};

void *ContextManager_Consumer(void *self);
void *ContextManager_Producer(void *self);
void ContextManager_ShutdownQueues(ContextManager *self);

ContextManager *new_ContextManager()
{
      ContextManager *self = (ContextManager*)malloc(sizeof(ContextManager));

	  cl_int err;
      cl_platform_id *cl_platforms;
      cl_uint num_platforms;
      cl_platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * MAX_PLATFORMS);
	  err = clGetPlatformIDs(MAX_PLATFORMS, cl_platforms, &num_platforms);
      if(PERR(err == CL_INVALID_VALUE, "Error getting platform IDs"))
            goto bail;

	  self->num_platforms = num_platforms;
	  if(self->num_platforms > 0)
		  self->platforms = (Platform**)malloc(sizeof(Platform*) * num_platforms);
      for(unsigned int i = 0; i < num_platforms; ++i)
            self->platforms[i] = new_Platform(cl_platforms[i]);

	  free(cl_platforms);

	  self->incoming_queue = new_Queue();
	  self->outgoing_queue = new_Queue();

      err = pthread_create(&self->threads[0], NULL, ContextManager_Consumer, (void*)self);
      err = pthread_create(&self->threads[1], NULL, ContextManager_Producer, (void*)self);
	  self->num_threads = 2;

      return self;
bail:
	  delete_ContextManager(self);
	  return NULL;
}

void delete_ContextManager(ContextManager *self)
{
      for(int i = 0; i < self->num_platforms; ++i)
		  delete_Platform(self->platforms[i]);
	  ContextManager_ShutdownQueues(self);
	  for(int i = 0; i < self->num_threads; ++i)
	  {
		  pthread_join(self->threads[i], NULL);
	  }
      delete_Queue(self->incoming_queue, true);
      delete_Queue(self->outgoing_queue, true);
      SFREE(self);
}

void ContextManager_AddTask(ContextManager *self, void *data, void (callback_func)(void*))
{
      Queue_Enqueue(self->incoming_queue, data);
}

void ContextManager_ShutdownQueues(ContextManager *self)
{
      Queue_Enqueue(self->incoming_queue, NULL);
      Queue_Enqueue(self->outgoing_queue, NULL);
}

void *ContextManager_Consumer(void *_self)
{
      ContextManager *self = (ContextManager*)_self;
	  Queue *q = self->incoming_queue;
      while(true)
	  {
		  while(Queue_Empty(q))
			  pthread_yield();
		  void *data = Queue_Dequeue(q);
		  if(data == NULL)
			  break;
		  printf("Enqueueing data!\n");
		  Queue_Enqueue(self->outgoing_queue, data);
	  }
	  printf("Consumer queue shut down\n");
      return NULL;
}

void *ContextManager_Producer(void *_self)
{
      ContextManager *self = (ContextManager*)_self;
	  Queue *q = self->outgoing_queue;
      while(true)
	  {
		  while(Queue_Empty(q))
			  pthread_yield();
		  void *data = Queue_Dequeue(q);
		  if(data == NULL)
			  break;
		  printf("%s\n", (char*)data);
	  }
	  printf("Producer queue shut down\n");
      return NULL;
}
