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
void dig(char*, Point[BOMB_COUNT]);
void delay(int);
void flag(char*);
//void link(char*, int*, int);
//int bomb_around(char*, int*, int);
void win(char*);
//void dig_around(char*, int*, int);
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

    random_bomb(tableau_bombe);

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
    *x = i / SIZE;
    *y = i % SIZE;
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

    for (i = 0; i < 19; i++)
    { 
        if (tableau_bombe[i].x == indice_x && tableau_bombe[i].y == indice_y) {
            printf("PERDU");
            delay(1);
            abort();
        }
    }

    //link(tableau_jeu, tableau_bombe, indice);
}

void flag(char *tableau_jeu)
{
    int indice;
    printf("Choisissez une case ou poser un drapeau entre 0 et 99 :");
    scanf_s("%d", &indice);

    tableau_jeu[indice] = 'P';
}

/*void link(char* tableau_jeu, int* tableau_bombe, int indice)
{
    if (bomb_around(tableau_jeu, tableau_bombe, indice) == 0) {
        bomb_around(tableau_jeu, tableau_bombe, indice);
        dig_around(tableau_jeu, tableau_bombe, indice);
    }

}

void dig_around(char* tableau_jeu, int* tableau_bombe, int indice)
{
    if ((indice + 1) % 10 != 0 && indice % 10 != 0) {
        bomb_around(tableau_jeu, tableau_bombe, indice - 11);
        bomb_around(tableau_jeu, tableau_bombe, indice - 10);
        bomb_around(tableau_jeu, tableau_bombe, indice - 9);
        bomb_around(tableau_jeu, tableau_bombe, indice - 1);
        bomb_around(tableau_jeu, tableau_bombe, indice + 1);
        bomb_around(tableau_jeu, tableau_bombe, indice + 9);
        bomb_around(tableau_jeu, tableau_bombe, indice + 10);
        bomb_around(tableau_jeu, tableau_bombe, indice + 11);
    }

    if ((indice + 1) % 10 == 0) {
        bomb_around(tableau_jeu, tableau_bombe, indice - 11);
        bomb_around(tableau_jeu, tableau_bombe, indice - 10);
        bomb_around(tableau_jeu, tableau_bombe, indice - 1);
        bomb_around(tableau_jeu, tableau_bombe, indice + 9);
        bomb_around(tableau_jeu, tableau_bombe, indice + 10);
    }

    if (indice % 10 == 0) {
        bomb_around(tableau_jeu, tableau_bombe, indice - 10);
        bomb_around(tableau_jeu, tableau_bombe, indice - 9);
        bomb_around(tableau_jeu, tableau_bombe, indice + 1);
        bomb_around(tableau_jeu, tableau_bombe, indice + 10);
        bomb_around(tableau_jeu, tableau_bombe, indice + 11);
    }

    if (indice % 90 < 10) {
        bomb_around(tableau_jeu, tableau_bombe, indice - 11);
        bomb_around(tableau_jeu, tableau_bombe, indice - 10);
        bomb_around(tableau_jeu, tableau_bombe, indice - 9);
        bomb_around(tableau_jeu, tableau_bombe, indice - 1);
        bomb_around(tableau_jeu, tableau_bombe, indice + 1);
    }

    if (indice < 10) {
        bomb_around(tableau_jeu, tableau_bombe, indice - 1);
        bomb_around(tableau_jeu, tableau_bombe, indice + 1);
        bomb_around(tableau_jeu, tableau_bombe, indice + 9);
        bomb_around(tableau_jeu, tableau_bombe, indice + 10);
        bomb_around(tableau_jeu, tableau_bombe, indice + 11);
    }


        if (bomb_around(tableau_jeu, tableau_bombe, indice - 11) == 0) {
            link(tableau_jeu, tableau_bombe, indice - 11);
        }
        if (bomb_around(tableau_jeu, tableau_bombe, indice - 10) == 0) {
            link(tableau_jeu, tableau_bombe, indice - 10);
        }
        if (bomb_around(tableau_jeu, tableau_bombe, indice - 9) == 0) {
            link(tableau_jeu, tableau_bombe, indice - 9);
        }
        if (bomb_around(tableau_jeu, tableau_bombe, indice - 1) == 0) {
            link(tableau_jeu, tableau_bombe, indice - 1);
        }
        if (bomb_around(tableau_jeu, tableau_bombe, indice + 1) == 0) {
            link(tableau_jeu, tableau_bombe, indice + 1);
        }
        if (bomb_around(tableau_jeu, tableau_bombe, indice + 9) == 0) {
            link(tableau_jeu, tableau_bombe, indice + 9);
        }
        if (bomb_around(tableau_jeu, tableau_bombe, indice + 10) == 0) {
            link(tableau_jeu, tableau_bombe, indice + 10);
        }
        if (bomb_around(tableau_jeu, tableau_bombe, indice + 11) == 0) {
            link(tableau_jeu, tableau_bombe, indice + 11);
        }
        bomb_around(tableau_jeu, tableau_bombe, indice - 11);
        bomb_around(tableau_jeu, tableau_bombe, indice - 10);
        bomb_around(tableau_jeu, tableau_bombe, indice - 9);
        bomb_around(tableau_jeu, tableau_bombe, indice - 1);
        bomb_around(tableau_jeu, tableau_bombe, indice + 1);
        bomb_around(tableau_jeu, tableau_bombe, indice + 9);
        bomb_around(tableau_jeu, tableau_bombe, indice + 10);
        bomb_around(tableau_jeu, tableau_bombe, indice + 11);
}


int bomb_around(char *tableau_jeu, int *tableau_bombe, int indice)
{
    int nb_bombe = 0;
    char int_str[2];

    if ((indice + 1) % 10 != 0 && indice % 10 != 0) {
        for (int i = 0; i < 19; i++)
        {
            if (tableau_bombe[i] == indice - 11) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice - 10) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice - 9) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice - 1) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice + 1) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice + 9) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice + 10) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice + 11) {
                nb_bombe++;
            }
        }
    }

    if ((indice + 1) % 10 == 0) {
        for (int i = 0; i < 19; i++)
        {
            if (tableau_bombe[i] == indice - 11) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice - 10) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice - 1) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice + 9) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice + 10) {
                nb_bombe++;
            }
        }
    }

    if (indice % 10 == 0) {
        for (int i = 0; i < 19; i++)
        {
            if (tableau_bombe[i] == indice - 10) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice - 9) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice + 1) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice + 10) {
                nb_bombe++;
            }
            if (tableau_bombe[i] == indice + 11) {
                nb_bombe++;
            }
        }
    }


    sprintf_s(int_str, 2, "%d", nb_bombe);
    tableau_jeu[indice] = int_str[0];
    return nb_bombe;
}*/

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
