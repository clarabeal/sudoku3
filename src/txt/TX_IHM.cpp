#include "TXT_IHM.h"

#include <iostream>
#include "../core/GrilleDeJeu.h"
#include <stdlib.h>

using namespace std;

TXT_IHM::TXT_IHM () {

}

TXT_IHM::~TXT_IHM () {

}

void termClear()  // efface le terminal
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void TXT_IHM::afficherGrille () {

}

void TXT_IHM::boucle () {
    
}