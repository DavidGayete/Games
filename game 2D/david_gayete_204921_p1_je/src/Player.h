
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include "framework.h"



class Player {
public:
	Vector2 player_pos;
	Vector2 player_pos_casa;
	Vector2 player_pos_lab;
	Vector2 player_pos_cas;
	Vector2 player_pos_ataque;
	Vector2 dragon_pos;
	int facing;
	int dragon_facing;
	int mov_x ;
	int mov_y ;
	int mov_x_casa;
	int mov_y_casa;
	int num_objetos;
	bool llaves;
	bool arma_especial;
	bool atacar_derecha;
	bool atacar_izquierda;
	bool atacar_abajo;
	bool atacar_arriba;
	bool casa1 = false;
	bool casa2 = false;
	bool casa3 = false;
	bool casa4 = false;
	Player(int face);
	bool en_mov = false;
	
	
};











#endif