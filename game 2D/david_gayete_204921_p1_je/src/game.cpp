#include "game.h"
#include "utils.h"
#include "input.h"
#include "image.h"



#include <cmath>


Game* Game::instance = NULL;



 Stage* Stage::current_stage = NULL;




Game::Game(int window_width, int window_height, SDL_Window* window)
{


	player = new Player(0);
	camera = new Camera();
	camera2 = new Camera();
	camera3 = new Camera();
	camera4 = new Camera();

	


	//int facing = FACE_DOWN;
	int inicial = 0;

	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;

	map = new GameMap(128,128);
	casas = new GameMap(128, 128);
	laberinto = new GameMap(128, 128);
	castillo = new GameMap(128, 128);

	map->loadMap("data/mymap.map");
	
	casas->loadMap("data/mymap2.map");
	laberinto->loadMap("data/laberinto.map");
	tileset.loadTGA("data/tileset_2_1.tga"); //load bitmap-font image
	dragon.loadTGA("data/dragon.tga"); //load bitmap-font image
	castillo->loadMap("data/castillo.map");
	derrota_final.loadTGA("data/derrota.tga");
	victoria_final.loadTGA("data/vicrotia.tga");
	tutorial_final.loadTGA("data/tutorial.tga");
	settings_final.loadTGA("data/settings.tga");
	intro_final.loadTGA("data/intro.tga");
	
	
	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;
	target_pos_2.x = player->player_pos_casa.x;
	target_pos_2.y = player->player_pos_casa.y;
	target_pos_3.x = player->player_pos_lab.x;
	target_pos_3.y = player->player_pos_lab.y;
	
	camera2->camera_pos.x = (casas->width / 2) * 16 - 40;
	camera2->camera_pos.y = (casas->height - 1) * 16 - 60;
	camera3->camera_pos.x = (laberinto->width / 2) * 16 - 40;
	camera3->camera_pos.y = (laberinto->height - 1) * 16 - 60;
	camera4->camera_pos.x = (castillo->width / 2) * 16 - 40;
	camera4->camera_pos.y = (castillo->height - 1) * 16 - 60;

	
											 
	font.loadTGA("data/bitmap-font-white.tga"); //load bitmap-font image
	minifont.loadTGA("data/mini-font-white-4x6.tga"); //load bitmap-font image
	sprite.loadTGA("data/spritesheet.tga"); //example to load an sprite
	sprite2.loadTGA("data/sprite2.tga"); //example to load an sprite
	enableAudio(); //enable this line if you plan to add audio to your application   //VOLUMEN

	//falta esto
	
	//synth.osc1.amplitude = 0.5;
	synth.playSample("data/musica.wav", 1, true);
	
	Stage::current_stage = new IntroStage();
	new PlayStage();
	new CasaStage();
	new LaberintoStage();
	new CastilloStage();
	new VictoriaStage();
	new DerrotaStage();
	new TutorialStage();
	new SettingsStage();
	
}

//what to do when the image has to be draw
void Game::render(void)
{
	//Create a new Image (or we could create a global one if we want to keep the previous frame)
	Image framebuffer(160, 120); //do not change framebuffer size
	player->mov_x = 0;
	player->mov_y = 0;
	Stage::current_stage->render(framebuffer,time);

	
	//add your code here to fill the framebuffer
	//...
	
	/*std::cout << player_pos.x << std::endl;
	std::cout << map.width << std::endl;
	std::cout << camera_pos.x << std::endl;
	*/
	
	//comentado

	//some new useful functions
		//framebuffer.fill( bgcolor );								//fills the image with one color
		//framebuffer.drawLine( 0, 0, 100,100, Color::RED );		//draws a line
		//framebuffer.drawImage( tileset, 0, 0 );					//draws full image
		//framebuffer.drawImage( sprite, 0, 0, framebuffer.width, framebuffer.height );			//draws a scaled image
		//framebuffer.drawImage(dragon, 0 , 0, Area(0, 2 * 38, 45, 38));	//draws only a part of an image

	//el dragon
	//framebuffer.drawImage(dragon, 0, 0, Area((int(time) % 3) * 45, 2 * 38, 45, 38));	//draws only a part of an image

		//framebuffer.drawText( "Hello World", 0, 0, font );				//draws some text using a bitmap font in an image (assuming every char is 7x9)
		//framebuffer.drawText( toString(time), 1, 10, minifont,4,6);	//draws some text using a bitmap font in an image (assuming every char is 4x6)

	//send image to screen



	showFramebuffer(&framebuffer);
}

void Game::update(double seconds_elapsed)
{
	//Add here your update method
	//...
	//const int notes[] = {69,71,72,74,76 };
	
	//synth.osc1.setNote(notes[int(time)%5]);
	//synth.osc1.freq = 440+ (sin(time * 10) * 0.5 + 0.5)*100;
	//synth.osc1.amplitude = sin(time*10)*0.5+0.5; //sonido sea como un sinus
	Stage::current_stage->update(seconds_elapsed);

	
	//Read the keyboard state, to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	if (Input::isKeyPressed(SDL_SCANCODE_Q)) //if key up
	{
		Stage::current_stage->changeStage("intro");
	}
	if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
	{
		
	}
	if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) //if key up
	{
		
	}
	if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) //if key down
	{
		
	}
	
	
	//example of 'was pressed'
	if (Input::wasKeyPressed(SDL_SCANCODE_A)) //if key A was pressed
	{

	}
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
	{
	}

	//to read the gamepad state
	if (Input::gamepads[0].isButtonPressed(A_BUTTON)) //if the A button is pressed
	{
	}

	if (Input::gamepads[0].direction & PAD_UP) //left stick pointing up
	{
		//bgcolor.set(0, 255, 0);
	}
	
}

//Keyboard event handler (sync input)
void Game::onKeyDown( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
	}
}

void Game::onKeyUp(SDL_KeyboardEvent event)
{
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{

}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{

}

void Game::onMouseMove(SDL_MouseMotionEvent event)
{
}

void Game::onMouseButtonDown( SDL_MouseButtonEvent event )
{
}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{
}

void Game::onMouseWheel(SDL_MouseWheelEvent event)
{
}

void Game::onResize(int width, int height)
{
    std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport( 0,0, width, height );
	window_width = width;
	window_height = height;
}

//sends the image to the framebuffer of the GPU
void Game::showFramebuffer(Image* img)
{
	static GLuint texture_id = -1;
	static GLuint shader_id = -1;
	if (!texture_id)
		glGenTextures(1, &texture_id);

	//upload as texture
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);

	glDisable(GL_CULL_FACE); glDisable(GL_DEPTH_TEST); glEnable(GL_TEXTURE_2D);
	float startx = -1.0; float starty = -1.0;
	float width = 2.0; float height = 2.0;

	//center in window
	float real_aspect = window_width / (float)window_height;
	float desired_aspect = img->width / (float)img->height;
	float diff = desired_aspect / real_aspect;
	width *= diff;
	startx = -diff;

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(startx, starty + height);
	glTexCoord2f(1.0, 0.0); glVertex2f(startx + width, starty + height);
	glTexCoord2f(1.0, 1.0); glVertex2f(startx + width, starty);
	glTexCoord2f(0.0, 1.0); glVertex2f(startx, starty);
	glEnd();

	/* this version resizes the image which is slower
	Image resized = *img;
	//resized.quantize(1); //change this line to have a more retro look
	resized.scale(window_width, window_height);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (1) //flip
	{
	glRasterPos2f(-1, 1);
	glPixelZoom(1, -1);
	}
	glDrawPixels( resized.width, resized.height, GL_RGBA, GL_UNSIGNED_BYTE, resized.pixels );
	*/
}

//AUDIO STUFF ********************

SDL_AudioSpec audio_spec;

void AudioCallback(void*  userdata,
	Uint8* stream,
	int    len)
{
	static double audio_time = 0;

	memset(stream, 0, len);//clear
	if (!Game::instance)
		return;

	Game::instance->onAudio((float*)stream, len / sizeof(float), audio_time, audio_spec);
	audio_time += len / (double)audio_spec.freq;
}

void Game::enableAudio()
{
	SDL_memset(&audio_spec, 0, sizeof(audio_spec)); /* or SDL_zero(want) */
	audio_spec.freq = 48000;
	audio_spec.format = AUDIO_F32;
	audio_spec.channels = 1;
	audio_spec.samples = 1024;
	audio_spec.callback = AudioCallback; /* you wrote this function elsewhere. */
	if (SDL_OpenAudio(&audio_spec, &audio_spec) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		exit(-1);
	}
	SDL_PauseAudio(0);
}

void Game::onAudio(float *buffer, unsigned int len, double time, SDL_AudioSpec& audio_spec)
{
	//fill the audio buffer using our custom retro synth
	synth.generateAudio(buffer, len, audio_spec);
}
