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
    sdl1Vs1(const unsigned char& d);
    sdl1Vs1(const unsigned char& d, const int& id, const unsigned long int& time, const Grille& g_sol, const Grille& g_orig, const Grille& g_jeu, const Grille& grilleJ1_, const Grille& grilleJ2_, const unsigned long int& chronoJ1_, const unsigned long int& chronoJ2_, const int& nbErrJ1, const int& nbErrj2, const bool& stopJ1, const bool& stopJ2);
    void init_SDL();
    void init_assets();
    void init_im_menu();
    ~sdl1Vs1();


    // ============= FONCTION DE GESTION DES HITBoxS =============== //
    void resetTabHitGrille();
    void resetTabHitSelectionNombre();
    void placementElementsMenu(const int& x1, const int& y1, const int& x2, int y2 = 0);
    void effacerElementsMenu();
    void placerHitBoxCaseGrille(const int& x, const int& y, const int& largeur, const int& hauteur);


    // ============= FONCTION D'AFFICHAGE =============== //
    void sdlAff();
    void sdlAffMenu(const int& x, const int& y, const int& largeur, const int& hauteur);
    void sdlAffSelectionChiffre(const int& x, const int& y, const int& largeur, const int& hauteur);
    void sdlAffGrille(const Grille& grille, const int& x1, const int& y1, const int& x2, const int& y2, const bool& afficher = true);
    void sdlAffChrono(const int& x, const int& y, const int& largeur, const int& hauteur, chronometre& chrono, const bool& full = false);
    void sdlAffFinDePartie();
    void sdlAffChargement();


    // ============= CLASS SDLJEU =============== //

    void sdlAttendreJoueurSuivant();
    void sdlBoucle();
    void sauvegarder(const bool& force = false);


    // ============= FONCTIONS UTILITAIRES =============== //
    void affImgInHitBox(Image& img, const hitBox& hit);
    void sdlAffTexte(const string& txt, const int& x, const int& y, const int& largeur, const int& hauteur, const SDL_Color& couleur);
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