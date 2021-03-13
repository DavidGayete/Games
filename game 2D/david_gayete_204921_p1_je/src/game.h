/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This class encapsulates the game, is in charge of creating the game, getting the user input, process the update and render.
*/

#ifndef GAME_H
#define GAME_H

#include "includes.h"
#include "image.h"
#include "utils.h"
#include "synth.h"
#include "GameMap.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"


class Game
{
public:
	static Game* instance;

	//window
	SDL_Window* window;
	int window_width;
	int window_height;

	//some globals
	long frame;
    float time;
	float elapsed_time;
	int fps;
	bool must_exit;
	Image font;
	Image minifont;
	Image sprite;
	Image sprite2;
	Image dragon;
	Image derrota_final;
	Image victoria_final;
	Image tutorial_final;
	Image settings_final;
	Image intro_final;
	Image tileset;
	Player* player;

	Camera* camera ;
	Camera* camera2 ;
	Camera* camera3 ;
	Camera* camera4 ;

	//Color bgcolor(130, 80, 100);
	GameMap* map;
	GameMap* casas;
	GameMap* laberinto;
	GameMap* castillo;


	Vector2 target_pos;
	Vector2 target_pos_2;
	Vector2 target_pos_3;





	//audio
	Synth synth;

	//ctor
	Game( int window_width, int window_height, SDL_Window* window );

	//main functions
	void render( void );
	void update( double dt );

	void showFramebuffer(Image* img);

	//events
	void onKeyDown( SDL_KeyboardEvent event );
	void onKeyUp(SDL_KeyboardEvent event);
	void onMouseButtonDown( SDL_MouseButtonEvent event );
	void onMouseButtonUp(SDL_MouseButtonEvent event);
	void onMouseMove(SDL_MouseMotionEvent event);
	void onMouseWheel(SDL_MouseWheelEvent event);
	void onGamepadButtonDown(SDL_JoyButtonEvent event);
	void onGamepadButtonUp(SDL_JoyButtonEvent event);
	void onResize(int width, int height);

	//audio stuff
	void enableAudio(); //opens audio channel to play sound
	void onAudio(float* buffer, unsigned int len, double time, SDL_AudioSpec &audio_spec); //called constantly to fill the audio buffer
};


#endif 