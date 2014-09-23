#ifndef __UTIL_H__
#define __UTIL_H__

#define SFREE(x) if(x) free((void*)x)
#define PERR(b, s) ((b) && (fprintf(stderr, s"\n")))

#define MAX_DEVICES 16
#define MAX_PLATFORMS 16

enum {
      FALSE = 0,
      TRUE = 1,
} bool;

#endif
