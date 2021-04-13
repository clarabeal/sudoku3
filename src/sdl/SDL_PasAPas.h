#ifndef _SDL_PasAPas
#define _SDL_PasAPas

#include "../core/Jeu.h"
#include "Image.h"
#include "HitBox.h"
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
class sdlJeuPasAPas {

public:

    sdlJeuPasAPas(unsigned char d);
    ~sdlJeuPasAPas();
    void sdlBoucle();
    void updateDiffCase();
    unsigned char getDiffCase(unsigned char l, unsigned char c, bool diff_type = 1);
    void coordCaseSimple(unsigned char& l, unsigned char& c);
    void printTabDiff() const;
    void retirerCasesFausses();
    void resetTabHitGrille();
    /////////////////Les fonctions d'affichage
    void sdlAff();
    void sdlAffSelectionChiffre(int x, int y, int largeur, int hauteur);
    void sdlAffGrille(Grille& grille, int x1, int y1, int x2, int y2);
    void sdlAffChrono(int x, int y, int largeur, int hauteur);

private:

    Jeu jeu;

    SDL_Window* window;
    SDL_Renderer* renderer;

    TTF_Font* font;
    Image font_im;
    SDL_Color font_color;

    Image im_grille;
    Image* im_selectionChiffre;
    Image bleu;
    Image gris;
    Image rouge;
    Image vert;


    float temps();

    hitBox* tabHitBoxeGrille;//tableau 2D stockant les positions des cases de la grille pour gerer les clics
    hitBox* tabHitBoxeSelectionNombre;//tableau 2D stockant les positions des cases de la grille pour gerer les clics

    const int dimGrille;
    int c_toChange, l_toChange, mousse_x, mousse_y;
    unsigned char* tabDiffCase;


};





#endif