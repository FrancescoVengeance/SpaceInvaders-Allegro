#ifndef  PLAYER_H
#define PLAYER_H

#include<iostream>
using namespace std;

enum DIRECTION {OTHER, LEFT, RIGHT};

class Player
{
private:
	int life = 3;
	float speed = 5.0;
	float y = 1080-160;
	int strenght = 5;
	ALLEGRO_BITMAP* immagine[3] = { nullptr };

public:
	Player() 
	{ 
		immagine[0] = al_load_bitmap("Player.png");
		immagine[1] = al_load_bitmap("Player1.png");
		immagine[2] = al_load_bitmap("Player2.png");
	}
	Player(int _strenght, float _speed) : strenght(_strenght), speed(_speed)
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

	float getY() { return y; }
	float x = 150;

	ALLEGRO_BITMAP* getPlayerImage(DIRECTION dir)
	{
		if (dir == LEFT) return immagine[2];
		if (dir == RIGHT) return immagine[1];
		return immagine[0];
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

