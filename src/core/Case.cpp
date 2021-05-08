#include "Case.h"

Case::Case() {

    modifiable = false;
    val = 0;
    etat = 0;
}

Case::Case(const unsigned char& valeur, const bool& mod, const unsigned char& _etat) {


    modifiable= mod;
    val = valeur;
    etat = _etat;
}

unsigned char Case::getVal () const {
    return val;
}

void Case::setVal (const unsigned char& nb) {
    val=nb;
    if ((int)etat == 3) {
        etat = 0;
    }
}