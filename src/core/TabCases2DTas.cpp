#include "TabCases2DTas.h"
#include <iostream>
#include <cassert>
#include <math.h>
using namespace std;

TabCases2DTas::TabCases2DTas(unsigned char dimLignes_, unsigned char dimColonnes_) {
	dimColonnes = dimColonnes_;
	dimLignes = dimLignes_;
	tab = new Case[dimLignes_*dimColonnes_];
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
	//cout << "v: case verouillee, m: case modifiable" << endl;
	unsigned char MaxTailleNombre ;
	unsigned char TailleNombre;

	if (dimColonnes >= 10) {
		MaxTailleNombre = 2;
	}else if (dimColonnes >= 100) {
		MaxTailleNombre =3;
	}
	else {
		MaxTailleNombre = 1;
	}
	for (int l = 0; l < dimLignes; l++) {
		if (dimColonnes >= 10) {
			TailleNombre = 2;
		}
		else if (dimColonnes >= 100) {
			TailleNombre = 3;
		}
		else {
			TailleNombre = 1;
		}
		if ((l) % (unsigned char)sqrt(dimLignes) == 0 && l > 0) {
			cout << " ";
			for (int i = 0; i < (static_cast<int>(dimColonnes) * static_cast<int>(TailleNombre+1) + 2 * static_cast<int>(dimColonnes / sqrt(dimColonnes) - 1)); i++) {
				cout << "-";
			}
			cout << endl;
			
		}
		for (int c = 0; c < dimLignes; c++) {
			if (c%(unsigned char)sqrt(dimColonnes) == 0 && c>0) {
				cout << "| ";
			}
			else if (c == 0) {
				cout << " ";
			}
			unsigned char value = getCase(l, c).getVal();
			if (value >= 10) {
				TailleNombre = MaxTailleNombre - 2;
			}
			else if (value >= 100) {
				TailleNombre = MaxTailleNombre - 3;
			}
			else {
				TailleNombre = MaxTailleNombre - 1;
			}
			if (!(int)getCase(l, c).modifiable) {
			//	cout << "v ";
			}
			else {
			//	cout << "m ";
			}
			if (value == 0) {
				cout << "  ";
				for (int i = 0; i < TailleNombre; i++) {
					cout << " ";
				}
			}
			else {
				
				if (!(int)getCase(l, c).modifiable) {
					
					cout<< (int)value << " ";

					for (int i = 0; i < TailleNombre; i++) {
						cout << " ";
					}
				}
				else {
					cout << (int)value << " ";
					for (int i = 0; i < TailleNombre; i++) {
						cout << " ";
					}
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

void TabCases2DTas::operator = (TabCases2DTas &tab)
{
	for (unsigned char l = 1; l <= dimLignes; l++) {
		for (unsigned char c = 1; c <= dimColonnes; c++) {
			getCase(l - 1, c - 1).setVal(tab.getCase(l - 1, c - 1).getVal());
			getCase(l - 1, c - 1).modifiable = tab.getCase(l - 1, c - 1).modifiable;
			getCase(l - 1, c - 1).etat = tab.getCase(l - 1, c - 1).etat;
		}
	}
}


