#include "GameMap.h"



GameMap::GameMap(int w, int h)
{
	width = w;
	height = h;
	data = new sCell[w * h];
}

sCell& GameMap::getCell(int x, int y)
{
	return data[x + y * width];
}
bool GameMap::loadMap(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) //file not found
		return false;

	sMapHeader header; //read header and store it in the struct
	fread(&header, sizeof(sMapHeader), 1, file);

	assert(header.bytes == 1); //always control bad cases!!

	//allocate memory for the cells data and read it
	unsigned char* cells = new unsigned char[header.w * header.h];
	fread(cells, header.bytes, header.w * header.h, file);
	fclose(file); //always close open files
	width = header.w;
	height = header.h;
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			getCell(x, y).type = (eCellType)cells[x + y * width];

	delete[] cells; //always free any memory allocated!

	return true;
}
bool GameMap::posible_caminar(int posicion_x, int posicion_y) {
	sCell& cell = getCell(floor(posicion_x / 16), floor(posicion_y / 16));
	



	if ((getCell(floor(posicion_x / 16), floor(posicion_y / 16)).type == 1 || getCell(floor(posicion_x / 16), floor(posicion_y / 16)).type == 22)
		&& (getCell(floor((posicion_x + 14) / 16), floor((posicion_y) / 16)).type == 1 || getCell(floor((posicion_x + 14) / 16), floor((posicion_y) / 16)).type == 22)
		&& (getCell(floor(posicion_x / 16), floor((posicion_y + 18) / 16)).type == 1 || getCell(floor(posicion_x / 16), floor((posicion_y + 18) / 16)).type == 22)
		&& (getCell(floor((posicion_x + 14) / 16), floor((posicion_y + 18) / 16)).type == 1 || getCell(floor((posicion_x + 14) / 16), floor((posicion_y + 18) / 16)).type == 22)) {
		return true;
	}
	else {
		return false;
	}

}
bool GameMap::posible_caminar_casa(int posicion_x, int posicion_y) {
	sCell& cell = getCell(floor(posicion_x / 16), floor(posicion_y / 16));




	if ((getCell(floor(posicion_x / 16), floor(posicion_y / 16)).type == 28 )
		&& (getCell(floor((posicion_x + 14) / 16), floor((posicion_y) / 16)).type == 28 )
		&& (getCell(floor(posicion_x / 16), floor((posicion_y + 18) / 16)).type == 28 )
		&& (getCell(floor((posicion_x + 14) / 16), floor((posicion_y + 18) / 16)).type == 28)) {
		return true;
	}
	else {
		return false;
	}



}

bool GameMap::posible_caminar_laberinto(int posicion_x, int posicion_y) {
	sCell& cell = getCell(floor(posicion_x / 16), floor(posicion_y / 16));




	if ((getCell(floor(posicion_x / 16), floor(posicion_y / 16)).type == 0)
		&& (getCell(floor((posicion_x + 14) / 16), floor((posicion_y) / 16)).type == 0)
		&& (getCell(floor(posicion_x / 16), floor((posicion_y + 18) / 16)).type == 0)
		&& (getCell(floor((posicion_x + 14) / 16), floor((posicion_y + 18) / 16)).type == 0)) {
		return true;
	}
	else {
		return false;
	}

}
bool GameMap::posible_caminar_castillo(int posicion_x, int posicion_y) {
	sCell& cell = getCell(floor(posicion_x / 16), floor(posicion_y / 16));




	if ((getCell(floor(posicion_x / 16), floor(posicion_y / 16)).type ==11)
		&& (getCell(floor((posicion_x + 14) / 16), floor((posicion_y) / 16)).type == 11)
		&& (getCell(floor(posicion_x / 16), floor((posicion_y + 18) / 16)).type == 11)
		&& (getCell(floor((posicion_x + 14) / 16), floor((posicion_y + 18) / 16)).type == 11)) {
		return true;
	}
	else {
		return false;
	}



}



bool GameMap::impacto_dragon(int pos_dragon_x, int pos_dragon_y) {
	//sCell& cell = getCell(floor(posicion_x / 16), floor(posicion_y / 16));


	for (int i = pos_dragon_x; i < pos_dragon_x+45 ; i++) {
		for (int j = pos_dragon_y; j < pos_dragon_y + 38; j++) {

			if (getCell(floor(i / 16), floor(j / 16)).type == 40) {
				return true;
			}
		}


	}

	return false;

}

bool GameMap::impacto_dragon_muerte(int pos_dragon_x, int pos_dragon_y, int pos_jugador_x, int pos_jugador_y) {
	//sCell& cell = getCell(floor(posicion_x / 16), floor(posicion_y / 16));


	for (int i = pos_dragon_x; i < pos_dragon_x + 45; i++) {
		for (int j = pos_dragon_y; j < pos_dragon_y + 38; j++) {
			
			if (i == pos_jugador_x && j == pos_jugador_y) {
				return true;
			}
			else if (i == pos_jugador_x && j == pos_jugador_y+18) {
				return true;
			}
			else if (i == pos_jugador_x + 14 && j == pos_jugador_y ) {
				return true;
			}
			else if (i == pos_jugador_x+14 && j == pos_jugador_y + 18) {
				return true;
			}
			
		}


	}

	return false;

}