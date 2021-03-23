#include "Ligne.h"
#include <iostream>
using namespace std;

Ligne::Ligne():valide(1){

}

Ligne::Ligne(unsigned char numeroLigne, TabCases2DTas& grille){

    remplir(numeroLigne, grille);
}

void Ligne::remplir(unsigned char numeroLigne, TabCases2DTas& grille){
    tailleGrille = grille.getDimCol();
    tailleLigne = tailleGrille;
    tab = new Case * [tailleGrille];
	
    for(unsigned char i=0;i<tailleGrille;i++)
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
	for (int i = 0; i < tailleLigne; i++) {
		if (tab[i]->getVal() == val) {
			return true;
		}
	}
	return false;
}

