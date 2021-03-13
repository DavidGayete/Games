#include "Entity.h"
#include "game.h"

extern bool tiempo_cumplido;
extern float tiempo_aguila;
extern bool primera;
extern Captain captain;
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
extern int levels_puntuacion[3][2];

void GameMap::create_map(char* filename) {
	FILE* f;
	f = fopen(filename, "w");
	for (int x = -512; x < 512; x += 16) {
		for (int z = -512; z < 512; z += 16) {
			if (rand() % 100 < 80)
				continue;
			if (x == 0 && z == 0)
				continue;
			float tree_angle = rand()*PI;
			//fprintf(f, "%d %d %f %d\n", x, z, tree_angle, this->TREES);

		}
	}
	float w = 0;
	for (int x = -10; x < -5; x++) {
		for (int z = -10; z < -5; z++) {
			fprintf(f, "%d %d %f %d\n", x, z, w, this->ZOMBIES);
		}
	}
	for (int x = -10; x < -5; x++) {
		for (int z = 5; z < 10; z++) {
			fprintf(f, "%d %d %f %d\n", x, z, w, this->ZOMBIES);
		}
	}
	for (int x = 5; x < 10; x++) {
		for (int z = -10; z < -5; z++) {
			fprintf(f, "%d %d %f %d\n", x, z, w, this->ZOMBIES);
		}
	}
	for (int x = 5; x < 10; x++) {
		for (int z = 5; z < 10; z++) {
			fprintf(f, "%d %d %f %d\n", x, z, w, this->ZOMBIES);
		}
	}
	fclose(f);
}

void GameMap::load_map(char* filename, float half_size_x, float half_size_z) {
	FILE* f;
	f = fopen(filename, "r");
	int x;
	int z;
	float angle;
	int type;
	while (fscanf(f, "%d %d %f %d", &x, &z, &angle, &type) > 0) {
		if (type == TREES) {
			Matrix44 m;
			m.setTranslation(x, 0, z);
			m.rotate(angle, Vector3(0, 1, 0));
			trees_model.push_back(m);
		}
		else if (type == ZOMBIES) {
			Matrix44 m;
			m.translate(x, 0, z);
			m.scale(0.5, 0.5, 0.5);
			zombies_vida.push_back(1);
			zombies_model.push_back(m);
			m.scale(0.6, 0.6, 0.6);
			houses_model.push_back(m);

			map_franges[int(angle)].push_back(zombies_count);
			posiciones[int(angle)][0] = x;
			posiciones[int(angle)][1] = z;
			zombies_count = zombies_count + 1;
		}
	}
	fclose(f);
	for (int i = 0; i < zombies_model.size(); i++) {
		zombie_angles.push_back(90 * DEG2RAD);
	}
	FILE* f2;
	f2 = fopen("data/h2.txt", "r");
	float fr1;
	while (fscanf(f2, "%d %d %f\n", &x, &z, &fr1) > 0) {
		//printf("%f", fr1);
		help_points[int(fr1)].push_back(Vector2(x, z));
	}
	fclose(f2);

}

bool GameMap::saving_game(char* filename) {
	FILE* f;
	f = fopen(filename, "w");
	if (f == NULL) {
		return false;
	}

	Game* a = Game::instance;
	Matrix44 q = captain.model;

	for (int i = 0; i < 7; i++) {
		if (i % 3 == 1) {
			continue;
		}
		
		fprintf(f, "%d\n", map_franges[i].size());
	}
	

	for (int i = 0; i < 7; i++) {
		if (i % 3 == 1) {
			continue;
		}
		if (map_franges[i].size() > 0) {
			for (int ind = 0; ind < map_franges[i].size(); ind++) {
				fprintf(f, "%d\n", map_franges[i][ind]);
			}
		}

	}
	
	fprintf(f, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", q.m[0], q.m[1], q.m[2], q.m[3], q.m[4], q.m[5], q.m[6], q.m[7], q.m[8], q.m[9], q.m[10], q.m[11], q.m[12], q.m[13], q.m[14], q.m[15]);
	fprintf(f, "%f %f %f %f %f %f %f %f %f %f %f %f %f\n", captain.front.x, captain.front.y, captain.front.z, captain.right.x, captain.right.y, captain.right.z, captain.target_pos.x, captain.target_pos.y, captain.target_pos.z, captain.position.x, captain.position.y, captain.position.z, captain.angle);
	fprintf(f, "%f %d %d %d %d %d %d %d %d %f %d\n", time_aux, franja, franja_real, zombies_count, primera_vez, current_color.x, current_color.y, current_color.z, tiempo_cumplido, tiempo_aguila, primera);
	fprintf(f, "%f %d %d %d %d %d %d %d %d %d %d %f %d %d\n", a->tiempo_aguila_game, a->modo_aguila_act, a->objeto_cercano, a->chasis_cogido, a->motor_cogido, a->neumatico_cogido, a->ataque_disponible, a->modo_aguila_disponible, a->player_vidas, a->inmune, a->primer_inmune, a->tiempo_inmune, a->puntuacion, a->tiempo_aux);
	for (int i = 0; i < zombies_model.size(); i++) {
		Vector3 zomb_pos = (zombies_model[i] * Vector4(0.0, 0.0, 0.0, 1.0)).xyz;
		fprintf(f, "%f %f %f %d\n", zomb_pos.x, zomb_pos.z, zombie_angles[i], zombies_vida[i]);
	}
	/*
	int aux1=0;
	int aux2=0;
	if(tiempo_cumplido == true) {
		aux1 = 1;
	}
	if (primera == true) {
		aux2 = 1;
	}
	*/

	fclose(f);
	return true;

}

bool GameMap::loading_game(char* filename) {
	FILE* f;
	f = fopen(filename, "r");
	if (f == NULL) {
		return false;
	}


	for (int i = 0; i < 7; i++) {
		map_franges[i].clear();
	}
	int counts[5];
	int c = -1;
	for (int i = 0; i < 7; i++) {

		if (i % 3 == 1) {
			continue;
		}
		c = c + 1;
		fscanf(f, "%d\n", &counts[c]);
	}
	
	c = -1;
	for (int i = 0; i < 7; i++) {
		if (i % 3 == 1) {
			continue;
		}
		c = c + 1;
		if (counts[c] > 0) {
			int var;
			for (int ind = 0; ind < counts[c]; ind++) {
				fscanf(f, "%d\n", &var);
				map_franges[i].push_back(var);
			}
		}
	}
	
	Game* a = Game::instance;
	Matrix44 q;
	fscanf(f, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", &q.m[0], &q.m[1], &q.m[2], &q.m[3], &q.m[4], &q.m[5], &q.m[6], &q.m[7], &q.m[8], &q.m[9], &q.m[10], &q.m[11], &q.m[12], &q.m[13], &q.m[14], &q.m[15]);
	
	for (int i = 0; i < 16; i++) {
		captain.model.m[i] = q.m[i];
	}
	fscanf(f, "%f %f %f %f %f %f %f %f %f %f %f %f %f\n", &captain.front.x, &captain.front.y, &captain.front.z, &captain.right.x, &captain.right.y, &captain.right.z, &captain.target_pos.x, &captain.target_pos.y, &captain.target_pos.z, &captain.position.x, &captain.position.y, &captain.position.z, &captain.angle);
	fscanf(f, "%f %d %d %d %d %d %d %d %d %f %d\n", &time_aux, &franja, &franja_real, &zombies_count, &primera_vez, &current_color.x, &current_color.y, &current_color.z, &tiempo_cumplido, &tiempo_aguila, &primera);
	fscanf(f, "%f %d %d %d %d %d %d %d %d %d %d %f %d %d\n", &a->tiempo_aguila_game, &a->modo_aguila_act, &a->objeto_cercano, &a->chasis_cogido, &a->motor_cogido, &a->neumatico_cogido, &a->ataque_disponible, &a->modo_aguila_disponible, &a->player_vidas, &a->inmune, &a->primer_inmune, &a->tiempo_inmune, &a->puntuacion, &a->tiempo_aux);
	

	Vector3 zomb_pos;
	float zomb_ang;
	int zomb_vida;
	zombies_model.clear();
	zombies_vida.clear();
	zombie_angles.clear();
	while (fscanf(f, "%f %f %f %d\n", &zomb_pos.x, &zomb_pos.z, &zomb_ang, &zomb_vida) > 0) {
		
		Matrix44 m;
		m.setTranslation(zomb_pos.x, 0, zomb_pos.z);
		m.scale(0.5, 0.5, 0.5);
		m.rotate(zomb_ang - 90 * DEG2RAD, Vector3(0, 1, 0));
		zombie_angles.push_back(zomb_ang);
		zombies_model.push_back(m);
		zombies_vida.push_back(zomb_vida);
	}
	/*
	int aux1=0;
	int aux2=0;
	if(tiempo_cumplido == true) {
		aux1 = 1;
	}
	if (primera == true) {
		aux2 = 1;
	}
	*/
	fclose(f);
	return true;


}
void GameMap::read_highscore(char* filename) {
	FILE* f;
	f = fopen(filename, "r");

	for (int i = 0; i < 3; i++) {
		fscanf(f, "%d %d\n", &levels_puntuacion[i][0], &levels_puntuacion[i][1]);
	}

	fclose(f);
}

void GameMap::update_highscore(char* filename) {
	FILE* f;
	f = fopen(filename, "w");
	for (int i = 0; i < 3; i++) {
		fprintf(f, "%d %d\n", levels_puntuacion[i][0], levels_puntuacion[i][1]);
		
	}
	fclose(f);
}
