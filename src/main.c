#include<stdio.h>
#include<stdbool.h>
#include<stdint.h>
#include<SDL2/SDL.h>
#include "array.h"
#include "display.h"
#include "vector.h"
#include "triangle.h"
#include "mesh.h"





/// </Declaring an array of vectors/points>
//const int N_POINTS = 9 * 9 * 9; // number of points

//#define N_POINTS (9*9*9)

//vect3_t cube_points[N_POINTS]; // 9 X 9 X 9 cube
//vect2_t projected_points[N_POINTS];

//triangle_t triangles_to_render[N_MESH_FACES];

triangle_t* triangles_to_render = NULL;

vect3_t camara_position = { .x = 0,.y = 0,.z = -5 };

// vect3_t cube_rotation = { .x = 0, .y = 0, .z = 0 };

float fov_factor = 640;


bool is_running = false;
int previous_frame_time = 0;




void setup(void) {
	// Allocate the required memory in bytes to hold the color buffer
	color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

	if (!color_buffer) {
		/*
		* there is a possibility that malloc fails to allocate that number of bytes in 
		* memory (maybe the machine does not have enough free memory). 
		* If that happens, malloc will return a NULL pointer.
		* 
		* If the return of the malloc is NULL pointer, the allocation was not successful.
		*/
	}
	else {
		/*Allocation was successful*/

	}

	// Creating a SDL texture that is used to display the color buffer
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height

	);

	//load_cube_mesh_data();

	load_obj_file_data("..\\assets\\efa.obj");

	//int point_count = 0;

	//// Start loading my array of vectors
	//// from -1 to 1 ( in this 9x9x9 cube )
	//for (float x = -1; x <= 1; x += 0.25) {
	//	for (float y = -1; y <= 1; y += 0.25) {
	//		for (float z = -1; z <= 1; z += 0.25) {
	//			vect3_t new_point = { .x = x, .y = y, .z = z };
	//			cube_points[point_count] = new_point;
	//			point_count += 1;
	//		}
	//	}
	//}
}

void process_input(void) {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		is_running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			is_running = false;
		}
		break;
	}
}

/// <summary>
/// Function that recieves a 3D vector and returns a 2D vector
/// </summary>
/// <param name="points"></param>

vect2_t project(vect3_t point) {
	vect2_t projected_point = {
		.x = (fov_factor*point.x)/point.z,
		.y = (fov_factor*point.y)/point.z
	};
	return projected_point;
}

void update(void) {

	// wait some time untill the reach the target frame time in milliseconds
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

	// Only delay execution if we are running too fast
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}

	// while (!SDL_TICKS_PASSED(SDL_GetTicks(), previous_frame_time + FRAME_TARGET_TIME));

	previous_frame_time = SDL_GetTicks();

	// Initialize the array of triangles to render.
	triangles_to_render = NULL;

	mesh.rotation.x += 0.001;
	mesh.rotation.y += 0.00;
	mesh.rotation.z += 0.00;

	// Loop all triangular faces of our mesh
	int num_faces = array_length(mesh.faces);
	for (int i = 0; i < num_faces; i++) {
		face_t mesh_face = mesh.faces[i];

		vect3_t face_vertices[3];
		face_vertices[0] = mesh.vertices[mesh_face.a - 1];
		face_vertices[1] = mesh.vertices[mesh_face.b - 1];
		face_vertices[2] = mesh.vertices[mesh_face.c - 1];

		triangle_t projected_triangle;

		// Loop all three vertices of this current face and apply transformations
		for (int j = 0; j < 3; j++) {
			vect3_t transformed_vertex = face_vertices[j];
			transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
			transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
			transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);

			// Move the points away from the camera
			transformed_vertex.z -= camara_position.z;

			// project the point
			vect2_t projected_point = project(transformed_vertex);

			// Scale and translate the projected points to the middle of the screen
			projected_point.x += (window_width / 2);
			projected_point.y += (window_height / 2);

			projected_triangle.points[j] = projected_point;
		}

		// Save the projected triangle in the array of triangles to render.
		//triangles_to_render[i] = projected_triangle;

		array_push(triangles_to_render, projected_triangle);
	}

	//for (int i = 0; i < N_MESH_FACES; i++) {
	//	face_t mesh_face = mesh_faces[i];

	//	vect3_t face_vertices[3];
	//	face_vertices[0] = mesh_vertices[mesh_face.a - 1];
	//	face_vertices[1] = mesh_vertices[mesh_face.b - 1];
	//	face_vertices[2] = mesh_vertices[mesh_face.c - 1];

	//	triangle_t projected_triangle;

	//	// Loop all three vertices of this current face and apply transformations
	//	for (int j = 0; j < 3; j++) {
	//		vect3_t transformed_vertex = face_vertices[j];
	//		transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
	//		transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
	//		transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);
	//		
	//		// Move the points away from the camera
	//		transformed_vertex.z -= camara_position.z;

	//		// project the point
	//		vect2_t projected_point = project(transformed_vertex);

	//		// Scale and translate the projected points to the middle of the screen
	//		projected_point.x += (window_width / 2);
	//		projected_point.y += (window_height / 2);

	//		projected_triangle.points[j] = projected_point;
	//	}

	//	// Save the projected triangle in the array of triangles to render.
	//	//triangles_to_render[i] = projected_triangle;

	//	array_push(triangles_to_render, projected_triangle);
	//}

	/*for (int i = 0; i < N_POINTS; i++) {
		vect3_t point = cube_points[i];

		vect3_t transformed_point = vec3_rotate_x(point, cube_rotation.x);
		transformed_point = vec3_rotate_y(transformed_point, cube_rotation.y);
		transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);

		// Move the points away from the camera
		transformed_point.z -= camara_position.z;

		// project the point
		vect2_t projected_point = project(transformed_point);

		// Save the projected 2D vector in the array of projected points
		projected_points[i] = projected_point;
	}*/

}


void render(void) {
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderClear(renderer);

	draw_grid();

	// Loop all projected triangles and render them
	int num_triangles = array_length(triangles_to_render);

	//draw_pixel(20, 50, 0xFFFFFF00);

	//draw_rect(300,200,300,150, 0xFFFF00FF);
	/*
	for (int i = 0; i < N_POINTS; i++) {
		vect2_t projected_point = projected_points[i];
		//draw_pixel(projected_points[i].x,projected_points[i].y, 0xFFFFFF00);
		draw_rect(
			projected_point.x + (window_width/2),
			projected_point.y + (window_height/2),
			4,
			4,
			0xFFFFFF00
		);
	}
	*/
	// Loop all projected points and render them
	for (int i = 0; i < num_triangles; i++) { // N_MESH_FACES changed to num_triangles
		triangle_t triangle = triangles_to_render[i];
		// Draw vertex points
		//draw_pixel(projected_points[i].x,projected_points[i].y, 0xFFFFFF00);
		draw_rect(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xFFFFFF00);
		draw_rect(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xFFFFFF00);
		draw_rect(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xFFFFFF00);

		/*draw_line(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y, 0xFF00FF00);
		draw_line(triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, 0xFF00FF00);
		draw_line(triangle.points[2].x, triangle.points[2].y, triangle.points[0].x, triangle.points[0].y, 0xFF00FF00);*/
		// Draw unfilled triangle
		draw_triangle(
			triangle.points[0].x,
			triangle.points[0].y,
			triangle.points[1].x,
			triangle.points[1].y,
			triangle.points[2].x,
			triangle.points[2].y,
			0xFF00FF00
		);
	}

	// clear the array of triangles to render every frame loop
	array_free(triangles_to_render);

	//draw_line(100, 200, 500, 50, 0xFF00FF00);


	render_color_buffer();

	clear_color_buffer(0xFF000000);

	SDL_RenderPresent(renderer);
}

/// <summary>
/// Free the memory that was dynamically allocated by the program 
/// </summary>
/// <param name=""></param>
void free_resources(void) {
	free(color_buffer);
	array_free(mesh.faces);
	array_free(mesh.vertices);
}


int main(int argc, char* args[]) {
	is_running = initialize_window();

	setup();

	//vect3_t myvector = { 2.0, 3.0, -4.0 };

	while (is_running) {
		process_input();
		update();
		render();
	}

	destroy_window();
	free_resources();

	SDL_Init(SDL_INIT_EVERYTHING);
	printf("Everything working fine !!");
	return 0;
}