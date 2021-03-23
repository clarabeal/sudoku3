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

Case& TabCases2DTas::get(unsigned char ligne, unsigned char col) const
{
	assert(ligne < dimLignes && col < dimColonnes);
	return tab[col * dimLignes + ligne];
}

Case* TabCases2DTas::getPtr(unsigned char ligne, unsigned char col) const
{
	assert(ligne < dimLignes&& col < dimColonnes);
	return &tab[col * dimLignes + ligne];
}

void TabCases2DTas::print() const
{
	for (int i = 0; i < dimLignes; i++) {
		cout << endl << "ligne " << i << ":"<< endl;
		for (int j = 0; j < dimLignes; j++) {
			Case *c = &get(i, j);
			cout << "    Colonne " << j << ": val     : " << (int)c->getVal() << endl;
			cout << "               Ligne   : " << (int)c->getL() << endl;
			cout << "               Colonne : " << (int)c->getC() << endl;
			cout << "               Carre   : " << (int)c->getCarre() << endl<<endl;
		}
		cout << endl;
	}
	cout << endl << endl << endl;
	for (int i = 0; i < dimLignes; i++) {
		for (int j = 0; j < dimLignes; j++) {
			cout << (int)get(i, j).getVal()<< "  |  ";
		}
		cout << endl;
	}


}


