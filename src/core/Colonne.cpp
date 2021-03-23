#include "Colonne.h"

#include <iostream>
#include <cassert>
using namespace std;

Colonne::Colonne():valide(1)
{
}

Colonne::Colonne(unsigned char numeroColonne, TabCases2DTas& grille)
{
	remplir(numeroColonne, grille);
}

void Colonne::remplir(unsigned char numeroColonne, TabCases2DTas& grille) {
	assert(grille.getDimCol() == grille.getDimLignes()); //Le tbl 2d grille doit �tre carr� sinon c'est pas une grille
	tab = new Case *[grille.getDimCol()];
	tailleGrille = grille.getDimLignes();
	for (unsigned char i = 0; i < tailleGrille; ++i) {
			tab[i] = grille.getPtr(i, numeroColonne-1);//tab[tab[col * tailleCarre + ligne];
			//cout << "i: " << i << " | " << tab[i] << " = " << tab[i]->getVal() << endl;
	}
}

Colonne::~Colonne()
{
	delete []tab;
}

void Colonne::print() const
{

	for (unsigned char i = 0; i < tailleGrille; i++) {
			cout << "i: " << (int)i << "  ||  " << tab[i] << " = " << (int)tab[i]->getVal() << endl;
	}
}

bool Colonne::isIn(unsigned char val)
{
	for (unsigned char i = 0; i < tailleGrille; i++) {
		if (tab[i]->getVal() == val) {
			return true;
		}
		
	}
	return false;
}

