#ifndef H_LINEARALGEBRA_TRANSFORM
#define H_LINEARALGEBRA_TRANSFORM

#include <math.h>

#include "type.h"
#include "vector.h"
#include "matrix.h"

typedef struct {
  vec2f32_t translation;
  vec2f32_t origin;
  vec2f32_t scale;
  f32_t     rotation;
} transfrom2d_t;

void        transfrom2d_look_at(transfrom2d_t* transform, const vec2f32_t* position, const vec2f32_t* target);
mat3x3f32_t transform2d_to_mat3x3f32(const transfrom2d_t* transform);

#endif
