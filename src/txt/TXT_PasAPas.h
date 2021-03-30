#ifndef _TXT_PasAPas_H
#define _TXT_PasAPas_H

#include "../core/Jeu.h"

class TXT_PasAPas
{
public:
	TXT_PasAPas(unsigned char d);

	~TXT_PasAPas();
	
	/**
	\brief Boucle du jeu
	*/
	void boucle();

private:
	Jeu jeu;
};


#endif