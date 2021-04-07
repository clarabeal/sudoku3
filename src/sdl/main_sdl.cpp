#include "sdlClassique.h"
#include <iostream>
using namespace std;

int main (){

    int d;

    cout << "dim: " << endl;
    cin >> d;

    sdlJeu sJeu(d);
    sJeu.sdlBoucle();
    return 0;
}