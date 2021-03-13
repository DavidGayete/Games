#include "Entity.h"
#include "animation.h"
#include "game.h"
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

Aguila::Aguila() {

};
Aguila::Aguila(char* texture_name, char* mesh_name) {
	//__super::EntityMesh(texture_name, mesh_name);
	angle = 1;
	this->texture = Texture::Get(texture_name);
	// example of loading Mesh from Mesh Manager
	this->mesh = Mesh::Get(mesh_name);
	// example of shader loading using the shaders manager

	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/phong.fs");
};
void Aguila::update(float speed) {

	this->model.rotate(0.7f, Vector3(1.0f, 0.0f, 0.0f));
	if (Input::isKeyPressed(SDL_SCANCODE_W)) {
		this->model.translate(0, 0, speed * 3);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_S)) {
		this->model.translate(0, 0, -speed * 3);
	}
	/*if (Input::isKeyPressed(SDL_SCANCODE_A)) {
		this->model.rotate(-angle * DEG2RAD, Vector3(0, 1, 0));
	}
	if (Input::isKeyPressed(SDL_SCANCODE_D)) {
		this->model.rotate(angle*DEG2RAD, Vector3(0, 1, 0));
	}
	*/
	if (Input::isKeyPressed(SDL_SCANCODE_A)) {
		this->model.translate(speed * 3, 0, 0);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_D)) {
		this->model.translate(-speed * 3, 0, 0);
	}
	if ((Input::mouse_state & SDL_BUTTON_LEFT)) //is left button pressed?
	{
		this->model.rotate(Input::mouse_delta.x * 0.005f, Vector3(0.0f, -1.0f, 0.0f));

	}

	this->model.rotate(0.7f, Vector3(-1.0f, 0.0f, 0.0f));
};
void Aguila::render_aguila(float time) {
	Matrix44 m;

	//m.scale(0.1, 0.1, 0.1);
	this->model.translate(0, 7, -9);
	//this->model.scale(0.1, 0.1, 0.1);
	//this->model.rotate(0.8f, Vector3(-1.0f, 0.0f, 0.0f));


};
void Aguila::render_aguila2(float time) {
	Matrix44 m;



	anim1 = Animation::Get("data/assets/aguila/animations_eagle1.skanim");

	anim1->assignTime(time);

	//anim1->skeleton.renderSkeleton(Camera::current, model);


	renderAnimated(model, Mesh::Get("data/assets/aguila/character.mesh"), this->texture, &anim1->skeleton);





	/*if (shader)
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
	}*/

};