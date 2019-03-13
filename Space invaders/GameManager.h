#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Libraries.h"

using namespace std;

class GameManager
{
	private:
		ALLEGRO_BITMAP* menuBackground = nullptr;
		ALLEGRO_BITMAP* gameBackground = nullptr;

		ALLEGRO_BITMAP* menuText = nullptr;

		ALLEGRO_BITMAP* startButton = nullptr;
		ALLEGRO_BITMAP* startButtonPressed = nullptr;
		ALLEGRO_BITMAP* startButtonPressedLong = nullptr;

		ALLEGRO_BITMAP* optionButton = nullptr;
		ALLEGRO_BITMAP* optionButtonPressed = nullptr;
		ALLEGRO_BITMAP* optionButtonPressedLong = nullptr;

		ALLEGRO_BITMAP* escButton = nullptr;
		ALLEGRO_BITMAP* escButtonPressed = nullptr;
		ALLEGRO_BITMAP* escButtonPressedLong = nullptr;

		ALLEGRO_FONT* font = nullptr;
		ALLEGRO_DISPLAY* display = nullptr;
		ALLEGRO_EVENT_QUEUE* queue = nullptr;
		ALLEGRO_EVENT_QUEUE* queue2 = nullptr;
		ALLEGRO_KEYBOARD_STATE keyState;
		ALLEGRO_MOUSE_STATE mouseState;
		ALLEGRO_TIMER* timer = nullptr;
		Barrier* barriere[3];
		bool close = false; //to close the game
		bool motion = true;
		bool shoot = false; //to shooting
		bool leggi = false;
		bool enemyshoot = false; //gestisce lo shoot del nemico
		Weapon* arma = nullptr;
		Weapon* armanemico = nullptr;//gestita dopo
		
		int numero;
		int row_enemy; //row poi generata casuale
		int column_enemy; //column poi generata casuale
		bool easter[3] = { false }; //for the easter egg
		bool enemies_initialize(Nemico*[][9], int, int);
		void winScreen();
		

	public:
		GameManager();
		~GameManager();
		
		bool menu(bool&);
		void level1();
		
		
};
#endif
