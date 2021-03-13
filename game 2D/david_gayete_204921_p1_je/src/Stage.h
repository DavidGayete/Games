
#ifndef STAGE_H
#define STAGE_H

#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include "Image.h"

#include "input.h"

enum { FACE_DOWN, FACE_RIGHT, FACE_LEFT, FACE_UP };

class Stage
{
public:
	static std::map<std::string, Stage*> s_stages;
	static Stage* current_stage;

	static void changeStage(const char* name);
	Stage(const char* name);
	virtual void render(Image& fb, float time);
	virtual void update(double seconds_elapsed);
};









class IntroStage : public Stage
{
public:
	IntroStage() : Stage("intro") {}
	int caso = 0;


	void render(Image& fb, float time);
	void update(double seconds_elapsed);
};
class TutorialStage : public Stage
{
public:
	TutorialStage() : Stage("tutorial") {}
	int caso = 0;


	void render(Image& fb, float time);
	void update(double seconds_elapsed);
};
class SettingsStage : public Stage
{
public:
	SettingsStage() : Stage("settings") {}
	int caso = 0;


	void render(Image& fb, float time);
	void update(double seconds_elapsed);
};

class VictoriaStage : public Stage
{
public:
	VictoriaStage() : Stage("victoria"){}
	int caso = 0;


	void render(Image& fb, float time);
	void update(double seconds_elapsed);
};

class DerrotaStage : public Stage
{
public:
	DerrotaStage() : Stage("derrota"){}
	int caso=0;


	void render(Image& fb, float time);
	void update(double seconds_elapsed);
};



class PlayStage : public Stage
{
public:

	PlayStage() : Stage("play"){}

	

	void render(Image& fb, float time);
	void update(double seconds_elapsed);
};

class CasaStage : public Stage
{
public:
	CasaStage() : Stage("casa") {}
	void render(Image& fb, float time);
	void update(double seconds_elapsed);
};

class LaberintoStage : public Stage
{
public:
	LaberintoStage() : Stage("laberinto") {}
	void render(Image& fb, float time);
	void update(double seconds_elapsed);

};

class CastilloStage : public Stage
{
public:
	CastilloStage() : Stage("castillo") {}
	void render(Image& fb, float time);
	void update(double seconds_elapsed);

	
};










#endif