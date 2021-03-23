#include "Case.h"
Case::Case() {

    l = 0;
    c = 0;
    carre = 0;
    modifiable = 0;
    val = 0;
}

Case::Case (unsigned char ligne, unsigned char colonne, unsigned char car, unsigned char valeur, bool mod) {

    l=ligne;
    c=colonne;
    carre=car;
    modifiable=mod;
    val = valeur;
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