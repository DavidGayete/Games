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

void renderAnimated(Matrix44 m, Mesh* mesh, Texture* text, Skeleton* sk) {
	Camera* camera = Camera::current;
	Vector3 position = m * mesh->box.center;

	BoundingBox global = transformBoundingBox(m, mesh->box);
	if (!camera->testBoxInFrustum(global.center, global.halfsize)) return;
	glPointSize(5);

	animacion = Shader::Get("data/shaders/skinning.vs", "data/shaders/texture.fs");

	animacion->enable();

	animacion->setUniform("u_color", Vector4(1, 1, 1, 1));
	animacion->setUniform("u_viewprojection", camera->viewprojection_matrix);

	if (text) {
		animacion->setUniform("u_texture", text);


	}

	animacion->setUniform("u_model", m);
	animacion->setUniform("u_texture_tiling", 1.0f);
	animacion->setUniform("u_time", Game::instance->time);
	animacion->setUniform("u_camera_pos", camera->eye);
	animacion->setUniform("u_camera_pos", camera->eye);
	//mesh->renderInstanced(GL_TRIANGLES, &zombies_in_frustum[0], zombies_in_frustum.size());
	//mesh->renderInstanced(GL_TRIANGLES, &zombies_in_frustum[0], zombies_in_frustum.size());
	//Shader::current = animacion;
	mesh->renderAnimated(GL_TRIANGLES, sk);



	animacion->disable();


}
void renderQuieto(Matrix44 m, Mesh* mesh, Texture* text) {
	Camera* camera = Camera::current;
	Vector3 position = m * mesh->box.center;

	BoundingBox global = transformBoundingBox(m, mesh->box);
	if (!camera->testBoxInFrustum(global.center, global.halfsize)) return;
	glPointSize(5);

	animacion = Shader::Get("data/shaders/skinning.vs", "data/shaders/texture.fs");

	animacion->enable();

	animacion->setUniform("u_color", Vector4(1, 1, 1, 1));
	animacion->setUniform("u_viewprojection", camera->viewprojection_matrix);

	if (text) {
		animacion->setUniform("u_texture", text);


	}

	animacion->setUniform("u_model", m);
	animacion->setUniform("u_texture_tiling", 1.0f);
	animacion->setUniform("u_time", Game::instance->time);
	animacion->setUniform("u_camera_pos", camera->eye);
	animacion->setUniform("u_camera_pos", camera->eye);
	//mesh->renderInstanced(GL_TRIANGLES, &zombies_in_frustum[0], zombies_in_frustum.size());
	//mesh->renderInstanced(GL_TRIANGLES, &zombies_in_frustum[0], zombies_in_frustum.size());
	//Shader::current = animacion;
	mesh->render(GL_TRIANGLES);
	animacion->disable();
}