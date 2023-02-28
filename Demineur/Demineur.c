// Demineur.c : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BOMB_COUNT 18

#define SIZE 10
#define TOTAL_SIZE (SIZE * SIZE)

typedef struct Point Point;

void random_bomb(Point[BOMB_COUNT]);
void manual_bomb(Point[BOMB_COUNT]);
void dig(char*, Point[BOMB_COUNT]);
void delay(int);
void flag(char*);
void link(char*, Point[BOMB_COUNT], int, int);
int bomb_around(char*, Point[BOMB_COUNT], int, int);
int is_bomb(Point[BOMB_COUNT], int, int);
void win(char*);
void dig_around(char*, Point[BOMB_COUNT], int, int);
int double_finder(Point[BOMB_COUNT], int, int);
int getIndex2D(int, int);
void getIndex1D(int, int *, int *);

struct Point
{
    int x;
    int y;
};


int main()
{
    int i;
    int j;
    char tableau_jeu[TOTAL_SIZE];
    Point tableau_bombe[BOMB_COUNT];
    int choix;

    // random_bomb(tableau_bombe);
    manual_bomb(tableau_bombe);

    for (i = 0; i < TOTAL_SIZE; i++)
    {
        tableau_jeu[i] = '_';
    }

    while(1)
    {
        for (j = 0; j < SIZE; j++)
        {
            for (i = 0; i < SIZE; i++)
            {
                printf("[%c]", tableau_jeu[j* SIZE +i]);
            }
            printf("\n");
        }

        for (i = 0; i < BOMB_COUNT; i++)
        {
            printf(" %d %d\n", tableau_bombe[i].x, tableau_bombe[i].y);
        }

        printf("Choisissez 0:creuser , 1:poser drapeau");
        scanf_s("%d", &choix);
        if (choix == 0) {
            dig(tableau_jeu, tableau_bombe);
        }
        if (choix == 1) {
            flag(tableau_jeu);
        }

        win(tableau_jeu);
        system("cls");
    }

    return 0;
}

int getIndex2D(int x, int y)
{
    return x * SIZE + y;
}

void getIndex1D(int i, int * x, int * y)
{
    *x = i / SIZE; // dizaine
    *y = i % SIZE; // unitée
}

void random_bomb(Point tableau_bombe[BOMB_COUNT])
{
    int a = 0;
    int b = 0;
    srand(time(NULL));

    for (int i = 0; i < BOMB_COUNT; i++) {
        a++;
    }

    while (a > 0) {

        int indice_x = rand() % 10;
        int indice_y = rand() % 10;

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

    for (int i = 0; i < 18; i++) {
        tableau_bombe[i].x = -1;
        tableau_bombe[i].y = -1;
    }

    tableau_bombe[0].x = 4;
    tableau_bombe[0].y = 0;

    tableau_bombe[1].x = 4;
    tableau_bombe[1].y = 1;

    tableau_bombe[2].x = 4;
    tableau_bombe[2].y = 2;

    tableau_bombe[3].x = 4;
    tableau_bombe[3].y = 3;

    tableau_bombe[4].x = 4;
    tableau_bombe[4].y = 4;

    tableau_bombe[5].x = 4;
    tableau_bombe[5].y = 5;

    tableau_bombe[6].x = 4;
    tableau_bombe[6].y = 6;

    tableau_bombe[7].x = 4;
    tableau_bombe[7].y = 7;
    
    tableau_bombe[8].x = 4;
    tableau_bombe[8].y = 8;

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

void dig(char* tableau_jeu, Point tableau_bombe[BOMB_COUNT])
{
    int i;
    int indice_x;
    int indice_y;
    printf("Choisissez une ligne ou jouer:");
    scanf_s("%d", &indice_x);
    printf("Choisissez une colone ou jouer:");
    scanf_s("%d", &indice_y);

    if (-1 >= indice_x || indice_x >= 10 || -1 >= indice_y || indice_y >= 10) {
        printf("Indice non valide\n");
        delay(1);
        dig(tableau_jeu, tableau_bombe);
    }

    else if (-1 < indice_x < 10 && -1 < indice_y < 10) {
        for (i = 0; i < 19; i++)
        {
            if (tableau_bombe[i].x == indice_x && tableau_bombe[i].y == indice_y) {
                printf("PERDU");
                delay(1);
                abort();
            }
        }
        link(tableau_jeu, tableau_bombe, indice_x, indice_y);
    }
}

void flag(char *tableau_jeu)
{
    int indice;
    printf("Choisissez une case ou poser un drapeau entre 0 et 99 :");
    scanf_s("%d", &indice);

    tableau_jeu[indice] = 'P';
}

void link(char* tableau_jeu, Point tableau_bombe[BOMB_COUNT], int indice_x, int indice_y)
{
        bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y);
        dig_around(tableau_jeu, tableau_bombe, indice_x, indice_y);

}

void dig_around(char* tableau_jeu, Point tableau_bombe[BOMB_COUNT], int indice_x, int indice_y)
{
    int x = 0;
    int y = 0;

    while (x < 2) {

        if (indice_x == 0 && indice_y == 9) {
            if (is_bomb(tableau_bombe, indice_x, indice_y - 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y - 1);
            }
            if (is_bomb(tableau_bombe, indice_x + 1, indice_y - 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x + 1, indice_y - 1);
            }
            if (is_bomb(tableau_bombe, indice_x + 1, indice_y) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x + 1, indice_y);
            }
        }
        else if (indice_x == 9 && indice_y == 0) {
            if (is_bomb(tableau_bombe, indice_x - 1, indice_y) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x - 1, indice_y);
            }
            if (is_bomb(tableau_bombe, indice_x - 1, indice_y + 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x - 1, indice_y + 1);
            }
            if (is_bomb(tableau_bombe, indice_x, indice_y + 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y + 1);
            }
        }
        else if (indice_x == 9 && indice_y == 9) {
            if (is_bomb(tableau_bombe, indice_x - 1, indice_y - 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x - 1, indice_y - 1);
            }
            if (is_bomb(tableau_bombe, indice_x - 1, indice_y) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x - 1, indice_y);
            }
            if (is_bomb(tableau_bombe, indice_x, indice_y - 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y - 1);
            }
        }
        else if (indice_x == 0 && indice_y == 0) {
            if (is_bomb(tableau_bombe, indice_x , indice_y + 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y + 1);
            }
            if (is_bomb(tableau_bombe, indice_x + 1, indice_y) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x + 1, indice_y);
            }
            if (is_bomb(tableau_bombe, indice_x + 1, indice_y + 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x + 1, indice_y + 1);
            }
        }
        else if (indice_x == 0) {
            if (is_bomb(tableau_bombe, indice_x, indice_y - 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y - 1);
            }
            if (is_bomb(tableau_bombe, indice_x, indice_y + 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y + 1);
            }
            if (is_bomb(tableau_bombe, indice_x + 1, indice_y - 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x + 1, indice_y - 1);
            }
            if (is_bomb(tableau_bombe, indice_x + 1, indice_y) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x + 1, indice_y);
            }
            if (is_bomb(tableau_bombe, indice_x + 1, indice_y + 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x + 1, indice_y + 1);
            }
        }
        else if (indice_x == 9) {
            if (is_bomb(tableau_bombe, indice_x, indice_y - 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y - 1);
            }
            if (is_bomb(tableau_bombe, indice_x, indice_y + 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y + 1);
            }
            if (is_bomb(tableau_bombe, indice_x - 1, indice_y - 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x - 1, indice_y - 1);
            }
            if (is_bomb(tableau_bombe, indice_x - 1, indice_y) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x - 1, indice_y);
            }
            if (is_bomb(tableau_bombe, indice_x - 1, indice_y + 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x - 1, indice_y + 1);
            }
        }
        else if (indice_y == 0) {
            if (is_bomb(tableau_bombe, indice_x - 1, indice_y) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x - 1, indice_y);
            }
            if (is_bomb(tableau_bombe, indice_x + 1, indice_y) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x + 1, indice_y);
            }
            if (is_bomb(tableau_bombe, indice_x - 1, indice_y + 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x - 1, indice_y + 1);
            }
            if (is_bomb(tableau_bombe, indice_x, indice_y + 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y + 1);
            }
            if (is_bomb(tableau_bombe, indice_x + 1, indice_y + 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x + 1, indice_y + 1);
            }
        }
        else if (indice_y == 9) {;
            if (is_bomb(tableau_bombe, indice_x - 1, indice_y) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x - 1, indice_y);
            }
            if (is_bomb(tableau_bombe, indice_x + 1 , indice_y) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x + 1, indice_y);
            }
            if (is_bomb(tableau_bombe, indice_x - 1, indice_y - 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x - 1, indice_y - 1);
            }
            if (is_bomb(tableau_bombe, indice_x , indice_y - 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y - 1);
            }
            if (is_bomb(tableau_bombe, indice_x + 1, indice_y - 1) == 0) {
                bomb_around(tableau_jeu, tableau_bombe, indice_x + 1, indice_y - 1);
            }
        }
        else {
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (is_bomb(tableau_bombe, indice_x + i, indice_y + j) == 0) {
                        bomb_around(tableau_jeu, tableau_bombe, indice_x + i, indice_y + j);
                    }
                }
            }
        }
        x++;
    }

    if (bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y + 1) == 0) {
        if (tableau_jeu[getIndex2D(indice_x, indice_y + 2)] == '_') {
            if (getIndex2D(indice_x, indice_y) != 99) {
                printf("aaaa");
                bomb_around(tableau_jeu, tableau_bombe, indice_x, indice_y + 1);
                dig_around(tableau_jeu, tableau_bombe, indice_x, indice_y + 1);
            }
        }
    }
}


int is_bomb(Point tableau_bombe[BOMB_COUNT], int indice_x, int indice_y)
{
    int vrai = 0;

    for (int i = 0; i < 19; i++)
    {
        if (tableau_bombe[i].x == indice_x && tableau_bombe[i].y == indice_y && tableau_bombe[i].x >= 0 && tableau_bombe[i].y >= 0) {
            vrai = 1;
        }
    }
    return vrai;
}

int bomb_around(char *tableau_jeu, Point tableau_bombe[BOMB_COUNT], int indice_x, int indice_y)
{
    int nb_bombe = 0;
    char int_str[2];

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
    else {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                nb_bombe = nb_bombe + is_bomb(tableau_bombe, indice_x + i, indice_y + j);
            }
        }
    }

    sprintf_s(int_str, 2, "%d", nb_bombe);
    tableau_jeu[getIndex2D(indice_x,indice_y)] = int_str[0];
    return nb_bombe;
}

void win(char* tableau_jeu)
{
    int nb_cases = 0;

    for (int i = 0; i < TOTAL_SIZE; i++)
    {
        if (tableau_jeu[i] != '_') {
            nb_cases++;
        }
    }
    if (nb_cases == TOTAL_SIZE) {
        printf("VICTOIRE !");
        delay(1);
        abort();
    }
}

void delay(int temps)
{
    int seconds = 1000 * temps;
    clock_t start = clock();

    while (clock() < start + seconds);
}
