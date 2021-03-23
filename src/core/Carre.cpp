#include "Carre.h";
#include "TabCases2DTas.h";

void Carre::print() const {
	for (int i = 0; i < tailleCarre; i++) {
		for (int j = 0; j < tailleCarre; j++) {
			cout << tab[i * tailleCarre + j].getVal() << "  |  ";
		}
		cout << endl;
	}

}

Carre::Carre(unsigned char numeroCarre, TabCases2DTas grille) :valide(0)
{
	assert(grille.getDimCol() == grille.getDimLignes()); //Le tbl 2d grille doit �tre carr� sinon c'est pas une grille
	tailleGrille = grille.getDimCol();
	tailleCarre = sqrt(tailleGrille);
	tab = new Case[tailleCarre * tailleCarre];
	unsigned char firstLigne;
	unsigned char firstCol;
	
	firstLigne = ((numeroCarre - 1) / tailleCarre) * tailleCarre;
	if (numeroCarre <= tailleCarre) {
		firstCol = ((numeroCarre % (tailleCarre + 1)) * tailleCarre) - 3;
	}
	else {
		firstCol = (((numeroCarre % tailleCarre + 1) + 1) * tailleCarre) - 3;
	}
	cout << "firstCol" << (int)firstCol << "  |firstLigne " << (int)firstLigne<< endl;
	for (int i = 0; i < tailleCarre; i++) {
		for (int j = 0; j < tailleCarre; j++) {
			tab[i * tailleCarre + j] = grille.get(firstCol + i, firstLigne + i);//tab[tab[col * tailleCarre + ligne];
			cout << "i: " << firstCol +  i << " j: " << firstLigne +  j << "  :  " << << endl;
		}
	}
}

Carre::~Carre()
{
	delete[] tab;
}

