#ifndef NEMICO_FORTE_H
#define NEMICO_FORTE_H

#include "NemicoMedio.h"

class Nemico3 : public Nemico
{
public:
	Nemico3() : Nemico(10, 8, 2.00)
	{
		immagine = al_load_bitmap("Nemico3.png");
	}
	~Nemico3() override { al_destroy_bitmap(immagine); cout << "distrutto Nemico3" << endl; }

	ENEMY_TYPE getTipo() const override { return FORTE; }
};

#endif // !NEMICO_FORTE_H

