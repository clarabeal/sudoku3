#include "TabCases2DTas.h"
#include <iostream>
#include <cassert>
using namespace std;

TabCases2DTas::TabCases2DTas(unsigned char dimLignes_, unsigned char dimColonnes_) {
	dimColonnes = dimColonnes_;
	dimLignes = dimLignes_;
	tab = new Case[(int)dimLignes_* (int)dimColonnes_];
}

TabCases2DTas::~TabCases2DTas()
{
	delete[]  tab;
}

unsigned char TabCases2DTas::getDimLignes() const
{
	return dimLignes;
}

unsigned char TabCases2DTas::getDimCol() const
{
	return dimColonnes;
}

Case& TabCases2DTas::getCase(unsigned char ligne, unsigned char col) const
{	//cout << "getCase" << (int)ligne << " " << (int)col << endl;
	assert(ligne < dimLignes);
	assert(col < dimColonnes);

	return tab[col * dimLignes + ligne];
}

Case* TabCases2DTas::getPtr(unsigned char ligne, unsigned char col) const
{
	assert(ligne < dimLignes&& col < dimColonnes);
	return &tab[col * dimLignes + ligne];
}

void TabCases2DTas::print() const
{
	/*for (int i = 0; i < dimLignes; i++) {
		cout << endl << "ligne " << i << ":"<< endl;
		for (int j = 0; j < dimLignes; j++) {
			Case *c = &getCase(i, j);
			cout << "    Colonne " << j << ": val          : " << (int)c->getVal() << endl;
			cout << "               Ligne        : " << (int)c->getL() << endl;
			cout << "               Colonne      : " << (int)c->getC() << endl;
			cout << "               Carre        : " << (int)c->getCarre() << endl<<endl;
			cout << "               modifiable   : " << (int)c->modifiable << endl<<endl;
		}
		cout << endl;
	}*/
	cout << endl << endl << "v: case verouillee, m: case modifiable" << endl;
	for (int i = 0; i < dimLignes; i++) {
		for (int j = 0; j < dimLignes; j++) {
			unsigned char value = getCase(i, j).getVal();
			if (!(int)getCase(i, j).modifiable) {
				cout << "v ";
			}
			else {
				cout << "m ";
			}
			if (value == 0) {
				cout << "  |";
			}
			else {
				if (!(int)getCase(i, j).modifiable) {
					cout<< (int)getCase(i, j).getVal() << " |";
				}
				else {
					cout << (int)getCase(i, j).getVal() << " |";
				}
			}
		}
		cout << endl;
	}
	/*for (int i = 0; i < dimLignes; i++) {   //affiche la grille sur une ligne pour pouvoir la copier sur https://www.dcode.fr/solveur-sudoku
		for (int j = 0; j < dimLignes; j++) {
			Case* c = &getCase(i, j);
			if (c->getVal() == 0) {
				cout << " ";
			}
			else {
				cout << (int)c->getVal();
			}
		}
	}
	cout << endl;*/


}

void TabCases2DTas::vider()
{
	for (unsigned char l = 0; l <dimLignes ; l++) {
		for (unsigned char c = 0; c <dimColonnes; c++) {
			tab[c * dimLignes + l].setVal(0);
			tab[c * dimLignes + l].modifiable = false;
		}
	}
}


