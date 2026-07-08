#include "include/physic2d.h"

static f32_t g_gravity = 9.81f;
static i32_t g_max_collision_pairs = 12;

static collision_pair_t g_collision_pairs[12] = {0};
static i32_t g_collison_pairs_length = 0;

void physic2d_set_gravity(f32_t gravity)
{
  g_gravity = gravity;
}

bool_t physic2d_check_aabb(body2d_t* a, body2d_t* b)
{
  return(
    a->transform->translation.x - (a->shape.box.w / 2) <= b->transform->translation.x + (b->shape.box.w / 2) &&
    a->transform->translation.x + (a->shape.box.w / 2) >= b->transform->translation.x - (b->shape.box.w / 2) &&
    a->transform->translation.y - (a->shape.box.h / 2) <= b->transform->translation.y + (b->shape.box.h / 2) &&
    a->transform->translation.y + (a->shape.box.h / 2) >= b->transform->translation.y - (b->shape.box.h / 2)
  );
}

void physic2d_update(f32_t dt, body2d_t** bodies, i32_t length)
{
  body2d_t* body = 0;
  body2d_type_t body_type = BODY2D_UNKNOWN;

  for(i32_t i = 0; i < length; i++)
  {
    body = bodies[i];
    body_type = body->body_type;

    switch(body_type) {
      case BODY2D_RIGID:
        body->force.y += g_gravity;

        vec2f32_t acceleration = {body->force.x / body->mass, body->force.y / body->mass};
        
        body->velocity.x += acceleration.x * (dt * dt);
        body->velocity.y += acceleration.y * (dt * dt);
        body->transform->translation.x += body->velocity.x;
        body->transform->translation.y += body->velocity.y;
      break;
      case BODY2D_STATIC:
        (void)0;
      break;
      default:
        (void)0;
    }
  }
}

void physic2d_collect_collisions(body2d_t **bodies, i32_t length)
{
  g_collison_pairs_length = 0;

  body2d_t* a = 0;
  body2d_t* b = 0;

  for(i32_t i = 0; i < length; i++)
  {
    for(i32_t j = 1; j < length; j++)
    {
      a = bodies[i];
      b = bodies[j];

      if(a != b && a->shape_type == SHAPE2D_QUAD && b->shape_type == SHAPE2D_QUAD)
      {
        if(physic2d_check_aabb(a, b))
        {
          g_collision_pairs[g_collison_pairs_length].a = a;
          g_collision_pairs[g_collison_pairs_length].b = b;
          g_collison_pairs_length++;
        }
      }
    }
  }
}

void physic2d_resolve_collisions()
{
  body2d_t* a = 0;
  body2d_t* b = 0;
  body2d_t* tmp = 0;
  
  for(i32_t i = 0; i < g_collison_pairs_length; i++)
  {
    a = g_collision_pairs[i].a;
    b = g_collision_pairs[i].b;

    if(a->body_type == BODY2D_STATIC && b->body_type == BODY2D_RIGID)
    {
      tmp = a;
      a = b;
      b = tmp;
    }

    f32_t dy = b->transform->translation.y - b->transform->translation.y * 1.018f;

    a->transform->translation.y = (b->transform->translation.y - b->shape.box.h) + dy;
    a->velocity.y = 0.0f;
  }
}
