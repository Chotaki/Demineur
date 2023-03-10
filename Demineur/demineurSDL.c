
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// création de valeures générales pour toutes les fonctions

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
void dig(char*, Point[BOMB_COUNT], int, int);
void flag(char*, int, int);
void spread(char*, Point[BOMB_COUNT], int, int);
int is_bomb(Point[BOMB_COUNT], int, int);
int bomb_around(char*, Point[BOMB_COUNT], int, int);
void win(char*, Point[BOMB_COUNT]);
void changeCases(char, Point[BOMB_COUNT], int, int, SDL_Renderer*, SDL_Texture**, SDL_Rect*);

// création d'une structure regroupant les coordonnées des bombes

struct Point
{
    int x;
    int y;
};

int main(int argc, char* args[])
{
    int i = 0;
    int j = 0;
    int X = 0;
    int Y = 0;
    char tableau_jeu[TOTAL_SIZE];
    Point tableau_bombe[BOMB_COUNT];
    int app = 0;
    int needRender = 0;
    
    SDL_Window* fenetre;
    SDL_Renderer* renderer; // déclaration du renderer
    SDL_bool run = SDL_TRUE;
    SDL_Event events;
    SDL_Point ligne_depart, ligne_arrivee;
    SDL_Rect cases[100];

    if (SDL_VideoInit(NULL) < 0) // initialisation de la SDL
    {
        printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
        return -1;
    }

    // création de la fenêtre :
    fenetre = SDL_CreateWindow("MineSweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
    if (fenetre == NULL) // gestion des erreurs
    {
        printf("Erreur lors de la creation d'une fenetre : %s", SDL_GetError());
        return -1;
    }
    
    // création du renderer :
    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // création du renderer
    if (renderer == NULL) // gestion des erreurs
    {
        printf("Erreur lors de la creation d'un renderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    // importation de l'image de fond
    SDL_Surface* image = SDL_LoadBMP("img/pixil-frame-0.bmp");
    if (!image)
    {
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
        return -1;
    }
    //la texture monImage contient maintenant l'image importée
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(renderer, image);

    // création d'une texture contenant nos numéro, drapeau et bombe, sous forme de tableau

    SDL_Surface* tmpTabl[11] =
    {
        SDL_LoadBMP("img/zero.bmp"),SDL_LoadBMP("img/one.bmp"),SDL_LoadBMP("img/two.bmp"),SDL_LoadBMP("img/three.bmp"),SDL_LoadBMP("img/four.bmp"),SDL_LoadBMP("img/five.bmp"),SDL_LoadBMP("img/six.bmp"),SDL_LoadBMP("img/seven.bmp"),SDL_LoadBMP("img/eight.bmp"),SDL_LoadBMP("img/flag.bmp"), SDL_LoadBMP("img/bomb.bmp")
    };
    SDL_Texture* imgTabl[11];

    // affichage de la texture de fond
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    SDL_QueryTexture(monImage, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer, monImage, NULL, &position);

    // création du rectangle de jeu
    SDL_Rect rectangle;
    rectangle.x = 100;
    rectangle.y = 100;
    rectangle.w = 300;
    rectangle.h = 300;
        
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
        printf("Erreur lors des remplissages de rectangles: %s", SDL_GetError());
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // lignes horizontales
    ligne_depart.x = 99;
    ligne_arrivee.x = 399;
    ligne_depart.y = 99;
    for (int i = 0; i != 10; i++)
    {
        ligne_depart.y += 30;
        ligne_arrivee.y = ligne_depart.y;
        SDL_RenderDrawLine(renderer, ligne_depart.x, ligne_depart.y, ligne_arrivee.x, ligne_arrivee.y);
    }

    // lignes verticales
    ligne_depart.x = 99;
    ligne_depart.y = 99;
    ligne_arrivee.y = 399;
    for (int i = 0; i != 10; i++)
    {
        ligne_depart.x += 30;
        ligne_arrivee.x = ligne_depart.x;
        SDL_RenderDrawLine(renderer, ligne_depart.x, ligne_depart.y, ligne_arrivee.x, ligne_arrivee.y);
    }
        
    // toujours penser au rendu, sinon on n'obtient rien du tout
    SDL_RenderPresent(renderer);

    random_bomb(tableau_bombe);

    while (run) {

        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_WINDOWEVENT:
                    // possibilité de fermer la fenêtre en SDL
                    if (events.window.event == SDL_WINDOWEVENT_CLOSE)
                        run = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // actions quand on clique gauche sur la souris
                    if (events.button.button == SDL_BUTTON_LEFT) {
                        SDL_Log("Dig");
                        dig(tableau_jeu, tableau_bombe, X, Y);
                        void changeCases(tableau_jeu, tableau_bombe, X, Y, renderer, imgTabl, cases);
                    }
                    // actions quand on clique droit sur la souris
                    if (events.button.button == SDL_BUTTON_RIGHT) {
                        SDL_Log("Flag");
                        flag(tableau_jeu, X, Y);
                        void changeCases(tableau_jeu, tableau_bombe, X, Y, renderer, imgTabl, cases);
                    }
                    // récupération et print des coordonnées du click souris
                    int clickX, clickY;
                    SDL_GetMouseState(&clickY, &clickX);
                    X = (clickX - 100) / 30;
                    Y = (clickY - 100) / 30;
                    printf("%d %d\n", X, Y);
                    break;
            }
        }

        // appel de la fonction de victoire
        win(tableau_jeu, tableau_bombe);

        SDL_RenderClear(renderer);
    }

    SDL_RenderPresent(renderer);

    // Destruction du renderer et de la fenêtre :
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre); 

    SDL_Quit(); // On quitte la SDL
}

// création de fonction permettant de dessiner un rectangle

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

void changeCases(char tableau_jeu, Point tableau_bombe[BOMB_COUNT], int X, int Y, SDL_Renderer* renderer, SDL_Texture* imgTabl[11], SDL_Rect* cases)
{
    //affichage du nombres de bombes atour de la case creusée, sur celle - ci

    if (SDL_BUTTON(1)) {
        if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 0)
            SDL_RenderCopy(renderer, imgTabl[0], NULL, NULL);
        else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 1)
            SDL_RenderCopy(renderer, imgTabl[1], NULL, NULL);
        else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 2)
            SDL_RenderCopy(renderer, imgTabl[2], NULL, NULL);
        else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 3)
            SDL_RenderCopy(renderer, imgTabl[3], NULL, NULL);
        else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 4)
            SDL_RenderCopy(renderer, imgTabl[4], NULL, NULL);
        else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 5)
            SDL_RenderCopy(renderer, imgTabl[5], NULL, NULL);
        else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 6)
            SDL_RenderCopy(renderer, imgTabl[6], NULL, NULL);
        else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 7)
            SDL_RenderCopy(renderer, imgTabl[7], NULL, NULL);
        else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 8)
            SDL_RenderCopy(renderer, imgTabl[8], NULL, NULL);
    }
}

// création des fonctions permettant de passer de coordonnées en 1 dimension à des coordonnées en 2 dimensions et inversement 

int getIndex2D(int X, int Y)
{
    return X * SIZE + Y;
}

void getIndex1D(int i, int* X, int* Y)
{
    *X = i / SIZE; // dizaine
    *Y = i % SIZE; // unitée
}

// création de des fonction permettant de gérer les bombes de façon aléatoire et d'éviter d'avoir deux bombes sur une seule case

void random_bomb(Point tableau_bombe[BOMB_COUNT])
{
    int a = 0;
    int b = 0;
    srand(time(NULL));

    for (int i = 0; i <= BOMB_COUNT; i++) {
        a++;
    }

    while (a > 0) {

        int X = rand() % SIZE;
        int Y = rand() % SIZE;

        if (double_finder(tableau_bombe, X, Y) == 0) {
            tableau_bombe[b].x = X;
            tableau_bombe[b].y = Y;
            a = a - 1;
            b++;
        }
    }
}

int double_finder(Point tableau_bombe[BOMB_COUNT], int X, int Y) {

    int x = 0;

    for (int i = 0; i < BOMB_COUNT; i++) {

        if (tableau_bombe[i].x == X && tableau_bombe[i].y == Y) {
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

void dig(char* tableau_jeu, Point tableau_bombe[BOMB_COUNT], int X, int Y)
{
    int i;
    int indice_x = X;
    int indice_y = Y;

    // vérification que l'indice saisie soit dans la grille de jeu

    if (-1 >= indice_x || indice_x >= SIZE || -1 >= indice_y || indice_y >= SIZE) {
        printf("Indice non valide\n");
        return;
    }

    // si l'indice saisie est une bombe, la partie est perdue

    else if (-1 < indice_x < SIZE && -1 < indice_y < SIZE) {
        for (i = 0; i < BOMB_COUNT; i++)
        {
            if (tableau_bombe[i].x == indice_x && tableau_bombe[i].y == indice_y) {
                printf("PERDU");
                abort();
            }
        }
        spread(tableau_jeu, tableau_bombe, indice_x, indice_y);
    }
}

// création de la fonction permettant de poser un drapeau

void flag(char* tableau_jeu, int X, int Y)
{
    // Affichage du drapeau sur la case cliquée
    if (-1 >= X && X >= SIZE && -1 >= Y && Y >= SIZE) {
        SDL_Surface* image = SDL_LoadBMP("img/flag.bmp");
    }
}

// création de la fonction permettant de creuser automatiquement jusqu'à une case a proximité d'une bombe

void spread(char* tableau_jeu, Point tableau_bombe[BOMB_COUNT], int X, int Y)
{
    // si on dépasse le tableau (x, y) on part de la fonction
    if (!(0 <= X && X < SIZE && 0 <= Y && Y < SIZE)) {
        return;
    }

    // si il n'y a pas de bombes autour de la case, on sort de la fonction pour éviter le stack overflow
    if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 0) {
        return;
    }

    // si la case est differente de '0' on part de la fonction
    if (bomb_around(tableau_jeu, tableau_bombe, X, Y) != 0) {
        return;
    }

    // on rappelle spread sur les 8 cases autours
    else {
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                spread(tableau_jeu, tableau_bombe, X + i, Y + j);
            }
        }
    }
}

// création de la fonction permettant de savoir si la case introduite est une bombe ou non

int is_bomb(Point tableau_bombe[BOMB_COUNT], int X, int Y)
{
    int vrai = 0;

    for (int i = 0; i < BOMB_COUNT; i++)
    {
        if (tableau_bombe[i].x == X && tableau_bombe[i].y == Y && tableau_bombe[i].x >= 0 && tableau_bombe[i].y >= 0) {
            vrai = 1;
        }
    }
    return vrai;
}

// création de la fonction permettant d'indiquer le nombre de bombe autour de la case introduite

int bomb_around(char* tableau_jeu, Point tableau_bombe[BOMB_COUNT], int X, int Y)
{
    int nb_bombe = 0;
    char int_str[2] = { 0, 0 };

    // vérification si il y a des bombes autour de la case creusée spécifique aux quatres coins du tableau de jeu

    if (X == 0 && Y == 9) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X, Y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X + 1, Y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X + 1, Y);
    }
    else if (X == 9 && Y == 0) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X - 1, Y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X - 1, Y + 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X, Y + 1);
    }
    else if (X == 9 && Y == 9) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X - 1, Y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X - 1, Y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X, Y - 1);
    }
    else if (X == 0 && Y == 0) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X, Y + 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X + 1, Y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X + 1, Y + 1);
    }

    // vérification si il y a des bombes autour de la case creusée spécifique aux quatres cotés du tableau de jeu

    else if (X == 0) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X, Y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X, Y + 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X + 1, Y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X + 1, Y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X + 1, Y + 1);
    }
    else if (X == 9) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X, Y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X, Y + 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X - 1, Y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X - 1, Y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X - 1, Y + 1);
    }
    else if (Y == 9) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X - 1, Y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X + 1, Y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X - 1, Y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X, Y - 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X + 1, Y - 1);
    }
    else if (Y == 0) {
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X - 1, Y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X + 1, Y);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X - 1, Y + 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X, Y + 1);
        nb_bombe = nb_bombe + is_bomb(tableau_bombe, X + 1, Y + 1);

    }

    // vérification si il y a des bombes autour de la case creusée quand on se situe ni dans les coins ni sur les cotés ni dans les coins du tableau de jeu

    else {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                nb_bombe = nb_bombe + is_bomb(tableau_bombe, X + i, Y + j);
            }
        }
    }
    printf("Bombes autour de la case : %d\n", nb_bombe);
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
            if (tableau_jeu[i] == 0) {
                nb_cases++;
            }
        }
    }
    if (nb_cases == TOTAL_SIZE - BOMB_COUNT) {
        printf("VICTOIRE !");
        abort();
    }
}