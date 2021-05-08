#include "Carre.h"

using namespace std;


Carre::Carre(): tailleGrille(0), tailleCarre(0)
{
	tabc = nullptr;
}

Carre::Carre(const unsigned char& numeroCarre, const TabCases2DTas& grille)
{
	remplir(numeroCarre, grille);
}

Carre::~Carre()
{
	delete[] tabc;
}

void Carre::remplir(const unsigned char& numeroCarre, const TabCases2DTas& grille) {
	assert(grille.getDimCol() == grille.getDimLignes()); //Le tbl 2d grille doit �tre carr� sinon c'est pas une grille
	tailleGrille = grille.getDimCol();
	tailleCarre = (unsigned char)sqrt(tailleGrille);
	tabc = new Case * [static_cast<unsigned int>(tailleCarre) * static_cast<unsigned int>(tailleCarre)];
	int firstLigne;
	int firstCol;

	firstLigne = ((numeroCarre - 1) / tailleCarre) * tailleCarre;
	firstCol = ((numeroCarre - 1) % (tailleCarre)) * tailleCarre;

	//cout << "carre num: "<< (int)numeroCarre <<" | firstCol " << (int)firstCol << "  |firstLigne " << (int)firstLigne <<" | dimGrille: " <<(int)tailleGrille<< " | dimCarre: "<<(int)tailleCarre<< endl;
	for (int c = 0; c < tailleCarre; ++c) {
		for (int l = 0; l < tailleCarre; ++l) {
			tabc[c * tailleCarre + l] = grille.getPtr(firstLigne + l, firstCol + c);//tab[tab[col * tailleCarre + ligne];
			//cout << "c: " << firstCol + c << " l: " << firstLigne + l << "  :  " << "tabc[" << c * tailleCarre + l << "]" << " = " << (int)tabc[c * tailleCarre + l]->getVal() << endl;
		}
	}
	//cout << endl;
}

bool Carre::isIn(const unsigned char& val)const
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

void Carre::print() const {
	for (unsigned char c = 0; c < tailleCarre; c++) {
		for (unsigned char l = 0; l < tailleCarre; l++) {
			cout << "c: " << (int)c << " l: " << (int)l << "  ||  " << "tabc[" << (int)c * tailleCarre + (int)l << "]" << " = " << (int)tabc[c * tailleCarre + l]->getVal() << endl;
		}
		cout << endl;
	}

}




