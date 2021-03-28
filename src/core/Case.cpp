#include "Case.h"
Case::Case() {

    l = 0;
    c = 0;
    carre = 0;
    modifiable = false;
    val = 0;
    etat = 0;
}

Case::Case (unsigned char ligne, unsigned char colonne, unsigned char car, unsigned char valeur, bool mod, unsigned char _etat) {

    l=ligne;
    c=colonne;
    carre=car;
    modifiable=mod;
    val = valeur;
    etat = _etat;
}

unsigned char Case::getL () const {
    return l;
}

unsigned char Case::getC () const {
    return c;
}

unsigned char Case::getCarre () const {
    return carre;
}

unsigned char Case::getVal () const {
    return val;
}

void Case::setVal (unsigned char nb) {
    val=nb;
}