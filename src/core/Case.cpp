#include "Case.h"
Case::Case() {

    modifiable = false;
    val = 0;
    etat = 0;
}

Case::Case(unsigned char valeur, bool mod, unsigned char _etat) {


    modifiable=mod;
    val = valeur;
    etat = _etat;
}

unsigned char Case::getVal () const {
    return val;
}

void Case::setVal (unsigned char nb) {
    val=nb;
}