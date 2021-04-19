#include "Colonne.h"

#include <iostream>
#include <cassert>
using namespace std;

Colonne::Colonne():valide(1)
{
	tabcl = nullptr;
	tailleGrille = 0;
}

Colonne::Colonne(unsigned char numeroColonne, TabCases2DTas& grille)
{
	remplir(numeroColonne, grille);
}

void Colonne::remplir(unsigned char numeroColonne, TabCases2DTas& grille) {
	assert(grille.getDimCol() == grille.getDimLignes()); //Le tbl 2d grille doit �tre carr� sinon c'est pas une grille
	tailleGrille = grille.getDimLignes();

	tabcl = new Case *[tailleGrille];
	for (unsigned char i = 0; i < tailleGrille; ++i) {
			tabcl[i] = grille.getPtr(i, numeroColonne-1);//tab[tab[col * tailleCarre + ligne];
			//cout << "i: " << i << " | " << tab[i] << " = " << tab[i]->getVal() << endl;
	}
}

Colonne::~Colonne()
{
	if(tabcl != nullptr) delete []tabcl;
}

void Colonne::print() const
{
	for (unsigned char l = 0; l < tailleGrille; l++) {
		cout << "l: " << (int)l << "  ||  " << "tabcl[" << (int)l << "]" << " = " << (int)tabcl[l]->getVal() << endl;
	}
}

bool Colonne::isIn(unsigned char val)
{
	for (unsigned char i = 0; i < tailleGrille; i++) {
		if (tabcl[i]->getVal() == val) {
			return true;
		}
		
	}
	return false;
}

