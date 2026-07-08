#ifndef H_PHYSIC2D_BODY2D
#define H_PHYSIC2D_BODY2D

#include "type.h"
#include "vector.h"
#include "transform.h"
#include "shape2d.h"

typedef enum {
  BODY2D_UNKNOWN,
  BODY2D_STATIC,
  BODY2D_RIGID
} body2d_type_t;

typedef struct {
  body2d_type_t   body_type;
  shape2d_type_t  shape_type;
  shape2d_t       shape;
  vec2f32_t       velocity;
  vec2f32_t       force;
  f32_t           mass;
  transfrom2d_t*  transform;
} body2d_t;

#endif
