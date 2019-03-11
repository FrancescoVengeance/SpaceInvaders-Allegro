#ifndef BARRIER_H
#define BARRIER_H
#include<iostream>
#include <allegro5/allegro.h>
using namespace std;
class Barrier
{
	private:
		//ALLEGRO_BITMAP* barriere[3] = { nullptr }; //array that contains sprites
		ALLEGRO_BITMAP* barriere = barriere = al_load_bitmap("test1.png");;
		bool draw = true;
	public:
		double x = 500; //x test, da cambiare
		double y = 800; //y test, da cambiare
		Barrier() {}
		~Barrier() { al_destroy_bitmap(barriere); }
		bool getDraw() const { return draw; }
		void setDraw(bool d) { draw = d; }
		ALLEGRO_BITMAP* getBarrierImage() const { return barriere; }
		
};

#endif