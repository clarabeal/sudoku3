#ifndef _TXT_1Vs1_H
#define _TXT_1Vs1_H

#include "../core/Jeu.h"

class TXT_1vs1
{
public:
	TXT_1vs1(unsigned char d);

	~TXT_1vs1();
	
	/**
	\brief Boucle du jeu
	*/
	void boucle();

	unsigned char menu () const;

private:

	Jeu jeu;

	void termClear() const;
};


#endif