#ifndef _SDL_CLASSIQUE
#define _SDL_CLASSIQUE
#include "../core/Jeu.h"

#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#elif __linux__
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

//! \brief Pour gerer une image avec SDL2
class Image {

public:
    Image () ;
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void loadFromCurrentSurface (SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);

private:

    SDL_Surface * surface;
    SDL_Texture * texture;
    bool has_changed;

};

/**
    La classe gerant le jeu avec un affichage SDL
*/
class sdlJeu {

public :

    sdlJeu (unsigned char d);
    ~sdlJeu ();
    void sdlAffChrono(int x, int y, int largeur, int hauteur);
    void sdlBoucle ();
    void sdlAff ();

    void sdlAffGrille(Grille& grille, int x1, int y1, int x2, int y2);

private :

	Jeu jeu;

    SDL_Window * window;
    SDL_Renderer * renderer;

    TTF_Font * font;
    Image font_im;
    SDL_Color font_color;

    Image im_grille;

};

#endif