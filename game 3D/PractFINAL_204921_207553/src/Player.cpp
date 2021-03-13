#include "Entity.h"
#include "game.h"
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
float moving = 0.0;
Machete::Machete() {

};
Machete::Machete(char* texture_name, char* mesh_name) {
	//__super::EntityMesh(texture_name, mesh_name);
	angle = 1;
	this->texture = Texture::Get(texture_name);
	// example of loading Mesh from Mesh Manager
	this->mesh = Mesh::Get(mesh_name);
	// example of shader loading using the shaders manager

	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
};

Captain::Captain() {

}


Captain::Captain(char* texture_name, char* mesh_name) {
	//__super::EntityMesh(texture_name, mesh_name);
	angle = 0;
	this->texture = Texture::Get(texture_name);
	// example of loading Mesh from Mesh Manager
	this->mesh = Mesh::Get(mesh_name);
	this->model.setIdentity();
	this->model.setScale(2.0f, 2.0f, 2.0f);
	this->position = Vector3(0, 0, 0);
	// example of shader loading using the shaders manager
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

}
void Captain::render(float time) {


	if (ataque == false) {
		anim1 = Animation::Get("data/assets/people/animations_great sword walk.skanim");
		if (time >= time_aux + anim1->duration) {
			Game::instance->ataque_disponible = true;
		}
		
		if (moving <= 0.05) {
			anim1->assignTime(0);
		}
		else {
			anim1->assignTime(time - time_aux);
		}
		

		//anim1->skeleton.renderSkeleton(Camera::current, model);


		renderAnimated(model, Mesh::Get("data/assets/people/character.mesh"), this->texture, &anim1->skeleton);
	}
	else {

		if (primera_vez == 0) {
			time_aux = time;
			
			primera_vez = 1;
		}
		if (time >= time_aux + 1.7) {
			ataque = false;
			primera_vez = 0;
		}
		else {
			anim1 = Animation::Get("data/assets/people/ataque/animations_standing melee attack horizontal.skanim");

			anim1->assignTime(time- time_aux);

			//anim1->skeleton.renderSkeleton(Camera::current, model);


			renderAnimated(model, Mesh::Get("data/assets/people/ataque/character.mesh"), this->texture, &anim1->skeleton);
		}

	}



	Matrix44 hand = anim1->skeleton.getBoneMatrix("mixamorig_RightHand", false);

	hand = hand * model;
	hand.rotate(90, Vector3(1, 1, 0));
	hand.scale(0.1, 0.1, 0.1);
	//this->machete.model.scale(0.2, 0.2, 0.2);

	renderQuieto(hand, this->machete.mesh, this->machete.texture);


}
void Captain::update(float speed, Neumatic neumatic, Motor motor, Chasis chasis) {
	
	target_pos = this->model.getTranslation();
	
	moving = false;

	Matrix44 m;
	m = this->model;
	speed = speed * 2;
	

	if (Input::isKeyPressed(SDL_SCANCODE_W)) {
		target_pos.z = target_pos.z - speed;
		m.translate(0, 0, speed);
		moving = true;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_S)) {
		target_pos.z = target_pos.z + speed;
		m.translate(0, 0, -speed);
		moving = true;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_A)) {
		target_pos.x = target_pos.x - speed;
		m.translate(speed, 0, 0);
		moving = true;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_D)) {
		target_pos.x = target_pos.x + speed;
		m.translate(-speed, 0, 0);
		moving = true;
	}
	int matados = 0;
	if (Input::wasKeyPressed(SDL_SCANCODE_F)) {

		if (Game::instance->ataque_disponible == true) {
			Game::instance->ataque_disponible = false;
			ataque = true;
			for (int ind = 0; ind < map_franges[franja_real].size(); ind++) {

				int i = map_franges[franja_real][ind];
				
				Vector3 character_center = this->model.getTranslation() + Vector3(0, 1, 0);
				Vector3 coll;
				Vector3 collnorm;

				Vector3 target_direction = (zombies_model[i].getTranslation() - (this->model.getTranslation()));
				float ang = dot(this->model.frontVector(), target_direction.normalize());

				if (abs(zombies_model[i].getTranslation().x - m.getTranslation().x) < 8 && abs(zombies_model[i].getTranslation().z - m.getTranslation().z) < 8 && ang > 0.5) {
					matados++;
					play_sound("data/audios/PlayerAttack.wav", false);
					if (zombies_vida[i] == 1) {
						zombies_vida[i] = 0;


					}
					else {
						zombies_vida.erase(zombies_vida.begin() + i);
						zombies_model.erase(zombies_model.begin() + i);

						for (int z = 0; z < 7; z++) {
							for (int ind1 = 0; ind1 < map_franges[z].size(); ind1++) {
								if (map_franges[z][ind1] > i) {
									map_franges[z][ind1]--;
								}
							}
						}
						map_franges[franja_real].erase(map_franges[franja_real].begin() + ind);
						zombie_angles.erase(zombie_angles.begin() + i);


						Game::instance->puntuacion = Game::instance->puntuacion + 3;
						zombies_count--;


					}



				}
				for (int aux1 = 0; aux1 < 1000000; aux1++) {

				}

			}
		}



	}






	if ((Input::mouse_state & SDL_BUTTON_LEFT)) //is left button pressed?
	{
		this->angle = this->angle + Input::mouse_delta.x * 0.005f;
		if (this->angle > 6.3) {
			this->angle = this->angle - 6.3;
		}
		else if (this->angle < -6.3) {
			this->angle = this->angle + 6.3;
		}
	
		m.rotate(Input::mouse_delta.x * 0.005f, Vector3(0.0f, -1.0f, 0.0f));

	}


	Vector3 character_center = m.getTranslation() + Vector3(0, 1, 0);
	Vector3 coll;
	Vector3 collnorm;
	bool colision = false;
	for (int i = 0; i < trees_in_frustum.size(); i++) {
		if ((this->mesh->testSphereCollision(trees_in_frustum[i], character_center, 1, coll, collnorm)) == true) {
			colision = true;
			break;
		}
	}


	Color c = floor_image.getPixel(512 - m.getTranslation().x, 512 - m.getTranslation().z);
	Vector3 c2 = c.toVector4().xyz;

	
	for (int i = 0; i < 3; i++) {
		if (i != franja && c2.x == colors[i].x && c2.y == colors[i].y && c2.z == colors[i].z) {
			current_color = c2;
			franja_real = franja_real + matriu[franja][i];
			franja = i;
			

		}
	}

	for (int ind = 0; ind < map_franges[franja_real].size(); ind++) {
		int i = map_franges[franja_real][ind];
		if ((this->mesh->testSphereCollision(zombies_model[i], character_center, 1, coll, collnorm)) == true) {
			if (Game::instance->inmune == false && Game::instance->primer_inmune == false) {
				Game::instance->primer_inmune = true;
				Game::instance->inmune = true;
				Game::instance->player_vidas--;
			}

			colision = true;
			break;
		}

	}

	
	for (int i = 0; i < houses_model.size(); i++) {
		if ((this->mesh->testSphereCollision(houses_model[i], character_center, 34, coll, collnorm)) == true) {
			colision = true;
			break;
		}
	}

	if ((this->mesh->testSphereCollision(chasis.model, character_center, 10, coll, collnorm)) == true) {
		colision = true;

	}
	if (!Game::instance->neumatico_cogido) {
		if ((this->mesh->testSphereCollision(neumatic.model, character_center, 1, coll, collnorm)) == true) {
			colision = true;

		}
	}

	

	if (!Game::instance->motor_cogido) {
		if (abs(motor.model.getTranslation().x - m.getTranslation().x) < 5 && abs(motor.model.getTranslation().z - m.getTranslation().z) < 5) {
			colision = true;

		}
	}
	if (colision == false) {

		if (m.getTranslation().x<510 && m.getTranslation().x > -510 && m.getTranslation().z<510 && m.getTranslation().z > -510) {
			this->model = m;
		}

	}

}
