//player 1

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;

enum DIRECTION { LEFT, RIGHT, OTHER };

class Player
{
private:
	int score = 0;
	int life = 3;
	int strenght_attack = 2;
	double speed = 10;
	int y = (1080/2)+370;
	ALLEGRO_BITMAP* immagine[3];
public:
	Player() 
	{
		immagine[0] = al_load_bitmap("Player.png");
		immagine[1] = al_load_bitmap("Player1.png");
		immagine[2] = al_load_bitmap("Player2.png");
	};
	Player(int _life, int _strenght, double _speed) : life(_life), strenght_attack(_strenght), speed(_speed) 
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

	ALLEGRO_BITMAP* getPlayerImage(DIRECTION dir) 
	{
		if (dir == LEFT) return immagine[2];
		if (dir == RIGHT) return immagine[1];
		
		return immagine[0];
	}

	int getPlayerLife() const { return life; }

	Player& operator --()
	{
		life--;
		return *this;
	}
	Player& operator ++()
	{
		life++;
		return *this;
	}

	int getScore() const { return score; }
	void setScore(int s) { score = s; }

	double x = 0; //position on x
	int getY() const { return y; }

	int getPlayerStrenght_attack() const { return strenght_attack; }
	void setPlayerStrenght_attack(int a) { strenght_attack = a; }

	double getPlayerSpeed() const { return speed; }
	void setPlayerSpeed(double a) { speed = a; }
};
#endif