#ifndef NEMICO_MEDIO_H
#define NEMICO_MEDIO_H

//nemico di media potenza
#include "NemicoScarso.h"

class Nemico2 : public Nemico
{
public:
	Nemico2() : Nemico(10, 8, 2.00)
	{
		immagine = al_load_bitmap("Nemico2.png");
	}
	~Nemico2() override { al_destroy_bitmap(immagine); cout << "distrutto Nemico2" << endl; }

	ENEMY_TYPE getTipo() const override { return MEDIO; }
};
#endif // ! NEMICO_MEDIO_H

//IMPORTANTE!!
//NON INCLUDERE Nemico.h AMTRIMENTI NON COMPILA
//NON ME NE SO SPIEGARE IL MOTIVOs
