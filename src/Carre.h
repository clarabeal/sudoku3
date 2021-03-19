#ifndef _CARRE_H
#define _CARRE_H
#include "Case.h";
#include "TabCases2DTas.h";
#include <iostream>;
#include <cassert>;
using namespace std;
#include <math.h>


class Carre
{
public:
	Carre(unsigned char numeroCarre, TabCases2DTas grille);
	~Carre();
	bool valide;
	unsigned char tailleGrille;
	unsigned char tailleCarre;
	void print() const;
	Case *tab;

private:

};



#endif
