#ifndef _SDL_CLASSIQUE
#define _SDL_CLASSIQUE

#include "../core/Sauvegarde.h"
#include "Image.h"
#include "HitBox.h"
#include "SdlSaisieTxt.h"

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

/**
    La classe gerant le jeu avec un affichage SDL
*/
class sdlJeuClassique {

public :

    sdlJeuClassique(unsigned char d);
    sdlJeuClassique(unsigned char d, int id, unsigned long time, Grille& g_sol, Grille& g_orig, Grille& g_jeu);
    ~sdlJeuClassique();

    void sdlAff();
    void sdlAffGrille(Grille& grille, int x1, int y1, int x2, int y2, bool force = false);
    void sdlAffChrono(int x, int y, int largeur, int hauteur);
    void sdlAffFinDePartie();

    void resetTabHitGrille();

    void sdlBoucle();

private :

	Jeu jeu;
    int c_toChange, l_toChange;
    int mousse_x, mousse_y;
    const int dimGrille;

    SDL_Window * window;
    SDL_Renderer * renderer;

    TTF_Font * font;
    Image font_im;
    SDL_Color font_color;

    Image im_grille;

    Image gris;

    hitBox * tabHitBoxeGrille; //tableau 2D stockant les positions des cases de la grille pour gerer les clics

};

#endif