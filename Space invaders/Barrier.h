#ifndef BARRIER_H
#define BARRIER_H
#include<iostream>
#include <allegro5/allegro.h>
using namespace std;
class Barrier
{
	private:
		//ALLEGRO_BITMAP* barriere[3] = { nullptr }; //array that contains sprites
		ALLEGRO_BITMAP* barriere = nullptr;
		bool draw = true;
	public:
		double x = 500; //x test, da cambiare
		double y = 800; //y test, da cambiare
		Barrier() {
			//init test with 3 barrier
			barriere = al_load_bitmap("test1.png");
			draw = true;
		}
		bool getDraw() const { return draw; }
		void setDraw(bool d) { draw = d; }
		ALLEGRO_BITMAP* getBarrierImage() const { return barriere; }
		~Barrier() {};
};

#endif