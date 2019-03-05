#ifndef  PLAYER_H
#define PLAYER_H

#include<iostream>
#include <allegro5/allegro.h>
using namespace std;

enum DIRECTION {OTHER, LEFT, RIGHT}; //enum that return the right sprite based on the direction in the main

class Player
{
private:
	int life = 3;
	float speed = 5.0;
	float y = 1080-160;
	int strenght = 5;
	ALLEGRO_BITMAP* immagine[3] = { nullptr }; //array that contains sprites

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
			cout << "Giocatore distrutto " << i << endl;
		}
	}

	float getPlayerSpeed() { return speed; }
	void setPlayerSpeed(float s) { speed = s; }

	float getY() { return y; }
	float x = 150;

	ALLEGRO_BITMAP* getPlayerImage(DIRECTION dir)
	{
		if (dir == LEFT) return immagine[1]; //if <- is pressed
		if (dir == RIGHT) return immagine[2]; //if -> is pressed
		return immagine[0]; //if no key is pressed
	}

	Player& operator ++() //prefix operator for increment of life
	{
		life++;
		return *this;
	}
	Player& operator--() //prefix operator for decrement of life
	{
		life--;
		return *this;
	}
};

#endif

