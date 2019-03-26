#ifndef NEMICO_FORTE_H
#define NEMICO_FORTE_H

#include "Nemico2.h"

class Nemico3 : public Nemico
{
public:
	Nemico3() : Nemico(10, 8, 2.00, FORTE)
	{
		immagine = al_load_bitmap("Enemy3.png");
	}
	~Nemico3() override { al_destroy_bitmap(immagine); cout << "distrutto Nemico3" << endl; }
};

#endif // !NEMICO_FORTE_H

