#include "SDL_PasAPas.h"
#include <iostream>
using namespace std;

#define WIDTH 1024
#define HEIGHT 576

float sdlJeuPasAPas::temps() {
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC;  // conversion des ms en secondes en divisant par 1000
}



// ============= CLASS SDLJEU =============== //

sdlJeuPasAPas::sdlJeuPasAPas(unsigned char d) : jeu(d), dimGrille(d) {

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
    if (window == NULL)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //creation du rendu : 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
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
    tabHitBoxeSelectionNombre = new hitBox[d];
    im_selectionChiffre = new Image[d];
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
    }//Chargement des images pour la selection du chiffre a plac�
    l_toChange = 0;
    c_toChange = 0;
    mousse_x = 0;
    mousse_y = 0;
    finDePartie = false;
    tabDiffCase = new unsigned char[2 * d * d];

}

sdlJeuPasAPas::~sdlJeuPasAPas() {

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete []tabHitBoxeGrille;
    delete[]tabHitBoxeSelectionNombre;
    delete[]im_selectionChiffre;
    delete[]tabDiffCase;

}

void sdlJeuPasAPas::resetTabHitSelectionNombre() {
    for (int i = 0; i < dimGrille; i++) {
        tabHitBoxeSelectionNombre[i].x1 = 0;
        tabHitBoxeSelectionNombre[i].y1 = 0;
        tabHitBoxeSelectionNombre[i].x2 = 0;
        tabHitBoxeSelectionNombre[i].y2 = 0;
    }
}

void sdlJeuPasAPas::sdlAff() {
    //supprime les hitboxe de i'affichage precendent
    resetTabHitGrille();
    resetTabHitSelectionNombre();
    //Remplir i'écran de blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);



    // Affiche la grille vide
    int hauteurGrille = HEIGHT * 80 / 100;
    int xGrille = HEIGHT * 10 / 100;
    int yGrille = WIDTH * 5 / 100;

    sdlAffGrille(jeu.grilleJeu, xGrille, yGrille, hauteurGrille, hauteurGrille);
    sdlAffChrono(xGrille + hauteurGrille + WIDTH * 2 / 100 , yGrille, (WIDTH-hauteurGrille-xGrille) * 80/100, (yGrille, (WIDTH - hauteurGrille - xGrille) * 80 / 100)*1/10);

    // Si une valeur doit �tre entree on affiche le menu 
    if (l_toChange != 0) {
        int selectHauteur = 40;
        sdlAffSelectionChiffre(620, 200, dimGrille * selectHauteur, selectHauteur);
    }
}

void sdlJeuPasAPas::sdlAffSelectionChiffre(int x, int y, int largeur, int hauteur) {
    for (int i = 0; i < dimGrille; i++) {
        tabHitBoxeSelectionNombre[i].x1 = x + (i * largeur/dimGrille);
        tabHitBoxeSelectionNombre[i].x2 = tabHitBoxeSelectionNombre[i].x1 + (largeur / dimGrille);
        tabHitBoxeSelectionNombre[i].y1 = y;
        tabHitBoxeSelectionNombre[i].y2 = tabHitBoxeSelectionNombre[i].y1 + hauteur;
    }
    for (int i = 0; i < dimGrille; i++) {
        if (tabHitBoxeSelectionNombre[i].is_in(mousse_x, mousse_y)) {
            im_selectionChiffre[i+1].draw(renderer, x, y, largeur, hauteur);
            return;
        }

    }
    im_selectionChiffre[0].draw(renderer, x, y, largeur, hauteur);




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

void sdlJeuPasAPas::sdlAffGrille(Grille& grille, int x, int y, int largeur, int hauteur) {
    im_grille.draw(renderer, x, y, largeur, hauteur);
    SDL_Color couleur = { 0, 0, 0 };
    SDL_Surface* texte = nullptr;
    SDL_Rect position;
    SDL_Texture* texte_texture = NULL;    //Create Texture pointer

    int dimGrille = (int)grille.dim;
    int largeurCase = largeur / dimGrille;
    int hauteurCase = hauteur / dimGrille;
    if (l_toChange != 0) {// si une case est en cours de modification, on met un fond gris sur celle ci
        gris.draw(renderer, x + (c_toChange-1) * largeurCase, y + (l_toChange-1)*hauteurCase, hauteurCase, largeurCase);
    }



    char* buffConversion = new char[3];
    for (int l = 0; l < dimGrille; l++) {
        for (int c = 0; c < dimGrille; c++) {
            switch ((int)grille.grille.getCase(l, c).etat)
            {
            case 0:
                couleur = { 0, 0, 0 };

                break;
            case 1:
                couleur = { 0, 255, 0 };
                break;
            case 2:
                couleur = { 255, 0, 0 };
                break;
            case 3:
                bleu.draw(renderer, x + (c - 1) * largeurCase, y + (l - 1) * hauteurCase, hauteurCase, largeurCase);
                break;
            default:
                break;
            }
            if (grille.grille.getCase(l, c).getVal() != 0) {
                if (!grille.grille.getCase(l, c).modifiable) {
                    couleur.r = 255;
                    couleur.g = 0;
                    couleur.b = 0;
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

                //on positionne le nombre au centre de ca case
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
                int ok = SDL_RenderCopy(renderer, texte_texture, NULL, &position);
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
    delete[]buffConversion;
}

void sdlJeuPasAPas::sdlAffChrono(int x, int y, int largeur, int hauteur,bool full) {
    SDL_Color couleur = { 0, 0, 0 };
    SDL_Surface* texte = nullptr;
    SDL_Rect position;
    SDL_Texture* texte_texture = NULL;    //Create Texture pointer
    char buffConversion[80];
    jeu.chrono.update();
    if (!full) {
        buffConversion[sprintf(buffConversion, "%luh  %lum  %lus", jeu.chrono.getTimeInHours(), jeu.chrono.getTimeInMin() % 60, jeu.chrono.getTimeInSec() % 60/*, jeu.chrono.getTimeInMSec()%1000*/) + 1] = '\0';
    }
    else {
        buffConversion[sprintf(buffConversion, "%luh  %lum  %lus %lums", jeu.chrono.getTimeInHours(), jeu.chrono.getTimeInMin() % 60, jeu.chrono.getTimeInSec() % 60, jeu.chrono.getTimeInMSec()%1000) + 1] = '\0';

    }
    texte = TTF_RenderText_Blended(font, buffConversion, couleur);
    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);


    position.x = x;
    position.y = y;
    position.w = largeur;
    position.h = hauteur;

    int ok = SDL_RenderCopy(renderer, texte_texture, NULL, &position);
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

    sdlAffGrille(jeu.grilleJeu, xGrille, yGrille, hauteurGrilles, hauteurGrilles);
    sdlAffGrille(jeu.grilleSolution, xGrille + hauteurGrilles + WIDTH * 2/100, yGrille, hauteurGrilles, hauteurGrilles);

    sdlAffChrono(xGrille , (yGrille)*2/100, WIDTH * 80 / 100, yGrille * 80/100,true);


}

void sdlJeuPasAPas::sdlBoucle() {
    bool gameRunning = true;
    SDL_Event event;
    if (!jeu.initDone) {
        jeu.init();
        jeu.initDone = true;
    }
    jeu.chrono.start();
    while (gameRunning) {

        while (SDL_PollEvent(&event))
        {
            sdlAff();
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
                case SDLK_a:
                    retirerCasesFausses();
                    cout << "case fausses retirees" << endl;
                    break;
                case SDLK_b:
                    unsigned char c_f, l_f;
                    coordCaseSimple(l_f, c_f);
                    jeu.grilleJeu.grille.getCase(l_f, c_f).etat = 3;
                    break;
                case SDLK_c:

                {bool aideRemplir = false;
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
                        aideRemplir = true; //aide � savoir si la valeur � �t� plac�e
                    }

                } while (aideRemplir == false && essaie < 500);
                jeu.grilleJeu.grille.getCase(l - 1, c - 1).modifiable = false;
                break; }
                case SDLK_d:
                    jeu.grilleJeu.grille = jeu.grilleOriginale.grille;

                    break;
                case SDLK_e:
                    jeu.init();
                    break;
                default:
                    break;
                }
            }

            //----On fait les actions liées aux clics souris

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                //---Si une case devait �tre chang� on verifie si le clic a �t� effectu� sur une des hit box des chiffres
                if (l_toChange != 0) {
                    for (int i = 0; i < dimGrille; i++) {
                        if (tabHitBoxeSelectionNombre[i].is_in(mousse_x, mousse_y)) {
                            jeu.grilleJeu.grille.getCase(l_toChange - 1, c_toChange - 1).setVal(i + 1);
                        }
                    }
                }
                c_toChange = 0;
                l_toChange = 0;
                //---On regarde si le clic a �t� effectu� sur une des case de la grille, si oui: clic gauche --> Selectionne la case et affiche le menu de selection chiffre, clic droit --> vide la case
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

            }
        }
      
        if (jeu.verifGrillePleine(jeu.grilleJeu)) {

            jeu.chrono.pause();
            sdlAffFinDePartie();
            finDePartie = true;

        }
        
        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }
}


//=========== Partie gestion des aides===============//

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
                bool* liste_val = new bool[dimGrille];//les valeur a true sont les valeurs possible pour la case (liste_val[0] == true veux dire que 1 est une valeur possible, liste_val[1] == false veux dire que 2 n'est pas  une valeur possible...)
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

            }
            else {
                tabDiffCase[(co - 1) * dimGrille + (li - 1)] = 0;
            }
        }
    }
}

unsigned char sdlJeuPasAPas::getDiffCase(unsigned char l, unsigned char c, bool diff_type)//diff type = 1: retourne le nombre de valeur possible, diff type = 0, retourne "la tendance a avoir bcp de chiffre dans un meme bloc/ligne/col permet de departager en les diff type = 1 egaux 
{
    unsigned char dimGrille = jeu.grilleJeu.dim;
    if (diff_type) {
        return tabDiffCase[(c - 1) * dimGrille + (l - 1)];
    }
    return tabDiffCase[(c - 1) * dimGrille + (l - 1) + dimGrille * dimGrille];
}

void sdlJeuPasAPas::coordCaseSimple(unsigned char& l, unsigned char& c)
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
