#ifndef _SDL_HitBox
#define _SDL_HitBox

/**
    La classe gerant les hitboxs (zone clicables)
*/
class hitBox {
public:
    /**\brief initialise la hitbox aux coordonnées x1 y1 x2 y2*/
    hitBox(const int& x1, const int& x2, const int& y1, const int& y2);

    hitBox();

    /**\brief initialise la hitbox aux coordonnées x1 y1 x2 y2*/
    bool is_in(const int x, const int y) const;

    /**\brief retourne la largeur de la hitbox */
    int getLargeur() const;
   
    /**\brief retourne la hauteur de la hitbox */
    int getHauteur() const;

    void reset();

    int x1, x2, y1, y2;

};


#endif
