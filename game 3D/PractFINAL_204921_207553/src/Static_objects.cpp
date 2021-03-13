#include "Entity.h"
#include "animation.h"

extern bool ataque;
extern std::vector<Matrix44> zombies_model;
extern std::vector<Matrix44> houses_model;
extern std::vector<int> zombies_vida;
extern std::vector<Matrix44> trees_model;
extern std::vector<Matrix44> zombies_in_frustum;
extern std::vector<Matrix44> trees_in_frustum;
extern std::vector<float> zombie_angles;
extern std::vector<int> map_franges[7];
extern std::vector<Vector2> help_points[7];
extern std::vector<Matrix44> wall_model;
extern std::vector<Matrix44> object_model;
extern Image floor_image;
extern float time_aux;
extern enum Map_colors;
extern Vector3 colors[3];
extern int franja;
extern int franja_real;
extern int zombies_count;
extern int primera_vez;
extern int matriu[3][3];
extern int posiciones[7][2];
extern Vector3 current_color;
extern Animation* anim1;
extern Shader* animacion;

Tree::Tree() {

}
Tree::Tree(char* texture_name, char* mesh_name) {
	//__super::EntityMesh(texture_name, mesh_name);
	this->texture = Texture::Get(texture_name);
	this->mesh = Mesh::Get(mesh_name);
	shader = Shader::Get("data/shaders/instanced.vs", "data/shaders/phong.fs");
}
void Tree::render_forest(float time) {
	trees_in_frustum.clear();
	for (int i = 0; i < trees_model.size(); i++) {
		Vector3 sphere_center = trees_model[i] * this->mesh->box.center;
		float sphere_radius = this->mesh->radius;
		if (Camera::current->testSphereInFrustum(sphere_center, sphere_radius) == false)
			continue;
		trees_in_frustum.push_back(trees_model[i]);
	}
	if (trees_in_frustum.size() > 0) {
		shader->enable();
		//upload uniforms
		shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		shader->setUniform("u_viewprojection", Camera::current->viewprojection_matrix);
		shader->setUniform("u_texture", texture);
		shader->setUniform("u_camera_pos", Camera::current->eye);
		shader->setUniform("u_model", this->model);
		shader->setUniform("u_time", time);
		this->mesh->renderInstanced(GL_TRIANGLES, &trees_in_frustum[0], trees_in_frustum.size());
		shader->disable();
	}
}

Floor::Floor() {

}
Floor::Floor(int size) {
	//this->texture = Texture::Get("data/flip_image.png");
	this->texture = Texture::Get("data/map2_flip.png");
	noise = Texture::Get("data/noisy_image.png");
	//floor_image.fromTexture(this->texture);
	//printf("%d %d", floor_image.width, floor_image.height);
	//floor_image.Image::loadPNG("data/mapa_1_zombies.png",false);
	floor_image.Image::loadPNG("data/map2.png", false);
	this->mesh = new Mesh();
	this->mesh->createPlane(size);
	this->texture->bind();
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture_floor.fs");
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
}

void Floor::render_floor(float time) {
	if (shader)
	{
		//enable shader
		shader->enable();
		//upload uniforms
		shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		shader->setUniform("u_viewprojection", Camera::current->viewprojection_matrix);
		shader->setUniform("u_texture", texture);
		shader->setUniform("u_noise_texture", noise);
		shader->setUniform("u_model", this->model);
		shader->setUniform("u_camera_pos", Camera::current->eye);
		shader->setUniform("u_time", time);
		//do the draw call
		mesh->render(GL_TRIANGLES);
		//disable shader
		shader->disable();
	}
}

Wall::Wall() {

}

Wall::Wall(int size) {
	this->texture = Texture::Get("data/wall.png");
	this->mesh = new Mesh();
	this->mesh->createQuad(0, 6.25f, 1024, 12.5f, false);
	this->texture->bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	Matrix44 m;
	m.rotate(90 * DEG2RAD, Vector3(0, 1, 0));
	m.setTranslation(0, 0, 512);
	wall_model.push_back(m);
	Matrix44 m2;
	m2.rotate(90 * DEG2RAD, Vector3(0, 1, 0));
	m2.setTranslation(0, 0, -512);
	wall_model.push_back(m2);
	Matrix44 m3;
	m3.rotate(90 * DEG2RAD, Vector3(0, 1, 0));
	m3.setTranslation(-512, 0, 0);
	m3.rotate(90 * DEG2RAD, Vector3(0, 1, 0));
	wall_model.push_back(m3);
	Matrix44 m4;
	m4.rotate(90 * DEG2RAD, Vector3(0, 1, 0));
	m4.setTranslation(512, 0, 0);
	m4.rotate(90 * DEG2RAD, Vector3(0, 1, 0));
	wall_model.push_back(m4);
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/phong.fs");
}

void Wall::render_walls(float time) {
	if (wall_model.size() > 0) {
		shader->enable();
		//upload uniforms
		shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		shader->setUniform("u_viewprojection", Camera::current->viewprojection_matrix);
		shader->setUniform("u_texture", texture);
		shader->setUniform("u_time", time);
		for (int i = 0; i < wall_model.size(); i++) {
			shader->setUniform("u_model", wall_model[i]);
			this->mesh->render(GL_TRIANGLES);
		}
		shader->disable();
	}
}
House::House() {

}
House::House(char* texture_name, char* mesh_name) {
	//__super::EntityMesh(texture_name, mesh_name);
	this->texture = Texture::Get(texture_name);
	this->mesh = Mesh::Get(mesh_name);
	shader = Shader::Get("data/shaders/instanced.vs", "data/shaders/phong.fs");
}

void House::render_houses(float time) {
	if (houses_model.size() > 0) {
		shader->enable();
		//upload uniforms
		shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		shader->setUniform("u_viewprojection", Camera::current->viewprojection_matrix);
		shader->setUniform("u_texture", texture);
		this->mesh->renderInstanced(GL_TRIANGLES, &houses_model[0], houses_model.size());
		shader->disable();
	}
}

Chasis::Chasis() {

}
Chasis::Chasis(char* texture_name, char* mesh_name) {
	//__super::EntityMesh(texture_name, mesh_name);

	this->model.setIdentity();
	this->model.translate(-10, 0, -10);
	this->model.scale(0.7f, 0.7f, 0.7f);
	this->texture = Texture::Get(texture_name);
	this->mesh = Mesh::Get(mesh_name);
	object_model.push_back(this->model);
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/phong.fs");
}


Motor::Motor() {

}
Motor::Motor(char* texture_name, char* mesh_name) {
	this->model.setIdentity();
	this->model.translate(300, 0, 300);
	this->model.scale(0.1f, 0.1f, 0.1f);

	this->texture = Texture::Get(texture_name);
	this->mesh = Mesh::Get(mesh_name);
	object_model.push_back(this->model);
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/phong.fs");
}

Neumatic::Neumatic() {

}
Neumatic::Neumatic(char* texture_name, char* mesh_name) {
	//__super::EntityMesh(texture_name, mesh_name);
	this->model.setIdentity();
	this->model.translate(-300, 0, -300);
	//this->model.scale(0.7f, 0.7f, 0.7f);
	this->texture = Texture::Get(texture_name);
	this->mesh = Mesh::Get(mesh_name);
	object_model.push_back(this->model);
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/phong.fs");
}

icono::icono() {
	//this->texture = Texture::Get("data/flip_image.png");


}