// Demineur.c : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>

int main()
{
    int i;
    int j;
    char * tableau[100];

    for (i = 0; i < 100; i++) /* boucle << classique >> pour le parcours d'un tableau */
    {
        tableau[i] = "[_]";  /* chaque case du tableau reçoit son indice comme valeur */
    }

    for (j = 0; j < 10; j++)
    {
        for (i = 0; i < 10; i++)
        {
            printf("%s", tableau[j*10+i]);
        }
        printf("\n");
    }

    return 0;
}

int rayan()
{

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
