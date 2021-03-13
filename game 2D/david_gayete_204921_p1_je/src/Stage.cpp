

#include "Stage.h"
#include "game.h"
#include "input.h"



std::map<std::string, Stage*> Stage::s_stages;

Stage::Stage(const char* name) {
	s_stages[name] = this;
	if (current_stage == NULL) current_stage = this;
}
void Stage::changeStage(const char* name) {
	current_stage = s_stages[name];
}
void Stage::render(Image& fb, float time) {
};
void Stage::update(double seconds_elapsed) {
};
	





void IntroStage::render(Image& fb, float time) {
	fb.fill(Color(255, 255, 255));

	fb.drawImage(Game::instance->intro_final, 0, 0, 160, 120);
	
	fb.drawText("Save us from ", 40, 10, Game::instance->font);
	fb.drawText("the dragon", 40, 20, Game::instance->font);

	fb.drawText("New Game", 40, 50, Game::instance->font);
	fb.drawText("Tutorial", 40, 70, Game::instance->font);
	fb.drawText("Control Settings", 40, 90, Game::instance->font);

	if (caso == 0) {
		fb.drawLine(40, 60, 95, 60, Color::WHITE);
	}
	else if (caso == 1) {
		fb.drawLine(40, 80, 95, 80, Color::WHITE);
	}
	else if (caso == 2) {
		fb.drawLine(40, 100, 150, 100, Color::WHITE);
	}



};
void IntroStage::update(double seconds_elapsed) {
		if (Input::wasMousePressed(0)) {
			std::cout << "clic" << std::endl;
			changeStage("play");
		}

		if (Input::wasKeyPressed(SDL_SCANCODE_DOWN)) //if key down
		{
			if (caso < 2) {
				caso++;
			}
		}
		if (Input::wasKeyPressed(SDL_SCANCODE_UP)) //if key down
		{
			if (caso > 0) {
				caso--;
			}
		}
		if (Input::wasKeyPressed(SDL_SCANCODE_A) && caso == 0) //if key down
		{
			changeStage("play");
		}
		if (Input::wasKeyPressed(SDL_SCANCODE_A) && caso == 1) //if key down
		{
			changeStage("tutorial");
		}
		if (Input::wasKeyPressed(SDL_SCANCODE_A) && caso == 2) //if key down
		{
			changeStage("settings");
		}




	};

void TutorialStage::render(Image& fb, float time) {
	fb.fill(Color(0, 0, 0));
	//fb.drawImage(Game::instance->tutorial_final, 0, 0, 150, 99);
	fb.drawText("Deberas:",0, 0, Game::instance->font);
	fb.drawText("Buscar 4 objetos en cofres", 5, 20, Game::instance->minifont, 4, 6);
	fb.drawText("Buscar una llave para abrir el bunker", 5, 30, Game::instance->minifont, 4, 6);
	fb.drawText("Juntar 4 objetos para el arma especial", 5, 40, Game::instance->minifont, 4, 6);
	fb.drawText("Matar al dragon", 5, 50, Game::instance->minifont, 4, 6);
	fb.drawText("Moriras:", 0, 60, Game::instance->font);
	fb.drawText("Te toca el dragon", 5, 80, Game::instance->minifont, 4, 6);
	fb.drawText("Sales de una casa sin abrir el cofre", 5, 90, Game::instance->minifont, 4, 6);

	fb.drawText("Click A para volver al menu", 5, 110, Game::instance->minifont, 4, 6);


};
void TutorialStage::update(double seconds_elapsed) {
	
	if (Input::wasKeyPressed(SDL_SCANCODE_A) ) //if key down
	{
		changeStage("intro");
	}



};

void SettingsStage::render(Image& fb, float time) {
	fb.fill(Color(0, 0, 0));
	fb.drawImage(Game::instance->settings_final, 0, 0, 150, 99);
	fb.drawText("Cofre sin abrir", 14, 5, Game::instance->minifont, 4, 6);
	fb.drawText("Cofre abierto", 14, 25, Game::instance->minifont, 4, 6);
	fb.drawText("A:", 0, 40, Game::instance->font);
	fb.drawText("Abrir cofre mirandolo", 5, 50, Game::instance->minifont, 4, 6);
	fb.drawText("Juntar los 4 objetos en el bunker", 5, 60, Game::instance->minifont, 4, 6);
	fb.drawText("Ataque especial", 5, 70, Game::instance->minifont, 4, 6);
	fb.drawText("B:", 0, 80, Game::instance->font);
	fb.drawText("Abrir puertas mirandolas", 5, 90, Game::instance->minifont, 4, 6);

	fb.drawText("Click A para volver al menu", 5, 110, Game::instance->minifont, 4, 6);

};
void SettingsStage::update(double seconds_elapsed) {
	

	if (Input::wasKeyPressed(SDL_SCANCODE_A)) //if key down
	{
		changeStage("intro");
	}
	

};








void VictoriaStage::render(Image& fb, float time) {
	fb.fill(Color(0, 0, 0));
	
	fb.drawImage(Game::instance->victoria_final, 0, 0, 150, 99);
	for (int i = 2; i < 179; i++) {
		for (int j = 0; j < 19; j++) {
			fb.setPixelSafe(i, j, Color(0, 0, 0));
		}

	}
	fb.drawText("Eres un heroe!", 5, 0, Game::instance->minifont, 4, 6);
	fb.drawText("has podido salvar al pueblo!", 5, 7, Game::instance->minifont, 4, 6);
	fb.drawText("pulsa R para volver a jugar o", 5, 12, Game::instance->minifont, 4, 6);
	fb.drawText("ESC para cerrar la aplicacion", 5, 19, Game::instance->minifont, 4, 6);
};

void VictoriaStage::update(double seconds_elapsed) {
	if (Input::wasKeyPressed(SDL_SCANCODE_R)) //if key up
	{
		Player* p2 = new Player(0);
		Game::instance->player = p2;
		Game::instance->target_pos.x = 0;
		Game::instance->target_pos.y = 0;
		Game::instance->camera->camera_pos.x = 0;
		Game::instance->camera->camera_pos.y = 0;
		changeStage("intro");
	}



};




	


void DerrotaStage::render(Image& fb, float time) {
	fb.fill(Color(0, 0, 0));
	fb.drawImage(Game::instance->derrota_final, 0, 0, 159,119);
	for (int i = 2; i < 179; i++) {
		for (int j = 70; j < 110; j++) {
			fb.setPixelSafe(i, j, Color(0, 0, 0));
		}
		
	}
	fb.drawText("No has podido salvar a tu pueblo", 5, 70, Game::instance->minifont, 4, 6);
	fb.drawText("has muerto!", 5, 80, Game::instance->minifont, 4, 6);
	fb.drawText("pulsa R para reiniciar o ", 5, 90, Game::instance->minifont, 4, 6);
	fb.drawText("ESC para cerrar la aplicacion", 5, 100, Game::instance->minifont, 4, 6);
	//framebuffer.drawImage(dragon, 0, 0, Area((int(time) % 3) * 45, 2 * 38, 45, 38));

};
void DerrotaStage::update(double seconds_elapsed) {
	if (Input::wasKeyPressed(SDL_SCANCODE_R)) //if key up
	{
		Player* p2 = new Player(0);
		Game::instance->player = p2;
		Game::instance->target_pos.x = 0;
		Game::instance->target_pos.y = 0;
		Game::instance->camera->camera_pos.x = 0;
		Game::instance->camera->camera_pos.y = 0;
		changeStage("intro");
	}
};




void PlayStage::render(Image& fb, float time) {
	//size in pixels of a cell

//for every cell
	int cs = 16;
	
	if (Game::instance->player->player_pos.x >= 0 && Game::instance->player->player_pos.x < Game::instance->map->width * 16 && Game::instance->player->player_pos.y >= 0 && Game::instance->player->player_pos.y < Game::instance->map->height * 16) {


		if (Game::instance->player->player_pos.x > 80 && Game::instance->player->player_pos.x < Game::instance->map->width * 16 - 80) {

			Game::instance->player->mov_x = 80;
			Game::instance->camera->camera_pos.x = Game::instance->player->player_pos.x - 80;
		}
		else if (Game::instance->player->player_pos.x < 80) {
			Game::instance->player->mov_x = floor(Game::instance->player->player_pos.x);


		}
		else if (Game::instance->player->player_pos.x > Game::instance->map->width * 16 - 80) {
			Game::instance->player->mov_x = 80 + floor(Game::instance->player->player_pos.x) - ((Game::instance->map->width * 16) - 80);
			Game::instance->camera->camera_pos.x = Game::instance->map->width * 16 - 80 - 80;





		}


		if (Game::instance->player->player_pos.y > 60 && Game::instance->player->player_pos.y < Game::instance->map->height * 16 - 60) {
			Game::instance->player->mov_y = 60;
			Game::instance->camera->camera_pos.y = Game::instance->player->player_pos.y - 60;
		}
		else if (Game::instance->player->player_pos.y < 60) {
			Game::instance->player->mov_y = floor(Game::instance->player->player_pos.y);

		}
		else if (Game::instance->player->player_pos.y > Game::instance->map->height * 16 - 60) {
			Game::instance->player->mov_y = 60 + floor(Game::instance->player->player_pos.y) - ((Game::instance->map->height * 16) - 60);
			Game::instance->camera->camera_pos.y = (Game::instance->map->height * 16) - 60 - 60;
			
		}
		//comentado


	}


	for (int x = 0; x < Game::instance->map->width; ++x)
		for (int y = 0; y < Game::instance->map->height; ++y)
		{
			int x_aux;
			int y_aux;
			//get cell info
			bool pintamos = false;



			sCell& cell = Game::instance->map->getCell(x, y);
			if (cell.type == 0) //skip empty
				continue;
			//compute tile pos in tileset image
			int tilex = (cell.type % 16) * cs;
			int tiley = floor(cell.type / 16) * cs;
			Area area(tilex, tiley, cs, cs);
			//avoid rendering out of screen stuff

			//draw area of tileset inside framebuffer
			//std::cout << framebuffer.width << std::endl;

			//comentado
			fb.drawImage(Game::instance->tileset, x * cs - Game::instance->camera->camera_pos.x, y * cs - Game::instance->camera->camera_pos.y, area);


		}


	if (Game::instance->player->arma_especial == false) {
		if (Game::instance->player->en_mov == true) {
			fb.drawImage(Game::instance->sprite, Game::instance->player->mov_x, Game::instance->player->mov_y, Area((int(Game::instance->time) % 4) * 14, Game::instance->player->facing * 18, 14, 18));
		}
		else {
			fb.drawImage(Game::instance->sprite, Game::instance->player->mov_x, Game::instance->player->mov_y, Area(0, Game::instance->player->facing * 18, 14, 18));
		}
			
	}
	else {
		if (Game::instance->player->en_mov == true) {
			fb.drawImage(Game::instance->sprite2, Game::instance->player->mov_x, Game::instance->player->mov_y, Area((int(Game::instance->time) % 4) * 14, Game::instance->player->facing * 18, 14, 18));
		}
		else {
			fb.drawImage(Game::instance->sprite2, Game::instance->player->mov_x, Game::instance->player->mov_y, Area(0, Game::instance->player->facing * 18, 14, 18));
		}

	}
	Game::instance->player->en_mov = false;
	fb.drawText("num objetos:" + toString(Game::instance->player->num_objetos), 0, 0, Game::instance->minifont, 4, 6);
	if (Game::instance->player->llaves == true) {
		fb.drawText("llaves", 60, 0, Game::instance->minifont, 4, 6);
	}
	if (Game::instance->player->arma_especial == true) {
		fb.drawText("arma_especial", 90, 0, Game::instance->minifont, 4, 6);
	}


};
void PlayStage::update(double seconds_elapsed) {
	if (Input::wasKeyPressed(SDL_SCANCODE_R)) //if key up
	{
		Player* p2 = new Player(0);
		Game::instance->player = p2;
		Game::instance->target_pos.x = 0;
		Game::instance->target_pos.y = 0;
		Game::instance->camera->camera_pos.x = 0;
		Game::instance->camera->camera_pos.y = 0;
		changeStage("intro");
	}
	float player_speed = 30;
	//Read the keyboard state, to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	if (Input::isKeyPressed(SDL_SCANCODE_UP)) //if key up
	{
		Game::instance->player->en_mov = true;
		Game::instance->player->facing = FACE_UP;
		Game::instance->target_pos.y -= seconds_elapsed * player_speed;  // empieza en el 0,0 arriba izquierda
	}
	if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
	{
		Game::instance->player->en_mov = true;
		Game::instance->player->facing = FACE_DOWN;
		Game::instance->target_pos.y += seconds_elapsed * player_speed;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) //if key up
	{
		Game::instance->player->en_mov = true;
		Game::instance->player->facing = FACE_LEFT;
		Game::instance->target_pos.x -= seconds_elapsed * player_speed;  // empieza en el 0,0 arriba izquierda
	}
	if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) //if key down
	{
		Game::instance->player->en_mov = true;
		Game::instance->player->facing = FACE_RIGHT;
		Game::instance->target_pos.x += seconds_elapsed * player_speed;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_B) && Game::instance->player->facing == FACE_UP && Game::instance->map->getCell(floor((Game::instance->player->player_pos.x) / 16), floor((Game::instance->player->player_pos.y - 16) / 16)).type == 12 && Game::instance->player->arma_especial == true) //if key down
	{

		changeStage("castillo");
	}
	
	
	if (Input::isKeyPressed(SDL_SCANCODE_B) && Game::instance->player->facing == FACE_UP && floor((Game::instance->player->player_pos.x) / 16)== 8 && floor((Game::instance->player->player_pos.y) / 16) == 17) //if key down
	{
		if (Game::instance->player->casa1 == false) {
			std::cout << "entra" << std::endl;
			Game::instance->casas->loadMap("data/mymap2.map");
			Game::instance->player->casa1 = true;
		}
		else {
			Game::instance->casas->loadMap("data/mymap2_2.map");
		}
		
		changeStage("casa");
	}
	else if (Input::isKeyPressed(SDL_SCANCODE_B) && Game::instance->player->facing == FACE_UP && floor((Game::instance->player->player_pos.x) / 16) == 18 && floor((Game::instance->player->player_pos.y) / 16) == 17) {
		if (Game::instance->player->casa2 == false) {
			Game::instance->casas->loadMap("data/mapa_1_objeto.map");
			Game::instance->player->casa2 = true;
		}
		else {
			Game::instance->casas->loadMap("data/mapa_1_objeto_2.map");
		}
		changeStage("casa");
	}

	else if (Input::isKeyPressed(SDL_SCANCODE_B) && Game::instance->player->facing == FACE_UP && floor((Game::instance->player->player_pos.x) / 16) == 25 && floor((Game::instance->player->player_pos.y) / 16) == 17) {
		if (Game::instance->player->casa3 == false) {
			Game::instance->casas->loadMap("data/mapa_2_objetos.map");
			Game::instance->player->casa3 = true;
		}
		else {
			Game::instance->casas->loadMap("data/mapa_2_objetos_2.map");
		}
		
		changeStage("casa");
	}
	else if (Input::isKeyPressed(SDL_SCANCODE_B) && Game::instance->player->facing == FACE_UP && floor((Game::instance->player->player_pos.x) / 16) == 8 && floor((Game::instance->player->player_pos.y) / 16) == 24) {
		if (Game::instance->player->casa4 == false) {
			Game::instance->casas->loadMap("data/mapa_3_objetos.map");
			Game::instance->player->casa4 = true;
		}
		else {
			Game::instance->casas->loadMap("data/mapa_3_objetos_2.map");
		}
		changeStage("casa");
	}
	else if (Input::isKeyPressed(SDL_SCANCODE_B) && Game::instance->player->facing == FACE_UP && floor((Game::instance->player->player_pos.x) / 16) == 25 && floor((Game::instance->player->player_pos.y) / 16) == 30) {
		if (Game::instance->player->llaves == false) {
			Game::instance->casas->loadMap("data/mymap3.map");
		}
		else {
			Game::instance->casas->loadMap("data/mymap3_2.map");
		}
			
		changeStage("casa");
	}
	else if(Input::isKeyPressed(SDL_SCANCODE_B) && Game::instance->player->facing == FACE_UP && Game::instance->map->getCell(floor((Game::instance->player->player_pos.x) / 16), floor((Game::instance->player->player_pos.y - 16) / 16)).type == 7) {
		Game::instance->casas->loadMap("data/mymap3_2.map");
		changeStage("casa");

	}
	if (Input::isKeyPressed(SDL_SCANCODE_B) && Game::instance->player->facing == FACE_UP && Game::instance->map->getCell(floor((Game::instance->player->player_pos.x) / 16), floor((Game::instance->player->player_pos.y - 16) / 16)).type == 26 && Game::instance->player->llaves == true) //if key down
	{


		changeStage("laberinto");
	}
	bool posible = Game::instance->map->posible_caminar(floor(Game::instance->target_pos.x), floor(Game::instance->target_pos.y));
	if (posible == true) {
		Game::instance->player->player_pos += (Game::instance->target_pos - Game::instance->player->player_pos) * 0.1;

	}
	else {
		Game::instance->target_pos = Game::instance->player->player_pos;
	}

};




void CasaStage::render(Image& fb, float time) {
	int cs = 16; //size in pixels of a cell

//for every cell
	
	

	if (Game::instance->player->player_pos_casa.x >= 0 && Game::instance->player->player_pos_casa.x < Game::instance->casas->width * 16 && Game::instance->player->player_pos_casa.y >= 0 && Game::instance->player->player_pos_casa.y < Game::instance->casas->height * 16) {


		if (Game::instance->player->player_pos_casa.x > 80 && Game::instance->player->player_pos_casa.x < Game::instance->casas->width * 16 - 80) {

			Game::instance->player->mov_x_casa = 80;
			Game::instance->camera2->camera_pos.x = Game::instance->player->player_pos_casa.x - 80;
		}
		else if (Game::instance->player->player_pos_casa.x < 80) {
			Game::instance->player->mov_x_casa = floor(Game::instance->player->player_pos_casa.x);


		}
		else if (Game::instance->player->player_pos_casa.x > Game::instance->casas->width * 16 - 80) {
			Game::instance->player->mov_x_casa = 80 + floor(Game::instance->player->player_pos_casa.x) - ((Game::instance->casas->width * 16) - 80);
			Game::instance->camera2->camera_pos.x = Game::instance->casas->width * 16 - 80 - 80;

		}

		if (Game::instance->player->player_pos_casa.y > 60 && Game::instance->player->player_pos_casa.y < Game::instance->casas->height * 16 - 60) {
			Game::instance->player->mov_y_casa = 60;
			Game::instance->camera2->camera_pos.y = Game::instance->player->player_pos_casa.y - 60;
		}
		else if (Game::instance->player->player_pos_casa.y < 60) {
			Game::instance->player->mov_y_casa = floor(Game::instance->player->player_pos_casa.y);

		}
		else if (Game::instance->player->player_pos_casa.y > Game::instance->casas->height * 16 - 60) {
			Game::instance->player->mov_y_casa = 60 + floor(Game::instance->player->player_pos_casa.y) - ((Game::instance->casas->height * 16) - 60);
			Game::instance->camera2->camera_pos.y = (Game::instance->casas->height * 16) - 60 - 60;
			//std::cout << "mov_x" << std::endl;
			//std::cout << mov_x << std::endl;
		}
		//comentado

	}
	
	

	for (int x = 0; x < Game::instance->casas->width; ++x)
		for (int y = 0; y < Game::instance->casas->height; ++y)
		{
			int x_aux;
			int y_aux;
			//get cell info
			bool pintamos = false;



			sCell& cell = Game::instance->casas->getCell(x, y);
			if (cell.type == 0) //skip empty
				continue;
			//compute tile pos in tileset image
			int tilex = (cell.type % 16) * cs;
			int tiley = floor(cell.type / 16) * cs;
			Area area(tilex, tiley, cs, cs);
			//avoid rendering out of screen stuff

			//draw area of tileset inside framebuffer
			//std::cout << framebuffer.width << std::endl;

			//comentado
			fb.drawImage(Game::instance->tileset, x * cs - Game::instance->camera2->camera_pos.x, y * cs - Game::instance->camera2->camera_pos.y, area);


		}
	if (Game::instance->player->arma_especial == false) {
		if (Game::instance->player->en_mov == true) {
			fb.drawImage(Game::instance->sprite, Game::instance->player->mov_x_casa, Game::instance->player->mov_y_casa, Area((int(Game::instance->time) % 4) * 14, Game::instance->player->facing * 18, 14, 18));
		}
		else {
			fb.drawImage(Game::instance->sprite, Game::instance->player->mov_x_casa, Game::instance->player->mov_y_casa, Area(0, Game::instance->player->facing * 18, 14, 18));
		}

	}
	else {
		if (Game::instance->player->en_mov == true) {
			fb.drawImage(Game::instance->sprite2, Game::instance->player->mov_x_casa, Game::instance->player->mov_y_casa, Area((int(Game::instance->time) % 4) * 14, Game::instance->player->facing * 18, 14, 18));	//draws only a part of an image
		}
		else {
			fb.drawImage(Game::instance->sprite2, Game::instance->player->mov_x_casa, Game::instance->player->mov_y_casa, Area(0, Game::instance->player->facing * 18, 14, 18));	//draws only a part of an image
		}

	}
	Game::instance->player->en_mov = false;

	fb.drawText("num objetos:" + toString(Game::instance->player->num_objetos), 0, 0, Game::instance->minifont, 4, 6);
	if (Game::instance->player->llaves == true) {
		fb.drawText("llaves", 60, 0, Game::instance->minifont, 4, 6);
	}
	if (Game::instance->player->arma_especial == true) {
		fb.drawText("arma_especial", 90, 0, Game::instance->minifont, 4, 6);
	}
	
};
	void CasaStage::update(double seconds_elapsed) {
		if (Input::wasKeyPressed(SDL_SCANCODE_R)) //if key up
		{
			Player* p2 = new Player(0);
			Game::instance->player = p2;
			Game::instance->target_pos.x = 0;
			Game::instance->target_pos.y = 0;
			Game::instance->camera->camera_pos.x = 0;
			Game::instance->camera->camera_pos.y = 0;
			changeStage("intro");
		}
		float player_speed = 30;
		//Read the keyboard state, to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
		if (Input::isKeyPressed(SDL_SCANCODE_UP)) //if key up
		{
			Game::instance->player->en_mov = true;
			Game::instance->player->facing = FACE_UP;
			Game::instance->target_pos_2.y -= seconds_elapsed * player_speed;  // empieza en el 0,0 arriba izquierda
		}
		if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
		{
			Game::instance->player->en_mov = true;
			Game::instance->player->facing = FACE_DOWN;
			Game::instance->target_pos_2.y += seconds_elapsed * player_speed;
		}
		if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) //if key up
		{
			Game::instance->player->en_mov = true;
			Game::instance->player->facing = FACE_LEFT;
			Game::instance->target_pos_2.x -= seconds_elapsed * player_speed;  // empieza en el 0,0 arriba izquierda
		}
		if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) //if key down
		{
			Game::instance->player->en_mov = true;
			Game::instance->player->facing = FACE_RIGHT;
			Game::instance->target_pos_2.x += seconds_elapsed * player_speed;
		}
		

		if (Input::isKeyPressed(SDL_SCANCODE_B) && Game::instance->player->facing == FACE_DOWN && Game::instance->casas->getCell(floor((Game::instance->player->player_pos_casa.x) / 16), floor((Game::instance->player->player_pos_casa.y + 16 + 18) / 16)).type == 34) //if key down
		{
			int aux = 0;
			//volvemos al mapa inicial, para volver a tener los cofres brillantes
			for (int i = 0; i < Game::instance->casas->width; i++) {
				for (int j = 0; j < Game::instance->casas->height; j++) {
					if (Game::instance->casas->getCell(i, j).type == 35) {
						aux = 1;
						

					}
				}
			}
			
			if (aux == 0) {
				changeStage("play");
			}
			else {
				changeStage("derrota");
			}
			
		}

		if (Input::isKeyPressed(SDL_SCANCODE_A) && Game::instance->player->facing == FACE_RIGHT && Game::instance->casas->getCell(floor((Game::instance->player->player_pos_casa.x + 14 + 16) / 16), floor((Game::instance->player->player_pos_casa.y) / 16)).type == 37) //if key down
		{
			Game::instance->player->llaves = true;


			Game::instance->casas->getCell(floor((Game::instance->player->player_pos_casa.x + 14 + 16) / 16), floor((Game::instance->player->player_pos_casa.y) / 16)).type = (eCellType)32;



		}


		if (Input::isKeyPressed(SDL_SCANCODE_A) && Game::instance->player->facing == FACE_LEFT && Game::instance->casas->getCell(floor((Game::instance->player->player_pos_casa.x - 16) / 16), floor((Game::instance->player->player_pos_casa.y) / 16)).type == 35) //if key down
		{
			Game::instance->player->num_objetos++;


			Game::instance->casas->getCell(floor((Game::instance->player->player_pos_casa.x - 16) / 16), floor((Game::instance->player->player_pos_casa.y) / 16)).type = (eCellType)36;
			if (Game::instance->casas->getCell(floor((Game::instance->player->player_pos_casa.x - 16) / 16), floor((Game::instance->player->player_pos_casa.y + 16) / 16)).type == 35) {
				Game::instance->casas->getCell(floor((Game::instance->player->player_pos_casa.x - 16) / 16), floor((Game::instance->player->player_pos_casa.y + 16) / 16)).type = (eCellType)36;
			}
			else if (Game::instance->casas->getCell(floor((Game::instance->player->player_pos_casa.x - 16) / 16), floor((Game::instance->player->player_pos_casa.y - 16) / 16)).type == 35) {
				Game::instance->casas->getCell(floor((Game::instance->player->player_pos_casa.x - 16) / 16), floor((Game::instance->player->player_pos_casa.y - 16) / 16)).type = (eCellType)36;
			}


		}
		bool posible = Game::instance->casas->posible_caminar_casa(floor(Game::instance->target_pos_2.x), floor(Game::instance->target_pos_2.y));
		if (posible == true) {
			Game::instance->player->player_pos_casa += (Game::instance->target_pos_2 - Game::instance->player->player_pos_casa) * 0.1;

		}
		else {
			Game::instance->target_pos_2 = Game::instance->player->player_pos_casa;
		}

	
};


	
void LaberintoStage::render(Image& fb, float time) {
		int cs = 16; //size in pixels of a cell

//for every cell


		if (Game::instance->player->player_pos_lab.x >= 0 && Game::instance->player->player_pos_lab.x < Game::instance->laberinto->width * 16 && Game::instance->player->player_pos_lab.y >= 0 && Game::instance->player->player_pos_lab.y < Game::instance->laberinto->height * 16) {


			if (Game::instance->player->player_pos_lab.x > 80 && Game::instance->player->player_pos_lab.x < Game::instance->laberinto->width * 16 - 80) {

				Game::instance->player->mov_x_casa = 80;
				Game::instance->camera2->camera_pos.x = Game::instance->player->player_pos_lab.x - 80;
			}
			else if (Game::instance->player->player_pos_lab.x < 80) {
				Game::instance->player->mov_x_casa = floor(Game::instance->player->player_pos_lab.x);


			}
			else if (Game::instance->player->player_pos_lab.x > Game::instance->laberinto->width * 16 - 80) {
				Game::instance->player->mov_x_casa = 80 + floor(Game::instance->player->player_pos_lab.x) - ((Game::instance->laberinto->width * 16) - 80);
				Game::instance->camera2->camera_pos.x = Game::instance->laberinto->width * 16 - 80 - 80;

			}

			if (Game::instance->player->player_pos_lab.y > 60 && Game::instance->player->player_pos_lab.y < Game::instance->laberinto->height * 16 - 60) {
				Game::instance->player->mov_y_casa = 60;
				Game::instance->camera2->camera_pos.y = Game::instance->player->player_pos_lab.y - 60;
			}
			else if (Game::instance->player->player_pos_lab.y < 60) {
				Game::instance->player->mov_y_casa = floor(Game::instance->player->player_pos_lab.y);

			}
			else if (Game::instance->player->player_pos_lab.y > Game::instance->laberinto->height * 16 - 60) {
				Game::instance->player->mov_y_casa = 60 + floor(Game::instance->player->player_pos_lab.y) - ((Game::instance->laberinto->height * 16) - 60);
				Game::instance->camera2->camera_pos.y = (Game::instance->laberinto->height * 16) - 60 - 60;
				//std::cout << "mov_x" << std::endl;
				//std::cout << mov_x << std::endl;
			}
			//comentado

		}


		for (int x = 0; x < Game::instance->laberinto->width; ++x)
			for (int y = 0; y < Game::instance->laberinto->height; ++y)
			{
				int x_aux;
				int y_aux;
				//get cell info
				bool pintamos = false;



				sCell& cell = Game::instance->laberinto->getCell(x, y);
				if (cell.type == 0) //skip empty
					continue;
				//compute tile pos in tileset image
				int tilex = (cell.type % 16) * cs;
				int tiley = floor(cell.type / 16) * cs;
				Area area(tilex, tiley, cs, cs);
				//avoid rendering out of screen stuff

				//draw area of tileset inside framebuffer
				//std::cout << framebuffer.width << std::endl;

				//comentado
				fb.drawImage(Game::instance->tileset, x * cs - Game::instance->camera2->camera_pos.x, y * cs - Game::instance->camera2->camera_pos.y, area);


			}

		if (Game::instance->player->arma_especial == false) {
			if (Game::instance->player->en_mov == true) {
				fb.drawImage(Game::instance->sprite, Game::instance->player->mov_x_casa, Game::instance->player->mov_y_casa, Area((int(Game::instance->time) % 4) * 14, Game::instance->player->facing * 18, 14, 18));
			}
			else {
				fb.drawImage(Game::instance->sprite, Game::instance->player->mov_x_casa, Game::instance->player->mov_y_casa, Area(0, Game::instance->player->facing * 18, 14, 18));
			}

		}
		else {
			if (Game::instance->player->en_mov == true) {
				fb.drawImage(Game::instance->sprite2, Game::instance->player->mov_x_casa, Game::instance->player->mov_y_casa, Area((int(Game::instance->time) % 4) * 14, Game::instance->player->facing * 18, 14, 18));	//draws only a part of an images only a part of an image
			}
			else {
				fb.drawImage(Game::instance->sprite2, Game::instance->player->mov_x_casa, Game::instance->player->mov_y_casa, Area(0, Game::instance->player->facing * 18, 14, 18));	//draws only a part of an image
			}

		}
		Game::instance->player->en_mov = false;
		fb.drawText("num objetos:" + toString(Game::instance->player->num_objetos), 0, 0, Game::instance->minifont, 4, 6);
		if (Game::instance->player->llaves == true) {
			fb.drawText("llaves", 60, 0, Game::instance->minifont, 4, 6);
		}
		if (Game::instance->player->arma_especial == true) {
			fb.drawText("arma_especial", 90, 0, Game::instance->minifont, 4, 6);
		}
		
	};

void LaberintoStage::update(double seconds_elapsed) {
	if (Input::wasKeyPressed(SDL_SCANCODE_R)) //if key up
	{
		Player* p2 = new Player(0);
		Game::instance->player = p2;
		Game::instance->target_pos.x = 0;
		Game::instance->target_pos.y = 0;
		Game::instance->camera->camera_pos.x = 0;
		Game::instance->camera->camera_pos.y = 0;
		changeStage("intro");
	}
		float player_speed = 30;
		//Read the keyboard state, to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
		if (Input::isKeyPressed(SDL_SCANCODE_UP)) //if key up
		{
			Game::instance->player->en_mov = true;
			Game::instance->player->facing = FACE_UP;
			Game::instance->target_pos_3.y -= seconds_elapsed * player_speed;  // empieza en el 0,0 arriba izquierda
		}
		if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
		{
			Game::instance->player->en_mov = true;
			Game::instance->player->facing = FACE_DOWN;
			Game::instance->target_pos_3.y += seconds_elapsed * player_speed;
		}
		if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) //if key up
		{
			Game::instance->player->en_mov = true;
			Game::instance->player->facing = FACE_LEFT;
			Game::instance->target_pos_3.x -= seconds_elapsed * player_speed;  // empieza en el 0,0 arriba izquierda
		}
		if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) //if key down
		{
			Game::instance->player->en_mov = true;
			Game::instance->player->facing = FACE_RIGHT;
			Game::instance->target_pos_3.x += seconds_elapsed * player_speed;
		}
		std::cout << Game::instance->laberinto->getCell(floor((Game::instance->player->player_pos_lab.x) / 16), floor((Game::instance->player->player_pos_lab.y + 16 + 18) / 16)).type << std::endl;

		if (Input::isKeyPressed(SDL_SCANCODE_B) && Game::instance->player->facing == FACE_DOWN && Game::instance->laberinto->getCell(floor((Game::instance->player->player_pos_lab.x) / 16), floor((Game::instance->player->player_pos_lab.y + 16 + 18) / 16)).type == 38) //if key down
		{
			//volvemos al mapa inicial, para volver a tener los cofres brillantes

			changeStage("play");
		}

		if (Input::isKeyPressed(SDL_SCANCODE_A) && Game::instance->player->facing == FACE_LEFT && Game::instance->laberinto->getCell(floor((Game::instance->player->player_pos_lab.x - 16) / 16), floor((Game::instance->player->player_pos_lab.y) / 16)).type == 39 && Game::instance->player->num_objetos == 4) //if key down
		{
			Game::instance->player->arma_especial = true;

		}
		if (Game::instance->player->arma_especial == true) {
			std::cout << "la tenemos" << std::endl;
		}
		bool posible = Game::instance->laberinto->posible_caminar_laberinto(floor(Game::instance->target_pos_3.x), floor(Game::instance->target_pos_3.y));
		if (posible == true) {
			Game::instance->player->player_pos_lab += (Game::instance->target_pos_3 - Game::instance->player->player_pos_lab) * 0.1;

		}
		else {
			Game::instance->target_pos_3 = Game::instance->player->player_pos_lab;
		}

	};



	void CastilloStage::render(Image& fb, float time) {
		int cs = 16; //size in pixels of a cell


		for (int x = 0; x < Game::instance->castillo->width; ++x)
			for (int y = 0; y < Game::instance->castillo->height; ++y)
			{
				int x_aux;
				int y_aux;
				//get cell info
				bool pintamos = false;



				sCell& cell = Game::instance->castillo->getCell(x, y);
				if (cell.type == 0) //skip empty
					continue;
				//compute tile pos in tileset image
				int tilex = (cell.type % 16) * cs;
				int tiley = floor(cell.type / 16) * cs;
				Area area(tilex, tiley, cs, cs);
				//avoid rendering out of screen stuff

				//draw area of tileset inside framebuffer
				//std::cout << framebuffer.width << std::endl;

				//comentado
				//fb.drawImage(tileset, x * cs - 0, y * cs - 0, area);
				fb.drawImage(Game::instance->tileset, x * cs - 0, y * cs - 0, area);


			}
		if (Game::instance->player->player_pos_cas.x < 0) {
			Game::instance->player->player_pos_cas.x = 0;
			Game::instance->target_pos_3 = Game::instance->player->player_pos_cas;

		}
		else if (Game::instance->player->player_pos_cas.x >= fb.width -14)
		{
			Game::instance->player->player_pos_cas.x = fb.width - 15;
			Game::instance->target_pos_3 = Game::instance->player->player_pos_cas;
		}

		if (Game::instance->player->player_pos_cas.y < 0) {
			Game::instance->player->player_pos_cas.y = 0;
			Game::instance->target_pos_3 = Game::instance->player->player_pos_cas;
		}
		else if (Game::instance->player->player_pos_cas.y >= (fb.height-18 ))
		{
			Game::instance->player->player_pos_cas.y = (fb.height - 19) ;
			Game::instance->target_pos_3 = Game::instance->player->player_pos_cas;
		}


		


		if (Game::instance->player->player_pos_cas.x >= 0 && Game::instance->player->player_pos_cas.x < Game::instance->castillo->width * 16 -14 && Game::instance->player->player_pos_cas.y >= 0 && Game::instance->player->player_pos_cas.y < Game::instance->castillo->height * 16-18) {

			if (Game::instance->player->en_mov == true) {
				fb.drawImage(Game::instance->sprite2, Game::instance->player->player_pos_cas.x, Game::instance->player->player_pos_cas.y, Area((int(time) % 4) * 14, Game::instance->player->facing * 18, 14, 18));	//draws only a part of an image
			}
			else {
				fb.drawImage(Game::instance->sprite2, Game::instance->player->player_pos_cas.x, Game::instance->player->player_pos_cas.y, Area(0, Game::instance->player->facing * 18, 14, 18));	//draws only a part of an image
			}

			//comentado
			

		}


		Game::instance->player->en_mov = false;

		fb.drawImage(Game::instance->dragon, Game::instance->player->dragon_pos.x, Game::instance->player->dragon_pos.y, Area((int(time) % 3) * 45, Game::instance->player->dragon_facing * 38, 45, 38));	//draws only a part of an image
	
		fb.drawText("num objetos:" + toString(Game::instance->player->num_objetos), 0, 0, Game::instance->minifont, 4, 6);
		if (Game::instance->player->llaves == true) {
			fb.drawText("llaves", 60, 0, Game::instance->minifont, 4, 6);
		}
		if (Game::instance->player->arma_especial == true) {
			fb.drawText("arma_especial", 90, 0, Game::instance->minifont, 4, 6);
		}
	};
	void CastilloStage::update(double seconds_elapsed) {
		if (Input::wasKeyPressed(SDL_SCANCODE_R)) //if key up
		{
			Player* p2 = new Player(0);
			Game::instance->player = p2;
			Game::instance->target_pos.x = 0;
			Game::instance->target_pos.y = 0;
			Game::instance->camera->camera_pos.x = 0;
			Game::instance->camera->camera_pos.y = 0;
			changeStage("intro");
		}
		float player_speed = 30;
		//Read the keyboard state, to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
		if (Input::isKeyPressed(SDL_SCANCODE_UP)) //if key up
		{
			Game::instance->player->en_mov = true;
			Game::instance->player->facing = FACE_UP;
			Game::instance->target_pos_3.y -= seconds_elapsed * player_speed;  // empieza en el 0,0 arriba izquierda
		}
		if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
		{
			Game::instance->player->en_mov = true;
			Game::instance->player->facing = FACE_DOWN;
			Game::instance->target_pos_3.y += seconds_elapsed * player_speed;
		}
		if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) //if key up
		{
			Game::instance->player->en_mov = true;
			Game::instance->player->facing = FACE_LEFT;
			Game::instance->target_pos_3.x -= seconds_elapsed * player_speed;  // empieza en el 0,0 arriba izquierda
		}
		if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) //if key down
		{
			Game::instance->player->en_mov = true;
			Game::instance->player->facing = FACE_RIGHT;
			Game::instance->target_pos_3.x += seconds_elapsed * player_speed;
		}
		

		if (Input::isKeyPressed(SDL_SCANCODE_B) && Game::instance->player->facing == FACE_DOWN && Game::instance->castillo->getCell(floor((Game::instance->player->player_pos_cas.x) / 16), floor((Game::instance->player->player_pos_cas.y + 16 + 18) / 16)).type == 38) //if key down
		{
			//volvemos al mapa inicial, para volver a tener los cofres brillantes


		}

		if (Input::isKeyPressed(SDL_SCANCODE_A) && Game::instance->player->facing == FACE_LEFT && Game::instance->castillo->getCell(floor((Game::instance->player->player_pos_cas.x - 16) / 16), floor((Game::instance->player->player_pos_cas.y) / 16)).type == 39 && Game::instance->player->num_objetos == 4) //if key down
		{


		}



		if (Input::wasKeyPressed(SDL_SCANCODE_A) && Game::instance->player->facing == FACE_DOWN && Game::instance->player->arma_especial == true) {
			Game::instance->player->arma_especial = false;
			Game::instance->player->player_pos_ataque.x = floor((Game::instance->player->player_pos_cas.x) / 16);
			Game::instance->player->player_pos_ataque.y = floor((Game::instance->player->player_pos_cas.y) / 16);
			Game::instance->castillo->getCell(floor((Game::instance->player->player_pos_cas.x) / 16), floor((Game::instance->player->player_pos_cas.y) / 16)).type = (eCellType)40;
			Game::instance->player->atacar_abajo = true;


		}

		if (Input::wasKeyPressed(SDL_SCANCODE_A) && Game::instance->player->facing == FACE_UP && Game::instance->player->arma_especial == true) {
			Game::instance->player->arma_especial = false;
			Game::instance->player->player_pos_ataque.x = floor((Game::instance->player->player_pos_cas.x) / 16);
			Game::instance->player->player_pos_ataque.y = floor((Game::instance->player->player_pos_cas.y) / 16);
			Game::instance->castillo->getCell(floor((Game::instance->player->player_pos_cas.x) / 16), floor((Game::instance->player->player_pos_cas.y) / 16)).type = (eCellType)40;
			Game::instance->player->atacar_arriba = true;
		}

		if (Input::wasKeyPressed(SDL_SCANCODE_A) && Game::instance->player->facing == FACE_RIGHT && Game::instance->player->arma_especial == true) {
			Game::instance->player->arma_especial = false;
			Game::instance->player->player_pos_ataque.x = floor((Game::instance->player->player_pos_cas.x) / 16);
			Game::instance->player->player_pos_ataque.y = floor((Game::instance->player->player_pos_cas.y) / 16);
			Game::instance->castillo->getCell(floor((Game::instance->player->player_pos_cas.x) / 16), floor((Game::instance->player->player_pos_cas.y) / 16)).type = (eCellType)40;
			Game::instance->player->atacar_derecha = true;
		}

		if (Input::wasKeyPressed(SDL_SCANCODE_A) && Game::instance->player->facing == FACE_LEFT && Game::instance->player->arma_especial == true) {
			Game::instance->player->arma_especial = false;
			Game::instance->player->player_pos_ataque.x = floor((Game::instance->player->player_pos_cas.x) / 16);
			Game::instance->player->player_pos_ataque.y = floor((Game::instance->player->player_pos_cas.y) / 16);
			Game::instance->castillo->getCell(floor((Game::instance->player->player_pos_cas.x) / 16), floor((Game::instance->player->player_pos_cas.y) / 16)).type = (eCellType)40;
			Game::instance->player->atacar_izquierda = true;
		}

		if (Game::instance->player->atacar_abajo == true) {
			if (Game::instance->player->player_pos_ataque.y >= Game::instance->castillo->height - 1) {
				Game::instance->player->arma_especial = true;
				Game::instance->player->atacar_abajo = false;
				Game::instance->castillo->getCell(Game::instance->player->player_pos_ataque.x, Game::instance->player->player_pos_ataque.y).type = (eCellType)11;
			}
			else {

				Game::instance->castillo->getCell(Game::instance->player->player_pos_ataque.x, Game::instance->player->player_pos_ataque.y).type = (eCellType)11;

				Game::instance->player->player_pos_ataque.y += seconds_elapsed * 5;

				//std::cout << Game::instance->player->player_pos_ataque.y << std::endl;
				Game::instance->castillo->getCell(Game::instance->player->player_pos_ataque.x, Game::instance->player->player_pos_ataque.y).type = (eCellType)40;
			}


		}
		else if (Game::instance->player->atacar_arriba == true) {
			if (Game::instance->player->player_pos_ataque.y < 0) {
				Game::instance->player->arma_especial = true;
				Game::instance->player->atacar_arriba = false;
				Game::instance->castillo->getCell(Game::instance->player->player_pos_ataque.x, Game::instance->player->player_pos_ataque.y).type = (eCellType)11;
			}
			else {

				Game::instance->castillo->getCell(Game::instance->player->player_pos_ataque.x, Game::instance->player->player_pos_ataque.y).type = (eCellType)11;

				Game::instance->player->player_pos_ataque.y -= seconds_elapsed * 5;

				//std::cout << player->player_pos_ataque.y << std::endl;
				Game::instance->castillo->getCell(Game::instance->player->player_pos_ataque.x, Game::instance->player->player_pos_ataque.y).type = (eCellType)40;
			}

		}
		else if (Game::instance->player->atacar_derecha == true) {
			if (Game::instance->player->player_pos_ataque.x >= Game::instance->castillo->width - 1) {
				Game::instance->player->arma_especial = true;
				Game::instance->player->atacar_derecha = false;
				Game::instance->castillo->getCell(Game::instance->player->player_pos_ataque.x, Game::instance->player->player_pos_ataque.y).type = (eCellType)11;
			}
			else {

				Game::instance->castillo->getCell(Game::instance->player->player_pos_ataque.x, Game::instance->player->player_pos_ataque.y).type = (eCellType)11;

				Game::instance->player->player_pos_ataque.x += seconds_elapsed * 5;

				//std::cout << player->player_pos_ataque.y << std::endl;
				Game::instance->castillo->getCell(Game::instance->player->player_pos_ataque.x, Game::instance->player->player_pos_ataque.y).type = (eCellType)40;
			}

		}
		else if (Game::instance->player->atacar_izquierda == true) {
			if (Game::instance->player->player_pos_ataque.x < 0) {
				Game::instance->player->arma_especial = true;
				Game::instance->player->atacar_izquierda = false;
				Game::instance->castillo->getCell(Game::instance->player->player_pos_ataque.x, Game::instance->player->player_pos_ataque.y).type = (eCellType)11;
			}
			else {

				Game::instance->castillo->getCell(Game::instance->player->player_pos_ataque.x, Game::instance->player->player_pos_ataque.y).type = (eCellType)11;

				Game::instance->player->player_pos_ataque.x -= seconds_elapsed * 5;

				//std::cout << player->player_pos_ataque.y << std::endl;
				Game::instance->castillo->getCell(Game::instance->player->player_pos_ataque.x, Game::instance->player->player_pos_ataque.y).type = (eCellType)40;
			}

		}


		bool posible = Game::instance->castillo->posible_caminar_castillo(floor(Game::instance->target_pos_3.x), floor(Game::instance->target_pos_3.y));
		if (posible == true) {
			Game::instance->player->player_pos_cas += (Game::instance->target_pos_3 - Game::instance->player->player_pos_cas) * 0.1;

		}
		else {
			Game::instance->target_pos_3 = Game::instance->player->player_pos_cas;
		}
		if (Game::instance->castillo->impacto_dragon(Game::instance->player->dragon_pos.x, Game::instance->player->dragon_pos.y) == true) {
			changeStage("victoria");
		}

		if (abs(Game::instance->player->player_pos_cas.x - Game::instance->player->dragon_pos.x) > abs(Game::instance->player->player_pos_cas.y - Game::instance->player->dragon_pos.y)) {
			if (Game::instance->player->player_pos_cas.x - Game::instance->player->dragon_pos.x > 0) {
				Game::instance->player->dragon_facing = 1;
				Game::instance->player->dragon_pos.x += seconds_elapsed * 20;


			}
			else {
				Game::instance->player->dragon_facing = 3;
				Game::instance->player->dragon_pos.x -= seconds_elapsed * 20;
			}


		}
		else {
			if (Game::instance->player->player_pos_cas.y - Game::instance->player->dragon_pos.y > 0) {
				Game::instance->player->dragon_facing = 2;
				Game::instance->player->dragon_pos.y += seconds_elapsed * 20;


			}
			else {
				Game::instance->player->dragon_facing = 0;
				Game::instance->player->dragon_pos.y -= seconds_elapsed * 20;
			}

		}
		if (Game::instance->castillo->impacto_dragon_muerte(Game::instance->player->dragon_pos.x, Game::instance->player->dragon_pos.y, Game::instance->player->player_pos_cas.x, Game::instance->player->player_pos_cas.y) == true) {
			changeStage("derrota");
		}


	
};

