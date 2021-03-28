#include "TXT_Classique.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main () {

	int d;
	//faire verification que ce nombre à une racine
	do {
		cout << "Dimension ?(4, 9 ou 16 une grille de taille superieur serat tres (tres) longue a generer)" << endl;
		cin >> d;
	} while (((float)((float)sqrt(d) - (int)sqrt(d)) != 0.0) || d == 1);
	
	TXT_Classique partieTxt((unsigned char)d);
	
	partieTxt.boucle();

	return 0;
}