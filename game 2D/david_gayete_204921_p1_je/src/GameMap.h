
#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include "framework.h"

enum eCellType : uint8 {
	EMPTY, START,
	WALL,
	DOOR,
	CHEST
};

enum eItemType : uint8 {
	NOTHING,
	SWORD,
	POTION
};
struct sCell {
	eCellType type;
	eItemType item;
};
struct sMapHeader {
	int w; //width of map
	int h; //height of map
	unsigned char bytes; //num bytes per cell
	unsigned char extra[7]; //filling bytes, not used
};
class GameMap {
public:
	int width;
	int height;
	sCell* data;

	GameMap(int w, int h);
	sCell& getCell(int x, int y);
	bool loadMap(const char* filename);
	bool posible_caminar(int posicion_x, int posicion_y);
	bool posible_caminar_casa(int posicion_x, int posicion_y);
	bool posible_caminar_laberinto(int posicion_x, int posicion_y);
	bool posible_caminar_castillo(int posicion_x, int posicion_y);
	bool impacto_dragon(int pos_dragon_x, int pos_dragon_y);
	bool impacto_dragon_muerte(int pos_dragon_x, int pos_dragon_y, int pos_jugador_x, int pos_jugador_y);
	
};











#endif