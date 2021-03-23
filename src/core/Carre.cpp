#include "Carre.h"
#include "TabCases2DTas.h"

using namespace std;

void Carre::print() const {
	for (int i = 0; i < tailleCarre; i++) {
		for (int j = 0; j < tailleCarre; j++) {
			cout << "i: " << i << " j: " << j << "  ||  " << tab[i * tailleCarre + j] << " = " << tab[i * tailleCarre + j]->getVal() << endl;
		}
		cout << endl;
	}

}

bool Carre::isIn(unsigned char val)
{

	for (int i = 0; i < tailleCarre; i++) {
		for (int j = 0; j < tailleCarre; j++) {
			if (tab[i * tailleCarre + j]->getVal() == val) {
				return true;
			}
		}
	}
	return false;
}

Carre::Carre():valide(1)
{
	
}

Carre::Carre(unsigned char numeroCarre, TabCases2DTas& grille)
{
	remplir(numeroCarre, grille);
}

void Carre::remplir(unsigned char numeroCarre, TabCases2DTas& grille) {
	assert(grille.getDimCol() == grille.getDimLignes()); //Le tbl 2d grille doit être carré sinon c'est pas une grille
	tailleGrille = grille.getDimCol();
	tailleCarre = sqrt(tailleGrille);
	tab = new Case * [tailleCarre * tailleCarre];
	int firstLigne;
	int firstCol;

	firstLigne = ((numeroCarre - 1) / tailleCarre) * tailleCarre;
	if (numeroCarre <= tailleCarre) {
		firstCol = ((numeroCarre % (tailleCarre + 1)) * tailleCarre) - 3;
	}
	else {
		firstCol = (((numeroCarre % tailleCarre + 1) + 1) * tailleCarre) - 3;
	}
	cout << "firstCol " << (int)firstCol << "  |firstLigne " << (int)firstLigne << endl;
	for (int i = 0; i < tailleCarre; ++i) {
		for (int j = 0; j < tailleCarre; ++j) {
			tab[i * tailleCarre + j] = grille.getPtr(firstLigne + j, firstCol + i);//tab[tab[col * tailleCarre + ligne];
			cout << "i: " << firstCol + i << " j: " << firstLigne + j << "  :  " << tab[i * tailleCarre + j] << " = " << tab[i * tailleCarre + j]->getVal() << endl;
		}
	}
}

Carre::~Carre()
{
	delete[] tab;
}


