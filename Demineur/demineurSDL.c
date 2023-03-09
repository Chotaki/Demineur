
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
void dig(char*, Point[BOMB_COUNT], int, int);
void flag(char*, int, int);
void spread(char*, Point[BOMB_COUNT], int, int);
int is_bomb(Point[BOMB_COUNT], int, int);
int bomb_around(char*, Point[BOMB_COUNT], int, int);
void win(char*, Point[BOMB_COUNT]);

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
    int X;
    int Y;
    char tableau_jeu[TOTAL_SIZE];
    Point tableau_bombe[BOMB_COUNT];
    int app = 0;
    
    SDL_Window* fenetre;
    SDL_Renderer* renderer; // Déclaration du renderere
    SDL_bool run = SDL_TRUE;
    SDL_Event events;
    SDL_Point ligne_depart, ligne_arrivee;

    SDL_Rect cases[100];

    if (SDL_VideoInit(NULL) < 0) // Initialisation de la SDL
    {
        printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
        return -1;
    }

    // Création de la fenêtre :
    fenetre = SDL_CreateWindow("MineSweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
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

    SDL_Surface* tmpTabl[10] =
    {
        SDL_LoadBMP("img/one.bmp"),SDL_LoadBMP("img/two.bmp"),SDL_LoadBMP("img/three.bmp"),SDL_LoadBMP("img/four.bmp"),SDL_LoadBMP("img/five.bmp"),SDL_LoadBMP("img/six.bmp"),SDL_LoadBMP("img/seven.bmp"),SDL_LoadBMP("img/eight.bmp"),SDL_LoadBMP("img/flag.bmp"), SDL_LoadBMP("img/bomb.bmp")
    };
    SDL_Texture* imgTabl[10];

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
            printf("Erreur lors des remplissages de rectangles: %s", SDL_GetError());
            return -1;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Lignes horizontales
        ligne_depart.x = 99;
        ligne_arrivee.x = 399;
        ligne_depart.y = 99;
        for (int i = 0; i != 10; i++)
        {
            ligne_depart.y += 30;
            ligne_arrivee.y = ligne_depart.y;
            SDL_RenderDrawLine(renderer, ligne_depart.x, ligne_depart.y, ligne_arrivee.x, ligne_arrivee.y);
        }

        // Lignes verticales
        ligne_depart.x = 99;
        ligne_depart.y = 99;
        ligne_arrivee.y = 399;
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
                int clickX, clickY;
                SDL_GetMouseState(&clickY, &clickX);
                X = (clickX - 100) / 30;
                Y = (clickY - 100) / 30;
                printf("%d %d\n", X, Y);
                break;
            }
        }

        SDL_RenderClear(renderer);
    }

    random_bomb(tableau_bombe);

    while (1)
    {
        // demande au joueur l'action qu'il veut effectuer

        if (SDL_BUTTON(1)) {
            dig(tableau_jeu, tableau_bombe, X, Y);
        }
        if (SDL_BUTTON(3)) {
            flag(tableau_jeu, X, Y);
        }

        // appel de la fonction de victoire

        win(tableau_jeu, tableau_bombe);
        system("cls");
    }

    if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 1)
        SDL_RenderCopy(renderer, imgTabl[0], NULL, cases);
    else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 2)
        SDL_RenderCopy(renderer, imgTabl[1], NULL, cases);
    else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 3)
        SDL_RenderCopy(renderer, imgTabl[2], NULL, cases);
    else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 4)
        SDL_RenderCopy(renderer, imgTabl[3], NULL, cases);
    else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 5)
        SDL_RenderCopy(renderer, imgTabl[4], NULL, cases);
    else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 6)
        SDL_RenderCopy(renderer, imgTabl[5], NULL, cases);
    else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 7)
        SDL_RenderCopy(renderer, imgTabl[6], NULL, cases);
    else if (bomb_around(tableau_jeu, tableau_bombe, X, Y) == 8)
        SDL_RenderCopy(renderer, imgTabl[7], NULL, cases);

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

// création des fonctions permettant de passer de coordonnées 1 dimension a 2 dimensions ou inversement 

int getIndex2D(int X, int Y)
{
    return X * SIZE + Y;
}

void getIndex1D(int i, int* X, int* Y)
{
    *X = i / SIZE; // dizaine
    *Y = i % SIZE; // unitée
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
    int indice = tableau_jeu[getIndex2D(X, Y)];

    // vérification que la case choisie ne soit pas déjà creusée et soit dans la grille de jeu

    if (-1 < indice && indice < TOTAL_SIZE - 1) {
        SDL_Surface* image = SDL_LoadBMP("img/flag.bmp");
    }
    else {
        printf("Indice non valide\n");
        return;
    }
}

// création de la fonction permettant de creuser automatiquement jusqu'à une case a proximité d'une bombe

void spread(char* tableau_jeu, Point tableau_bombe[BOMB_COUNT], int X, int Y)
{

    // si on dépasse le tableau (x, y) on part de la fonction
    if (!(0 <= X && X < SIZE && 0 <= Y && Y < SIZE)) {
        return;
    }

    /* si la case est déjà revelé on sort de la fonction
    else if (tableau_jeu[getIndex2D(X, Y)] != '_') {
        return;
    }*/

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

    //affichage du nombres de bombes atour de la case creusée, sur celle - ci
    
    /*sprintf_s(int_str, 2, "%d", nb_bombe);
    tableau_jeu[getIndex2D(indice_x, indice_y)] = int_str[0];*/
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

        /*if (is_bomb(tableau_bombe, x, y) == 0) {
            if (tableau_jeu[i] != '_') {
                nb_cases++;
            }
        }
    }
    if (nb_cases == TOTAL_SIZE - BOMB_COUNT) {
        printf("VICTOIRE !");
        abort();*/
    }
}