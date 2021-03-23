#ifndef _COLONNE_H
#define _COLONNE_H
#include "Case.h"
#include "TabCases2DTas.h"
#include <iostream>
#include <cassert>
using namespace std;
#include <math.h>


class Colonne
{
public:
	Colonne();
	Colonne(unsigned char numeroColonne, TabCases2DTas& grille);
	~Colonne();
	void remplir(unsigned char numeroColonne, TabCases2DTas& grille);
	bool valide;
	unsigned char tailleGrille;
	void print() const;
	Case **tab;
	bool isIn(unsigned char val);

private:

};



#endif
