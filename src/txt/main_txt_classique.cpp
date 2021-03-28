#include "TXT_Classique.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main () {

	int d;
	//faire verification que ce nombre à une racine
	cout << "Dimension ?" << endl;
	cin >> d;
	
	TXT_Classique partieTxt((unsigned char)d);
	
	partieTxt.boucle();

	return 0;
}