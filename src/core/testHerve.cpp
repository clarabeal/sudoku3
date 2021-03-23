#include "TabCases2DTas.h";
#include "Ligne.h"
#include "Carre.h"
#include "Colonne.h"
using namespace std;
int main() {
	//Test TabCase2DTas
	TabCases2DTas tab(9, 9);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			tab.get(i, j).setVal(j*9+i+1);

		}
	}

	tab.print();
	cout << endl << "end tab" << endl << "Test carre (1)" << endl;
	Carre c(1, tab);
	c.print();


	cout << endl << "test colonne(4)" << endl;
	Colonne col(4, tab);
	col.print();

	cout << endl << "test ligne(3)" << endl;
	Ligne li(3,tab);
	li.print();

	while (1); //pour pas fermer la fenêtre

	return 0;
}