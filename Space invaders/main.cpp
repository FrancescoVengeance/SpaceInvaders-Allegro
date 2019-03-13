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
	bool close = false;
	bool start = true;

	inizio:
	while (!close)
	{
		close = game.menu(start);
	}
	if (close && start)
	{
		game.level1();
	}
	return 0;
}