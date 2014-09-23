#include <stdlib.h>
#include "ContextManager.h"
#include "Device.h"
#include "Util.h"


struct _ContextManager
{
      Device *device_list;
      unsigned int num_devices;
      unsigned int *devices_in_use;
      
};

ContextManager *new_ContextManager()
{
      ContextManager *self = (ContextManager*)malloc(sizeof(ContextManager));
      return self;
}

void delete_ContextManager(ContextManager *self)
{
      SFREE(self);
}
