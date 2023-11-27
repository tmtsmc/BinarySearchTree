// ------------------------
//
//    PROJET ARBRE B46
//
//     Anon Anon
//	   tmtsmc tmtsmc
//
// ------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// strcmp, strcpy
#include <Windows.h> 	// clear

// Arbre
typedef struct noeud{
	char mot[20];
	struct noeud *fg,*fd;
} liste_noeud;

typedef liste_noeud *DICO;

FILE *f;
DICO pROOT = NULL;

// Entêtes
int lookup(char mot[20], DICO d);	//Recherche la présence d'un mot dans le dictionnaire
int comparer(DICO a, DICO b);		//Compare deux arbres
DICO insert(char mot[20], DICO d);	//Permet l'insertion d'un mot dans le dictionnaire
void afficherDico(DICO d);			//Affiche les mots du dictionnaire
void Menu();						//Affiche le menu
void MenuComparer();				//Affiche le menu pour la comparaison
void bufferManager();

int main(int argc, char *argv[]) {
	int x = 0, q = 1, u = 1, y = 0;
	char mot[20];
	DICO A = NULL, B = NULL;
	f = fopen("mini_dico.txt","r+");
	if (f == NULL) {
		fprintf(stderr,"Erreur ouverture de fichier !\n");
		return -1;
	}
	while (!feof(f)) {
		fscanf(f, "%s", mot);
		pROOT = insert(mot, pROOT);
	
	}
	while (q) {
		Menu();
		//Saisie sécurisée.
		while (!scanf("%d", &x)) {
			printf(">Veuillez entrer un choix correct !\nChoix : ");
			bufferManager();
		}
		bufferManager();
		switch (x) {
			case 1 : //insertion d'un élément
				printf("sélectionnez un mot:\n");
				//Saisie sécurisée.
				while (!scanf("%30[a-z]s", mot)) {
					printf(">Veuillez entrer un choix correct !\n> ");
					bufferManager();
				}
				pROOT = insert(mot, pROOT);
				if (lookup(mot, pROOT)) printf("Le mot a été inseré dans le dictionnaire\n");
				else printf("Le mot n'a pas pu être inséré\n");
				bufferManager();
				getchar();
				system("cls");
				break;
			case 2 : //Vérifier la présence d'un mot
				printf("sélectionnez un mot:\n");
				//Saisie sécurisée.
				while (!scanf("%30[a-z]s", mot)) {
					printf(">Veuillez entrer un choix correct !\n> ");
					bufferManager();
				}
				if (lookup(mot, pROOT)) printf("Le mot est présent\n");
				else printf("Le mot n'est pas présent\n");
				bufferManager();
				getchar();
				system("cls");
				break;
			case 3 : //Affichage Dictionnaire
				afficherDico(pROOT);
				getchar();
				system("cls");
				break;
			case 4 : //Deuxième menu.
				while (u) {
					system("cls");
					MenuComparer();
					//Saisie sécurisée.
					while (!scanf("%d", &y)) {
						printf(">Veuillez entrer un choix correct !\nChoix : ");
						bufferManager();
					}
					bufferManager();
					switch (y) {
						case 1: //inserer un mot dans Dico A
							printf("Selectionnez un mot:\n");
							//Saisie sécurisée.
							while (!scanf("%30[a-z]s", mot)) {
								printf(">Veuillez entrer un choix correct !\n> ");
								bufferManager();
							}
							A = insert(mot, A);
							bufferManager();
							system("cls");
							break;
						case 2: //inserer un mot dans Dico B
							printf("Selectionnez un mot:\n");
							//Saisie sécurisée.
							while (!scanf("%30[a-z]s", mot)) {
								printf(">Veuillez entrer un choix correct !\n> ");
								bufferManager();
							}
							B = insert(mot, B);
							bufferManager();
							system("cls");
							break;
						case 3: //Afficher le Dico A
							afficherDico(A);
							getchar();
							system("cls");
							break;
						case 4: //Afficher le Dico B
							afficherDico(B);
							getchar();
							system("cls");
							break;
						case 5:	//comparaison entre Dico A et Dico B
							if (comparer(A, B)) printf("les dictionnaires sont identiques\n");
							else printf("Les dictionnaires ne sont pas identiques\n");
							getchar();
							system("cls");
							break;
						case 6: //Retour au premier menu.
							u = 0;
							system("cls");
							break;
						}
					}
				break;
			case 5 :
				q = 0;
				break;
		}
	}
	return 0;
}

// Fonction de recherche
int lookup(char mot[20], DICO d) {
	if (d == NULL) return 0;
	if (strcmp(d->mot, mot) == 0) return 1;
	if (strcmp(d->mot, mot) > 0) return lookup(mot, d->fg);
	if (strcmp(d->mot, mot) < 0) return lookup(mot, d->fd);
	return 0;
}

// Comparaison des deux dictionnaires
int comparer(DICO a, DICO b){
	if (a == NULL && b == NULL) return 1;
	if ((a == NULL && b) || (a && b == NULL)) return 0;
	else return (strcmp(a->mot, b->mot) == 0) && comparer(a->fg, b->fg) && comparer(a->fd, b->fd);	
}

// Insertion d'un élémént
DICO insert(char mot[20], DICO d) {
	if (d == NULL) {
		DICO p = (DICO) malloc(sizeof (liste_noeud));
		strcpy(p->mot, mot);
		p->fg = NULL;
		p->fd = NULL;
		return p;
	} else if (strcmp(mot, d->mot) < 0) {
		d->fg=insert( mot, d->fg);
		return d;
	} else if(strcmp(mot, d->mot) > 0) {
		d->fd=insert(mot, d->fd);
		return d;
	} else return d;
}

// Affichage d'un des dictionnaires
void afficherDico(DICO d) {
	if (d) {
		afficherDico(d->fg);
		printf("%s \n",d->mot);
		afficherDico(d->fd);
	}
}

// Menu principal
void Menu() {
	printf("                           |                        |\n");
    printf("                           |     PROJET TP4 B46     |\n");
    printf("                           |                        |\n");
    printf("                           |     Anon & tmtsmc     |\n");
    printf("                           |________________________|\n\n");
	printf("Sélectionnez une option:\n\n");
	printf("1. Insérer un élement\n");
	printf("2. Vérifier la présence d'un mot\n");
	printf("3. Afficher Dictionnaire\n");
	printf("4. Comparer deux dictionnaire\n");
	printf("5. Quitter\n\n");
}

// Menu secondaire
void MenuComparer() {
	printf("                           |                        |\n");
    printf("                           |     PROJET TP4 B46     |\n");
    printf("                           |                        |\n");
    printf("                           |     Anon & tmtsmc     |\n");
    printf("                           |________________________|\n\n");
	printf("1. Inserer un mot dans le Dictionnaire A\n");
	printf("2. Inserer un mot dans le Dictionnaire B\n");
	printf("3. Afficher le Dictionnaire A\n");
	printf("4. Afficher le Dictionnaire B\n");
	printf("5. Comparer les Dictionnaires\n");
	printf("6. Quitter la comparaison\n\n");
}

// Vide le buffer.
void bufferManager() {
    scanf("%*[^\n]"); // Se sert du regex pour gérer le buffer.
    getchar();
}