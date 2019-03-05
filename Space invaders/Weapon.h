#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <allegro5/allegro.h>
using namespace std;

class Weapon
{
protected:
	double speed = 15.0;
	int strenght = 5;
	ALLEGRO_BITMAP* immagine = nullptr;
public:
	Weapon() { immagine = al_load_bitmap("Weapon.png"); cout << "ARMA COSTRUITA" << endl; }
	Weapon(const Weapon& w) //copy constructor
	{
		speed = w.speed;
		strenght = w.strenght;
		x = w.x;
		y = w.y;
		immagine = al_load_bitmap("Weapon.png");
	}
	~Weapon() { al_destroy_bitmap(immagine); cout << "ARMA DISTRUTTA" << endl; }
	
	ALLEGRO_BITMAP* getWeaponImage() const { return immagine; }
	int getStrenght() const { return strenght; }
	void setStrenght(int s) { strenght = s; }
	double getSpeed() const { return speed; }
	double x = 0;
	double y = 0;
};
#endif // !WEAPON_H
