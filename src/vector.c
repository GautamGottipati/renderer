#include <math.h>
#include "vector.h"

// TODO: Implementation of all the functions

///////////////////////////////////////////////////////
// Implementation of Vector 2D functions
//////////////////////////////////////////////////////

float vec2_length(vect2_t v){
	return sqrt(v.x * v.x + v.y * v.y);
}

vect2_t vec2_add(vect2_t a, vect2_t b){
	vect2_t result = {
		.x = a.x + b.x,
		.y = a.y + b.y
	};
	return result;
}

vect2_t vec2_sub(vect2_t a, vect2_t b){
	vect2_t result = {
		.x = a.x - b.x,
		.y = a.y - b.y
	};
	return result;
}


///////////////////////////////////////////////////////
// Implementation of Vector 3D functions
//////////////////////////////////////////////////////

float vec3_length(vect3_t v){
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vect3_t  vec3_rotate_x(vect3_t v, float angle) {
	vect3_t rotated_vector = {
		.x = v.x,
		.y = v.y * cos(angle) - v.z * sin(angle),
		.z = v.y * sin(angle) + v.z * cos(angle)
	};
	return rotated_vector;
}

vect3_t vec3_rotate_y(vect3_t v, float angle) {
	vect3_t rotated_vector = {
		.x = v.x * cos(angle) - v.z * sin(angle),
		.y = v.y,
		.z = v.x * sin(angle) + v.z * cos(angle)
	};
	return rotated_vector;
}

vect3_t vec3_rotate_z(vect3_t v, float angle) {
	vect3_t rotated_vector = {
		.x = v.x * cos(angle) - v.y * sin(angle),
		.y = v.x * sin(angle) + v.y * cos(angle),
		.z = v.z
	};

	return rotated_vector;
}

vect3_t vec3_add(vect3_t a, vect3_t b){
	vect3_t result = {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	};
	return result;
}

vect3_t vec3_sub(vect3_t a, vect3_t b){
	vect3_t result = {
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	};
	return result;
}