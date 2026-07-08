#ifndef H_PHYSIC2D_SHAPE2D
#define H_PHYSIC2D_SHAPE2D

#include "type.h"

typedef enum {
  SHAPE2D_UNKNOWN,
  SHAPE2D_QUAD
} shape2d_type_t;

typedef struct {
  f32_t w, h;
} box_shape2d_t;

typedef union {
  box_shape2d_t box;
} shape2d_t;


#endif
