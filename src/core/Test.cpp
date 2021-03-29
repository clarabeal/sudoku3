#include "Jeu.h"

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
	
	}*/
	
	

	

	Jeu grille(9);
	grille.init();
	cout << "la grille pleine :" << endl;
	grille.grilleSolution.grille.print();
	cout << "la grille minimale :" << endl;
	grille.grilleJeu.grille.print();
	grille.init();
	cout << "la grille pleine :" << endl;
	grille.grilleSolution.grille.print();
	cout << "la grille minimale :" << endl;
	grille.grilleJeu.grille.print();
	srand((unsigned int)time(NULL));// a mettre dans le main apres

	for (int i = 0; i < 60; i++) {//enleve 60 chiffres au hasard
		grille.grilleSolution.grille.getCase((rand() % 9), (rand() % 9)).setVal(0);
	}
	
	cout << "la grille avec trous :" << endl;

	grille.grilleSolution.grille.print();
	cout << "Nombre de solution differentes:" << endl;
	cout << (int)grille.nombreDeSolutions(grille.grilleJeu) << endl;
	while (1); //pour pas fermer la fenêtre

	return 0;
}