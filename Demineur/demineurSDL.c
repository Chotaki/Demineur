
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

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
                case SDL_MOUSEBUTTONDOWN :
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
