#include "sdlClassique.h"
#include <iostream>
using namespace std;

int main (int argc, char* argv[]){

    int d;

   cout << "dim: " << endl;
   cin >> d;

    sdlJeu sJeu(d);
    sJeu.sdlBoucle();
    return 0;
}