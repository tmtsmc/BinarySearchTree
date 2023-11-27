// ------------------------
//
//   PROJET HACHAGE B46
//
//     Anon Anon
//	   tmtsmc tmtsmc
//
// ------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// strcmp, strcpy
#include <Windows.h>	// clear.

#define C 1000

// Liste chainée
typedef struct Maillon {
	char mot[30];
	struct Maillon *pSuiv;
} list_maillon;

typedef list_maillon *LISTE;

FILE *f;
LISTE T[C];

// Entêtes
int hachage(char mot[30]);
LISTE supprimer(char mot[30], LISTE A);
LISTE Insert(char mot[30], LISTE L);
int NbElements(LISTE L);
void Affichage(LISTE L);
int Element(char mot[30], LISTE L);
void Menu();
void bufferManager();

// Créé à la présentation du projet
void Compteur(LISTE A) {
	LISTE crt;
	printf("La classe contient %d elements");
}

int main(int argc, char *argv[]) {
	char mot[30];
	int i = 0, h = 0, x = 0, q = 1, nbr = 0;
	/*f = fopen("mini_dico.txt", "r+");
	if (!f) {
		fprintf(stderr,"Erreur ouverture de fichier !\n");
		return -1;
	}
	while (!feof(f)) {
		fscanf(f,"%s", mot);
		h = hachage(mot);
		T[h] = Insert(mot, T[h]);
	}*/
	while (q) {
		Menu();
		//Saisie sécurisée.
		while (!scanf("%d", &x)) {
			printf(">Veuillez entrer un choix correct !\nChoix : ");
			bufferManager();
		}
		bufferManager();
		switch (x) {
			case 0 : // fin du programme.
				q = 0;
				break;
			case 1 : //insertion d'un élément
				printf("Sélectionnez un mot: \n");
				//Saisie sécurisée.
				while (!scanf("%30[a-z]s", mot)) {
					printf(">Veuillez entrer un choix correct !\n> ");
					bufferManager();
				}
				h = hachage(mot);
				T[h] = Insert(mot, T[h]);
				bufferManager();
				system("cls");
				break;
			case 2 : //Vérifier la présence d'un mot
				printf("Sélectionnez un mot: \n");
				//Saisie sécurisée.
				while (!scanf("%30[a-z]s", mot)) {
					printf(">Veuillez entrer un choix correct !\n> ");
					bufferManager();
				}
				h = hachage(mot);
				if (Element(mot, T[h])) printf("%s est présent dans le dictionnaire\n", mot);
				else printf("%s n'est pas présent dans le dictionnaire\n", mot);
				bufferManager();
				getchar();
				system("cls");
				break;
			case 3:	//Affichage Dictionnaire
				for (i = 0; i < C; i++) Affichage(T[i]);
				getchar();
				system("cls");
				break;
			case 4: //Nombre d'élements
				for (i = 0; i < C; i++) nbr += NbElements(T[i]);
				printf(">Il y a %d elements dans le dictionnaire", nbr);
				nbr = 0;
				getchar();
				system("cls");
				break;
			case 5:	//Supprimer un élément.
				printf("Supprimer un mot: \n");
				//Saisie sécurisée.
				while (!scanf("%30[a-z]s", mot)) {
					printf(">Veuillez entrer un choix correct !\n> ");
					bufferManager();
				}
				h = hachage(mot);
				T[h] = supprimer(mot, T[h]);
				printf("L'element %s a ete supprime", mot);
				bufferManager();
				getchar();
				system("cls");
				break;
			case 6 :
				for (i = 0; i < C; i++) printf("Il y a %d elements\n",  NbElements(T[i]));
				getchar();
				system("cls");
				break;
		}
	}
	return 0;
}

// Fonction de Hachage
int hachage(char mot[30]) {
	int i = 0, x = 0;
	for (i = 0; mot[i] != '\0'; i++) x += mot[i];
	x %= C;
	if (x < 0) return x + C;
	return x;
}

// Supprime l'élément de la liste identique à la chaîne de caratères passée en argument.
LISTE supprimer(char mot[30], LISTE A) {
	LISTE crt, prc;
    crt = prc = A;
    while (crt) {
        if (!strcmp(crt->mot, mot)) {
            if (prc == crt) A = crt->pSuiv;
            else prc->pSuiv = crt->pSuiv;
            free(crt->mot);
            free(crt);
            return A;
        } else {
            prc = crt;
            crt = crt->pSuiv;
        }
    }
    printf(">Element non trouve.\n");
    return A;
}

/*LISTE Insert(char mot[30], LISTE L) { // Ne gère pas les doublons.
	LISTE temp = (LISTE) malloc(sizeof(list_maillon));
	strcpy(temp->mot, mot);
	temp->pSuiv = L;
	return temp;
}*/

LISTE Insert(char mot[30], LISTE L) { // Gère les doublons
	int a = 1;
	LISTE temp = L;
	while (temp) {
		if (!strcmp(mot, temp->mot)) a = 0;
		temp = temp->pSuiv;
	}
	if (a) {
		temp = (LISTE) malloc(sizeof(list_maillon));
		strcpy(temp->mot, mot);
		temp->pSuiv = L;
		return temp;
	} else {
		return L;
	}
}

int NbElements(LISTE L) {
	int cpt = 0;
	while (L) {
		cpt++;
		L = L->pSuiv;
	}
	return cpt;
}

void Affichage(LISTE L) {
	if (L) {
		printf("%s\n", L->mot);
		Affichage(L->pSuiv);
	}
}

int Element(char mot[30], LISTE L) {
	while (L) {
		if (strcmp(L->mot,mot) == 0) return 1;
		L = L->pSuiv;
	}
	return 0;
}

void Menu() {
	printf("                           |                        |\n");
    printf("                           |   PROJET HACHAGE B46   |\n");
    printf("                           |                        |\n");
    printf("                           |     Anon & tmtsmc     |\n");
    printf("                           |________________________|\n\n");
	printf("Sélectionnez une option:\n\n");
	printf("0. Quitter\n");
	printf("1. Insérer un élement\n");
	printf("2. Vérifier la présence d'un mot\n");
	printf("3. Afficher Dictionnaire\n");
	printf("4. Nombre d'élément dans le dictionnaire\n");
	printf("5. Supprimer un element\n");
}

// Vide le buffer.
void bufferManager() {
    scanf("%*[^\n]"); // Se sert du regex pour gérer le buffer.
    getchar();
}
