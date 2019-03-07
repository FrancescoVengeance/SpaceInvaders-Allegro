#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include<iostream>
#include <allegro5/allegro.h>
using namespace std;
class GameManager
{
	private:
		ALLEGRO_BITMAP* menu = nullptr;
	public:
		GameManager(){
			menu = al_load_bitmap("MenuProgetto.png");
		}
		void drawMenu() {
			al_draw_bitmap(menu, 0, 0, 1);
			al_flip_display();
		}

		~GameManager(){}
};
#endif
