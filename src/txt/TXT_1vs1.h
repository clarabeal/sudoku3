#ifndef _TXT_1Vs1_H
#define _TXT_1Vs1_H

#include "Jeu.h"

class TXT_1vs1
{
public:
	TXT_1vs1(unsigned char d);

	~TXT_1vs1();
	
	/**
	\brief Boucle du jeu
	*/
	void boucle();

private:
	Jeu jeu;
};


#endif