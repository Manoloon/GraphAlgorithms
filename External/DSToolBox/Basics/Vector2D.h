#pragma once
#include <math.h>
/*
    Basic vector2D
*/

typedef struct vec2i{ int x,y;}vec2i;
typedef struct vec2f { float x,y;}vec2f;


static vec2i to_vec2i(vec2f value)
{
    return (vec2i){(int)value.x,(int)value.y};
}
static vec2f to_vec2f(vec2i value)
{
    return (vec2f){(float)value.x,(float)value.y};
}
static float vec2f_length(vec2f v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

static vec2f vec2f_normalize(vec2f v)
{
    float len = vec2f_length(v);
    if(len == 0.0f) return (vec2f){0.0f,0.0f};
    return (vec2f){v.x / len, v.y / len};
}