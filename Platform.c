#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CL/cl.h>
#include "Platform.h"
#include "Device.h"
#include "Util.h"

static int CL_PLATFORM_INFO[5] = { 
                                    CL_PLATFORM_PROFILE,
                                    CL_PLATFORM_VERSION,
                                    CL_PLATFORM_NAME,
                                    CL_PLATFORM_VENDOR,
                                    CL_PLATFORM_EXTENSIONS,
                                 };

enum {
      kPlatformInfoProfile,
      kPlatformInfoVersion,
      kPlatformInfoName,
      kPlatformInfoVendor,
      kPlatformInfoExtenstions,
      kPlatformInfoSize,
} PlatformInfo;

struct _Platform
{
      cl_platform_id platform_id;
      char *platform_info[kPlatformInfoSize];
      Device **devices;
};

Platform *new_Platform(cl_platform_id platform_id)
{
      Platform *self = (Platform*)malloc(sizeof(Platform));
      self->platform_id = platform_id;

      for(int i = 0; i < kPlatformInfoSize; ++i)
      {
            cl_int err;
            char buf[256];
            size_t str_size;
            err = clGetPlatformInfo(platform_id,
                              CL_PLATFORM_INFO[i],
                              sizeof(buf),
                              (void*)buf,
                              &str_size);
            if (PERR(err == CL_INVALID_PLATFORM, "Invalid Platform"))
                  goto bail;
            if (PERR(err == CL_INVALID_VALUE, "Invalid Value"))
                  goto bail;
            self->platform_info[i] = malloc(str_size);
            memcpy(self->platform_info[i], buf, str_size);
      }

      cl_int err; 
      cl_uint num_devices;
      cl_device_id *devices;
      devices = (cl_device_id*)malloc(sizeof(cl_device_id) * MAX_DEVICES);
      if((PERR(err = clGetDeviceIDs(platform_id,
                     CL_DEVICE_TYPE_GPU,
                     MAX_DEVICES, 
                     devices, 
                     &num_devices), "Unable to get device IDs")))
            goto bail;
      self->devices = (Device**)malloc(sizeof(Device*) * num_devices);

      for(unsigned int i = 0; i < num_devices; ++i)
            self->devices[i] = new_Device(devices[i]);

      free(devices);

      return self;
bail:
      delete_Platform(self);
      return NULL;
}

void delete_Platform(Platform *self)
{
      for(int i = 0; i < kPlatformInfoSize; ++i)
            SFREE(self->platform_info[i]);
      SFREE(self);
}
