#include "GrilleDeJeu.h"

using namespace std;
int main() {
	//Test TabCase2DTas
	/*TabCases2DTas tab(9, 9);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			tab.getCase(i, j).setVal(j*9+i+1); //appel de grille.setCase(l,c,nb) aurait permis d'avoir val de l, col et carre
		}
	}

	tab.print();
	for (int i = 1; i < 10; i++) {
		cout << endl << "end tab" << endl << "Test carre ("<<i<<")" << endl;
		Carre c(i, tab);
		c.print();
		cout << endl << "test colonne("<<i<<")" << endl;
		Colonne col(i, tab);
		col.print();

		cout << endl << "test ligne("<<i<<")" << endl;
		Ligne li(i, tab);
		li.print();
	
	}
	*/
	

	

	GrilleDeJeu grille(4);

	grille.genererGrillePleine();

	grille.grilleSolution.grille.print();

	//while (1); //pour pas fermer la fenêtre


	return 0;
}