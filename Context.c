#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Context.h"
#include "Util.h"

struct _Context
{
     int i; 
};

Context *new_Context()
{
      Context *self = (Context*)malloc(sizeof(Context));
      return self;
}

void delete_Context(Context *self)
{
      SFREE(self);
}
