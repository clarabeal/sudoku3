#ifndef _LIGNE_H
#define _LIGNE_H

#include "Case.h"
#include "TabCases2DTas.h"

class Ligne
{
	public:

	Ligne();
	Ligne(unsigned char numeroLigne, TabCases2DTas& grille);
	void remplir(unsigned char numeroLigne, TabCases2DTas& grille);
	~Ligne();
	bool valide;
	unsigned char tailleGrille;
	unsigned char tailleLigne;
	void print() const;
	Case **tab;
	bool isIn(unsigned char val);

};


#endif
