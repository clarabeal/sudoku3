#include "SDL_PasAPas.h"

#include <algorithm>  //pour la fonciton max(a, b)
#include <iostream>
#include <string.h>
using namespace std;

#define WIDTH 1024
#define HEIGHT 576


// ============= FONCTION D'INITIALISATION DE LA PARTIE(CONSTRUCTEURS & CO) + DESTRUCTEUR =============== //
sdlJeuPasAPas::sdlJeuPasAPas(const unsigned char& d) : jeu(d), dimGrille(d), autoSave(false), gestionnaireSauvegarde("../data/saves/", "data/saves/"){
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



}

sdlJeuPasAPas::sdlJeuPasAPas(const unsigned char& d, const int& id, const unsigned long& time, const Grille& g_sol, const Grille& g_orig, const Grille& g_jeu) : jeu(d, id, time, g_sol, g_orig, g_jeu), dimGrille(d), autoSave(false), gestionnaireSauvegarde("../data/saves/", "data/saves/") {//presque identique (qq donnes membres en plus dans 1vs1)
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



}

void sdlJeuPasAPas::init_SDL() //identique
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

void sdlJeuPasAPas::init_assets()//identique
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

    indicateurCaseSelectionee.loadFromFile("data/assets/couleursDeFond/Gris.png", renderer);
    indicateurCaseFacile.loadFromFile("data/assets/couleursDeFond/Bleu.png", renderer);

}

void sdlJeuPasAPas::init_im_menu(){
    //Bouton Retrirer cases fausses
    im_menu[0].loadFromFile("data/assets/menu/pasAPas/retirerCasesFausses_MousseAway.png", renderer);
    im_menu[1].loadFromFile("data/assets/menu/pasAPas/retirerCasesFausses_MousseOver.png", renderer);

    //Bouton Afficher une case simple
    im_menu[2].loadFromFile("data/assets/menu/pasAPas/AffCaseSimple_MousseAway.png", renderer);
    im_menu[3].loadFromFile("data/assets/menu/pasAPas/AffCaseSimple_MousseOver.png", renderer);

    //Bouton Reveler un indice
    im_menu[4].loadFromFile("data/assets/menu/pasAPas/RevelerIndice_MousseAway.png", renderer);
    im_menu[5].loadFromFile("data/assets/menu/pasAPas/RevelerIndice_MousseOver.png", renderer);

    //Bouton recommencer
    im_menu[6].loadFromFile("data/assets/menu/pasAPas/Recommencer_MousseAway.png", renderer);
    im_menu[7].loadFromFile("data/assets/menu/pasAPas/Recommencer_MousseOver.png", renderer);

    //Bouton nouvelle grille
    im_menu[8].loadFromFile("data/assets/menu/pasAPas/NouvelleGrille_MousseAway.png", renderer);
    im_menu[9].loadFromFile("data/assets/menu/pasAPas/NouvelleGrille_MousseOver.png", renderer);

    //Bouton sauvegarder
    im_menu[10].loadFromFile("data/assets/menu/pasAPas/Sauvegarder_MousseAway.png", renderer);
    im_menu[11].loadFromFile("data/assets/menu/pasAPas/Sauvegarder_MousseOver.png", renderer);

    //Bouton activer sauvegarde auto
    im_menu[12].loadFromFile("data/assets/menu/pasAPas/ActSauvegardeAutoActive_MousseAway.png", renderer);
    im_menu[13].loadFromFile("data/assets/menu/pasAPas/ActSauvegardeAutoActive_MousseOver.png", renderer);

    //Bouton desactiver sauvegarde auto
    im_menu[14].loadFromFile("data/assets/menu/pasAPas/DesactSauvegardeAutoActive_MousseAway.png", renderer);
    im_menu[15].loadFromFile("data/assets/menu/pasAPas/DesactSauvegardeAutoActive_MousseOver.png", renderer);

    //Bouton start
    im_menu[16].loadFromFile("data/assets/menu/pasAPas/Start_MousseAway.png", renderer);
    im_menu[17].loadFromFile("data/assets/menu/pasAPas/Start_MousseOver.png", renderer);

    //Bouton pause
    im_menu[18].loadFromFile("data/assets/menu/pasAPas/Pause_MousseAway.png", renderer);
    im_menu[19].loadFromFile("data/assets/menu/pasAPas/Pause_MousseOver.png", renderer);

    //Bouton activer la coloration des cases
    im_menu[20].loadFromFile("data/assets/menu/pasAPas/ActColorCase_MousseAway.png", renderer);
    im_menu[21].loadFromFile("data/assets/menu/pasAPas/ActColorCase_MousseOver.png", renderer);

    //Bouton desactiver la coloration des cases
    im_menu[22].loadFromFile("data/assets/menu/pasAPas/DesactColorCase_MousseAway.png", renderer);
    im_menu[23].loadFromFile("data/assets/menu/pasAPas/DesactColorCase_MousseOver.png", renderer);

}

sdlJeuPasAPas::~sdlJeuPasAPas() {//identique
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    delete[] tabHitBoxGrille;
    delete[] tabHitBoxSelectionNombre;
    delete[] im_selectionChiffre;
}

// ============= FONCTION DE GESTION DES HITBoxS =============== //

void sdlJeuPasAPas::placementElementsMenu(const int& x1, const int& y1, const int& x2, int y2) {
    effacerElementsMenu();
    const int nb_element = 9;

    if (y2 == 0) {
        y2 = (x2 - x1) * nb_element / 11;//on respecte le format par defaut pour que la police ne soit pas deform??e
    }

    int y1courant = y1;//variables permetants de placer les elements les un sous les autres
    int y2courant = 0;
    y2courant = y1courant + y2 / nb_element;

    //---------> On positionne les hitboxs des 5 premieres options ( Retirer cases fausses, aff case simple, Recommencer grille, generer nouvelle grille)
    tabHitBoxSelectionMenu[0].x1 = x1;
    tabHitBoxSelectionMenu[0].x2 = x2;
    tabHitBoxSelectionMenu[0].y1 = y1courant;
    tabHitBoxSelectionMenu[0].y2 = y2courant;
    tabHitBoxSelectionMenu[1].x1 = x1;
    tabHitBoxSelectionMenu[1].x2 = x2;
    tabHitBoxSelectionMenu[1].y1 = y1courant;
    tabHitBoxSelectionMenu[1].y2 = y2courant;

    for (int i = 2; i <= 9; i = i + 2) {
        y1courant = y2courant;
        y2courant = y1courant + y2 / nb_element;

        tabHitBoxSelectionMenu[i].x1 = x1;
        tabHitBoxSelectionMenu[i].x2 = x2;
        tabHitBoxSelectionMenu[i].y1 = y1courant;
        tabHitBoxSelectionMenu[i].y2 = y2courant;
        tabHitBoxSelectionMenu[i + 1].x1 = x1;
        tabHitBoxSelectionMenu[i + 1].x2 = x2;
        tabHitBoxSelectionMenu[i + 1].y1 = y1courant;
        tabHitBoxSelectionMenu[i + 1].y2 = y2courant;
    }

    //---------> On positionne les hitboxs des btn activer/desactiver la jeu.coloration
    y1courant = y2courant;
    y2courant = y1courant + y2 / nb_element;
    if (!jeu.coloration) {

        tabHitBoxSelectionMenu[20].x1 = x1;
        tabHitBoxSelectionMenu[20].y1 = y1courant;
        tabHitBoxSelectionMenu[20].x2 = x2;
        tabHitBoxSelectionMenu[20].y2 = y2courant;
        tabHitBoxSelectionMenu[21].x1 = x1;
        tabHitBoxSelectionMenu[21].y1 = y1courant;
        tabHitBoxSelectionMenu[21].x2 = x2;
        tabHitBoxSelectionMenu[21].y2 = y2courant;
        tabHitBoxSelectionMenu[22].reset();
        tabHitBoxSelectionMenu[23].reset();

    }
    else {
        tabHitBoxSelectionMenu[22].x1 = x1;
        tabHitBoxSelectionMenu[22].y1 = y1courant;
        tabHitBoxSelectionMenu[22].x2 = x2;
        tabHitBoxSelectionMenu[22].y2 = y2courant;
        tabHitBoxSelectionMenu[23].x1 = x1;
        tabHitBoxSelectionMenu[23].y1 = y1courant;
        tabHitBoxSelectionMenu[23].x2 = x2;
        tabHitBoxSelectionMenu[23].y2 = y2courant;
        tabHitBoxSelectionMenu[20].reset();
        tabHitBoxSelectionMenu[21].reset();
    }

    //---------> On positionne les hitboxs des btn start/pause
    y1courant = y2courant;
    y2courant = y1courant + y2 / nb_element;
    if (jeu.chrono.estEnPause()) {

        tabHitBoxSelectionMenu[16].x1 = x1;
        tabHitBoxSelectionMenu[16].y1 = y1courant;
        tabHitBoxSelectionMenu[16].x2 = x2;
        tabHitBoxSelectionMenu[16].y2 = y2courant;
        tabHitBoxSelectionMenu[17].x1 = x1;
        tabHitBoxSelectionMenu[17].y1 = y1courant;
        tabHitBoxSelectionMenu[17].x2 = x2;
        tabHitBoxSelectionMenu[17].y2 = y2courant;
        tabHitBoxSelectionMenu[18].reset();
        tabHitBoxSelectionMenu[19].reset();

    }
    else {
        tabHitBoxSelectionMenu[18].x1 = x1;
        tabHitBoxSelectionMenu[18].y1 = y1courant;
        tabHitBoxSelectionMenu[18].x2 = x2;
        tabHitBoxSelectionMenu[18].y2 = y2courant;
        tabHitBoxSelectionMenu[19].x1 = x1;
        tabHitBoxSelectionMenu[19].y1 = y1courant;
        tabHitBoxSelectionMenu[19].x2 = x2;
        tabHitBoxSelectionMenu[19].y2 = y2courant;
        tabHitBoxSelectionMenu[16].reset();
        tabHitBoxSelectionMenu[17].reset();
    }

    //---------> On positionne les hitboxs des btn de sauvegarde
    y1courant = y2courant;
    y2courant = y1courant + y2 / nb_element;
    if (!autoSave && jeu.sauvegardeId != 0) {// si la sauvegarde automatique est desactiv??e et que la partie a deja ete sauvegard?? au moins une fois

        tabHitBoxSelectionMenu[12].x1 = x1;
        tabHitBoxSelectionMenu[12].x2 = x2;
        tabHitBoxSelectionMenu[12].y1 = y1courant;
        tabHitBoxSelectionMenu[12].y2 = y2courant;

        tabHitBoxSelectionMenu[13].x1 = x1;
        tabHitBoxSelectionMenu[13].x2 = x2;
        tabHitBoxSelectionMenu[13].y1 = y1courant;
        tabHitBoxSelectionMenu[13].y2 = y2courant;

        tabHitBoxSelectionMenu[14].reset();
        tabHitBoxSelectionMenu[15].reset();
        y1courant = y2courant;
        y2courant = y1courant + y2 / nb_element;
    }
    else if (autoSave && jeu.sauvegardeId != 0) {
        tabHitBoxSelectionMenu[14].x1 = x1;
        tabHitBoxSelectionMenu[14].x2 = x2;
        tabHitBoxSelectionMenu[14].y1 = y1courant;
        tabHitBoxSelectionMenu[14].y2 = y2courant;

        tabHitBoxSelectionMenu[15].x1 = x1;
        tabHitBoxSelectionMenu[15].x2 = x2;
        tabHitBoxSelectionMenu[15].y1 = y1courant;
        tabHitBoxSelectionMenu[15].y2 = y2courant;

        tabHitBoxSelectionMenu[12].reset();
        tabHitBoxSelectionMenu[13].reset();
        y1courant = y2courant;
        y2courant = y1courant + y2 / nb_element;
    }

    if (jeu.sauvegardeId == 0 || !autoSave) {
        tabHitBoxSelectionMenu[10].x1 = x1;
        tabHitBoxSelectionMenu[10].x2 = x2;
        tabHitBoxSelectionMenu[10].y1 = y1courant;
        tabHitBoxSelectionMenu[10].y2 = y2courant;

        tabHitBoxSelectionMenu[11].x1 = x1;
        tabHitBoxSelectionMenu[11].x2 = x2;
        tabHitBoxSelectionMenu[11].y1 = y1courant;
        tabHitBoxSelectionMenu[11].y2 = y2courant;

        y1courant = y2courant;
        y2courant = y1courant + y2 / nb_element;
    }
}

void sdlJeuPasAPas::effacerElementsMenu() {//supprime les hitboxs du menu pour qu'on ne puisse pas cliquer dessus lorsqu'il n'est pas affich??(presque identique)
    for (int i = 0; i <= 20; i++) {
        tabHitBoxSelectionMenu[i].reset();
    }
}

void sdlJeuPasAPas::placerHitBoxCaseGrille(const int& x, const int& y, const int& largeur, const int& hauteur) {//supprime les hitboxs du menu pour qu'on ne puisse pas cliquer dessus lorsqu'il n'est pas affich??(indentique)
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

void sdlJeuPasAPas::resetTabHitSelectionNombre() {
    for (int i = 0; i < dimGrille; i++) {
        tabHitBoxSelectionNombre[i].x1 = 0;
        tabHitBoxSelectionNombre[i].y1 = 0;
        tabHitBoxSelectionNombre[i].x2 = 0;
        tabHitBoxSelectionNombre[i].y2 = 0;
    }
}

void sdlJeuPasAPas::resetTabHitGrille() {
    for (int l = 0; l < dimGrille; l++) {
        for (int c = 0; c < dimGrille; c++) {
            tabHitBoxGrille[l * dimGrille + c].x1 = 0;
            tabHitBoxGrille[l * dimGrille + c].y1 = 0;
            tabHitBoxGrille[l * dimGrille + c].x2 = 0;
            tabHitBoxGrille[l * dimGrille + c].y2 = 0;
        }
    }
}

// ============= FONCTION D'AFFICHAGE =============== //

void sdlJeuPasAPas::sdlAff() {

    //supprime les hitboxs de l'affichage precedent
    resetTabHitGrille();
    resetTabHitSelectionNombre();

    //Remplir l'??cran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Affiche la grille
    int hauteurGrille = HEIGHT * 80 / 100;
    int xGrille = HEIGHT * 10 / 100;
    int yGrille = WIDTH * 5 / 100;

    sdlAffGrille(jeu.grilleJeu, xGrille, yGrille, hauteurGrille, hauteurGrille, !jeu.chrono.estEnPause());

    sdlAffChrono(xGrille + hauteurGrille + WIDTH * 2 / 100, yGrille, (WIDTH - hauteurGrille - xGrille) * 80 / 100, ((WIDTH - hauteurGrille - xGrille) * 80 / 100) * 1 / 10, jeu.chrono);

    // Si une valeur doit etre entree on affiche la selection 
    int selectHauteur = 0;
    int y_pos_select = yGrille + (WIDTH - hauteurGrille - xGrille) * 80 / 100 * 1 / 10 + HEIGHT * 5 / 100;

    if (l_toChange != 0) {

        selectHauteur = 40;
        sdlAffSelectionChiffre(xGrille + hauteurGrille + WIDTH * 1 / 100, y_pos_select, dimGrille * selectHauteur, selectHauteur);
    }

    sdlAffMenu(xGrille + hauteurGrille + WIDTH * 2 / 100 + 20, y_pos_select + selectHauteur, hauteurGrille * 80 / 100, hauteurGrille * 80 / 100);

}

void sdlJeuPasAPas::sdlAffMenu(const int& x, const int& y, const int& largeur, const int& hauteur) {
    placementElementsMenu(x, y, x + largeur, 0);
    for (int i = 0; i < 24; i += 2) {
        if (!tabHitBoxSelectionMenu[i].is_in(mousse_x, mousse_y)) {
            affImgInHitBox(im_menu[i], tabHitBoxSelectionMenu[i]);
        }
        else {
            affImgInHitBox(im_menu[i + 1], tabHitBoxSelectionMenu[i + 1]);
        }
    }
}

void sdlJeuPasAPas::sdlAffSelectionChiffre(const int& x, const int& y, const int& largeur, const int& hauteur) {
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

void sdlJeuPasAPas::sdlAffGrille(const Grille& grille, const int& x, const int& y, const int& largeur, const int& hauteur, const bool& afficher) {
    assert((int)grille.dim == dimGrille);
    jeu.colorerCase();
    im_grille.draw(renderer, x, y, largeur, hauteur);
    placerHitBoxCaseGrille(x, y, largeur, hauteur);
    if (afficher) {
        SDL_Color couleur = { 0, 0, 0 };
        int largeurCase = largeur / dimGrille;
        int hauteurCase = hauteur / dimGrille;
        for (int l = 0; l < dimGrille; l++) {
            for (int c = 0; c < dimGrille; c++) {

                switch ((int)grille.grille.getCase(l, c).etat)
                {
                case 0:
                    couleur.r = 0;
                    couleur.g = 0;
                    couleur.b = 0;

                    break;
                case 1:
                    couleur.r = 0;
                    couleur.g = 255;
                    couleur.b = 0;
                    break;
                case 2:
                    couleur.r = 150;
                    couleur.g = 50;
                    couleur.b = 50;
                    break;
                case 3:
                    indicateurCaseFacile.draw(renderer, x + (c)*largeurCase, y + (l)*hauteurCase, hauteurCase, largeurCase);
                    break;
                default:
                    break;
                }

                if (l_toChange != 0) {// si une case est en cours de modification, on met un fond gris sur celle ci
                    indicateurCaseSelectionee.draw(renderer, x + (c_toChange - 1) * largeurCase, y + (l_toChange - 1) * hauteurCase, hauteurCase, largeurCase);
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

void sdlJeuPasAPas::sdlAffChrono(const int& x, const int& y, const int& largeur, const int& hauteur, chronometre& chrono, const bool& full) {

    chrono.update();// a enlever apres les tests, ne doit pas ??tre la
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

void sdlJeuPasAPas::sdlAffFinDePartie()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Affiche des grilles
    int hauteurGrilles = HEIGHT * 80 / 100;
    int xGrille = HEIGHT * 10 / 100;
    int yGrille = WIDTH * 5 / 100;

    sdlAffGrille(jeu.grilleJeu, xGrille, yGrille, hauteurGrilles, hauteurGrilles, true);
    sdlAffGrille(jeu.grilleSolution, xGrille + hauteurGrilles + WIDTH * 2 / 100, yGrille, hauteurGrilles, hauteurGrilles, true);

    sdlAffChrono(xGrille, (yGrille) * 2 / 100, WIDTH * 80 / 100, yGrille * 80 / 100, jeu.chrono, true);


}

void sdlJeuPasAPas::sdlAffChargement()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    string txt_sdlAffTxt = "Generation de la grille";
    sdlAffTexte(txt_sdlAffTxt, 0, 0, WIDTH / 2, ((WIDTH / 2) * 1.6) / txt_sdlAffTxt.length(), font_color);
    SDL_RenderPresent(renderer);


}
// ============= CLASS SDLJEU =============== //

void sdlJeuPasAPas::sdlBoucle() {
    sdlAffChargement();
    bool gameRunning = true;

    if (!jeu.initDone) {
        jeu.init();
        jeu.initDone = true;
        SDL_RenderPresent(renderer);

    }
    jeu.chrono.start();
    unsigned long timeAutoSave = jeu.chrono.getTimeInSec();
    while (gameRunning) {
        sdlAff();
        if (jeu.chrono.getTimeInSec() - timeAutoSave > 30) {
            sauvegarder();
            timeAutoSave = jeu.chrono.getTimeInSec();
        }
        while (SDL_PollEvent(&event))
        {
            //----Quitte la partie si croix
            if (event.type == SDL_QUIT) gameRunning = false;

            //----On enregistre la postion de la souris
            if (event.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&mousse_x, &mousse_y);
            }

            //----On fait les actions li??es au differentes touches du clavier si elles sont press??es
            if (event.type == SDL_KEYDOWN)
            {
                sauvegarder();

                switch (event.key.keysym.sym)
                {
                default:
                    if (c_toChange != 0) {
                        if (event.key.keysym.sym == SDLK_0 || event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_2 || event.key.keysym.sym == SDLK_3 || event.key.keysym.sym == SDLK_4 || event.key.keysym.sym == SDLK_5 || event.key.keysym.sym == SDLK_6 || event.key.keysym.sym == SDLK_7 || event.key.keysym.sym == SDLK_8 || event.key.keysym.sym == SDLK_9) {
                            if (dimGrille < 10) {
                                jeu.grilleJeu.grille.getCase((unsigned char)(l_toChange - 1), (unsigned char)c_toChange - 1).setVal(int(event.key.keysym.sym - '0'));
                                c_toChange = 0;
                                l_toChange = 0;
                            }
                            else {
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
                    }

                    break;
                }
            }

            //----On fait les actions li??es aux clics souris

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                //---Si une case devait etre change on verifie si le clic a ete effectue sur une des hit box des chiffres
                sauvegarder();

                if (l_toChange != 0) {
                    for (int i = 0; i < dimGrille; i++) {
                        if (tabHitBoxSelectionNombre[i].is_in(mousse_x, mousse_y)) {
                            jeu.grilleJeu.grille.getCase((unsigned char)(l_toChange - 1), (unsigned char)c_toChange - 1).setVal(i + 1);

                        }
                    }
                }
                c_toChange = 0;
                l_toChange = 0;
                //---On regarde si le clic a ete effectue sur une des case de la grille, si oui: clic gauche --> Selectionne la case et affiche le menu de selection chiffre, clic droit --> vide la case
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
                for (int i = 0; i < 21; i++) {
                    if (tabHitBoxSelectionMenu[i].is_in(mousse_x, mousse_y)) {
                        cout << "clic sur la hit box: " << i << endl;
                    }
                }
                if (tabHitBoxSelectionMenu[0].is_in(mousse_x, mousse_y)) {//Retirer les cases fausses
                    jeu.retirerCasesFausses();
                    cout << "case fausses retirees" << endl;
                }
                else if (tabHitBoxSelectionMenu[2].is_in(mousse_x, mousse_y)) {//Afficher une case simple
                    unsigned char c_f, l_f;
                    jeu.coordCaseSimple(l_f, c_f);
                    jeu.grilleJeu.grille.getCase(l_f - 1, c_f - 1).etat = 3;
                }
                else if (tabHitBoxSelectionMenu[4].is_in(mousse_x, mousse_y)) {//reveler un indice
                    bool aideRemplir = false;
                    int essaie = 0;
                    int l;
                    int c;
                    do { //remplit une case au hasard
                        essaie++;
                        l = rand() % jeu.grilleJeu.dim + 1;
                        c = rand() % jeu.grilleJeu.dim + 1;

                        cout << "l :" << l << "c :" << c << endl;

                        unsigned char valeur = jeu.grilleJeu.grille.getCase(l - 1, c - 1).getVal();

                        if (valeur == 0) { //place la valeur si la case est vide
                            jeu.grilleJeu.setCase(l - 1, c - 1, jeu.grilleSolution.grille.getCase(l - 1, c - 1).getVal());
                            aideRemplir = true; //aide a savoir si la valeur a ete placee
                        }

                    } while (aideRemplir == false && essaie < 500);
                    jeu.grilleJeu.grille.getCase(l - 1, c - 1).modifiable = false;
                }
                else if (tabHitBoxSelectionMenu[6].is_in(mousse_x, mousse_y)) {//recommencer la meme grille
                    jeu.grilleJeu.grille = jeu.grilleOriginale.grille;

                }
                else if (tabHitBoxSelectionMenu[8].is_in(mousse_x, mousse_y)) {//Generer une nouvelle grille
                    jeu.init();

                }
                else if (tabHitBoxSelectionMenu[10].is_in(mousse_x, mousse_y)) {//sauvegarder
                    sauvegarder(true);
                }
                else if (tabHitBoxSelectionMenu[12].is_in(mousse_x, mousse_y)) {//Activer sauvegarde auto
                    autoSave = true;
                }
                else if (tabHitBoxSelectionMenu[14].is_in(mousse_x, mousse_y)) {//desactiver sauvegarde auto
                    autoSave = false;
                }
                else if (tabHitBoxSelectionMenu[16].is_in(mousse_x, mousse_y)) {//start
                    jeu.chrono.start();
                }
                else if (tabHitBoxSelectionMenu[18].is_in(mousse_x, mousse_y)) {//Pause
                    jeu.chrono.pause();
                }
                else if (tabHitBoxSelectionMenu[20].is_in(mousse_x, mousse_y)) {//aide color act
                    jeu.coloration = true;
                }
                else if (tabHitBoxSelectionMenu[22].is_in(mousse_x, mousse_y)) {//aide color desact
                    jeu.coloration = false;
                }

            }
        }

        if (jeu.verifGrillePleine(jeu.grilleJeu)) {

            jeu.chrono.pause();
            jeu.coloration = true;
            sdlAffFinDePartie();
            finDePartie = true;

        }

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }
}

void sdlJeuPasAPas::sauvegarder(const bool& force) {
    cout << "Sauvegarde ...";
    if (force || autoSave) {
        if (jeu.sauvegardeId == 0) {
            SaisieTextPopUp popUp(font);
            string nouveauNom = popUp.getTexteSaisie(800, 100, "Un nom pour votre sauvegarde", "", "nom dans la liste des sauvegardes", true);
            jeu.sauvegardeId = gestionnaireSauvegarde.sauvegarder(jeu, nouveauNom, 2);

        }
        else {
            jeu.sauvegardeId = gestionnaireSauvegarde.sauvegarder(jeu, "", 2, jeu.sauvegardeId);
        }
        cout << "succes" << endl;

    }
    else {
        cout << "Abandon, sauv auto desactiv??e" << endl;

    }
}

// ============= FONCTIONS UTILITAIRES =============== //

void sdlJeuPasAPas::affImgInHitBox(Image& img, const hitBox& hit)
{
    img.draw(renderer, hit.x1, hit.y1, hit.getLargeur(), hit.getHauteur());
}

void sdlJeuPasAPas::sdlAffTexte(const string& txt, const int& x, const int& y, const int& largeur, const int& hauteur, const SDL_Color& couleur) {
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

