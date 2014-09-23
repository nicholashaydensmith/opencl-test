#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CL/cl.h>
#include "Platform.h"
#include "Device.h"
#include "Util.h"

static int CL_DEVICE_INFO[37] = { 
      CL_DEVICE_ADDRESS_BITS,
      CL_DEVICE_AVAILABLE,
      CL_DEVICE_ENDIAN_LITTLE,
      CL_DEVICE_EXTENSIONS,
      CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,
      CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,
      CL_DEVICE_GLOBAL_MEM_SIZE,
      CL_DEVICE_MAX_COMPUTE_UNITS,
      CL_DEVICE_MAX_CONSTANT_ARGS,
      CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
      CL_DEVICE_MAX_MEM_ALLOC_SIZE,
      CL_DEVICE_MAX_PARAMETER_SIZE,
      CL_DEVICE_MAX_READ_IMAGE_ARGS,
      CL_DEVICE_MAX_SAMPLERS,
      CL_DEVICE_MAX_WORK_GROUP_SIZE,
      CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
      CL_DEVICE_MAX_WORK_ITEM_SIZES,
      CL_DEVICE_MAX_WRITE_IMAGE_ARGS,
      CL_DEVICE_MEM_BASE_ADDR_ALIGN,
      CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE,
      CL_DEVICE_NAME,
      CL_DEVICE_PLATFORM,
      CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR,
      CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT,
      CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT,
      CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG,
      CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,
      CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,
      CL_DEVICE_PROFILE,
      CL_DEVICE_PROFILING_TIMER_RESOLUTION,
      CL_DEVICE_QUEUE_PROPERTIES,
      CL_DEVICE_SINGLE_FP_CONFIG,
      CL_DEVICE_TYPE,
      CL_DEVICE_VENDOR,
      CL_DEVICE_VENDOR_ID,
      CL_DEVICE_VERSION,
      CL_DRIVER_VERSION,
};

enum {
      kDeviceInfoProfile,
      kDeviceInfoVersion,
      kDeviceInfoName,
      kDeviceInfoVendor,
      kDeviceInfoExtenstions,
      kDeviceInfoSize,
} DeviceInfo;

struct _Device
{
      Platform *platform;
      cl_device_id device_id;
      char *device_info[kDeviceInfoSize];
      int num_contexts;
      
};

Device *new_Device(Platform *platform, cl_device_id device_id)
{
      Device *self = (Device*)malloc(sizeof(Device));
      self->device_id = device_id;
      self->platform = platform;
      self->num_contexts = 0;

      for(int i = 0; i < kDeviceInfoSize; ++i)
      {
            cl_int err;
            char buf[256];
            size_t str_size;
            err = clGetDeviceInfo(device_id,
                              CL_DEVICE_INFO[i],
                              sizeof(buf),
                              (void*)buf,
                              &str_size);
            if (PERR(err == CL_INVALID_DEVICE, "Invalid Device"))
                  goto bail;
            if (PERR(err == CL_INVALID_VALUE, "Invalid Value"))
                  goto bail;
            self->device_info[i] = malloc(str_size);
            memcpy(self->device_info[i], buf, str_size);
      }

      return self;

bail:
      delete_Device(self);
      return NULL;
}

void delete_Device(Device *self)
{
      for(int i = 0; i < kDeviceInfoSize; ++i)
            SFREE(self->device_info[i]);
      SFREE(self);
}
