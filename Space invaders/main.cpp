#include "GameManager.h"
//note
/*
power up
1) velocit�
2) scudo attivabile o non...
*/

int main(int argc, char **argv)
{
	GameManager game;
	bool close = false;
	
	while (!close)
	{
		close = game.menu();
	}

	//cout << (fine - start).count() << endl;



	return 0;
}