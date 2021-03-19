#include "Case.h"
Case::Case() {

    l = 0;
    c = 0;
    carre = 0;
    modifiable = 0;
    val = 0;
}

Case::Case (unsigned int ligne, unsigned int colonne, unsigned int car, unsigned int valeur, bool mod) {

    l=ligne;
    c=colonne;
    carre=car;
    modifiable=mod;
    val = valeur;
}

unsigned int Case::getL () const {
    return l;
}

unsigned int Case::getC () const {
    return c;
}

unsigned int Case::getCarre () const {
    return carre;
}

unsigned int Case::getVal () const {
    return val;
}

void Case::setVal (unsigned int nb) {
    val=nb;
}