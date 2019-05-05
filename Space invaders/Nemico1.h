#ifndef NEMICO_SCARSO_H
#define NEMICO_SCARSO_H

//nemico più debole di tutti
#include "Nemico.h"

class Nemico1 : public Nemico
{
public:
	Nemico1() : Nemico(5, 5, 2.00,SCARSO)
	{
		immagine = al_load_bitmap("Enemy1.png");
	}
	~Nemico1() override { al_destroy_bitmap(immagine); }
};
#endif // !NEMICO_SCARSO_H

