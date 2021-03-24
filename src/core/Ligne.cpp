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
    tabl = new Case * [tailleLigne];
	
    for(unsigned char c=0;c<tailleLigne;c++)
    {
        tabl[c] = grille.getPtr(numeroLigne-1,c); // -1 car numeroLigne de 1 à 9
        cout << "c: " << (int)c << "  :  " << "tabl[" << (int)c << "]" << " = " << (int)tabl[c]->getVal() << endl;
    }
}

Ligne::~Ligne(){
    delete [] tabl;
}

void Ligne::print() const {
	for (unsigned char c = 0; c < tailleLigne; c++) {
		cout << "c: " << (int)c << "  ||  " << "tabl[" << (int)c << "]" << " = " << (int)tabl[c]->getVal() << endl;
	}
}

bool Ligne::isIn(unsigned char val)
{
	for (unsigned char i = 0; i < tailleLigne; i++) {
		if (tabl[i]->getVal() == val) {
			return true;
		}
	}
	return false;
}

