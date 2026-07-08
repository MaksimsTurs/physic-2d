#ifndef H_PHYSIC2D
#define H_PHYSIC2D

#include "type.h"
#include "body2d.h"

typedef struct {
  body2d_t* a;
  body2d_t* b;
} collision_pair_t;

void physic2d_set_gravity(f32_t gravity);

bool_t physic2d_check_aabb(body2d_t* a, body2d_t* b);

void physic2d_update(f32_t dt, body2d_t** bodies, i32_t length);
void physic2d_collect_collisions(body2d_t** bodies, i32_t length);
void physic2d_resolve_collisions();

#endif
