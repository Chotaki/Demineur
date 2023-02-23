// Demineur.c : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void rayan(int *);
void loris(char*, int*);
void delay(int);
void antoine(char*);
void vianney(char*, int*, int);
int william(char*, int*, int);
void victor(char*);
void lilian(char*, int*, int);

int main()
{
    int i;
    int j;
    char tableau_jeu[100];
    int tableau_bombe[18];
    int choix;

    for (i = 0; i < 100; i++) 
    {
        tableau_jeu[i] = '_';
    }

    rayan(tableau_bombe);

    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 10; j++)
        {
            for (i = 0; i < 10; i++)
            {
                printf("[%c]", tableau_jeu[j*10+i]);
            }
            printf("\n");
        }

        for (i = 0; i < 19; i++)
        {
            printf("%d\n", tableau_bombe[i]);
        }

        printf("Choisissez 0:creuser , 1:poser drapeau");
        scanf_s("%d", &choix);
        if (choix == 0) {
            loris(tableau_jeu, tableau_bombe);
        }
        if (choix == 1) {
            antoine(tableau_jeu);
        }

        victor(tableau_jeu);
        system("cls");
    }

    return 0;
}

void rayan(int *tableau_bombe)
{
    int indice = 0;
    srand(time(NULL));

    for (int i = 0; i < 19; i++)
    {
        int x = 0;

        indice = rand() % (100);

        for (int j = 0; j < 19; j++) {

            if (tableau_bombe[j] == indice) {
                x++;    
            }
        }

        if (x == 0) {
            tableau_bombe[i] = indice;
        }
    }
}

void loris(char *tableau_jeu, int *tableau_bombe)
{
    int i;
    int j = 0;
    int indice;
    printf("Choisissez une case a creuser entre 0 et 99 :");
    scanf_s("%d", &indice);

    for (i = 0; i < 19; i++)
    { 
        if (tableau_bombe[i] == indice) {
            j = i;
        }
    }

    if (tableau_bombe[j] == indice) {
        printf("PERDU");
        delay(1);
        abort();
    }
    else {
        vianney(tableau_jeu,tableau_bombe,indice);
    }
}

void antoine(char *tableau_jeu)
{
    int indice;
    printf("Choisissez une case ou poser un drapeau entre 0 et 99 :");
    scanf_s("%d", &indice);

    tableau_jeu[indice] = 'P';
}

void vianney(char *tableau_jeu, int* tableau_bombe, int indice)
{
    if (william(tableau_jeu, tableau_bombe, indice) == 0  && (indice + 1) % 10 != 0) {
        william(tableau_jeu, tableau_bombe, indice);
        lilian(tableau_jeu, tableau_bombe, indice);
    }

}

void lilian(char* tableau_jeu, int* tableau_bombe, int indice)
{
    william(tableau_jeu, tableau_bombe, indice - 11);
    william(tableau_jeu, tableau_bombe, indice - 10);
    william(tableau_jeu, tableau_bombe, indice - 9);
    william(tableau_jeu, tableau_bombe, indice - 1);
    william(tableau_jeu, tableau_bombe, indice + 1);
    william(tableau_jeu, tableau_bombe, indice + 9);
    william(tableau_jeu, tableau_bombe, indice + 10);
    william(tableau_jeu, tableau_bombe, indice + 11);

        /*if (william(tableau_jeu, tableau_bombe, indice - 11) == 0) {
            vianney(tableau_jeu, tableau_bombe, indice - 11);
        }
        if (william(tableau_jeu, tableau_bombe, indice - 10) == 0) {
            vianney(tableau_jeu, tableau_bombe, indice - 10);
        }
        if (william(tableau_jeu, tableau_bombe, indice - 9) == 0) {
            vianney(tableau_jeu, tableau_bombe, indice - 9);
        }
        if (william(tableau_jeu, tableau_bombe, indice - 1) == 0) {
            vianney(tableau_jeu, tableau_bombe, indice - 1);
        }
        if (william(tableau_jeu, tableau_bombe, indice + 1) == 0) {
            vianney(tableau_jeu, tableau_bombe, indice + 1);
        }
        if (william(tableau_jeu, tableau_bombe, indice + 9) == 0) {
            vianney(tableau_jeu, tableau_bombe, indice + 9);
        }
        if (william(tableau_jeu, tableau_bombe, indice + 10) == 0) {
            vianney(tableau_jeu, tableau_bombe, indice + 10);
        }
        if (william(tableau_jeu, tableau_bombe, indice + 11) == 0) {
            vianney(tableau_jeu, tableau_bombe, indice + 11);
        }*/
}


int william(char *tableau_jeu, int *tableau_bombe, int indice)
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
}

void victor(char* tableau_jeu)
{
    int nb_cases = 0;

    for (int i = 0; i < 100; i++)
    {
        if (tableau_jeu[i] != '_') {
            nb_cases++;
        }
    }
    if (nb_cases == 100) {
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

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
