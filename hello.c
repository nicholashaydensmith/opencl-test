#include <stdio.h>
#include <string.h>
#include <CL/cl.h>

int main(void)
{
      fprintf(stderr, "TESTERR\n");
      cl_int err;
      cl_int num_entries = 5;
      cl_platform_id *platforms;
      cl_uint num_platforms;
      platforms = malloc(sizeof(cl_platform_id) * num_entries);
      err = clGetPlatformIDs(num_entries, platforms, &num_platforms);
      if(err)
            fprintf(stderr, "Error getting platform IDs\n");

      for(unsigned int i = 0; i < num_platforms; ++i)
      {
            char buf[256];
            size_t str_size;
            err = clGetPlatformInfo(platforms[i],
                              CL_PLATFORM_NAME,
                              sizeof(buf),
                              (void*)buf,
                              &str_size);
            if (err == CL_INVALID_PLATFORM)
            {
                  fprintf(stderr, "Invalid device\n");
                  break;
            }
            if (err == CL_INVALID_VALUE)
            {
                  fprintf(stderr, "Invalid value\n");
                  break;
            }
            char *platform_name = malloc(str_size);
            memcpy(platform_name, buf, str_size);
            printf("Platform[%d]: %s\n", i, platform_name);
            free(platform_name);
      }
      cl_platform_id platform = platforms[0];
      cl_int device_entries = 1;
      cl_uint num_devices;
      cl_device_id *devices;
      devices = malloc(sizeof(cl_device_id) * device_entries);
      clGetDeviceIDs(platform,
                     CL_DEVICE_TYPE_GPU,
                     device_entries, 
                     devices, 
                     &num_devices);

      for(unsigned int i = 0; i < num_devices; ++i)
      {
            char buf[256];
            size_t str_size;
            clGetDeviceInfo(devices[i],
                              CL_DEVICE_NAME,
                              sizeof(buf),
                              (void*)buf,
                              &str_size);
            if (err == CL_INVALID_DEVICE)
            {
                  fprintf(stderr, "Invalid device\n");
                  break;
            }
            if (err == CL_INVALID_VALUE)
            {
                  fprintf(stderr, "Invalid value\n");
                  break;
            }
            char *device_name = malloc(str_size);
            memcpy(device_name, buf, str_size);
            printf("Device[%d]: %s\n", i, device_name);
            free(device_name);
      }
      free(devices);
      free(platforms);
}
