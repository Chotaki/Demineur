// Demineur.c : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void rayan(int *);
void loris(char**, int*);
void delay(int);
void antoine(char**);
void vianney(char**, int*, int);

int main()
{
    int i;
    int j;
    char* tableau_jeu[100];
    int tableau_bombe[18];
    int choix;

    for (i = 0; i < 100; i++) 
    {
        tableau_jeu[i] = "[_]"; 
    }

    rayan(tableau_bombe);

    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 10; j++)
        {
            for (i = 0; i < 10; i++)
            {
                printf("%s", tableau_jeu[j*10+i]);
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
        indice = rand() % (100);

        tableau_bombe[i] = indice;
    }
}

void loris(char* *tableau_jeu, int *tableau_bombe)
{
    int i;
    int j;
    int indice;
    printf("Choisissez une case a creuser entre 0 et 99 :");
    scanf_s("%d", &indice);

    for (i = 0; i < 19; i++)
    { 
        if (tableau_bombe[i] == indice) {
            j = i;
        }
    }

    if (tableau_bombe[j] == indice)
    {
        printf("PERDU");
        delay(1);
        abort();
    }
    else {
        vianney(tableau_jeu,tableau_bombe,indice);

    }
}

void antoine(char* *tableau_jeu)
{
    int indice;
    printf("Choisissez une case ou poser un drapeau entre 0 et 99 :");
    scanf_s("%d", &indice);

    tableau_jeu[indice] = "[4]";
}

void vianney(char* *tableau_jeu, int* tableau_bombe, int indice)
{
    int j1;
    int j2;
    int j3;
    int j4;
    int j5;
    int j6;
    int j7;
    int j8;

    for (int i = 0; i < 19; i++)
    {
        if (tableau_bombe[i] == indice - 11)
        {
            j1 = 1;
        }
        if (tableau_bombe[i] == indice - 10)
        {
            j2 = 1;
        }
        if (tableau_bombe[i] == indice - 9)
        {
            j3 = 1;
        }
        if (tableau_bombe[i] == indice - 1)
        {
            j4 = 1;
        }
        if (tableau_bombe[i] == indice + 1)
        {
            j5 = 1;
        }
        if (tableau_bombe[i] == indice + 9)
        {
            j6 = 1;
        }
        if (tableau_bombe[i] == indice + 10)
        {
            j7 = 1;
        }
        if (tableau_bombe[i] == indice + 11)
        {
            j8 = 1;
        }

    }
    if (j1 == 0) {
        tableau_jeu[indice - 11] = "[0]";
    }
    if (j2 == 0) {
        tableau_jeu[indice - 10] = "[0]";
    }
    if (j3 == 0) {
        tableau_jeu[indice - 9] = "[0]";
    }
    if (j4 == 0) {
        tableau_jeu[indice - 1] = "[0]";
    }
    if (j5 == 0) {
        tableau_jeu[indice + 1] = "[0]";
    }
    if (j6 == 0) {
        tableau_jeu[indice + 9] = "[0]";
    }
    if (j7 == 0) {
        tableau_jeu[indice + 10] = "[0]";
    }
    if (j8 == 0) {
        tableau_jeu[indice + 11] = "[0]";
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
