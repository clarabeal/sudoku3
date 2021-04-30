#include "SDL_PasAPas.h"

#include <algorithm>  //pour la fonciton max(a, b)
#include <iostream>
#include <string.h>
using namespace std;

#define WIDTH 1024
#define HEIGHT 576

float sdlJeuPasAPas::temps() {
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}



// ============= CLASS SDLJEU =============== //

sdlJeuPasAPas::sdlJeuPasAPas(unsigned char d) : jeu(d), dimGrille(d), gestionnaireSauvegarde("../data/saves/", "data/saves/"), autoSave(false)
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
    font = TTF_OpenFont("data/fonts/BungeeShade-Regular.ttf", 120);
    if (!font) {
        font = TTF_OpenFont("../data/fonts/BungeeShade-Regular.ttf", 120);

    }
    //font = TTF_OpenFont("../data/fonts/arial.ttf", 40);

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
    font_color.r = 0;
    font_color.g = 0;
    font_color.b = 0;

    //creation des images :
    if (d == 4) {
        im_grille.loadFromFile("data/assets/grilles/4x4color.jpg", renderer);
    }
    else if (d == 9) {
        im_grille.loadFromFile("data/assets/grilles/9x9color.jpg", renderer);
    }
    else if (d == 16) {
        im_grille.loadFromFile("data/assets/grilles/16x16color.jpg", renderer);
    }

    tabHitBoxeGrille = new hitBox[d*d];
    //tabHitBoxeGrille = new hitBox[100];

    tabHitBoxeSelectionNombre = new hitBox[d+1];
    im_selectionChiffre = new Image[d+1];
    char buffConversion[3];
    bleu.loadFromFile("data/assets/couleursDeFond/Bleu.png", renderer);
    rouge.loadFromFile("data/assets/couleursDeFond/Rouge.png", renderer);
    vert.loadFromFile("data/assets/couleursDeFond/Vert.png", renderer);
    gris.loadFromFile("data/assets/couleursDeFond/Gris.png", renderer);
    for (int i = 0; i < d+1; i++) {
        if (i == 0){
            string path = "data/assets/selectionChiffres/";
            if (d < 10) {
                buffConversion[0] = (int)d + '0';
                buffConversion[1] = '\0';
            }
            else {
                buffConversion[0] = '1';
                buffConversion[1] = (int)d - 10 + '0';
                buffConversion[2] = '\0';
            }


            path += buffConversion;
            path += "/chiffres";
            path += "_Away.png";
            im_selectionChiffre[i].loadFromFile(path.c_str(), renderer);

        }
        else {
            string path = "data/assets/selectionChiffres/";
            if (d < 10) {
                buffConversion[0] = (int)d + '0';
                buffConversion[1] = '\0';
            }
            else {
                buffConversion[0] = '1';
                buffConversion[1] = (int)d - 10 + '0';
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
    l_toChange = 0;
    c_toChange = 0;
    mousse_x = 0;
    mousse_y = 0;
    finDePartie = false;
    tabDiffCase = new unsigned char[2*d*d];
    init_im_menu();

}

sdlJeuPasAPas::sdlJeuPasAPas(unsigned char d, int id, unsigned long time, Grille& g_sol, Grille& g_orig, Grille& g_jeu) : jeu(d, id, time, g_sol, g_orig, g_jeu), dimGrille(d), gestionnaireSauvegarde("../data/saves/", "data/saves/"), autoSave(false) {
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
    font = TTF_OpenFont("data/fonts/BungeeShade-Regular.ttf", 120);
    if (!font) {
        font = TTF_OpenFont("../data/fonts/BungeeShade-Regular.ttf", 120);

    }
    //font = TTF_OpenFont("../data/fonts/arial.ttf", 40);

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
    font_color.r = 0;
    font_color.g = 0;
    font_color.b = 0;

    //creation des images :
    if (d == 4) {
        im_grille.loadFromFile("data/assets/grilles/4x4color.jpg", renderer);
    }
    else if (d == 9) {
        im_grille.loadFromFile("data/assets/grilles/9x9color.jpg", renderer);
    }
    else if (d == 16) {
        im_grille.loadFromFile("data/assets/grilles/16x16color.jpg", renderer);
    }

    tabHitBoxeGrille = new hitBox[d * d];
    //tabHitBoxeGrille = new hitBox[100];

    tabHitBoxeSelectionNombre = new hitBox[d + 1];
    im_selectionChiffre = new Image[d + 1];
    char buffConversion[3];
    bleu.loadFromFile("data/assets/couleursDeFond/Bleu.png", renderer);
    rouge.loadFromFile("data/assets/couleursDeFond/Rouge.png", renderer);
    vert.loadFromFile("data/assets/couleursDeFond/Vert.png", renderer);
    gris.loadFromFile("data/assets/couleursDeFond/Gris.png", renderer);
    for (int i = 0; i < d + 1; i++) {
        if (i == 0) {
            string path = "data/assets/selectionChiffres/";
            if (d < 10) {
                buffConversion[0] = (int)d + '0';
                buffConversion[1] = '\0';
            }
            else {
                buffConversion[0] = '1';
                buffConversion[1] = (int)d - 10 + '0';
                buffConversion[2] = '\0';
            }


            path += buffConversion;
            path += "/chiffres";
            path += "_Away.png";
            im_selectionChiffre[i].loadFromFile(path.c_str(), renderer);

        }
        else {
            string path = "data/assets/selectionChiffres/";
            if (d < 10) {
                buffConversion[0] = (int)d + '0';
                buffConversion[1] = '\0';
            }
            else {
                buffConversion[0] = '1';
                buffConversion[1] = (int)d - 10 + '0';
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
    l_toChange = 0;
    c_toChange = 0;
    mousse_x = 0;
    mousse_y = 0;
    finDePartie = false;
    tabDiffCase = new unsigned char[2 * d * d];
    init_im_menu();


}

void sdlJeuPasAPas::init_im_menu()
{
    im_menu[0].loadFromFile("data/assets/menu/pasAPas/retirerCasesFausses_MousseAway.png", renderer);
    im_menu[1].loadFromFile("data/assets/menu/pasAPas/retirerCasesFausses_MousseOver.png", renderer);
    im_menu[2].loadFromFile("data/assets/menu/pasAPas/AffCaseSimple_MousseAway.png", renderer);
    im_menu[3].loadFromFile("data/assets/menu/pasAPas/AffCaseSimple_MousseOver.png", renderer);
    im_menu[4].loadFromFile("data/assets/menu/pasAPas/RevelerIndice_MousseAway.png", renderer);
    im_menu[5].loadFromFile("data/assets/menu/pasAPas/RevelerIndice_MousseOver.png", renderer);
    im_menu[6].loadFromFile("data/assets/menu/pasAPas/Recommencer_MousseAway.png", renderer);
    im_menu[7].loadFromFile("data/assets/menu/pasAPas/Recommencer_MousseOver.png", renderer);
    im_menu[8].loadFromFile("data/assets/menu/pasAPas/NouvelleGrille_MousseAway.png", renderer);
    im_menu[9].loadFromFile("data/assets/menu/pasAPas/NouvelleGrille_MousseOver.png", renderer);
    im_menu[10].loadFromFile("data/assets/menu/pasAPas/Sauvegarder_MousseAway.png", renderer);
    im_menu[11].loadFromFile("data/assets/menu/pasAPas/Sauvegarder_MousseOver.png", renderer);
    im_menu[12].loadFromFile("data/assets/menu/pasAPas/ActSauvegardeAutoActive_MousseAway.png", renderer);
    im_menu[13].loadFromFile("data/assets/menu/pasAPas/ActSauvegardeAutoActive_MousseOver.png", renderer);
    im_menu[14].loadFromFile("data/assets/menu/pasAPas/DesactSauvegardeAutoActive_MousseAway.png", renderer);
    im_menu[15].loadFromFile("data/assets/menu/pasAPas/DesactSauvegardeAutoActive_MousseOver.png", renderer);
    im_menu[16].loadFromFile("data/assets/menu/pasAPas/Start_MousseAway.png", renderer);
    im_menu[17].loadFromFile("data/assets/menu/pasAPas/Start_MousseOver.png", renderer);
    im_menu[18].loadFromFile("data/assets/menu/pasAPas/Pause_MousseAway.png", renderer);
    im_menu[19].loadFromFile("data/assets/menu/pasAPas/Pause_MousseOver.png", renderer);


    im_menu[20].loadFromFile("data/assets/menu/pasAPas/ActColorCase_MousseAway.png", renderer);
    im_menu[21].loadFromFile("data/assets/menu/pasAPas/ActColorCase_MousseOver.png", renderer);
    im_menu[22].loadFromFile("data/assets/menu/pasAPas/DesactColorCase_MousseAway.png", renderer);
    im_menu[23].loadFromFile("data/assets/menu/pasAPas/DesactColorCase_MousseOver.png", renderer);

}

void sdlJeuPasAPas::init_hit_menu(int x1, int y1, int x2, int y2) {
    effacer_hit_menu();
    const int nb_element = 9;

    if (y2 == 0) {
        y2 = (x2 - x1) * nb_element /11;//on respecte le format par defaut pour que la police ne soit pas deformée
    }
    int y1courant = y1;
    int y2courant = 0;
    //---------> Les hitboxs des 5 premieres options ( Retirer cases fausses, aff case simple, Recommencer grille, generer nouvelle grille)
    y2courant = y1courant + y2 / nb_element;
    tabHitBoxeSelectionMenu[0].x1 = x1;
    tabHitBoxeSelectionMenu[0].x2 = x2;
    tabHitBoxeSelectionMenu[0].y1 = y1courant;
    tabHitBoxeSelectionMenu[0].y2 = y2courant;
    tabHitBoxeSelectionMenu[1].x1 = x1;
    tabHitBoxeSelectionMenu[1].x2 = x2;
    tabHitBoxeSelectionMenu[1].y1 = y1courant;
    tabHitBoxeSelectionMenu[1].y2 = y2courant;
    for (int i = 2; i <= 9; i = i+2) {
        y1courant = y2courant;
        y2courant = y1courant + y2 / nb_element;

        tabHitBoxeSelectionMenu[i].x1 = x1;
        tabHitBoxeSelectionMenu[i].x2 = x2;
        tabHitBoxeSelectionMenu[i].y1 = y1courant;
        tabHitBoxeSelectionMenu[i].y2 = y2courant;
        tabHitBoxeSelectionMenu[i+1].x1 = x1;
        tabHitBoxeSelectionMenu[i+1].x2 = x2;
        tabHitBoxeSelectionMenu[i+1].y1 = y1courant;
        tabHitBoxeSelectionMenu[i+1].y2 = y2courant;
    }

    //---------> Les hitboxs des btn activer/desactiver la jeu.coloration
    y1courant = y2courant;
    y2courant = y1courant + y2 / nb_element;
    if (!jeu.coloration) {

        tabHitBoxeSelectionMenu[20].x1 = x1;
        tabHitBoxeSelectionMenu[20].y1 = y1courant;
        tabHitBoxeSelectionMenu[20].x2 = x2;
        tabHitBoxeSelectionMenu[20].y2 = y2courant;
        tabHitBoxeSelectionMenu[21].x1 = x1;
        tabHitBoxeSelectionMenu[21].y1 = y1courant;
        tabHitBoxeSelectionMenu[21].x2 = x2;
        tabHitBoxeSelectionMenu[21].y2 = y2courant;
        tabHitBoxeSelectionMenu[22].reset();
        tabHitBoxeSelectionMenu[23].reset();

    }
    else {
        tabHitBoxeSelectionMenu[22].x1 = x1;
        tabHitBoxeSelectionMenu[22].y1 = y1courant;
        tabHitBoxeSelectionMenu[22].x2 = x2;
        tabHitBoxeSelectionMenu[22].y2 = y2courant;
        tabHitBoxeSelectionMenu[23].x1 = x1;
        tabHitBoxeSelectionMenu[23].y1 = y1courant;
        tabHitBoxeSelectionMenu[23].x2 = x2;
        tabHitBoxeSelectionMenu[23].y2 = y2courant;
        tabHitBoxeSelectionMenu[20].reset();
        tabHitBoxeSelectionMenu[21].reset();
    }

    //---------> Les hitboxs des btn start/pause
    y1courant = y2courant;
    y2courant = y1courant + y2 / nb_element;
    if (jeu.chrono.estEnPause()) {

        tabHitBoxeSelectionMenu[16].x1 = x1;
        tabHitBoxeSelectionMenu[16].y1 = y1courant;
        tabHitBoxeSelectionMenu[16].x2 = x2;
        tabHitBoxeSelectionMenu[16].y2 = y2courant;
        tabHitBoxeSelectionMenu[17].x1 = x1;
        tabHitBoxeSelectionMenu[17].y1 = y1courant;
        tabHitBoxeSelectionMenu[17].x2 = x2;
        tabHitBoxeSelectionMenu[17].y2 = y2courant;
        tabHitBoxeSelectionMenu[18].reset();
        tabHitBoxeSelectionMenu[19].reset();

    }
    else {
        tabHitBoxeSelectionMenu[18].x1 = x1;
        tabHitBoxeSelectionMenu[18].y1 = y1courant;
        tabHitBoxeSelectionMenu[18].x2 = x2;
        tabHitBoxeSelectionMenu[18].y2 = y2courant;
        tabHitBoxeSelectionMenu[19].x1 = x1;
        tabHitBoxeSelectionMenu[19].y1 = y1courant;
        tabHitBoxeSelectionMenu[19].x2 = x2;
        tabHitBoxeSelectionMenu[19].y2 = y2courant;
        tabHitBoxeSelectionMenu[16].reset();
        tabHitBoxeSelectionMenu[17].reset();
    }

    //---------> Les hitboxs des btn de sauvegarde
    y1courant = y2courant;
    y2courant = y1courant + y2 / nb_element;
    if (!autoSave) {

        tabHitBoxeSelectionMenu[12].x1 = x1;
        tabHitBoxeSelectionMenu[12].x2 = x2;
        tabHitBoxeSelectionMenu[12].y1 = y1courant;
        tabHitBoxeSelectionMenu[12].y2 = y2courant;

        tabHitBoxeSelectionMenu[13].x1 = x1;
        tabHitBoxeSelectionMenu[13].x2 = x2;
        tabHitBoxeSelectionMenu[13].y1 = y1courant;
        tabHitBoxeSelectionMenu[13].y2 = y2courant;

        tabHitBoxeSelectionMenu[14].reset();
        tabHitBoxeSelectionMenu[15].reset();
        y1courant = y2courant;
        y2courant = y1courant + y2 / nb_element;
    }
    else if (jeu.sauvegardeId != 0) {
        tabHitBoxeSelectionMenu[14].x1 = x1;
        tabHitBoxeSelectionMenu[14].x2 = x2;
        tabHitBoxeSelectionMenu[14].y1 = y1courant;
        tabHitBoxeSelectionMenu[14].y2 = y2courant;

        tabHitBoxeSelectionMenu[15].x1 = x1;
        tabHitBoxeSelectionMenu[15].x2 = x2;
        tabHitBoxeSelectionMenu[15].y1 = y1courant;
        tabHitBoxeSelectionMenu[15].y2 = y2courant;

        tabHitBoxeSelectionMenu[12].reset();
        tabHitBoxeSelectionMenu[13].reset();
        y1courant = y2courant;
        y2courant = y1courant + y2 / nb_element;
    }
   
    if(jeu.sauvegardeId == 0 || !autoSave) {
        tabHitBoxeSelectionMenu[10].x1 = x1;
        tabHitBoxeSelectionMenu[10].x2 = x2;
        tabHitBoxeSelectionMenu[10].y1 = y1courant;
        tabHitBoxeSelectionMenu[10].y2 = y2courant;

        tabHitBoxeSelectionMenu[11].x1 = x1;
        tabHitBoxeSelectionMenu[11].x2 = x2;
        tabHitBoxeSelectionMenu[11].y1 = y1courant;
        tabHitBoxeSelectionMenu[11].y2 = y2courant;

        y1courant = y2courant;
        y2courant = y1courant + y2 / nb_element;
    }
   

    
   
}

void sdlJeuPasAPas::effacer_hit_menu() {//supprime les hitboxs du menu pour qu'on ne puisse pas cliquer dessus lorsqu'il n'est pas affiché
    for (int i = 0; i <= 20; i++) {
        tabHitBoxeSelectionMenu[i].reset();
    }
}

void sdlJeuPasAPas::affImgInHitBox(Image& img, hitBox& hit)
{
    img.draw(renderer, hit.x1, hit.y1, hit.getLargeur(), hit.getHauteur());
}

sdlJeuPasAPas::~sdlJeuPasAPas() {

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    delete[] tabHitBoxeGrille;
    delete[] tabHitBoxeSelectionNombre;
    delete[] im_selectionChiffre;
    delete[] tabDiffCase;
}

void sdlJeuPasAPas::resetTabHitSelectionNombre() {
    for (int i = 0; i < dimGrille; i++) {
        tabHitBoxeSelectionNombre[i].x1 = 0;
        tabHitBoxeSelectionNombre[i].y1 = 0;
        tabHitBoxeSelectionNombre[i].x2 = 0;
        tabHitBoxeSelectionNombre[i].y2 = 0;
    }
}

void sdlJeuPasAPas::resetTabHitGrille() {
    for (int l = 0; l < dimGrille; l++) {
        for (int c = 0; c < dimGrille; c++) {
            tabHitBoxeGrille[l * dimGrille + c].x1 = 0;
            tabHitBoxeGrille[l * dimGrille + c].y1 = 0;
            tabHitBoxeGrille[l * dimGrille + c].x2 = 0;
            tabHitBoxeGrille[l * dimGrille + c].y2 = 0;
        }
    }
}

void sdlJeuPasAPas::sdlBoucle() {
    bool gameRunning = true;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    string txt_sdlAffTxt = "Chargement";
    sdlAffTexte(txt_sdlAffTxt , 0, 0, WIDTH / 2, ((WIDTH / 2) * 1.6)/ txt_sdlAffTxt.length());
    SDL_RenderPresent(renderer);

    if (!jeu.initDone) {
        jeu.init();
        jeu.initDone = true;
        SDL_RenderPresent(renderer);

    }
    jeu.chrono.start();
    unsigned long timeAutoSave = jeu.chrono.getTimeInSec();
    while (gameRunning) {
        sdlAff();
        if (jeu.chrono.getTimeInSec() - timeAutoSave > 30 ) {
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

            //----On fait les actions liées au differentes touches du clavier si elles sont pressées
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

            //----On fait les actions liées aux clics souris
            
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                //---Si une case devait etre change on verifie si le clic a ete effectue sur une des hit box des chiffres
                sauvegarder();

                if (l_toChange != 0) {
                    for (int i = 0; i < dimGrille; i++) {
                        if (tabHitBoxeSelectionNombre[i].is_in(mousse_x, mousse_y)) {
                            jeu.grilleJeu.grille.getCase((unsigned char)(l_toChange - 1), (unsigned char)c_toChange - 1).setVal(i + 1);

                        }
                    }
                }
                c_toChange = 0;
                l_toChange = 0;
                //---On regarde si le clic a ete effectue sur une des case de la grille, si oui: clic gauche --> Selectionne la case et affiche le menu de selection chiffre, clic droit --> vide la case
                for (int l = 0; l < dimGrille; l++) {
                    for (int c = 0; c < dimGrille; c++) {
                        if (tabHitBoxeGrille[l * dimGrille + c].is_in(mousse_x, mousse_y)) {
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
                    if (tabHitBoxeSelectionMenu[i].is_in(mousse_x, mousse_y)) {
                        cout << "clic sur la hit box: " << i << endl;
                    }
                }
                if (tabHitBoxeSelectionMenu[0].is_in(mousse_x, mousse_y)) {//Retirer les cases fausses
                    jeu.retirerCasesFausses();
                    cout << "case fausses retirees" << endl;
                }
                else if (tabHitBoxeSelectionMenu[2].is_in(mousse_x, mousse_y)) {//Afficher une case simple
                    unsigned char c_f, l_f;
                    jeu.coordCaseSimple(l_f, c_f);
                    jeu.grilleJeu.grille.getCase(l_f - 1, c_f - 1).etat = 3;
                }
                else if (tabHitBoxeSelectionMenu[4].is_in(mousse_x, mousse_y)) {//reveler un indice
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
                else if (tabHitBoxeSelectionMenu[6].is_in(mousse_x, mousse_y)) {//recommencer la meme grille
                    jeu.grilleJeu.grille = jeu.grilleOriginale.grille;

                }
                else if (tabHitBoxeSelectionMenu[8].is_in(mousse_x, mousse_y)) {//Generer une nouvelle grille
                    jeu.init();

                }
                else if (tabHitBoxeSelectionMenu[10].is_in(mousse_x, mousse_y)) {//sauvegarder
                    sauvegarder(true);
                }
                else if (tabHitBoxeSelectionMenu[12].is_in(mousse_x, mousse_y)) {//Activer sauvegarde auto
                    autoSave = true;
                }
                else if (tabHitBoxeSelectionMenu[14].is_in(mousse_x, mousse_y)) {//desactiver sauvegarde auto
                    autoSave = false;
                }
                else if (tabHitBoxeSelectionMenu[16].is_in(mousse_x, mousse_y)) {//start
                    jeu.chrono.start();
                }
                else if (tabHitBoxeSelectionMenu[18].is_in(mousse_x, mousse_y)) {//Pause
                    jeu.chrono.pause();
                }
                else if (tabHitBoxeSelectionMenu[20].is_in(mousse_x, mousse_y)) {//Pause
                    jeu.coloration = true;
                }
                else if (tabHitBoxeSelectionMenu[22].is_in(mousse_x, mousse_y)) {//Pause
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


void sdlJeuPasAPas::sauvegarder(bool force) {
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
        cout << "Abandon, sauv auto desactivée"<< endl;

    }
}


// ============= Partie affichage =============== //

void sdlJeuPasAPas::sdlAff() {

    //supprime les hitboxs de l'affichage precedent
    resetTabHitGrille();


    resetTabHitSelectionNombre();

    //Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);



    // Affiche la grille vide
    int hauteurGrille = HEIGHT * 80 / 100;
    int xGrille = HEIGHT * 10 / 100;
    int yGrille = WIDTH * 5 / 100;

    sdlAffGrille(jeu.grilleJeu, xGrille, yGrille, hauteurGrille, hauteurGrille);

    sdlAffChrono(xGrille + hauteurGrille + WIDTH * 2 / 100, yGrille, (WIDTH - hauteurGrille - xGrille) * 80 / 100, ((WIDTH - hauteurGrille - xGrille) * 80 / 100) * 1 / 10);

    // Si une valeur doit etre entree on affiche la selection 
    int selectHauteur = 0;
    int y_pos_select = yGrille + (WIDTH - hauteurGrille - xGrille) * 80 / 100 * 1 / 10 + HEIGHT * 5 / 100;

    if (l_toChange != 0) {

        selectHauteur = 40;
        sdlAffSelectionChiffre(xGrille + hauteurGrille + WIDTH * 1 / 100, y_pos_select, dimGrille * selectHauteur, selectHauteur);
    }

    sdlAffMenu(xGrille + hauteurGrille + WIDTH * 2 / 100 +20, y_pos_select + selectHauteur, hauteurGrille*80/100, hauteurGrille*80/100);

}

void sdlJeuPasAPas::sdlAffMenu(int x, int y, int largeur, int hauteur) {
    init_hit_menu(x, y , x + largeur, 0);
    for (int i = 0; i < 24; i += 2) {
        if (!tabHitBoxeSelectionMenu[i].is_in(mousse_x, mousse_y)) {
            affImgInHitBox(im_menu[i], tabHitBoxeSelectionMenu[i]);
        }
        else {
            affImgInHitBox(im_menu[i+1], tabHitBoxeSelectionMenu[i+1]);

        }

    }
}


void sdlJeuPasAPas::sdlAffSelectionChiffre(int x, int y, int largeur, int hauteur) {
    for (int i = 0; i < dimGrille; i++) {
        tabHitBoxeSelectionNombre[i].x1 = x + (i * largeur / dimGrille);
        tabHitBoxeSelectionNombre[i].x2 = tabHitBoxeSelectionNombre[i].x1 + (largeur / dimGrille);
        tabHitBoxeSelectionNombre[i].y1 = y;
        tabHitBoxeSelectionNombre[i].y2 = tabHitBoxeSelectionNombre[i].y1 + hauteur;
    }
    for (int i = 0; i < dimGrille; i++) {
        if (tabHitBoxeSelectionNombre[i].is_in(mousse_x, mousse_y)) {
            im_selectionChiffre[i + 1].draw(renderer, x, y, largeur, hauteur);
            return;
        }

    }
    im_selectionChiffre[0].draw(renderer, x, y, largeur, hauteur);




}

void sdlJeuPasAPas::sdlAffGrille(Grille& grille, int x, int y, int largeur, int hauteur, bool force) {

    jeu.colorerCase();
    im_grille.draw(renderer, x, y, largeur, hauteur);
    if (!jeu.chrono.estEnPause() || force) {
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
                    bleu.draw(renderer, x + (c)*largeurCase, y + (l)*hauteurCase, hauteurCase, largeurCase);
                    break;
                default:
                    break;
                }
                if (l_toChange != 0) {// si une case est en cours de modification, on met un fond gris sur celle ci
                    gris.draw(renderer, x + (c_toChange - 1) * largeurCase, y + (l_toChange - 1) * hauteurCase, hauteurCase, largeurCase);
                }
                if (grille.grille.getCase(l, c).getVal() != 0) {
                    if (!grille.grille.getCase(l, c).modifiable && grille.grille.getCase(l, c).etat == 0) {
                        couleur.r = 100;
                        couleur.g = 100;
                        couleur.b = 100;
                    }

                    if (grille.grille.getCase(l, c).getVal() < 10) {
                        buffConversion[0] = (int)grille.grille.getCase(l, c).getVal() + '0';
                        buffConversion[1] = '\0';
                    }
                    else {

                        buffConversion[0] = '1';
                        buffConversion[1] = (int)grille.grille.getCase(l, c).getVal() - 10 + '0';
                        buffConversion[2] = '\0';

                    }

                    //cout << "res: " << (int)grille.grille.getCase(i, c).getVal() << " n1: " << buffConversion[0] << " n2: " << buffConversion[1] << endl;
                    texte = TTF_RenderText_Blended(font, buffConversion, couleur);
                    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
                    SDL_FreeSurface(texte);

                    //on positionne le nombre au centre de la case
                    if (dimGrille > 9) {
                        if (grille.grille.getCase(l, c).getVal() < 10) {// si il n'y a qu'un chiffre
                            position.x = x + c * largeurCase + 4 * (largeurCase / 12);
                            position.y = y + l * hauteurCase + hauteurCase / 4;
                            position.w = 5 * (float)(largeurCase / 12);
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
                    int ok = SDL_RenderCopy(renderer, texte_texture, nullptr, &position);
                    SDL_DestroyTexture(texte_texture);


                    assert(ok == 0);
                }
                tabHitBoxeGrille[l * dimGrille + c].x1 = x + c * largeurCase;
                tabHitBoxeGrille[l * dimGrille + c].y1 = y + l * hauteurCase;
                tabHitBoxeGrille[l * dimGrille + c].x2 = x + c * largeurCase + largeurCase;
                tabHitBoxeGrille[l * dimGrille + c].y2 = y + l * hauteurCase + hauteurCase;
                couleur.r = 0;
                couleur.g = 0;
                couleur.b = 0;

            }
        }
    }
}

void sdlJeuPasAPas::sdlAffTexte(string txt, int x, int y, int largeur, int hauteur) {
    SDL_Color couleur = { 0, 0, 0 };
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

void sdlJeuPasAPas::sdlAffChrono(int x, int y, int largeur, int hauteur, bool full) {
    SDL_Color couleur;
    if (jeu.chrono.estEnPause()) {
        couleur.r = 255;
        couleur.g = 0;
        couleur.b = 0;
    }
    else {
        couleur.r = 0;
        couleur.g = 0;
        couleur.b = 0;
    }
    SDL_Surface* texte = nullptr;
    SDL_Rect position;
    SDL_Texture* texte_texture = nullptr;    //Create Texture pointeur
    char buffConversion[80];
    jeu.chrono.update();
    if (!full) {
        buffConversion[sprintf(buffConversion, "%luh  %lum  %lus", jeu.chrono.getTimeInHours(), jeu.chrono.getTimeInMin() % 60, jeu.chrono.getTimeInSec() % 60/*, jeu.chrono.getTimeInMSec()%1000*/) + 1] = '\0';
    }
    else {
        buffConversion[sprintf(buffConversion, "%luh  %lum  %lus %lums", jeu.chrono.getTimeInHours(), jeu.chrono.getTimeInMin() % 60, jeu.chrono.getTimeInSec() % 60, jeu.chrono.getTimeInMSec() % 1000) + 1] = '\0';

    }
    texte = TTF_RenderText_Blended(font, buffConversion, couleur);
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

void sdlJeuPasAPas::sdlAffFinDePartie()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Affiche des grilles
    int hauteurGrilles = HEIGHT * 80 / 100;
    int xGrille = HEIGHT * 10 / 100;
    int yGrille = WIDTH * 5 / 100;

    sdlAffGrille(jeu.grilleJeu, xGrille, yGrille, hauteurGrilles, hauteurGrilles, true);
    sdlAffGrille(jeu.grilleSolution, xGrille + hauteurGrilles + WIDTH * 2 / 100, yGrille, hauteurGrilles, hauteurGrilles,true);

    sdlAffChrono(xGrille, (yGrille) * 2 / 100, WIDTH * 80 / 100, yGrille * 80 / 100, true);


}



//=========== Partie gestion des aides===============//
/*
void sdlJeuPasAPas::updateDiffCase() {
    unsigned char dimGrille = jeu.grilleJeu.dim;
    for (unsigned char li = 1; li <= dimGrille; ++li) {
        for (unsigned char co = 1; co <= dimGrille; ++co) {
            if (jeu.grilleJeu.grille.getCase(li - 1, co - 1).getVal() == 0 || jeu.grilleSolution.grille.getCase(li - 1, co - 1).getVal() != jeu.grilleJeu.grille.getCase(li - 1, co - 1).getVal()) {
                // Verison nombre total indices i/c/carre
                unsigned char scoreLi = 1;
                unsigned char scoreCol = 1;
                unsigned char scoreCar = 1;

                for (unsigned char i = 0; i < dimGrille; i++) {
                    if (jeu.grilleJeu.lignes[li - 1].tabl[i]->getVal() == jeu.grilleSolution.lignes[li - 1].tabl[i]->getVal()) {
                        scoreLi = scoreLi * 2;
                    }
                    if (jeu.grilleJeu.colonnes[co - 1].tabcl[i]->getVal() == jeu.grilleSolution.colonnes[co - 1].tabcl[i]->getVal()) {
                        scoreCol = scoreCol * 2;
                    }
                    if (jeu.grilleJeu.carres[jeu.trouverNumeroCarre(li, co) - 1].tabc[i]->getVal() == jeu.grilleSolution.carres[jeu.trouverNumeroCarre(li, co) - 1].tabc[i]->getVal()) {
                        scoreCar = scoreCar * 2;
                    }
                }
                tabDiffCase[(co - 1) * dimGrille + (li - 1) + dimGrille * dimGrille] = scoreCar + scoreCol + scoreLi;
                //std::cout << "La case " << (int)li << " " << (int)co << " a un score de: " << (int)tabDiffCase[(co - 1) * dimGrille + (li - 1)] << endl;

                //version nombre d'indice different
                bool* liste_val = new bool[dimGrille];//les valeur a true sont les valeurs possibles pour la case (liste_val[0] == true veux dire que 1 est une valeur possible, liste_val[1] == false veux dire que 2 n'est pas une valeur possible...)
                for (unsigned char i = 0; i < dimGrille; i++) {
                    liste_val[i] = true;
                }
                for (unsigned char i = 0; i < dimGrille; i++) {
                    if (jeu.grilleJeu.lignes[li - 1].tabl[i]->getVal() == jeu.grilleSolution.lignes[li - 1].tabl[i]->getVal()) {
                        liste_val[jeu.grilleJeu.lignes[li - 1].tabl[i]->getVal() - 1] = false;
                    }
                    if (jeu.grilleJeu.colonnes[co - 1].tabcl[i]->getVal() == jeu.grilleSolution.colonnes[co - 1].tabcl[i]->getVal()) {
                        liste_val[jeu.grilleJeu.colonnes[co - 1].tabcl[i]->getVal() - 1] = false;
                    }
                    if (jeu.grilleJeu.carres[jeu.trouverNumeroCarre(li, co) - 1].tabc[i]->getVal() == jeu.grilleSolution.carres[jeu.trouverNumeroCarre(li, co) - 1].tabc[i]->getVal()) {
                        liste_val[jeu.grilleJeu.carres[jeu.trouverNumeroCarre(li, co) - 1].tabc[i]->getVal() - 1] = false;
                    }
                }
                tabDiffCase[(co - 1) * dimGrille + (li - 1)] = dimGrille;
                for (unsigned char i = 0; i < dimGrille; i++) {
                    if (liste_val[i]) {
                        tabDiffCase[(co - 1) * dimGrille + (li - 1)] --;
                    }
                }
                delete [] liste_val;

            }
            else {
                tabDiffCase[(co - 1) * dimGrille + (li - 1)] = 0;
            }
        }
    }
}

unsigned char sdlJeuPasAPas::getDiffCase(unsigned char l, unsigned char c, bool diff_type)//diff type = 1: retourne le nombre de valeur possibles, diff type = 0, retourne "la tendance a avoir bcp de chiffre dans un meme bloc/ligne/col permet de departager en les diff type = 1 egaux 
{
    unsigned char dimGrille = jeu.grilleJeu.dim;
    if (diff_type) {
        return tabDiffCase[(c - 1) * dimGrille + (l - 1)];
    }
    return tabDiffCase[(c - 1) * dimGrille + (l - 1) + dimGrille * dimGrille];
}

void sdlJeuPasAPas::jeu.coordCaseSimple(unsigned char& l, unsigned char& c)
{
    unsigned char dimGrille = jeu.grilleJeu.dim;
    updateDiffCase();
    unsigned char l_f = 1;
    unsigned char c_f = 1;
    unsigned char max = getDiffCase(1, 1);
    for (unsigned char li = 1; li <= dimGrille; ++li) {
        for (unsigned char co = 2; co <= dimGrille; ++co) {
            unsigned char value = getDiffCase(li, co);
            if (value > max) {
                max = getDiffCase(li, co);
                l_f = li;
                c_f = co;
            }
            else if (value == max) {
                if (getDiffCase(li, co) > getDiffCase(l_f, c_f)) {
                    l_f = li;
                    c_f = co;
                }
            }
        }
    }
    l = l_f;
    c = c_f;

}

void sdlJeuPasAPas::printTabDiff() const {

    for (int l = 0; l < jeu.grilleJeu.dim; l++) {
        for (int c = 0; c < jeu.grilleJeu.dim; c++) {
            cout << "tabDiffCase[" << l + 1 << "][" << c + 1 << "] = " << (int)tabDiffCase[c * jeu.grilleJeu.dim + l] << endl;
        }
    }
}

void sdlJeuPasAPas::retirerCasesFausses()
{
    unsigned char dimGrille = jeu.grilleJeu.dim;
    for (unsigned char li = 0; li < dimGrille; ++li) {
        for (unsigned char co = 0; co < dimGrille; ++co) {
            if (jeu.grilleJeu.grille.getCase(li, co).getVal() != jeu.grilleSolution.grille.getCase(li, co).getVal()) {
                jeu.grilleJeu.grille.getCase(li, co).setVal(0);

            }
        }
    }
}

void sdlJeuPasAPas::colorerCase(){
    if (coloration) {
        for (int l = 0; l < jeu.grilleJeu.dim; l++) {
            for (int c = 0; c < jeu.grilleJeu.dim; c++) {
                if (jeu.grilleJeu.grille.getCase(l, c).getVal() != 0 && jeu.grilleJeu.grille.getCase(l, c).modifiable && jeu.grilleJeu.grille.getCase(l, c).etat != 3) {
                    if (jeu.grilleJeu.grille.getCase(l, c).getVal() == jeu.grilleSolution.grille.getCase(l, c).getVal()) {
                        jeu.grilleJeu.grille.getCase(l, c).etat = 1;
                    }
                    else {
                        jeu.grilleJeu.grille.getCase(l, c).etat = 2;
                    }
                }
            }
        }
    }
    else {
        for (int l = 0; l < jeu.grilleJeu.dim; l++) {
            for (int c = 0; c < jeu.grilleJeu.dim; c++) {
                if (jeu.grilleJeu.grille.getCase(l, c).etat != 3) {
                    jeu.grilleJeu.grille.getCase(l, c).etat = 0;
                }
            }
        }
    }
}

*/