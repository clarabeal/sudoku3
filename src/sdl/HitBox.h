#ifndef _SDL_HitBox
#define _SDL_HitBox

/**
    La classe gerant les hitboxs (zone de clic)
*/
class hitBox {
public:
    hitBox(int x1, int x2, int y1, int y2);
    hitBox();

    int x1, x2, y1, y2;
    bool is_in(const int x, const int y);
    int getLargeur();
    int getHauteur();
};


#endif
