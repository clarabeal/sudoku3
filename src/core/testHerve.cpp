#include "TabCases2DTas.h";
#include "Carre.h"
int main() {
	//Test TabCase2DTas
	TabCases2DTas tab(9, 9);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			tab.get(i, j).setVal(j*9+i+1);

		}
	}
	tab.print();
	cout << endl << "end tab" << endl << "carre" << endl;
	Carre c(2, tab);
	c.print();
	while (1); //pour pas fermer la fenêtre
	return 0;
}