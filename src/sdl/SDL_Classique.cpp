#include "SDL_Classique.h"

#include <iostream>

using namespace std;

#define WIDTH 1280
#define HEIGHT 720

float temps () {
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}



// ============= CLASS SDLJEU =============== //

sdlJeuClassique::sdlJeuClassique(unsigned char d) : jeu(d), dimGrille(d), font_color() {


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

    gris.loadFromFile("data/assets/couleursDeFond/Gris.png", renderer);

    l_toChange = 0;
    c_toChange = 0;
    mousse_x = 0;
    mousse_y = 0;

    tabHitBoxGrille = new hitBox[d*d];

    init_im_menu();

}

sdlJeuClassique::sdlJeuClassique(unsigned char d, int id, unsigned long time, Grille& g_sol, Grille& g_orig, Grille& g_jeu) : jeu(d, id, time, g_sol, g_orig, g_jeu), dimGrille(d), font_color() {


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

    gris.loadFromFile("data/assets/couleursDeFond/Gris.png", renderer);

    l_toChange = 0;
    c_toChange = 0;
    mousse_x = 0;
    mousse_y = 0;

    tabHitBoxGrille = new hitBox[d*d];

    init_im_menu();

}

sdlJeuClassique::~sdlJeuClassique(){

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete[] tabHitBoxGrille;

}

void sdlJeuClassique::init_im_menu(){

    im_menu[0].loadFromFile("data/assets/menu/classique/NouvelleGrille_MousseAway.png", renderer);
    im_menu[1].loadFromFile("data/assets/menu/classique/NouvelleGrille_MousseOver.png", renderer);
    im_menu[2].loadFromFile("data/assets/menu/classique/Recommencer_MousseAway.png", renderer);
    im_menu[3].loadFromFile("data/assets/menu/classique/Recommencer_MousseOver.png", renderer);
    im_menu[4].loadFromFile("data/assets/menu/classique/Start_MousseAway.png", renderer);
    im_menu[5].loadFromFile("data/assets/menu/classique/Start_MousseOver.png", renderer);
    im_menu[6].loadFromFile("data/assets/menu/classique/Pause_MousseAway.png", renderer);
    im_menu[7].loadFromFile("data/assets/menu/classique/Pause_MousseOver.png", renderer);
}


void sdlJeuClassique::init_hit_menu(int x1, int y1, int x2, int y2){

    resetTabHitSelectionMenu();

    const int nb_element = 9;

    if (y2 == 0) {

        y2 = (x2 - x1) * nb_element /11;//on respecte le format par defaut pour que la police ne soit pas deformée
    }

    int y1courant = y1;
    int y2courant = 0;

    y2courant = y1courant + y2 / nb_element;
    tabHitBoxSelectionMenu[0].x1 = x1;
    tabHitBoxSelectionMenu[0].x2 = x2;
    tabHitBoxSelectionMenu[0].y1 = y1courant;
    tabHitBoxSelectionMenu[0].y2 = y2courant;
    tabHitBoxSelectionMenu[1].x1 = x1;
    tabHitBoxSelectionMenu[1].x2 = x2;
    tabHitBoxSelectionMenu[1].y1 = y1courant;
    tabHitBoxSelectionMenu[1].y2 = y2courant;

    for (int i = 2; i < 8; i = i+2) {

        y1courant = y2courant;
        y2courant = y1courant + y2 / nb_element;

        tabHitBoxSelectionMenu[i].x1 = x1;
        tabHitBoxSelectionMenu[i].x2 = x2;
        tabHitBoxSelectionMenu[i].y1 = y1courant;
        tabHitBoxSelectionMenu[i].y2 = y2courant;
        tabHitBoxSelectionMenu[i+1].x1 = x1;
        tabHitBoxSelectionMenu[i+1].x2 = x2;
        tabHitBoxSelectionMenu[i+1].y1 = y1courant;
        tabHitBoxSelectionMenu[i+1].y2 = y2courant;
    }

}


void sdlJeuClassique::resetTabHitSelectionMenu(){

    for (int i = 0; i < 8; i++) {

        tabHitBoxSelectionMenu[i].reset();

    }
}


void sdlJeuClassique::resetTabHitGrille() {

    for (int l = 0; l < dimGrille; l++) {
        for (int c = 0; c < dimGrille; c++) {
            tabHitBoxGrille[l * dimGrille + c].reset();
        }
    }
}



void sdlJeuClassique::sdlAff(){

    //supprime les hitboxs de l'affichage precedent
    resetTabHitGrille();

    //Remplir l'écran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Affiche la grille vide
    sdlAffGrille(jeu.grilleJeu, 10, 80, 600, 600);
    sdlAffChrono(620, 80, 400, 100);

    
    int hauteurGrille = HEIGHT * 80 / 100;
    int xGrille = HEIGHT * 10 / 100;
    int yGrille = WIDTH * 5 / 100;
    int selectHauteur = 0;
    int y_pos_select = yGrille + (WIDTH - hauteurGrille - xGrille) * 80 / 100 * 1 / 10 + HEIGHT * 5 / 100;

    sdlAffMenu(xGrille + hauteurGrille + WIDTH * 2 / 100 +20, y_pos_select + selectHauteur, hauteurGrille*80/100, hauteurGrille*80/100);
    


}

void sdlJeuClassique::sdlAffGrille(Grille& grille, int x, int y, int largeur, int hauteur, bool force) {

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

                if (l_toChange != 0) { // si une case est en cours de modification, on met un fond gris sur celle ci

                    gris.draw(renderer, x + (c_toChange - 1) * largeurCase, y + (l_toChange - 1) * hauteurCase, hauteurCase, largeurCase);

                }

                if (grille.grille.getCase(l, c).getVal() != 0) {

                    if (grille.grille.getCase(l, c).getVal() < 10) {

                        buffConversion[0] = (int)grille.grille.getCase(l, c).getVal() + '0';
                        buffConversion[1] = '\0';

                    }
                    else {

                        buffConversion[0] = '1';
                        buffConversion[1] = (int)grille.grille.getCase(l, c).getVal() - 10 + '0';
                        buffConversion[2] = '\0';

                    }
                
                    //cout << "res: " << (int)grille.grille.getCase(l, c).getVal() << " n1: " << buffConversion[0] << " n2: " << buffConversion[1] << endl;
                    texte = TTF_RenderText_Blended(font, buffConversion, couleur);
                    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
                    SDL_FreeSurface(texte);

                    //on positionne le nombre au centre de la case
                    if (dimGrille > 9) {

                        if (grille.grille.getCase(l, c).getVal() < 10) {// si il n'y a qu'un chiffre
                            position.x = x + c * largeurCase + 4*(largeurCase / 12);
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

                //on initialise les coordonnées des cases

                tabHitBoxGrille[l * dimGrille + c].x1 = x + c * largeurCase;
                tabHitBoxGrille[l * dimGrille + c].y1 = y + l * hauteurCase;
                tabHitBoxGrille[l * dimGrille + c].x2 = x + c * largeurCase + largeurCase;
                tabHitBoxGrille[l * dimGrille + c].y2 = y + l * hauteurCase + hauteurCase;

            }
        }

    }
}

void sdlJeuClassique::sdlAffChrono(int x, int y, int largeur, int hauteur) {

    jeu.chrono.update();// a enlever apres les tests, ne doit pas être la
    SDL_Color couleur = { 0, 0, 0 };
    SDL_Surface* texte = nullptr;
    SDL_Rect position;
    SDL_Texture* texte_texture = nullptr;    //Create Texture pointeur
    char buffConversion[80];
    buffConversion[sprintf(buffConversion, "%luh  %lum  %lus", jeu.chrono.getTimeInHours(), jeu.chrono.getTimeInMin()%60, jeu.chrono.getTimeInSec()%60/*, jeu.chrono.getTimeInMSec()%1000*/)+1] = '\0';
    texte = TTF_RenderText_Blended(font, buffConversion, couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);


    position.x = x ;
    position.y = y ;
    position.w = largeur;
    position.h = hauteur;
                
    int ok = SDL_RenderCopy(renderer, texte_texture, nullptr, &position);
    SDL_DestroyTexture(texte_texture);
    assert(ok == 0);
}

void sdlJeuClassique::sdlAffMenu(int x, int y, int largeur, int hauteur){

    init_hit_menu(x, y , x + largeur, 0);

    for (int i = 0; i < 8; i += 2) {
        if (!tabHitBoxSelectionMenu[i].is_in(mousse_x, mousse_y)) {

            affImgInHitBox(im_menu[i], tabHitBoxSelectionMenu[i]);
        }
        else {
            affImgInHitBox(im_menu[i+1], tabHitBoxSelectionMenu[i+1]);

        }

    }

}

void sdlJeuClassique::affImgInHitBox(Image& img, hitBox& hit){

    img.draw(renderer, hit.x1, hit.y1, hit.getLargeur(), hit.getHauteur());

}

void sdlJeuClassique::sdlAffFinDePartie() {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Affiche des grilles
    int hauteurGrilles = HEIGHT * 80 / 100;
    int xGrille = HEIGHT * 10 / 100;
    int yGrille = WIDTH * 5 / 100;

    sdlAffGrille(jeu.grilleJeu, xGrille, yGrille, hauteurGrilles, hauteurGrilles, true);
    sdlAffGrille(jeu.grilleSolution, xGrille + hauteurGrilles + WIDTH * 2 / 100, yGrille, hauteurGrilles, hauteurGrilles, true);

    sdlAffChrono(xGrille, (yGrille) * 2 / 100, WIDTH * 80 / 100, yGrille * 80 / 100);

}

void sdlJeuClassique::sdlBoucle(){

    bool gameRunning = true;
    SDL_Event event;

    if (!jeu.initDone) {
        jeu.init();
        jeu.initDone = true;
    }

    while (gameRunning) {

        sdlAff();

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
                        jeu.chrono.pause();
                        break;

                    case SDLK_s: //start
                        jeu.chrono.start();
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

                for (int i = 0; i < 8; i++) {
                    if (tabHitBoxSelectionMenu[i].is_in(mousse_x, mousse_y)) {
                        cout << "clic sur la hit box: " << i << endl;
                    }
                }

                if (tabHitBoxSelectionMenu[0].is_in(mousse_x, mousse_y)) {//Nouvelle grille
                    jeu.init();
                }

                if (tabHitBoxSelectionMenu[2].is_in(mousse_x, mousse_y)) {//Recommencer sur la meme grille
                    jeu.grilleJeu.grille = jeu.grilleOriginale.grille;
                }

                if (tabHitBoxSelectionMenu[4].is_in(mousse_x, mousse_y)) {//Start
                    jeu.chrono.start();
                }

                if (tabHitBoxSelectionMenu[6].is_in(mousse_x, mousse_y)) {//Pause
                    jeu.chrono.pause();
                }
            }
        }

        if(jeu.verifGrillePleine(jeu.grilleJeu)){

            jeu.chrono.pause();
            sdlAffFinDePartie();

        }

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer); 
    }

}