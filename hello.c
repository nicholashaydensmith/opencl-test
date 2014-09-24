#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <CL/cl.h>
#include "ContextManager.h"
#include "Util.h"

typedef struct {
      char *data;
	  int width;
	  int height;
} Bitmap;

Bitmap *new_Bitmap()
{
      Bitmap *self = malloc(sizeof(Bitmap));
	  self->data = NULL;
	  self->width = 0;
	  self->height = 0;
	  return self;
}

void delete_Bitmap(Bitmap *self)
{
      SFREE(self->data);
	  SFREE(self);
}

void write_file(void *stuff)
{
	printf("Made it here!\n");
}

int main(void)
{
      cl_int err;
      Bitmap *test = new_Bitmap();
	  ContextManager *context_manager = new_ContextManager();
	  //ContextManager_AddTask(context_manager, test, write_file);
	  ContextManager_AddTask(context_manager, "hello", write_file);
	  ContextManager_AddTask(context_manager, "world", write_file);
	  ContextManager_AddTask(context_manager, "foo", write_file);
	  ContextManager_AddTask(context_manager, "bar", write_file);
	  sleep(3);
	  delete_ContextManager(context_manager);
      delete_Bitmap(test);
      err = EXIT_SUCCESS;
      return err;
}
