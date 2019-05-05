#ifndef  PLAYER_H
#define PLAYER_H

#include<iostream>
#include <allegro5/allegro.h>
#include "Nemico3.h"
using namespace std;

enum DIRECTION {OTHER, LEFT, RIGHT}; //enum che restituisce la giusta immagine in base al tasto premuto

class Player
{
private:
	int life = 3;
	float speed = 5.0;
	float y = 1080-160;
	int strenght = 5;
	unsigned score = 0;
	ALLEGRO_BITMAP* immagine[3] = { nullptr }; //array che contiene le sprites

public:
	Player() 
	{ 
		immagine[0] = al_load_bitmap("Player.png");
		immagine[1] = al_load_bitmap("Player1.png");
		immagine[2] = al_load_bitmap("Player2.png");
	}

	~Player()
	{
		for (unsigned i = 0; i < 3; i++)
		{
			al_destroy_bitmap(immagine[i]);
		}
	}

	float getPlayerSpeed() { return speed; }
	void setPlayerSpeed(float s) { speed = s; }

	int getLife() { return life; }

	float getY() { return y; }
	float x = 150;

	void setScore(unsigned s) { score = s; }
	unsigned getScore() const { return score; }

	ALLEGRO_BITMAP* getPlayerImage(DIRECTION dir)
	{
		if (dir == LEFT) return immagine[1]; //se <- è premuto
		if (dir == RIGHT) return immagine[2]; //se -> è premuto
		return immagine[0]; //se nessun tasto è premuto
	}

	Player& operator ++() //operatore di pre-incremento per la vita
	{
		life++;
		return *this;
	}
	Player& operator--() //operatore di pre-decremento per la vita
	{
		life--;
		return *this;
	}

	void gestionePunteggio(Nemico* n, bool& shoot)
	{
		if (n->getTipo() == SCARSO) score += 100;
		if (n->getTipo() == MEDIO) score += 200;
		if (n->getTipo() == FORTE) score += 300;

		n->setDraw(false);
		shoot = false;
	}
};

#endif

