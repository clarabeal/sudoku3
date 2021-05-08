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

    // ============= FONCTION D'INITIALISATION DE LA PARTIE(CONSTRUCTEURS & CO) + DESTRUCTEUR =============== //
    sdl1Vs1(unsigned char d);
    sdl1Vs1(unsigned char d, int id, unsigned long int time, Grille& g_sol, Grille& g_orig, Grille& g_jeu, Grille& grilleJ1_, Grille& grilleJ2_, unsigned long int chronoJ1_, unsigned long int chronoJ2_, int nbErrJ1, int nbErrj2, bool stopJ1, bool stopJ2);
    void init_SDL();
    void init_assets();
    void init_im_menu();
    ~sdl1Vs1();


    // ============= FONCTION DE GESTION DES HITBoxS =============== //
    void resetTabHitGrille();
    void resetTabHitSelectionNombre();
    void placementElementsMenu(int x1, int y1, int x2, int y2 = 0);
    void effacerElementsMenu();
    void placerHitBoxCaseGrille(int x, int y, int largeur, int hauteur);


    // ============= FONCTION D'AFFICHAGE =============== //
    void sdlAff();
    void sdlAffMenu(int x, int y, int largeur, int hauteur);
    void sdlAffSelectionChiffre(int x, int y, int largeur, int hauteur);
    void sdlAffGrille(Grille& grille, int x1, int y1, int x2, int y2, bool afficher = true);
    void sdlAffChrono(int x, int y, int largeur, int hauteur, chronometre& chrono, bool full = false);
    void sdlAffFinDePartie();
    void sdlAffChargement();


    // ============= CLASS SDLJEU =============== //

    void sdlAttendreJoueurSuivant();
    void sdlBoucle();
    void sauvegarder(bool force = false);


    // ============= FONCTIONS UTILITAIRES =============== //
    void affImgInHitBox(Image& img, hitBox& hit);
    void sdlAffTexte(string txt, int x, int y, int largeur, int hauteur, SDL_Color& couleur);
private :

    //------------------Donn�es core mode pas a pas
    Jeu1Vs1 jeu;
    chronometre* ChronoJactif;
    Grille* GrilleJactif;

    const int dimGrille;
    int c_toChange, l_toChange;
    int mousse_x, mousse_y;
    bool finDePartie;
    bool autoSave;
    //------------------Donne�es/focntions sauvegarde
    gestSauvegarde gestionnaireSauvegarde;

    //------------------Donn�es SDL
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    TTF_Font* font;
    SDL_Color font_color;

    //------------------Image globale
    Image im_grille;
    Image im_menu[12];

    Image* im_selectionChiffre;
    Image bleu;
    Image gris;
    Image rouge;
    Image vert;
    //------------------HitBoxs
    hitBox* tabHitBoxGrille;//tableau 2D stockant les positions des cases de la grille pour gerer les clics
    hitBox* tabHitBoxSelectionNombre;//tableau 2D stockant les positions des cases de la grille pour gerer les clics
    hitBox  tabHitBoxSelectionMenu[12];//tableau 2D stockant les positions des bouton du menu (associe a im_menu)



};

#endif