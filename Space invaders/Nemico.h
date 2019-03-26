#ifndef NEMICO_H
#define NEMICO__H

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
using namespace std;

enum ENEMY_TYPE { SCARSO , MEDIO, FORTE, FORTISSIMO };

class Nemico
{
protected:
	bool draw = true; //variabile per il disegno della sprite
	int life = 0;
	int strenght_attack = 0;
	ENEMY_TYPE tipo;
	double speed = 0; //velocità del nemico
	ALLEGRO_BITMAP* immagine = nullptr;
	
public:
	Nemico(int _life, int _strenght, double _speed, ENEMY_TYPE _tipo) : life(_life), strenght_attack(_strenght), speed(_speed), tipo(_tipo) {}
	virtual ~Nemico() {}

	//coordinate
	float x = 0;
	float y = 20;

	bool getDraw() const { return draw; }
	void setDraw(bool d) { draw = d; }

	int getEnemyLife() const { return life; }
	void setEnemyLife(int l) { life = l; }

	int getEnemyStrenght_attack() const { return strenght_attack; }
	double getEnemySpeed() const { return speed; }
	ENEMY_TYPE getTipo() const { return tipo; }
	ALLEGRO_BITMAP* getEnemyImage() const { return immagine; }
};
#endif
