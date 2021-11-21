#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	float x;
	float y;
} vect2_t;

typedef struct {
	float x;
	float y;
	float z;
} vect3_t;

// TODO: Add functions to manipulate vectors 2D and 3D
///////////////////////////////////////////////////////
// Vector 2D functions
//////////////////////////////////////////////////////

float vec2_length(vect2_t v);

vect2_t vec2_add(vect2_t a, vect2_t b);
vect2_t vec2_sub(vect2_t a, vect2_t b);
vect2_t vec2_mul(vect2_t v, float factor);
vect2_t vec2_div(vect2_t v, float factor);
float vec2_dot(vect2_t a, vect2_t b);

///////////////////////////////////////////////////////
// Vector 3D functions
///////////////////////////////////////////////////////
float vec3_length(vect3_t v);

vect3_t vec3_add(vect3_t a, vect3_t b);
vect3_t vec3_sub(vect3_t a, vect3_t b);
vect3_t vec3_mul(vect3_t v, float factor);
vect3_t vec3_div(vect3_t v, float factor);
vect3_t vec3_cross(vect3_t a, vect3_t b);
float vec3_dot(vect3_t a, vect3_t b);

vect3_t vec3_rotate_x(vect3_t v, float angle);
vect3_t vec3_rotate_y(vect3_t v, float angle);
vect3_t vec3_rotate_z(vect3_t v, float angle);


#endif