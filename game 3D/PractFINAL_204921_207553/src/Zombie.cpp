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

Zombie::Zombie() {

};
Zombie::Zombie(char* texture_name, char* mesh_name) {
	//__super::EntityMesh(texture_name, mesh_name);
	this->texture = Texture::Get(texture_name);
	// example of loading Mesh from Mesh Manager
	this->mesh = Mesh::Get(mesh_name);
	// example of shader loading using the shaders manager
	shader = Shader::Get("data/shaders/instanced.vs", "data/shaders/texture.fs");
}
void Zombie::render_zombie(float time) {
	zombies_in_frustum.clear();

	for (int i = 0; i < zombies_model.size(); i++) {
		//Vector3 sphere_center = zombies_model[i] * this->mesh->box.center;



		anim1 = Animation::Get("data/assets/zombie/animations_walking.skanim");
		bool quieto = false;
		for (int fr = 0; fr < 7; fr++) {
			if (abs(zombies_model[i].getTranslation().x - posiciones[fr][0]) < 7 && abs(zombies_model[i].getTranslation().z - posiciones[fr][1]) < 7) {
				quieto = true;
			}

		}
		if (zombies_vida[i] == 1) {
			anim1 = Animation::Get("data/assets/zombie/animations_walking.skanim");

		}
		else {
			anim1 = Animation::Get("data/assets/zombie/muerto/animations_zombie crawl.skanim");

		}




		if (quieto == false) {
			anim1->assignTime(time);
		}
		else {
			anim1->assignTime(0);
		}


		//anim1->skeleton.renderSkeleton(Camera::current, zombies_model[i]);




		//anim1->skeleton.renderSkeleton(Camera::current, model);

		if (zombies_vida[i] == 1) {
			renderAnimated(zombies_model[i], Mesh::Get("data/assets/zombie/character.mesh"), this->texture, &anim1->skeleton);

		}
		else {
			renderAnimated(zombies_model[i], Mesh::Get("data/assets/zombie/muerto/character.mesh"), this->texture, &anim1->skeleton);

		}





		//float sphere_radius = this->mesh->radius;
		//if (Camera::current->testSphereInFrustum(sphere_center, sphere_radius) == false)
			//continue;
		zombies_in_frustum.push_back(zombies_model[i]);
	}
	/*if (zombies_in_frustum.size() > 0) {
		shader->enable();
		//upload uniforms


		shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		shader->setUniform("u_viewprojection", Camera::current->viewprojection_matrix);
		shader->setUniform("u_texture", texture);
		this->mesh->renderInstanced(GL_TRIANGLES, &zombies_in_frustum[0], zombies_in_frustum.size());
		shader->disable();


	}*/




}
int frames = 0;
void Zombie::update(float speed, Captain* capt) {

	float final_speed = speed * Game::instance->zombie_speed;
	for (int fr = 0; fr < 7; fr++) {
		
		if (fr % 3 == 1) {
			continue;
		}
		if (frames % 300 == 0 && zombies_model.size() < 3000) {

			bool posible_spawn = false;
			for (int ind = 0; ind < map_franges[franja_real].size(); ind++) {
				int i = map_franges[franja_real][ind];

				if (zombies_model[i].getTranslation().x == posiciones[franja_real][0] && zombies_model[i].getTranslation().z == posiciones[franja_real][1]) {
					posible_spawn = true;

				}

			}
			if (posible_spawn == false && franja_real != 4 && franja_real != 1) {
				
				Matrix44 m;
				m.translate(posiciones[franja_real][0], 0, posiciones[franja_real][1]);
				m.scale(0.5, 0.5, 0.5);
				Vector3 character_center = m.getTranslation() + Vector3(0, 1, 0);
				Vector3 coll;
				Vector3 collnorm;
				bool cuarto_choque = false;
				for (int ind1 = 0; ind1 < map_franges[franja_real].size(); ind1++) {
					int ii = map_franges[franja_real][ind1];

					if ((this->mesh->testSphereCollision(zombies_model[ii], character_center, 1, coll, collnorm)) == true) {
						cuarto_choque = true;
						break;
					}

				}
				if (cuarto_choque == false) {
					zombies_vida.push_back(1);
					zombies_model.push_back(m);
					map_franges[franja_real].push_back(zombies_count);
					zombie_angles.push_back(90 * DEG2RAD);
					zombies_count = zombies_count + 1;
					
				}


			}

		}

		Vector2 A;
		Vector3 target_direction;


		if (fr == franja_real) {
			A = Vector2(capt->model.getTranslation().x, capt->model.getTranslation().z);


		}
		else {
			A = Vector2(posiciones[fr][0], posiciones[fr][1]);

		}
		for (int ind = 0; ind < map_franges[fr].size(); ind++) {
			int i = map_franges[fr][ind];
			int point_index = 0;
			Vector2 B = Vector2((zombies_model[i] * Vector4(0, 0, 0, 1)).x, (zombies_model[i] * Vector4(0, 0, 0, 1)).z);
			if (simple_pathfinding(int(512 - A.x), int(512 - A.y), int(512 - B.x), int(512 - B.y), colors[fr % 3]) == true) {
				if (fr == franja_real) {
					target_direction = (capt->model.getTranslation() - (zombies_model[i] * Vector4(0, 0, 0, 1)).xyz);
				}
				else {
					Vector3 pos_base = Vector3(posiciones[fr][0], (zombies_model[i] * Vector4(0, 0, 0, 1)).y, posiciones[fr][1]);
					target_direction = (pos_base - (zombies_model[i] * Vector4(0, 0, 0, 1)).xyz);





					if (map_franges[fr].size() > 1 && abs(zombies_model[i].getTranslation().x - posiciones[fr][0]) < 7 && abs(zombies_model[i].getTranslation().z - posiciones[fr][1]) < 7) {
						
						zombies_model.erase(zombies_model.begin() + i);

						for (int z = 0; z < 7; z++) {
							for (int ind1 = 0; ind1 < map_franges[z].size(); ind1++) {
								if (map_franges[z][ind1] > i) {
									map_franges[z][ind1]--;
								}
							}
						}
						map_franges[fr].erase(map_franges[fr].begin() + ind);
						zombie_angles.erase(zombie_angles.begin() + i);
						zombies_count = zombies_count - 1;
						continue;

					}
				}
				float target_angle = atan2(target_direction.z, target_direction.x) + (rand() * 2 - 1) * 0.00000003;
				float final_angle = (target_angle - zombie_angles[i]);
				zombies_model[i].rotate(final_angle, Vector3(0, 1, 0));
				zombie_angles[i] = target_angle;
				float dist = sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
				Vector3 character_center = zombies_model[i].getTranslation() + Vector3(0, 1, 0);

				Vector3 coll;
				Vector3 collnorm;
				bool tercer_choque = false;
				for (int ind1 = 0; ind1 < map_franges[franja_real].size(); ind1++) {
					int ii = map_franges[franja_real][ind1];
					if (i != ii) {
						if (abs(zombies_model[i].getTranslation().x - capt->model.getTranslation().x) < 3 && abs(zombies_model[i].getTranslation().z - capt->model.getTranslation().z) < 3) {
							if (Game::instance->inmune == false && Game::instance->primer_inmune == false) {
								Game::instance->primer_inmune = true;
								Game::instance->inmune = true;
								play_sound("data/audios/Bite.wav", false);
								Game::instance->player_vidas--;
							}
							tercer_choque = true;
							break;
						}
						if ((this->mesh->testSphereCollision(zombies_model[ii], character_center, 1, coll, collnorm)) == true) {
							tercer_choque = true;
							break;
						}



					}
				}

				if (dist > 3 && tercer_choque == false) {

					zombies_model[i].translate(0, 0, final_speed);



				}

				if (compare_colors(floor_image.getPixel(int(512 - (zombies_model[i] * Vector4(0, 0, 0, 1)).x), int(512 - (zombies_model[i] * Vector4(0, 0, 0, 1)).z)).toVector4().xyz, colors[fr % 3]) == false) {
					bool primer_choque = false;

					for (int ind1 = 0; ind1 < map_franges[franja_real].size(); ind1++) {
						int ii = map_franges[franja_real][ind1];
						if (i != ii) {
							if (abs(zombies_model[i].getTranslation().x - capt->model.getTranslation().x) < 3 && abs(zombies_model[i].getTranslation().z - capt->model.getTranslation().z) < 3) {
								if (Game::instance->inmune == false && Game::instance->primer_inmune == false) {
									Game::instance->primer_inmune = true;
									Game::instance->inmune = true;
									Game::instance->player_vidas--;
								}
								primer_choque = true;
								break;
							}
							if ((this->mesh->testSphereCollision(zombies_model[ii], character_center, 1, coll, collnorm)) == true) {
								primer_choque = true;
								break;
							}

						}


					}
					if (primer_choque == false) {
						zombies_model[i].translate(0, 0, -2 * final_speed);

					}

					if (compare_colors(floor_image.getPixel(int(512 - (zombies_model[i] * Vector4(0, 0, 0, 1)).x), int(512 - (zombies_model[i] * Vector4(0, 0, 0, 1)).z)).toVector4().xyz, colors[franja]) == false) {
						bool segundo_choque = false;
						for (int ind1 = 0; ind1 < map_franges[franja_real].size(); ind1++) {
							int ii = map_franges[franja_real][ind1];
							if (i != ii) {
								if (abs(zombies_model[i].getTranslation().x - capt->model.getTranslation().x) < 3 && abs(zombies_model[i].getTranslation().z - capt->model.getTranslation().z) < 3) {
									if (Game::instance->inmune == false && Game::instance->primer_inmune == false) {
										Game::instance->primer_inmune = true;
										Game::instance->inmune = true;
										Game::instance->player_vidas--;
									}
									segundo_choque = true;
									break;
								}
								if ((this->mesh->testSphereCollision(zombies_model[ii], character_center, 1, coll, collnorm)) == true) {
									segundo_choque = true;
									break;
								}

							}


							if (segundo_choque == false) {
								zombies_model[i].translate(0, 0, final_speed);


							}




						}
					}
				}
			}
			else if (help_points[fr].size() > 0) {
				int exit = 0;
				while (exit == 0 && help_points[fr].size() > point_index) {
					Vector2 z = help_points[fr][point_index];
					if (simple_pathfinding(int(512 - A.x), int(512 - A.y), int(512 - z.x), int(512 - z.y), colors[fr % 3]) == true && simple_pathfinding(int(512 - z.x), int(512 - z.y), int(512 - B.x), int(512 - B.y), colors[fr % 3]) == true) {
						exit = 1;
						Vector3 pos_base = Vector3(z.x, (zombies_model[i] * Vector4(0, 0, 0, 1)).y, z.y);
						target_direction = (pos_base - (zombies_model[i] * Vector4(0, 0, 0, 1)).xyz);
						float target_angle = atan2(target_direction.z, target_direction.x) + (rand() * 2 - 1) * 0.00000003;
						float final_angle = (target_angle - zombie_angles[i]);
						zombies_model[i].rotate(final_angle, Vector3(0, 1, 0));
						zombie_angles[i] = target_angle;
						float dist = sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
						//final_speed = final_speed * velocity_tanh(dist);
						Vector3 character_center = zombies_model[i].getTranslation() + Vector3(0, 1, 0);

						Vector3 coll;
						Vector3 collnorm;
						bool tercer_choque = false;
						for (int ind1 = 0; ind1 < map_franges[franja_real].size(); ind1++) {
							int ii = map_franges[franja_real][ind1];
							if (i != ii) {
								if (abs(zombies_model[i].getTranslation().x - capt->model.getTranslation().x) < 3 && abs(zombies_model[i].getTranslation().z - capt->model.getTranslation().z) < 3) {
									if (Game::instance->inmune == false && Game::instance->primer_inmune == false) {
										Game::instance->primer_inmune = true;
										Game::instance->inmune = true;
										play_sound("data/audios/Bite.wav", false);
										Game::instance->player_vidas--;
									}
									tercer_choque = true;
									break;
								}
								if ((this->mesh->testSphereCollision(zombies_model[ii], character_center, 1, coll, collnorm)) == true) {
									tercer_choque = true;
									break;
								}



							}
						}

						if (dist > 3 && tercer_choque == false) {

							zombies_model[i].translate(0, 0, final_speed*10);



						}

						
					}
					else {
						point_index = point_index + 1;
					}

				}

			}

		}

	}
	frames = frames + 1;
}