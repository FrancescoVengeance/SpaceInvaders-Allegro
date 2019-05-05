#ifndef MOTORE_GRAFICO_H
#define MOTORE_GRAFICO_H

#include "Player.h"
#include "Nemico3.h"

class MotoreGrafico 
{
public:
	static void draw(Nemico& n)
	{
		al_draw_bitmap(n.getEnemyImage(), n.x, n.y, 0);
	}

	static void draw(Player& p, DIRECTION d)
	{
		al_draw_bitmap(p.getPlayerImage(d), p.x, p.getY(), 0);
	}

	static void draw(ALLEGRO_BITMAP* immagine, float x, float y)
	{
		al_draw_bitmap(immagine, x, y, 0);
	}

	static void draw(Bunker& bunker)
	{
		if (bunker.getDraw()) al_draw_bitmap(bunker.getImage(), bunker.getX(), bunker.getY(), 0);
	}

	static void draw(Weapon* arma)
	{
		al_draw_bitmap(arma->getWeaponImage(), arma->x, arma->y, 0);
	}

	static void refreshDisplay() { al_flip_display(); }
};
#endif // !MOTORE_GRAFICO_H

