#include "TabCases2DTas.h";
#include "Carre.h"
#include "Colonne.h"
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



	while (1);
	return 0;
}