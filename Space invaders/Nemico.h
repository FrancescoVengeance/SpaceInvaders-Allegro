﻿#ifndef NEMICO_H
#define NEMICO__H

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
using namespace std;

enum ENEMY_TYPE { SCARSO , MEDIO, FORTE, FORTISSIMO };

class Nemico
{
protected:
	bool draw = true;
	int life = 0; //vita
	int strenght_attack = 0; //forza di attacco
	double speed = 0; //velocità del nemico
	ALLEGRO_BITMAP* immagine = nullptr;
	
public:
	Nemico(int _life, int _strenght, double _speed) : life(_life), strenght_attack(_strenght), speed(_speed) {}
	virtual ~Nemico() {}

	double x = 0;
	double y = 20;

	bool getDraw() const { return draw; }
	void setDraw(bool d) { draw = d; }
	int getEnemyLife() const { return life; }
	void setEnemyLife(int l) { life = l; }
	int getEnemyStrenght_attack() const { return strenght_attack; }
	double getEnemySpeed() const { return speed; }
	virtual ENEMY_TYPE getTipo() const = 0;
	ALLEGRO_BITMAP* getEnemyImage() const { return immagine; }
};
#endif