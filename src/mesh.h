#pragma once
#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"
#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2)

/*Define an array of vertices*/
extern vect3_t cube_vertices[N_CUBE_VERTICES];/* = {
	{-1,-1,-1},
	{-1, 1,-1},
	{ 1, 1,-1},
	{ 1,-1,-1},
	{ 1, 1, 1},
	{ 1,-1, 1},
	{-1, 1, 1},
	{-1,-1, 1}

};*/

extern face_t cube_faces[N_CUBE_FACES]; /* = {
	// front 
	{1,2,3},
	{1,3,4},

	// right
	{4,3,5},
	{4,5,6},

	// back
	{6,5,7},
	{6,7,8},

	// left
	{8,7,2},
	{8,7,1},

	// top
	{2,7,5},
	{2,5,3},

	// bottom
	{6,8,1},
	{6,1,4}

};*/

/// <summary title="MESH_T">
/// Define a struct for dynamic size meshes, with array of vertices and faces
/// </summary>

typedef struct {
	vect3_t* vertices; // dynamic array of vertices
	face_t* faces;     // dynamic array of faces
	vect3_t rotation;  // rotation with x,y and z values
} mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data(void);

void load_obj_file_data(char* filename);

#endif 
