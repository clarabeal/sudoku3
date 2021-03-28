#include "TXT_Classique.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main () {

	unsigned char d;

	cout << "Dimension ?" << endl;
	cin >> d;
	
	TXT_Classique partieTxt(d);
	partieTxt.boucle();
	
	return 0;
}