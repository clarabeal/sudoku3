#ifndef _SDL_1vs1
#define _SDL_1vs1

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
class sdl1Vs1 {

public :

    sdl1Vs1(unsigned char d);
    sdl1Vs1(unsigned char d, int id, unsigned long int time, Grille& g_sol, Grille& g_orig, Grille& g_jeu, Grille& grilleJ1_, Grille& grilleJ2_, unsigned long int chronoJ1_, unsigned long int chronoJ2_, int nbErrJ1, int nbErrj2, bool stopJ1, bool stopJ2);
    ~sdl1Vs1();
    void placerHitBoxCaseGrille(int x, int y, int largeur, int hauteur);
    void init_im_menu();
    void placementElementsMenu(int x1, int y1, int x2, int y2);
    void effacerElementsMenu(); //supprime les hitboxs du menu pour qu'on ne puisse pas cliquer dessus lorsqu'il n'est pas affiché
    void resetTabHitGrille();

    void sdlAff();
    void sdlAffGrille(Grille& grille, int x1, int y1, int x2, int y2, bool afficher = true);
    void sdlAffSelectionChiffre(int x, int y, int largeur, int hauteur);

    void sdlAffChrono(int x, int y, int largeur, int hauteur, chronometre& chrono, bool full = false);
    void sdlAffMenu(int x, int y, int largeur, int hauteur);
    void affImgInHitBox(Image& img, hitBox& hit);
    void sdlAffFinDePartie();

    void sdlBoucle();
    void sdlAttendreJoueurSuivant();
    void resetTabHitSelectionNombre();
    void init_SDL();
    void init_assets();
private :

    chronometre* ChronoJactif;
    Grille* GrilleJactif;

    Jeu1Vs1 jeu;
    int c_toChange, l_toChange;
    int mousse_x, mousse_y;
    const int dimGrille;

    gestSauvegarde gestionnaireSauvegarde;

    SDL_Window * window;
    SDL_Renderer * renderer;

    TTF_Font * font;
    Image font_im;
    SDL_Color font_color;

    Image im_grille;
    Image im_menu[12];

    Image gris;

    hitBox * tabHitBoxGrille; //tableau 2D stockant les positions des cases de la grille pour gerer les clics
    hitBox tabHitBoxSelectionMenu[12];//tableau 2D stockant les positions des bouton du menu (associe a im_menu)
    hitBox* tabHitBoxSelectionNombre;//tableau 2D stockant les positions des cases de la grille pour gerer les clics
    Image* im_selectionChiffre;


    bool finDePartie;
    bool autoSave;
    void sauvegarder(bool force);
    void sdlAffTexte(string txt, int x, int y, int largeur, int hauteur, SDL_Color& couleur);
    void sdlAffChargement();

};

#endif