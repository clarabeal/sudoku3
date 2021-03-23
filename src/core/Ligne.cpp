#include "Ligne.h"
#include <iostream>
#include <cassert>
using namespace std;

Ligne::Ligne():valide(1){

}

Ligne::Ligne(unsigned char numeroLigne, TabCases2DTas& grille){

    remplir(numeroLigne, grille);
}

void Ligne::remplir(unsigned char numeroLigne, TabCases2DTas& grille){
    assert(grille.getDimCol() == grille.getDimLignes()); //Le tbl 2d grille doit �tre carr� sinon c'est pas une grille
    tailleLigne = grille.getDimCol();
    tab = new Case * [tailleLigne];
	
    for(unsigned char i=0;i<tailleLigne;i++)
    {
        tab[i] = grille.getPtr(numeroLigne-1,i);
        cout << "i: " << (int)i << "  :  " << tab[i] << " = " << (int)tab[i]->getVal() << endl;
    }
}

Ligne::~Ligne(){
    delete [] tab;
}

void Ligne::print() const {
	for (int i = 0; i < tailleLigne; i++) {
		cout << "i: " << (int)i << "  ||  " << tab[i] << " = " << (int)tab[i]->getVal() << endl;
	}
}

bool Ligne::isIn(unsigned char val)
{
	for (unsigned char i = 0; i < tailleLigne; i++) {
		if (tab[i]->getVal() == val) {
			return true;
		}
	}
	return false;
}

