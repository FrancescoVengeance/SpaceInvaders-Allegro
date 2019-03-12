#include "GameManager.h"

//note
/*
power up
1) velocità
2) scudo attivabile o non...
*/

int main(int argc, char **argv)
{
	GameManager game;
	bool closeMenu = false;
	while (!closeMenu)
	{
		closeMenu = game.menu();
	}
	game.level1();
	return 0;
}