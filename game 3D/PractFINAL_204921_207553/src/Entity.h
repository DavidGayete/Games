#pragma once
#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "texture.h"
#include "input.h"
#include "PathFinding.h"
#include "bass.h"
void renderQuieto(Matrix44 m, Mesh* mesh, Texture* text);
void renderAnimated(Matrix44 m, Mesh* mesh, Texture* text, Skeleton* sk);
void play_sound(const char* audioname, bool loop);
void stop_sound(const char* audioname, bool loop);
class Sonido {
public:
	static std::map<std::string, HSAMPLE> audios_cargados;
	Sonido();
	static HSAMPLE Get(const char* filename, bool loop);
};

class Entity {
public:
	std::string name;
	Matrix44 model;
	Entity();
	void render(float time);
	void update();
};


class EntityMesh : public Entity {
public:
	Mesh* mesh;
	Texture* texture;
	Shader* shader;
	Vector4 color;
	EntityMesh();
	EntityMesh(char* texture_name, char* mesh_name);
	virtual void render(float time);
	void update();
};

class Tree : public EntityMesh {
public:

	Tree();
	Tree(char* texture_name, char* mesh_name);

	void render_forest(float time);
};
class Machete : public EntityMesh {
public:
	float angle;
	Machete();
	Machete(char* texture_name, char* mesh_name);
	//void render_zombie(float time);


};

class Floor : public EntityMesh {
public:
	Texture* noise;
	Floor();
	Floor(int size);
	void render_floor(float time);
};
class icono : public EntityMesh {
public:

	icono();
};


class Aguila : public EntityMesh {
public:
	float angle;
	Aguila();
	Aguila(char* texture_name, char* mesh_name);
	virtual void update(float speed);
	void render_aguila(float time);
	void render_aguila2(float time);
};






class GameMap {
public:
	enum object_types { TREES, ZOMBIES };
	GameMap() {

	};
	void create_map(char* filename);
	void load_map(char* filename, float half_size_x, float half_size_z);
	bool saving_game(char* filename);
	bool loading_game(char* filename);
	void read_highscore(char* filename);
	void update_highscore(char* filename);
};

class Wall : public EntityMesh {
public:
	Wall();
	Wall(int size);
	void render_walls(float time);
};
class House : public EntityMesh {
public:
	House();
	House(char* texture_name, char* mesh_name);
	void render_houses(float time);
};
class Chasis : public EntityMesh {
public:
	Chasis();
	Chasis(char* texture_name, char* mesh_name);
	
};
class Neumatic : public EntityMesh {
public:
	Neumatic();
	Neumatic(char* texture_name, char* mesh_name);
	
};
class Motor : public EntityMesh {
public:
	Motor();
	Motor(char* texture_name, char* mesh_name);
	
};

class Captain : public EntityMesh {
public:
	bool player_colision = false;
	enum captain_direction { FRONT, BACK };
	Vector3 front;
	Vector3 right;
	Vector3 target_pos;
	Vector3 position;
	Machete machete;
	float angle;
	Captain();
	Captain(char* texture_name, char* mesh_name);
	virtual void render(float time);
	virtual void update(float speed, Neumatic neumatic, Motor motor, Chasis chasis);
};
class Zombie : public EntityMesh {
public:
	float angle;
	Zombie();
	Zombie(char* texture_name, char* mesh_name);
	void render_zombie(float time);
	virtual void update(float speed, Captain* capt);
	bool atac = false;
};