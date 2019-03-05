#ifndef NEMICO_SCARSO_H
#define NEMICO_SCARSO_H

//nemico più debole di tutti
#include "Enemy.h"

class Nemico1 : public Nemico
{
public:
	Nemico1() : Nemico(5, 5, 2.00)
	{
		immagine = al_load_bitmap("Enemy1.png");
	}
	~Nemico1() override { al_destroy_bitmap(immagine); cout << "distrutto Nemico1" << endl; }
	
	ENEMY_TYPE getTipo() const override { return SCARSO; }
};
#endif // !NEMICO_SCARSO_H

