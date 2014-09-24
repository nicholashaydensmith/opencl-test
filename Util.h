#ifndef __UTIL_H__
#define __UTIL_H__

#define SFREE(x) if(x) free((void*)x)
#define PERR(b, s) ((b) && (fprintf(stderr, s"\n")))

#define MAX_DEVICES 16
#define MAX_PLATFORMS 16
#define MAX_THREADS 1024

typedef enum {
      false = 0,
      true = 1,
} Bool;

#endif
