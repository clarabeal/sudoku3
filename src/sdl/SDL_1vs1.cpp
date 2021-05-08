#include "SDL_1vs1.h"

#include <algorithm>  //pour la fonciton max(a, b)
#include <iostream>
#include <string.h>
using namespace std;

#define WIDTH 1024
#define HEIGHT 576


// ============= FONCTION D'INITIALISATION DE LA PARTIE(CONSTRUCTEURS & CO) + DESTRUCTEUR =============== //
sdl1Vs1::sdl1Vs1(const unsigned char& d) : jeu(d), gestionnaireSauvegarde("data/saves/", "../data/saves/"), dimGrille(d), autoSave(false) {
    init_SDL();
    init_im_menu();
    init_assets();

    tabHitBoxGrille = new hitBox[d * d];
    tabHitBoxSelectionNombre = new hitBox[d + 1];

    l_toChange = 0;
    c_toChange = 0;

    mousse_x = 0;
    mousse_y = 0;

    finDePartie = false;

    ChronoJactif = NULL;
    GrilleJactif = NULL;
}

sdl1Vs1::sdl1Vs1(const unsigned char& d, const int& id, const unsigned long int& time, const Grille& g_sol, const Grille& g_orig, const Grille& g_jeu, const Grille& grilleJ1_, const Grille& grilleJ2_, const unsigned long int& chronoJ1_, const unsigned long int& chronoJ2_, const int& nbErrJ1, const int& nbErrJ2, const bool& stopJ1, const bool& stopJ2) : jeu(d, id, time, g_sol, g_orig, g_jeu, grilleJ1_, grilleJ2_, chronoJ1_, chronoJ2_, nbErrJ1, nbErrJ2, stopJ1, stopJ2), gestionnaireSauvegarde("data/saves/", "../data/saves/"), dimGrille(d), autoSave(true) {
    init_SDL();
    init_im_menu();
    init_assets();

    tabHitBoxGrille = new hitBox[d * d];
    tabHitBoxSelectionNombre = new hitBox[d + 1];

    l_toChange = 0;
    c_toChange = 0;

    mousse_x = 0;
    mousse_y = 0;

    finDePartie = false;

    ChronoJactif = NULL;
    GrilleJactif = NULL;
}

void sdl1Vs1::init_SDL() 
{
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    font_color.r = 0;
    font_color.g = 0;
    font_color.b = 0;
    font = TTF_OpenFont("data/fonts/BungeeShade-Regular.ttf", 120);

    if (!font) {
        font = TTF_OpenFont("../data/fonts/BungeeShade-Regular.ttf", 120);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //creation de la fenetre : 
    window = SDL_CreateWindow("Sudoku 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //creation du rendu : 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        cout << "Erreur lors de la creation du renderer : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
}

void sdl1Vs1::init_assets()//identique
{
    //creation des images :
    if (dimGrille == 4) {
        im_grille.loadFromFile("data/assets/grilles/4x4color.jpg", renderer);
    }
    else if (dimGrille == 9) {
        im_grille.loadFromFile("data/assets/grilles/9x9color.jpg", renderer);
    }
    else if (dimGrille == 16) {
        im_grille.loadFromFile("data/assets/grilles/16x16color.jpg", renderer);
    }

    im_selectionChiffre = new Image[dimGrille + 1];

    char buffConversion[3];
    for (int i = 0; i < dimGrille + 1; i++) {
        if (i == 0) {
            string path = "data/assets/selectionChiffres/";
            if (dimGrille < 10) {
                buffConversion[0] = (int)dimGrille + '0';
                buffConversion[1] = '\0';
            }
            else {
                buffConversion[0] = '1';
                buffConversion[1] = (int)dimGrille - 10 + '0';
                buffConversion[2] = '\0';
            }


            path += buffConversion;
            path += "/chiffres";
            path += "_Away.png";
            im_selectionChiffre[i].loadFromFile(path.c_str(), renderer);

        }
        else {
            string path = "data/assets/selectionChiffres/";
            if (dimGrille < 10) {
                buffConversion[0] = (int)dimGrille + '0';
                buffConversion[1] = '\0';
            }
            else {
                buffConversion[0] = '1';
                buffConversion[1] = (int)dimGrille - 10 + '0';
                buffConversion[2] = '\0';
            }
            path += buffConversion;
            path += "/chiffres";
            if (i < 10) {
                buffConversion[0] = i + '0';
                buffConversion[1] = '\0';
            }
            else {
                buffConversion[0] = '1';
                buffConversion[1] = i - 10 + '0';
                buffConversion[2] = '\0';
            }
            path += buffConversion;
            path += "_Over.png";
            im_selectionChiffre[i].loadFromFile(path.c_str(), renderer);
        }
    }//Chargement des images pour la selection du chiffre a placer

    gris.loadFromFile("data/assets/couleursDeFond/Gris.png", renderer);



}

void sdl1Vs1::init_im_menu() {
    im_menu[0].loadFromFile("data/assets/menu/1vs1/Recommencer_MousseAway.png", renderer);
    im_menu[1].loadFromFile("data/assets/menu/1vs1/Recommencer_MousseOver.png", renderer);
    im_menu[2].loadFromFile("data/assets/menu/1vs1/Start_MousseAway.png", renderer);
    im_menu[3].loadFromFile("data/assets/menu/1vs1/Start_MousseOver.png", renderer);
    im_menu[4].loadFromFile("data/assets/menu/1vs1/Pause_MousseAway.png", renderer);
    im_menu[5].loadFromFile("data/assets/menu/1vs1/Pause_MousseOver.png", renderer);
    im_menu[6].loadFromFile("data/assets/menu/1vs1/Sauvegarder_MousseAway.png", renderer);
    im_menu[7].loadFromFile("data/assets/menu/1vs1/Sauvegarder_MousseOver.png", renderer);
    im_menu[8].loadFromFile("data/assets/menu/1vs1/ActSauvegardeAutoActive_MousseAway.png", renderer);
    im_menu[9].loadFromFile("data/assets/menu/1vs1/ActSauvegardeAutoActive_MousseOver.png", renderer);
    im_menu[10].loadFromFile("data/assets/menu/1vs1/DesactSauvegardeAutoActive_MousseAway.png", renderer);
    im_menu[11].loadFromFile("data/assets/menu/1vs1/DesactSauvegardeAutoActive_MousseOver.png", renderer);
}

sdl1Vs1::~sdl1Vs1() {

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete[] tabHitBoxGrille;

}

// ============= FONCTION DE GESTION DES HITBoxS =============== //
void sdl1Vs1::placementElementsMenu(const int& x1, const int& y1, const int& x2, int y2) {
    effacerElementsMenu();
    const int nb_element = 9;

    if (y2 == 0) {
        y2 = (x2 - x1) * nb_element / 11;//on respecte le format par defaut pour que la police ne soit pas deformée
    }
    int y1courant = y1;
    int y2courant = 0;

    //---------> On positionne la hitbox de l'option Recommencer
    y2courant = y1courant + y2 / nb_element;
    tabHitBoxSelectionMenu[0].x1 = x1;
    tabHitBoxSelectionMenu[0].x2 = x2;
    tabHitBoxSelectionMenu[0].y1 = y1courant;
    tabHitBoxSelectionMenu[0].y2 = y2courant;
    tabHitBoxSelectionMenu[1].x1 = x1;
    tabHitBoxSelectionMenu[1].x2 = x2;
    tabHitBoxSelectionMenu[1].y1 = y1courant;
    tabHitBoxSelectionMenu[1].y2 = y2courant;
 
    //---------> On positionne les hitboxs des btn start/pause
    y1courant = y2courant;
    y2courant = y1courant + y2 / nb_element;

    if (ChronoJactif->estEnPause()) {
        tabHitBoxSelectionMenu[2].x1 = x1;
        tabHitBoxSelectionMenu[2].y1 = y1courant;
        tabHitBoxSelectionMenu[2].x2 = x2;
        tabHitBoxSelectionMenu[2].y2 = y2courant;
        tabHitBoxSelectionMenu[3].x1 = x1;
        tabHitBoxSelectionMenu[3].y1 = y1courant;
        tabHitBoxSelectionMenu[3].x2 = x2;
        tabHitBoxSelectionMenu[3].y2 = y2courant;
        tabHitBoxSelectionMenu[4].reset();
        tabHitBoxSelectionMenu[5].reset();

    }
    else {
        tabHitBoxSelectionMenu[4].x1 = x1;
        tabHitBoxSelectionMenu[4].y1 = y1courant;
        tabHitBoxSelectionMenu[4].x2 = x2;
        tabHitBoxSelectionMenu[4].y2 = y2courant;
        tabHitBoxSelectionMenu[5].x1 = x1;
        tabHitBoxSelectionMenu[5].y1 = y1courant;
        tabHitBoxSelectionMenu[5].x2 = x2;
        tabHitBoxSelectionMenu[5].y2 = y2courant;
        tabHitBoxSelectionMenu[2].reset();
        tabHitBoxSelectionMenu[3].reset();
    }

    //---------> On positionne les hitboxs des btn de sauvegarde
    y1courant = y2courant;
    y2courant = y1courant + y2 / nb_element;
    if (!autoSave && jeu.sauvegardeId != 0) { // si la sauvegarde automatique est desactivée et que la partie a deja ete sauvegardé au moins une fois

        tabHitBoxSelectionMenu[8].x1 = x1;  //on place les hitBox des btn pour activer la sauvegarde auto (2hitbox une pour l'image avec la souris dessus et une pour limage quand la souris n'est pas la)
        tabHitBoxSelectionMenu[8].x2 = x2;
        tabHitBoxSelectionMenu[8].y1 = y1courant;
        tabHitBoxSelectionMenu[8].y2 = y2courant;

        tabHitBoxSelectionMenu[9].x1 = x1;
        tabHitBoxSelectionMenu[9].x2 = x2;
        tabHitBoxSelectionMenu[9].y1 = y1courant;
        tabHitBoxSelectionMenu[9].y2 = y2courant;

        tabHitBoxSelectionMenu[10].reset(); // on enleve les hitbox des pour desactiver la sauveagrde auto
        tabHitBoxSelectionMenu[11].reset();
        y1courant = y2courant;
        y2courant = y1courant + y2 / nb_element;
    }
    else if (autoSave && jeu.sauvegardeId != 0) {// si la sauvegarde automatique est activée et que la partie a deja ete sauvegardé au moins une fois
        tabHitBoxSelectionMenu[10].x1 = x1;
        tabHitBoxSelectionMenu[10].x2 = x2;
        tabHitBoxSelectionMenu[10].y1 = y1courant;
        tabHitBoxSelectionMenu[10].y2 = y2courant;

        tabHitBoxSelectionMenu[11].x1 = x1;
        tabHitBoxSelectionMenu[11].x2 = x2;
        tabHitBoxSelectionMenu[11].y1 = y1courant;
        tabHitBoxSelectionMenu[11].y2 = y2courant;

        tabHitBoxSelectionMenu[8].reset();
        tabHitBoxSelectionMenu[9].reset();

        y1courant = y2courant;
        y2courant = y1courant + y2 / nb_element;
    }

    if (jeu.sauvegardeId == 0 || !autoSave) {//on place le btn sauveagrder
        tabHitBoxSelectionMenu[6].x1 = x1;
        tabHitBoxSelectionMenu[6].x2 = x2;
        tabHitBoxSelectionMenu[6].y1 = y1courant;
        tabHitBoxSelectionMenu[6].y2 = y2courant;

        tabHitBoxSelectionMenu[7].x1 = x1;
        tabHitBoxSelectionMenu[7].x2 = x2;
        tabHitBoxSelectionMenu[7].y1 = y1courant;
        tabHitBoxSelectionMenu[7].y2 = y2courant;
    }
}

void sdl1Vs1::effacerElementsMenu(){
    for (int i = 0; i < 8; i++) {
        tabHitBoxSelectionMenu[i].reset();
    }
}

void sdl1Vs1::placerHitBoxCaseGrille(const int& x, const int& y, const int& largeur, const int& hauteur) {//supprime les hitboxs du menu pour qu'on ne puisse pas cliquer dessus lorsqu'il n'est pas affiché(indentique)
    int largeurCase = largeur / dimGrille;
    int hauteurCase = hauteur / dimGrille;
    for (int l = 0; l < dimGrille; l++) {
        for (int c = 0; c < dimGrille; c++) {
            tabHitBoxGrille[l * dimGrille + c].x1 = x + c * largeurCase;
            tabHitBoxGrille[l * dimGrille + c].y1 = y + l * hauteurCase;
            tabHitBoxGrille[l * dimGrille + c].x2 = x + c * largeurCase + largeurCase;
            tabHitBoxGrille[l * dimGrille + c].y2 = y + l * hauteurCase + hauteurCase;
        }
    }
}

void sdl1Vs1::resetTabHitSelectionNombre() {
    for (int i = 0; i < dimGrille; i++) {
        tabHitBoxSelectionNombre[i].x1 = 0;
        tabHitBoxSelectionNombre[i].y1 = 0;
        tabHitBoxSelectionNombre[i].x2 = 0;
        tabHitBoxSelectionNombre[i].y2 = 0;
    }
}

void sdl1Vs1::resetTabHitGrille() {
    for (int l = 0; l < dimGrille; l++) {
        for (int c = 0; c < dimGrille; c++) {
            tabHitBoxGrille[l * dimGrille + c].reset();
        }
    }
}

// ============= FONCTION D'AFFICHAGE =============== //

void sdl1Vs1::sdlAff(){

    //supprime les hitboxs de l'affichage precedent
    resetTabHitGrille();
    resetTabHitSelectionNombre();

    //Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Affiche la grille
    int hauteurGrille = HEIGHT * 80 / 100;
    int xGrille = HEIGHT * 10 / 100;
    int yGrille = WIDTH * 5 / 100;

    sdlAffGrille(jeu.grilleJeu, xGrille, yGrille, hauteurGrille, hauteurGrille, !ChronoJactif->estEnPause());

    sdlAffChrono(xGrille + hauteurGrille + WIDTH * 2 / 100, yGrille, (WIDTH - hauteurGrille - xGrille) * 80 / 100, ((WIDTH - hauteurGrille - xGrille) * 80 / 100) * 1 / 10, *ChronoJactif);
    int y_pos = yGrille + (WIDTH - hauteurGrille - xGrille) * 80 / 100 * 1 / 10 + HEIGHT * 5 / 100;
    if (jeu.stopBoucleJ1) {
        sdlAffChrono(xGrille + hauteurGrille + WIDTH * 2 / 100, yGrille + ((WIDTH - hauteurGrille - xGrille) * 80 / 100) * 1 / 10, (WIDTH - hauteurGrille - xGrille) * 80 / 100 * 50/100 , ((WIDTH - hauteurGrille - xGrille) * 80 / 100) * 1 / 10 * 50/100, jeu.chronoJ1);
        y_pos += ((WIDTH - hauteurGrille - xGrille) * 80 / 100) * 1 / 10 * 50 / 100;
    }
    // Si une valeur doit etre entree on affiche la selection 
    int selectHauteur = 0;

    if (l_toChange != 0) {

        selectHauteur = 40;
        sdlAffSelectionChiffre(xGrille + hauteurGrille + WIDTH * 2 / 100 + 20, y_pos, dimGrille * selectHauteur, selectHauteur);
    }
    y_pos += selectHauteur;
    sdlAffMenu(xGrille + hauteurGrille + WIDTH * 2 / 100 + 20, y_pos, hauteurGrille * 80 / 100, hauteurGrille * 80 / 100);


}

void sdl1Vs1::sdlAffMenu(const int& x, const int& y, const int& largeur, const int& hauteur) {
    placementElementsMenu(x, y, x + largeur, 0);
    for (int i = 0; i < 11; i += 2) {
        if (!tabHitBoxSelectionMenu[i].is_in(mousse_x, mousse_y)) {
            affImgInHitBox(im_menu[i], tabHitBoxSelectionMenu[i]);
        }
        else {
            affImgInHitBox(im_menu[i + 1], tabHitBoxSelectionMenu[i + 1]);
        }
    }
}

void sdl1Vs1::sdlAffSelectionChiffre(const int& x, const int& y, const int& largeur, const int& hauteur) {
    for (int i = 0; i < dimGrille; i++) {
        tabHitBoxSelectionNombre[i].x1 = x + (i * largeur / dimGrille);
        tabHitBoxSelectionNombre[i].x2 = tabHitBoxSelectionNombre[i].x1 + (largeur / dimGrille);
        tabHitBoxSelectionNombre[i].y1 = y;
        tabHitBoxSelectionNombre[i].y2 = tabHitBoxSelectionNombre[i].y1 + hauteur;
    }
    for (int i = 0; i < dimGrille; i++) {
        if (tabHitBoxSelectionNombre[i].is_in(mousse_x, mousse_y)) {
            im_selectionChiffre[i + 1].draw(renderer, x, y, largeur, hauteur);
            return;
        }

    }
    im_selectionChiffre[0].draw(renderer, x, y, largeur, hauteur);




}

void sdl1Vs1::sdlAffGrille(const Grille& grille, const int& x, const int& y, const int& largeur, const int& hauteur, const bool& afficher) {
    assert((int)grille.dim == dimGrille);
    im_grille.draw(renderer, x, y, largeur, hauteur);
    placerHitBoxCaseGrille(x, y, largeur, hauteur);
    if (afficher) {
        SDL_Color couleur = { 0, 0, 0 };
        SDL_Surface* texte = nullptr;
        SDL_Rect position;
        SDL_Texture* texte_texture = nullptr;    //Create Texture pointeur

        int dimGrille = (int)grille.dim;
        int largeurCase = largeur / dimGrille;
        int hauteurCase = hauteur / dimGrille;
        char buffConversion[3];

        for (int l = 0; l < dimGrille; l++) {
            for (int c = 0; c < dimGrille; c++) {

                if (l_toChange != 0) {// si une case est en cours de modification, on met un fond gris sur celle ci
                    gris.draw(renderer, x + (c_toChange - 1) * largeurCase, y + (l_toChange - 1) * hauteurCase, hauteurCase, largeurCase);
                }

                if (grille.grille.getCase(l, c).getVal() != 0) {
                    if (!grille.grille.getCase(l, c).modifiable && grille.grille.getCase(l, c).etat == 0) //si il s'agit d'une case non modifiable, on la grise
                    {
                        couleur.r = 100;
                        couleur.g = 100;
                        couleur.b = 100;
                    }
                    SDL_Rect position;
                    if (dimGrille > 9) {
                        if (grille.grille.getCase(l, c).getVal() < 10) {// si il n'y a qu'un chiffre
                            position.x = x + c * largeurCase + largeurCase / 4;
                            position.y = y + l * hauteurCase + hauteurCase / 4;
                            position.w = 3 * (float)(largeurCase / 4);
                            position.h = 3 * (float)(hauteurCase / 4);
                        }
                        else {// si il y a deux chiffres
                            position.x = x + c * largeurCase + largeurCase / 12;
                            position.y = y + l * hauteurCase + hauteurCase / 4;
                            position.w = 10 * (float)(largeurCase / 12);
                            position.h = 3 * (float)(hauteurCase / 4);
                        }
                    }
                    else {
                        position.x = x + c * largeurCase + largeurCase / 4;
                        position.y = y + l * hauteurCase + hauteurCase / 4;
                        position.w = 3 * (float)(largeurCase / 4);
                        position.h = 3 * (float)(hauteurCase / 4);
                    }
                    sdlAffTexte(to_string(grille.grille.getCase(l, c).getVal()), position.x, position.y, position.w, position.h, couleur);
                }
                couleur.r = 0;
                couleur.g = 0;
                couleur.b = 0;
            }
        }
    }
}

void sdl1Vs1::sdlAffChrono(const int& x, const int& y, const int& largeur, const int& hauteur, chronometre& chrono, const bool& full) {

    chrono.update();// a enlever apres les tests, ne doit pas être la
    SDL_Color couleur = { 0, 0, 0 };
    if (chrono.estEnPause() && !full) {
        couleur.r = 255;
        couleur.g = 0;
        couleur.b = 0;
    }
    else {
        couleur.r = 0;
        couleur.g = 0;
        couleur.b = 0;
    }

    if (full) {
        string str = to_string(chrono.getTimeInHours()) + "h " + to_string(chrono.getTimeInMin() % 60) + "m " + to_string(chrono.getTimeInSec() % 60) + "s " + to_string(chrono.getTimeInMSec() % 1000) + "ms";
        sdlAffTexte(str, x, y, largeur, hauteur, couleur);
    }
    else {
        string str = to_string(chrono.getTimeInHours()) + "h " + to_string(chrono.getTimeInMin() % 60) + "m " + to_string(chrono.getTimeInSec() % 60) + "s";
        sdlAffTexte(str, x, y, largeur, hauteur, couleur);
    }

}

void sdl1Vs1::sdlAffFinDePartie() {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Affiche des grilles
    int hauteurGrilles = HEIGHT * 80 / 100;
    int xGrille = (WIDTH / 2) - hauteurGrilles / 2;;
    int yGrille = HEIGHT * 10 / 100;

    int laregeurChronos = (WIDTH - hauteurGrilles) /2;
    int hauteurChronos = 100*laregeurChronos/(60*15);
    int yChrono = (HEIGHT/2) - (hauteurChronos/2);

    int xChronoj1 = 0;
    int xChronoj2 = xGrille + hauteurGrilles;


    SDL_Color couleur = { 0, 0, 0 };
    SDL_Surface* texte = nullptr;
    SDL_Rect position;
    SDL_Texture* texte_texture = nullptr;    //Create Texture pointer
    if (jeu.chronoJ1.getTimeInMSec() < jeu.chronoJ2.getTimeInMSec()) {
        couleur.r = 0;
        couleur.g = 255;
    }
    else {
        couleur.r = 255;
        couleur.g = 0;
    }
    position.w = laregeurChronos;
    position.h = 100 * laregeurChronos / (60 * 9);
    position.x = xChronoj1;
    position.y = yChrono - position.h - hauteurChronos;
    char txtj1[10] = "Joueur 1:";
    texte = TTF_RenderText_Blended(font, txtj1, couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    SDL_RenderCopy(renderer, texte_texture, nullptr, &position);
    SDL_DestroyTexture(texte_texture);

    if (jeu.chronoJ1.getTimeInMSec() > jeu.chronoJ2.getTimeInMSec()) {
        couleur.r = 0;
        couleur.g = 255;
    }
    else {
        couleur.r = 255;
        couleur.g = 0;
    }
    position.x = xChronoj2;
    char txtj2[10] = "Joueur 2:";
    texte = TTF_RenderText_Blended(font, txtj2, couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    SDL_RenderCopy(renderer, texte_texture, nullptr, &position);
    SDL_DestroyTexture(texte_texture);
    sdlAffGrille(jeu.grilleJ1, xGrille, yGrille, hauteurGrilles, hauteurGrilles, true);
    sdlAffChrono(xChronoj1, yChrono, laregeurChronos, hauteurChronos, jeu.chronoJ1, true);
    sdlAffChrono(xChronoj2, yChrono, laregeurChronos, hauteurChronos, jeu.chronoJ2, true);


}

void sdl1Vs1::sdlAffChargement()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    string txt_sdlAffTxt = "Generation de la grille";
    sdlAffTexte(txt_sdlAffTxt, 0, 0, WIDTH / 2, ((WIDTH / 2) * 1.6) / txt_sdlAffTxt.length(), font_color);
    SDL_RenderPresent(renderer);


}

// ============= CLASS SDLJEU =============== //

void sdl1Vs1::sdlAttendreJoueurSuivant()
{
    SDL_Event event;
    bool valide = false;
    while (SDL_PollEvent(&event) || !valide)
    {
        if (event.type == SDL_KEYDOWN)
        {
            valide = true;
        }
        resetTabHitGrille();

        //Remplir l'écran de blanc
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Color couleur = { 0, 0, 0 };
        SDL_Surface* texte = nullptr;
        SDL_Rect position;
        SDL_Texture* texte_texture = nullptr;    //Create Texture pointer
        position.w = WIDTH * 95 / 100;
        position.h = 100 * position.w / (60 * 63);
        position.x = (WIDTH - WIDTH * 95 / 100) / 2;
        position.y = HEIGHT / 2 - position.h / 2;
        char txtj1[63] = "Appuyer sur une touche pour demarrer/passer au joueur suivant";
        texte = TTF_RenderText_Blended(font, txtj1, couleur);
        texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
        SDL_FreeSurface(texte);
        SDL_RenderCopy(renderer, texte_texture, nullptr, &position);
        SDL_DestroyTexture(texte_texture);
        SDL_RenderPresent(renderer);

    }
}

void sdl1Vs1::sdlBoucle() {
    sdlAffChargement();
    bool gameRunning = true;
    SDL_Event event;

    if (!jeu.initDone) {
        jeu.init();
        jeu.initDone = true;
        jeu.chrono.start();
        jeu.chronoJ1.reset();
        jeu.chronoJ2.reset();
        jeu.chronoJ1.pause();
        jeu.chronoJ2.pause();
    }
    ChronoJactif = NULL;
    GrilleJactif = NULL;
    if (!jeu.stopBoucleJ1) {
        GrilleJactif = &jeu.grilleJ1;
        ChronoJactif = &jeu.chronoJ1;
        ChronoJactif->start();
    }
    else {
        GrilleJactif = &jeu.grilleJ2;
        ChronoJactif = &jeu.chronoJ2;
        ChronoJactif->start();
    }

    sdlAttendreJoueurSuivant();
    while (gameRunning) {
        if (!finDePartie) {
            sdlAff();
        }
        else {
            sdlAffFinDePartie();
        }

        while (SDL_PollEvent(&event))
        {
            //----Quitte la partie si croix
            if (event.type == SDL_QUIT) {
                sauvegarder(false);
                gameRunning = false;
            }
            //----On enregistre la postion de la souris
            if (event.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&mousse_x, &mousse_y);
            }

            //----On fait les actions liées au differentes touches du clavier si elles sont pressées
            if (event.type == SDL_KEYDOWN)
            {
                sauvegarder(false);

                switch (event.key.keysym.sym)
                {
                case SDLK_q: //quitter
                    gameRunning = false;
                    break;

                case SDLK_r: //recommencer sur la meme grille
                    jeu.grilleJeu.grille = jeu.grilleOriginale.grille;
                    break;

                case SDLK_n: //nouvelle grille
                    jeu.init();
                    break;

                case SDLK_p: //pause
                    ChronoJactif->pause();
                    break;

                case SDLK_s: //start
                    ChronoJactif->start();
                    break;

                default: //remplir une case

                    if (c_toChange != 0) {
                        if (event.key.keysym.sym == SDLK_0 || event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_2 || event.key.keysym.sym == SDLK_3 || event.key.keysym.sym == SDLK_4 || event.key.keysym.sym == SDLK_5 || event.key.keysym.sym == SDLK_6 || event.key.keysym.sym == SDLK_7 || event.key.keysym.sym == SDLK_8 || event.key.keysym.sym == SDLK_9) {

                            SaisieTextPopUp popUp(font);
                            cout << to_string(int(event.key.keysym.sym - '0')) << endl;
                            string valeurSaisie = popUp.getTexteSaisie(500, 100, "Saisie valeur", to_string(int(event.key.keysym.sym - '0')), "", false);

                            if (stoi(valeurSaisie) >= 0 && stoi(valeurSaisie) <= dimGrille) {
                                jeu.grilleJeu.grille.getCase((unsigned char)(l_toChange - 1), (unsigned char)c_toChange - 1).setVal(stoi(valeurSaisie));
                                c_toChange = 0;
                                l_toChange = 0;
                            }
                        }
                    }
                    break;
                }
            }

            //----On fait les actions liées aux clics souris

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                sauvegarder(false);
                if (l_toChange != 0) {
                    for (int i = 0; i < dimGrille; i++) {
                        if (tabHitBoxSelectionNombre[i].is_in(mousse_x, mousse_y)) {
                            jeu.grilleJeu.grille.getCase((unsigned char)(l_toChange - 1), (unsigned char)c_toChange - 1).setVal(i + 1);

                        }
                    }
                }
                c_toChange = 0;
                l_toChange = 0;
                //---On regarde si le clic a ete effectue sur une des case de la grille, si oui: clic gauche --> selectionne la case, clic droit --> vide la case
                for (int l = 0; l < dimGrille; l++) {
                    for (int c = 0; c < dimGrille; c++) {

                        if (tabHitBoxGrille[l * dimGrille + c].is_in(mousse_x, mousse_y)) {
                            cout << "Colonne " << c + 1 << " | Ligne " << l + 1 << endl;
                            if (jeu.grilleJeu.grille.getCase(l, c).modifiable) {

                                if (event.button.button == SDL_BUTTON_LEFT) {
                                    c_toChange = c + 1;
                                    l_toChange = l + 1;
                                }
                                else if (event.button.button == SDL_BUTTON_RIGHT) {
                                    c_toChange = 0;
                                    l_toChange = 0;
                                    jeu.grilleJeu.grille.getCase(l, c).setVal(0);
                                }

                            }
                            else {
                                cout << "la case n'est pas modifiable" << endl;
                                c_toChange = 0;
                                l_toChange = 0;
                            }
                        }
                    }
                }
                //---On regarde si clic sur le menu

                if (tabHitBoxSelectionMenu[0].is_in(mousse_x, mousse_y)) {//Recommencer sur la meme grille
                    jeu.grilleJeu.grille = jeu.grilleOriginale.grille;
                }

                if (tabHitBoxSelectionMenu[2].is_in(mousse_x, mousse_y)) {//Start
                    ChronoJactif->start();
                }

                if (tabHitBoxSelectionMenu[4].is_in(mousse_x, mousse_y)) {//Start
                    ChronoJactif->pause();
                }

                if (tabHitBoxSelectionMenu[6].is_in(mousse_x, mousse_y)) {//Sauvegarder
                    sauvegarder(true);
                }

                if (tabHitBoxSelectionMenu[8].is_in(mousse_x, mousse_y)) {//activer sauvegarde auto
                    autoSave = true;
                }
                if (tabHitBoxSelectionMenu[10].is_in(mousse_x, mousse_y)) {//desactiver sauvegarde auto
                    autoSave = false;
                }

            }
        }

        



        if (jeu.verifGrillePleine(jeu.grilleJeu) && jeu.nbErreurs() == 0) {
            cout << jeu.stopBoucleJ1 << " " << jeu.stopBoucleJ2 << endl;
            *GrilleJactif = jeu.grilleJeu;
            if (!jeu.stopBoucleJ1) {
                ChronoJactif->pause();
                jeu.stopBoucleJ1 = true;
                jeu.nbErreurJ1 = jeu.nbErreurs();
                //On copie la grille dans une grille temporaire
                jeu.grilleJ1 = jeu.grilleJeu;
                //On remet la grille de jeu comme au départ
                jeu.grilleJeu = jeu.grilleOriginale;
                GrilleJactif = &jeu.grilleJ2;
                ChronoJactif = &jeu.chronoJ2;
                sdlAttendreJoueurSuivant();
                ChronoJactif->start();
            }
            else {
                ChronoJactif->pause();
                jeu.stopBoucleJ2 = true;
                jeu.nbErreurJ2 = jeu.nbErreurs();
                //On copie la grille dans une grille temporaire
                jeu.grilleJ2 = jeu.grilleJeu;
                //On remet la grille de jeu comme au départ
                jeu.grilleJeu = jeu.grilleOriginale;
                finDePartie = true;
            }
        }
        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }

    
}

void sdl1Vs1::sauvegarder(const bool& force) {
    cout << "Sauvegarde ...";
    if (force || autoSave) {
        if (jeu.sauvegardeId == 0) {
            SaisieTextPopUp popUp(font);
            string nouveauNom = popUp.getTexteSaisie(800, 100, "Un nom pour votre sauvegarde", "", "nom dans la liste des sauvegardes", true);
            jeu.sauvegardeId = gestionnaireSauvegarde.sauvegarder(jeu, nouveauNom, 3);

        }
        else {
            jeu.sauvegardeId = gestionnaireSauvegarde.sauvegarder(jeu, "", 3, jeu.sauvegardeId);
        }
        cout << "succes" << endl;

    }
    else {
        cout << "Abandon, sauv auto desactivée" << endl;

    }
}
// ============= FONCTIONS UTILITAIRES =============== //

void sdl1Vs1::affImgInHitBox(Image& img, const hitBox& hit)
{
    img.draw(renderer, hit.x1, hit.y1, hit.getLargeur(), hit.getHauteur());
}

void sdl1Vs1::sdlAffTexte(const string& txt, const int& x, const int& y, const int& largeur, const int& hauteur, const SDL_Color& couleur) {
    SDL_Surface* texte = nullptr;
    SDL_Rect position;
    SDL_Texture* texte_texture = nullptr;    //Create Texture pointeur
    texte = TTF_RenderText_Blended(font, txt.c_str(), couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);


    position.x = x;
    position.y = y;
    position.w = largeur;
    position.h = hauteur;

    int ok = SDL_RenderCopy(renderer, texte_texture, nullptr, &position);
    SDL_DestroyTexture(texte_texture);
    assert(ok == 0);
}