// Demineur.c : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL.h>


void draw_rectangle_fill(SDL_Renderer*, const SDL_Rect*, const SDL_Color*);

int main(int argc, char* args[])
{
    SDL_Window* fenetre;
    SDL_Renderer* renderer; // Déclaration du renderer
    //SDL_Texture* monImage; // Déclaration d'une texture
    SDL_Event events;
    SDL_bool run = SDL_TRUE;

    SDL_Rect cases[100];
    SDL_Point ligne_depart, ligne_arrivee;

    if (SDL_VideoInit(NULL) < 0) // Initialisation de la SDL
    {
        printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
        return -1;
    }

    // Création de la fenêtre :
    fenetre = SDL_CreateWindow("Une fenetre SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
    if (fenetre == NULL) // Gestion des erreurs
    {
        printf("Erreur lors de la creation d'une fenetre : %s", SDL_GetError());
        return -1;
    }

    // Création du renderer :
    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Création du renderer
    if (renderer == NULL) // Gestion des erreurs
    {
        printf("Erreur lors de la creation d'un renderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    // Importation de l'image de fond
    SDL_Surface* image = SDL_LoadBMP("img/pixil-frame-0.bmp");
    if (!image)
    {
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
        return -1;
    }
    //La texture monImage contient maintenant l'image importée
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(renderer, image);

    while (run) {

        // Affichage de la texture
        SDL_Rect position;
        position.x = 0;
        position.y = 0;
        SDL_QueryTexture(monImage, NULL, NULL, &position.w, &position.h);
        SDL_RenderCopy(renderer, monImage, NULL, &position);

        // Creation du rectangle de jeu
        SDL_Rect rectangle;
        rectangle.x = 100;
        rectangle.y = 100;
        rectangle.w = 300;
        rectangle.h = 300;

        // Dessine le rectangle de jeu
        // SDL_Color color = { 255, 255, 255, 255 };
        // draw_rectangle_fill(renderer, &rectangle, &color);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        cases[0].x = cases[0].y = 100;
        cases[0].w = cases[0].h = 30;

        for (int i = 1; i != 100; i++) {
            cases[i].x = cases[i - 1].x + 30;
            cases[i].y = cases[i - 1].y;

            if (i % 10 == 0) {
                cases[i].x = (i % 100 == 0) ? 0 : 100;
                cases[i].y = cases[i - 1].y + 30;
            }
            cases[i].w = cases[i].h = 30;
        }

        if (SDL_RenderFillRects(renderer, cases, 100) < 0) {
            printf("Erreur lors des ramplissages de rectangles: %s", SDL_GetError());
            return -1;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Lignes horizontales
        ligne_depart.x = 100;
        ligne_arrivee.x = 400;
        ligne_depart.y = 100;
        for (int i = 0; i != 10; i++)
        {
            ligne_depart.y += 30;
            ligne_arrivee.y = ligne_depart.y;
            SDL_RenderDrawLine(renderer, ligne_depart.x, ligne_depart.y, ligne_arrivee.x, ligne_arrivee.y);
        }

        // Lignes verticales
        ligne_depart.x = 100;
        ligne_depart.y = 100;
        ligne_arrivee.y = 400;
        for (int i = 0; i != 10; i++)
        {
            ligne_depart.x += 30;
            ligne_arrivee.x = ligne_depart.x;
            SDL_RenderDrawLine(renderer, ligne_depart.x, ligne_depart.y, ligne_arrivee.x, ligne_arrivee.y);
        }

        // Toujours penser au rendu, sinon on n'obtient rien du tout
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&events)) {
            switch (events.type) {
            case SDL_WINDOWEVENT:
                if (events.window.event == SDL_WINDOWEVENT_CLOSE)
                    run = SDL_FALSE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (events.button.button == SDL_BUTTON_LEFT)
                    SDL_Log("+left");
                if (events.button.button == SDL_BUTTON_RIGHT)
                    SDL_Log("+right");
                break;
            }
        }
        SDL_RenderClear(renderer);
    }

    //SDL_Delay(20000);  Pause de 20 secondes, pour admirer notre œuvre autant que l'on veut
    // Vous remarquerez d'ailleurs une illusion d'optique : quelques lignes paraissent plus grosses que d'autres

    // Destruction du renderer et de la fenêtre :
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);

    //Équivalent du destroyTexture pour les surface, permet de libérer la mémoire quand on n'a plus besoin d'une surface  SDL_FreeSurface(image); 

    SDL_Quit(); // On quitte la SDL
}

void draw_rectangle_fill(SDL_Renderer* renderer, const SDL_Rect* rectangle, const SDL_Color* color)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

    for (auto y = rectangle->y; y < rectangle->y + rectangle->h; y++)
    {
        for (auto x = rectangle->x; x < rectangle->x + rectangle->w; x++)
        {
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}



// création de valeur général a toute les fonctions a l'aide de macro

#define SIZE 10
#define TOTAL_SIZE (SIZE * SIZE)
#define BOMB_COUNT TOTAL_SIZE/5

// initialisation d'une structure regroupant les coordonnées des bombes

typedef struct Point Point;

// initialisation des fonctions secondaires

int getIndex2D(int, int);
void getIndex1D(int, int*, int*);
void random_bomb(Point[BOMB_COUNT]);
void manual_bomb(Point[BOMB_COUNT]);
int double_finder(Point[BOMB_COUNT], int, int);
void dig(char*, Point[BOMB_COUNT]);
void flag(char*);
void spread(char*, Point[BOMB_COUNT], int, int);
int is_bomb(Point[BOMB_COUNT], int, int);
int bomb_around(char*, Point[BOMB_COUNT], int, int);
void win(char*, Point[BOMB_COUNT]);
void delay(int);

// création d'une structure regroupant les coordonnées des bombes

struct Point
{
    int x;
    int y;
};

// création de la fonction principale du démineur

int main2()
{
    int i;
    int j;
    char tableau_jeu[TOTAL_SIZE];
    Point tableau_bombe[BOMB_COUNT];
    int choix;
    int app = 0;

    random_bomb(tableau_bombe);
    //manual_bomb(tableau_bombe);

    for (i = 0; i < TOTAL_SIZE; i++)
    {
        tableau_jeu[i] = '_';
    }

    while(1)
    {

        // affichage des numéros de lignes et colonnes

        printf("    0  1  2  3  4  5  6  7  8  9\n");
        for (j = 0; j < SIZE; j++)
        {
            printf(" %d ", j);
            for (i = 0; i < SIZE; i++)
            {
               // Permets d'afficher les bombes sur la grille de jeu pour effectuer des test administrateurs

               /* if (is_bomb(tableau_bombe, j, i) == 1) {
                    tableau_jeu[getIndex2D(j, i)] = 'x';
               }*/

                // affichage du tableau de jeu

                printf("[%c]", tableau_jeu[j* SIZE +i]);

            }
            printf("\n");
        }

        // Permets d'afficher les bombes sous la forme d'une liste de coordonés pour effectuer des test administrateurs

        /*printf(" Bombe :");
        printf("\n"); 

        for (i = 0; i <= BOMB_COUNT; i++)
        {
            if (app <= 5) {
                printf(" %d %d /", tableau_bombe[i].x, tableau_bombe[i].y);
                app++;
            }
            else {
                printf("\n");
                app = 0;
            }
        }
        printf("\n");
        printf("\n");*/

        // demande au joueur l'action qu'il veut effectuer

        printf(" Choisissez 0:creuser , 1:poser drapeau");
        scanf_s("%d", &choix);
        if (choix == 0) {
            dig(tableau_jeu, tableau_bombe);
        }
        if (choix == 1) {
            flag(tableau_jeu);
        }

        // appel de la fonction de victoire

        win(tableau_jeu, tableau_bombe);
        system("cls");
    }

    return 0;
}

// création des fonctions permettant de passer de coordonnées 1 dimension a 2 dimensions ou inversement 

int getIndex2D(int x, int y)
{
    return x * SIZE + y;
}

void getIndex1D(int i, int * x, int * y)
{
    *x = i / SIZE; // dizaine
    *y = i % SIZE; // unitée
}

// création de des fonction permettant de gérer les bombes de facon random ou manuel et d'éviter d'avoir deux bombe sur une case

void random_bomb(Point tableau_bombe[BOMB_COUNT])
{
    int a = 0;
    int b = 0;
    srand(time(NULL));

    for (int i = 0; i <= BOMB_COUNT; i++) {
        a++;
    }

    while (a > 0) {

        int indice_x = rand() % SIZE;
        int indice_y = rand() % SIZE;

        if (double_finder(tableau_bombe, indice_x, indice_y) == 0) {
            tableau_bombe[b].x = indice_x;
            tableau_bombe[b].y = indice_y;
            a = a - 1;
            b++;
        }
    }
}

void manual_bomb(Point tableau_bombe[BOMB_COUNT])
{
    int indice_x;
    int indice_y;

    for (int i = 0; i <= BOMB_COUNT; i++) {
        tableau_bombe[i].x = -1;
        tableau_bombe[i].y = -1;
    }

    tableau_bombe[0].x = 3;
    tableau_bombe[0].y = 0;

    tableau_bombe[1].x = 3;
    tableau_bombe[1].y = 1;

    tableau_bombe[2].x = 3;
    tableau_bombe[2].y = 2;

    tableau_bombe[3].x = 3;
    tableau_bombe[3].y = 3;

    tableau_bombe[4].x = 3;
    tableau_bombe[4].y = 4;

    tableau_bombe[5].x = 3;
    tableau_bombe[5].y = 5;

    tableau_bombe[6].x = 2;
    tableau_bombe[6].y = 5;

    tableau_bombe[7].x = 1;
    tableau_bombe[7].y = 5;
    
    tableau_bombe[8].x = 0;
    tableau_bombe[8].y = 5;

    tableau_bombe[9].x = 4;
    tableau_bombe[9].y = 9;
}

int double_finder(Point tableau_bombe[BOMB_COUNT], int indice_x, int indice_y) {

    int x = 0;

    for (int i = 0; i < BOMB_COUNT; i++) {
        
        if (tableau_bombe[i].x == indice_x && tableau_bombe[i].y == indice_y) {
            x++;
        }
    }

    if (x == 0) {
        return 0;
    }
    else {
        return 1;
    }
}

// création de la fonction permettant de creuser une case

void dig(char* tableau_jeu, Point tableau_bombe[BOMB_COUNT])
{
    int i;
    int indice_x;
    int indice_y;

    printf(" Choisissez une ligne ou jouer:");
    scanf_s("%d", &indice_x);
    printf(" Choisissez une colone ou jouer:");
    scanf_s("%d", &indice_y);

    // vérification que l'indice saisie soit dans la grille de jeu

    if (-1 >= indice_x || indice_x >= SIZE || -1 >= indice_y || indice_y >= SIZE) {
        printf("Indice non valide\n");
        delay(1);
        return;
    }

    // si l'indice saisie est une bombe, la partie est perdue

    else if (-1 < indice_x < SIZE && -1 < indice_y < SIZE) {
        for (i = 0; i < BOMB_COUNT; i++)
        {
            if (tableau_bombe[i].x == indice_x && tableau_bombe[i].y == indice_y) {
                printf("PERDU");
                delay(1);
                abort();
            }
        }
        spread(tableau_jeu, tableau_bombe, indice_x, indice_y);
    }
}

// création de la fonction permettant de poser un drapeau

void flag(char *tableau_jeu)
{
    int indice;
    printf("Choisissez une case ou poser un drapeau entre 0 et %d :", TOTAL_SIZE - 1);
    scanf_s("%d", &indice);

    // vérification que la case choisie ne soit pas déjà creusée et soit dans la grille de jeu

    if(tableau_jeu[indice] != '_') {
        printf("Case deja creusee\n");
        delay(1);
        return;
    }
    else if (-1 < indice && indice < TOTAL_SIZE - 1) {
        tableau_jeu[indice] = 'P';
    }
    else {
        printf("Indice non valide\n");
        delay(1);
        return;
    }

}

// création de la fonction permettant de creuser automatiquement jusqu'à une case a proximité d'une bombe

void spread(char* tableau_jeu, Point tableau_bombe[BOMB_COUNT], int indice_x, int indice_y)
{
    
    // si on dépasse le tableau (x, y) on part de la fonction
    if (!(0 <= indice_x && indice_x < SIZE && 0 <= indice_y && indice_y < SIZE)) {
        return;
    }

    // si la case est déjà revelé on sort de la fonction
    else if (tableau_jeu[getIndex2D(indice_x, indice_y)] != '_') {
        return;
    }

    // si la case est differente de '0' on part de la fonction
    if (bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y) != 0) {
        return;
    }

    // on rappelle spread sur les 8 cases autours
    else {
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                 spread(tableau_jeu, tableau_bombe, indice_x + i, indice_y + j);
            }
        }
    }
}

// création de la fonction permettant de savoir si la case introduite est une bombe ou non

int is_bomb(Point tableau_bombe[BOMB_COUNT], int indice_x, int indice_y)
{
    int vrai = 0;

    for (int i = 0; i < BOMB_COUNT; i++)
    {
        if (tableau_bombe[i].x == indice_x && tableau_bombe[i].y == indice_y && tableau_bombe[i].x >= 0 && tableau_bombe[i].y >= 0) {
            vrai = 1;
        }
    }
    return vrai;
}

// création de la fonction permettant d'indiquer le nombre de bombe autour de la case introduite

int bomb_around(char *tableau_jeu, Point tableau_bombe[BOMB_COUNT], int indice_x, int indice_y)
{
    int nb_bombe = 0;
    char int_str[2];

    // vérification si il y a des bombes autour de la case creusée spécifique aux quatres coins du tableau de jeu

    if (indice_x == 0 && indice_y == 9) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x, indice_y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x + 1, indice_y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x + 1, indice_y);
    }
    else if (indice_x == 9 && indice_y == 0) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x - 1, indice_y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x - 1, indice_y + 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x, indice_y + 1);
    }
    else if (indice_x == 9 && indice_y == 9) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x - 1, indice_y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x - 1, indice_y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x, indice_y - 1);
    }
    else if (indice_x == 0 && indice_y == 0) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x, indice_y + 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x + 1, indice_y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x + 1, indice_y + 1);
    }

    // vérification si il y a des bombes autour de la case creusée spécifique aux quatres cotés du tableau de jeu

    else if (indice_x == 0) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x, indice_y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x , indice_y + 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x + 1, indice_y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x + 1, indice_y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x + 1, indice_y + 1);
    }
    else if (indice_x == 9) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x, indice_y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x, indice_y + 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x - 1, indice_y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x - 1, indice_y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x - 1, indice_y + 1);
    }
    else if (indice_y == 9) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x - 1, indice_y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x + 1, indice_y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x - 1, indice_y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x, indice_y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x + 1, indice_y - 1);
    }
    else if (indice_y == 0) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x - 1, indice_y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x + 1, indice_y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x - 1, indice_y + 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x, indice_y + 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x + 1, indice_y + 1);

    }

    // vérification si il y a des bombes autour de la case creusée quand on se situe ni dans les coins ni sur les cotés ni dans les coins du tableau de jeu

    else {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x + i, indice_y + j);
            }
        }
    }

    // affichage du nombres de bombes atour de la case creusée, sur celle-ci

    sprintf_s(int_str, 2, "%d", nb_bombe);
    tableau_jeu[getIndex2D(indice_x,indice_y)] = int_str[0];
    return nb_bombe;
}

// création de la fonction de victoire

void win(char* tableau_jeu, Point tableau_bombe[BOMB_COUNT])
{
    int nb_cases = 0;
    int x = 0;
    int y = 0;

    // vérification si la totalité des cases sont révélées excéptées les bombes

    for (int i = 0; i < TOTAL_SIZE; i++)
    {
        getIndex1D(i, &x, &y);

        if (is_bomb(tableau_bombe, x, y) == 0) {
            if (tableau_jeu[i] != '_') {
                nb_cases++;
            }
        }
    }
    if (nb_cases == TOTAL_SIZE - BOMB_COUNT) {
        printf("VICTOIRE !");
        delay(1);
        abort();
    }
}

// création de la fonction permettant de laisser des information affiché un certain temps dans la console

void delay(int temps)
{
    int seconds = 1000 * temps;
    clock_t start = clock();

    while (clock() < start + seconds);
}
