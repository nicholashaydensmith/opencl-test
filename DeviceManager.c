#include "Device.h"
#include "DeviceManager.h"

#define sfree(x) if(x) free(x);

struct _DeviceManager
{
      Device *device_list;
      int num_devices;
      int *devices_in_use;
      
};

DeviceManager *new_DeviceManager()
{
      DeviceManager *this = (DeviceManager*)malloc(sizeof(DeviceManager));
      this->device_list = NULL;
      this->num_devices = 0;
      this->devices_in_use = NULL;
      init_gpu();
      return this;
}

void delete_DeviceManager(DeviceManager *this)
{
      sfree(this->device_list);
      sfree(this->devices_in_use);
      sfree(this);
}
