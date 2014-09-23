#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CL/cl.h>
#include "Platform.h"
#include "Device.h"
#include "Util.h"

int main(void)
{
      cl_int err = EXIT_SUCCESS;
      cl_platform_id *cl_platforms;
      cl_uint num_platforms;
      cl_platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * MAX_PLATFORMS);
      if((err = PERR(clGetPlatformIDs(MAX_PLATFORMS, cl_platforms, &num_platforms), "Error getting platform IDs")));
            goto bail;

      Platform **platforms = (Platform**)malloc(sizeof(Platform*) * num_platforms);
      for(unsigned int i = 0; i < num_platforms; ++i)
            platforms[i] = new_Platform(cl_platforms[i]);

      err = EXIT_SUCCESS;
bail:
      free(cl_platforms);
      return err;
}
