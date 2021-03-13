#include "game.h"
#include "Stage.h"
//some globals

Game* Game::instance = NULL;
extern InitStage* init_stage;
extern MenuStage* menu_stage;
extern MenuStage2* menu_stage2;
extern EagleStage* eagle_stage;
extern PlayStage* play_stage;
extern LoadStage* load_stage ;
extern VictoryStage* vic_stage;
extern LoseStage* loser_stage;
extern ControlStage* control_stage;
extern Stage* current_stage;
extern int posiciones[7][2];

Game::Game(int window_width, int window_height, SDL_Window* window)
{
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;
	
	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;
	mouse_locked = false;

	//OpenGL flags
	glEnable(GL_CULL_FACE); //render both sides of every triangle
	glEnable(GL_DEPTH_TEST); //check the occlusions using the Z buffer
	init_stage = new InitStage();
	menu_stage = new MenuStage();
	menu_stage2 = new MenuStage2();
	eagle_stage = new EagleStage();
	play_stage = new PlayStage();
	load_stage = new LoadStage();
	loser_stage = new LoseStage();
	control_stage = new ControlStage();
	vic_stage = new VictoryStage();
	current_stage = init_stage;
	current_stage->init(window_width, window_height);
	SDL_ShowCursor(!mouse_locked); //hide or show the mouse
	zombie_speed = 25;
}

//what to do when the image has to be draw
void Game::render(void)
{
	current_stage->render(time);
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);
	

	//swap between front buffer and back buffer*/
	SDL_GL_SwapWindow(this->window);
}

void Game::update(double seconds_elapsed)
{
	float speed = seconds_elapsed * 1;
	
	
	current_stage->update(speed);
	
}

//Keyboard event handler (sync input)
void Game::onKeyDown(SDL_KeyboardEvent event)
{
	switch (event.keysym.sym)
	{
	case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
	case SDLK_F1: Shader::ReloadAll(); break;
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

void Game::onMouseButtonDown(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_MIDDLE) //middle mouse
	{
		mouse_locked = !mouse_locked;
		SDL_ShowCursor(!mouse_locked);
	}
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
	glViewport(0, 0, width, height);
	camera->aspect = width / (float)height;
	window_width = width;
	window_height = height;
}

