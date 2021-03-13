#include "Player.h"



Player::Player(int face)
{
	player_pos.x = 0;
	player_pos.y = 0;
	player_pos_casa.x = 8 * 16 - 40;
	player_pos_casa.y = 15 * 16 -18;
	player_pos_lab.x = 16 * 16 - 40;
	player_pos_lab.y = 31 * 16 - 18;
	player_pos_cas.x = 5 * 16 - 40;
	player_pos_cas.y = 5 * 16 - 18;
	facing = face;
	mov_x=0;
	mov_y=0;
	mov_x_casa = 96;
	mov_y_casa = 96;
	num_objetos = 0;
	llaves = false;
	arma_especial = false;
	atacar_derecha = false;
	atacar_izquierda = false;
	atacar_abajo = false;
	atacar_arriba = false;
	dragon_pos.x = 0;
	dragon_pos.y = 0;
	dragon_facing = 2;



}

