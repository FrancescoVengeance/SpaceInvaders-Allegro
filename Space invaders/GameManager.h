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
	ALLEGRO_TIMER* timer = nullptr;
	ALLEGRO_EVENT mouseEvent;

	bool motion = true;
	bool shoot = false; //per sparare
	bool leggi = false;
	bool enemyshoot = false; //gestisce lo shoot del nemico
	bool easter[3] = { false }; //per l'easter egg
	bool enemies_initialize(Nemico*[][9], unsigned, unsigned);
	//int gestionePunteggio(Nemico*,bool&,unsigned);
	bool aggiornaCoordinate(Nemico*[][9], unsigned, unsigned, float, bool&);


	Weapon* arma = nullptr; //arma del giocatore
	Weapon* armanemico = nullptr; //arma del nemico

	int numero;
	int row_enemy; //riga poi generata casuale
	int column_enemy; //colonna poi generata casuale

	void winScreen();
	void pause();
	void level1();
	void level2();

public:
	GameManager();
	~GameManager();

	bool menu();

};
#endif