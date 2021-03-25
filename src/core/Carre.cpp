#include "Carre.h"

using namespace std;

void Carre::print() const {
	for (unsigned char c = 0; c < tailleCarre; c++) {
		for (unsigned char l = 0; l < tailleCarre; l++) {
			cout << "c: " << (int)c << " l: " << (int)l << "  ||  " << "tabc[" << (int)c * tailleCarre + (int)l << "]" << " = " << (int)tabc[c * tailleCarre + l]->getVal() << endl;
		}
		cout << endl;
	}

}

bool Carre::isIn(unsigned char val)
{

	for (int i = 0; i < tailleCarre; i++) {
		for (int j = 0; j < tailleCarre; j++) {
			if (tabc[i * tailleCarre + j]->getVal() == val) {
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
	assert(grille.getDimCol() == grille.getDimLignes()); //Le tbl 2d grille doit �tre carr� sinon c'est pas une grille
	tailleGrille = grille.getDimCol();
	tailleCarre = sqrt(tailleGrille);
	tabc = new Case * [tailleCarre * tailleCarre];
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
	for (int c = 0; c < tailleCarre; ++c) {
		for (int l = 0; l < tailleCarre; ++l) {
			tabc[c * tailleCarre + l] = grille.getPtr(firstLigne + l, firstCol + c);//tab[tab[col * tailleCarre + ligne];
			cout << "c: " << firstCol + c << " l: " << firstLigne + l << "  :  " << "tabc[" << c * tailleCarre + l << "]" << " = " << (int)tabc[c * tailleCarre + l]->getVal() << endl;
		}
	}
	cout << endl;
}

Carre::~Carre()
{
	delete[] tabc;
}


