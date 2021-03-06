#include <stdio.h>
#include <string.h>
#include "mesh.h"
#include "array.h"
// TODO: Create implementation for mesh.h functions

mesh_t mesh = {
	.vertices = NULL,
	.faces = NULL,
	.rotation = {0,0,0}
};

vect3_t cube_vertices[N_CUBE_VERTICES] = {
	{-1,-1,-1},
	{-1, 1,-1},
	{ 1, 1,-1},
	{ 1,-1,-1},
	{ 1, 1, 1},
	{ 1,-1, 1},
	{-1, 1, 1},
	{-1,-1, 1}

};

face_t cube_faces[N_CUBE_FACES] = {
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

};

// Loads the cubes values in the mesh data structure

void load_cube_mesh_data(void) {
	for (int i = 0; i < N_CUBE_VERTICES; i++) {
		vect3_t cube_vertex = cube_vertices[i];
		array_push(mesh.vertices, cube_vertex);
	}

	for (int i = 0; i < N_CUBE_FACES; i++) {
		face_t cube_face = cube_faces[i];
		array_push(mesh.faces, cube_face);
	}
}

void load_obj_file_data(char* filename) {
	// TODO: Read the contents of the .obj file
	// and load the vertices and faces in our mesh.vertices and mesh.faces
	printf("Opening the file . . .");
	FILE* file;
	file = fopen(filename, "r");

	char line[1024];

	while (fgets(line,1024, file)) {
		// vertex information
		if(strncmp(line,"v ",2) == 0){
			vect3_t vertex;
			sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			array_push(mesh.vertices, vertex);
		}
		// face information
		if(strncmp(line, "f ",2)==0){
			int vertex_indices[3];
			int texture_indices[3];
			int normal_indices[3];
			sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &vertex_indices[0],&texture_indices[0],&normal_indices[0],
														 &vertex_indices[1],&texture_indices[1],&normal_indices[1],
														 &vertex_indices[2],&texture_indices[2],&normal_indices[2] );
			
			face_t face = {
				.a = vertex_indices[0],
				.b = vertex_indices[1],
				.c = vertex_indices[2]
			};

			array_push(mesh.faces, face);
		}
		// printf("Line = %s", line);
	}


}
