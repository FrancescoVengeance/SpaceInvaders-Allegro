#ifndef BUNKER_H
#define BUNKER_H

#include <iostream>
#include <allegro5/allegro.h>

class Bunker
{
private:
	ALLEGRO_BITMAP* immagine[4];
	float x;
	float y;
	bool draw = true;
	float colpiRicevuti = 0;

public:
	Bunker(float x, float y) : x(x), y(y)
	{
		immagine[0] = al_load_bitmap("intatto.png"); //integro
		immagine[1] = al_load_bitmap("medio.png");
		immagine[2] = al_load_bitmap("semiDistrutto.png");
		immagine[3] = al_load_bitmap("distrutto.png");
	}

	~Bunker()
	{
		for (short i = 0; i < 4; i++)
		{
			al_destroy_bitmap(immagine[i]);
		}
		std::cout << "Bunker distrutto" << std::endl;
	}

	float getX() const { return x; }
	float getY() const { return y; }

	bool getDraw() const { return draw; }
	void setDraw(bool draw) { this->draw = draw; }
	short getColpiRicevuti() const { return colpiRicevuti; }

	ALLEGRO_BITMAP* getImage() const
	{
		if (colpiRicevuti >= 0 && colpiRicevuti < 10) return immagine[0];
		if (colpiRicevuti >= 10 && colpiRicevuti < 20) return immagine[1];
		if (colpiRicevuti >= 20 && colpiRicevuti <= 25 ) return immagine[2];
		return immagine[3];
	}

	Bunker& operator ++() //operatore di pre-incremento per i colpi ricevuti
	{
		colpiRicevuti += 0.5;
		if (colpiRicevuti > 30) draw = false;
		return *this;
	}

	bool colpito(Weapon* arma)
	{
		if (arma != nullptr && arma->y >= y && draw && arma->x >= x && arma->x <= x + al_get_bitmap_width(immagine[0]))
		{
			++(*this);
			return true;
		}

		return false;
	}
};
#endif