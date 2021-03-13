#include "Entity.h"
#include "animation.h"
#include "game.h"
bool ataque = false;
std::vector<Matrix44> zombies_model;
std::vector<Matrix44> houses_model;
std::vector<int> zombies_vida;
std::vector<Matrix44> trees_model;
std::vector<Matrix44> zombies_in_frustum;
std::vector<Matrix44> trees_in_frustum;
std::vector<float> zombie_angles;
std::vector<int> map_franges[7];
std::vector<Vector2> help_points[7];
std::vector<Matrix44> wall_model;
std::vector<Matrix44> object_model;

Image floor_image;
float time_aux =0;
enum Map_colors { YELLOW, GREEN, PURPLE };
Vector3 colors[3] = { Vector3(239,228,176),Vector3(128,255,128),Vector3(200,191,231) };
int franja = GREEN;
int franja_real = 4;
int zombies_count = 0;
int primera_vez = 0;
int matriu[3][3] = {
	0,1,-1,
	-1,0,1,
	1,-1,0
};
int posiciones[7][2];
Vector3 current_color = colors[GREEN];
Animation* anim1;
Shader* animacion;

Entity::Entity() {};
EntityMesh::EntityMesh() {};
EntityMesh::EntityMesh(char* texture_name, char* mesh_name) {
	//__super::Entity();
	this->texture = Texture::Get(texture_name);
	// example of loading Mesh from Mesh Manager
	this->mesh = Mesh::Get(mesh_name);
	// example of shader loading using the shaders manager
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/phong.fs");
}
void EntityMesh::render(float time) {
	int window_width = 800;
	int window_height = 600;

	Matrix44 m;

	
	if (shader)
	{
		//enable shader
		shader->enable();
		//upload uniforms
		shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		shader->setUniform("u_viewprojection", Camera::current->viewprojection_matrix);
		shader->setUniform("u_texture", texture);
		shader->setUniform("u_model", this->model);
		shader->setUniform("u_camera_pos", Camera::current->eye);
		shader->setUniform("u_time", time);
		//do the draw call
		mesh->render(GL_TRIANGLES);
		//disable shader
		shader->disable();
	}

}
void EntityMesh::update() {

}