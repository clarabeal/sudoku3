#ifndef _GRILLE_H
#define _GRILLE_H

#include "Case.h"
#include "Ligne.h"
#include "Colonne.h"
#include "Carre.h"

class Grille {

    public :

    Case * grille;
    unsigned int taille;

    Grille (unsigned int t);

    ~Grille();

    bool setCase (unsigned int x, unsigned int y, unsigned int nb);

    private :

    Ligne * lignes;
    Colonne * colonnes;
    Carre * carres ;

};


#endif