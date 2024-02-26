#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "eolienne.h"
#include "vent.h"
#include "menu.h"

// Fonction principale du menu
void menu(Parametres *param){
    bool quitter = false;
    int choix;
    while (!quitter){

        Vent ventActuel=NUL;
        int c=0;
        float p=0.0;
        float *energieProduite=&p;
        int *cout= &c;
        int nombreEolienne,nombreJour;
        
        // Saisie du nombre d'éoliennes et de jours pour la simulation
        printf("\nCombien d'éoliennes souhaitez-vous simuler ? ");
        scanf("%d",&nombreEolienne);
        printf("\nCombien de jours souhaitez-vous simuler ? ");
        scanf("%d",&nombreJour);

        // Affichage du menu principal
        printf("\n===== MENU =====\n");
        printf("1  Afficher les étapes d'une simulation\n");
        printf("2  Afficher le résultat d'une simulation\n");
        printf("3  Sauvegarder une simulation dans un fichier externe\n");
        printf("4  Afficher les éoliennes qui produisent le plus et le moins\n");
        printf("5  Modifier les paramètres\n");
        printf("6  Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);
        
        switch (choix){
            case 1 :
            simulationEolienne(param,ventActuel,energieProduite,nombreJour,nombreEolienne,cout,true,false,false);
            break;
            case 2 :
            simulationEolienne(param,ventActuel,energieProduite,nombreJour,nombreEolienne,cout,false,false,false);
            break;
            case 3 :
            simulationEolienne(param,ventActuel,energieProduite,nombreJour,nombreEolienne,cout,true,true,false);
            break;
            case 4 :
            simulationEolienne(param,ventActuel,energieProduite,nombreJour,nombreEolienne,cout,false,false,true);
            break;
            case 5 :
            modifierParam(param);
            break;
            case 6 :
            quitter = true;
            break;
            default :
            printf("Merci d'entrer un numéro valide\n");
            break;
        }
    }
}

// Fonction pour modifier les paramètres
void modifierParam(Parametres *param){
    bool quitter = false;
    int choix;
    while (!quitter){
        // Affichage du menu de modification des paramètres
        printf("\n===== PARAMETRES =====\n");
        printf("1  Modifier les valeurs de V\n");
        printf("2  Modifier les valeurs de la production d'une éolienne\n");
        printf("3  Modifier la probabilité (en pourcents) qu'une éolienne tombe en panne\n");
        printf("4  Modifier le temps d'une intervention\n");
        printf("5  Modifier le prix d'une intervention\n");
        printf("6  Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);
        
        switch (choix){
            case 1 :
            bool quitterV = false;
            int choixV;
            while (!quitterV){
                int valeur;
                printf("\n===== VALEURS V =====(en pourcents)\n");
                printf("1  Modifier valeur vent nul -> vent nul\n");
                printf("2  Modifier valeur vent nul -> vent moyen\n");
                printf("3  Modifier valeur vent nul -> vent fort\n");
                printf("4  Modifier valeur vent moyen -> vent nul\n");
                printf("5  Modifier valeur vent moyen -> vent moyen\n");
                printf("6  Modifier valeur vent moyen -> vent fort\n");
                printf("7  Modifier valeur vent fort -> vent nul\n");
                printf("8  Modifier valeur vent fort -> vent moyen\n");
                printf("9  Modifier valeur vent fort -> vent fort\n");
                printf("10  Quitter\n");
                printf("Choix : ");
                scanf("%d", &choixV);
                
                switch (choixV){
                    case 1 :
                    printf("\nValeur : ");
                    scanf("%d", &valeur);
                    param->ventNN=valeur;
                    break;
                    case 2 :
                    printf("\nValeur : ");
                    scanf("%d", &valeur);
                    param->ventNM=valeur;
                    break;
                    case 3 :
                    printf("\nValeur : ");
                    scanf("%d", &valeur);
                    param->ventNF=valeur;
                    break;
                    case 4 :
                    printf("\nValeur : ");
                    scanf("%d", &valeur);
                    param->ventMN=valeur;
                    break;
                    case 5 :
                    printf("\nValeur : ");
                    scanf("%d", &valeur);
                    param->ventMM=valeur;
                    break;
                    case 6 :
                    printf("\nValeur : ");
                    scanf("%d", &valeur);
                    param->ventMF=valeur;
                    break;
                    case 7 :
                    printf("\nValeur : ");
                    scanf("%d", &valeur);
                    param->ventFN=valeur;
                    break;
                    case 8 :
                    printf("\nValeur : ");
                    scanf("%d", &valeur);
                    param->ventFM=valeur;
                    break;
                    case 9 :
                    printf("\nValeur : ");
                    scanf("%d", &valeur);
                    param->ventFF=valeur;
                    break;
                    case 10 :
                    quitterV = true;
                    break;
                    default :
                    printf("Merci d'entrer un numéro valide\n");
                    break;
                }
            }
            break;
            case 2 :
            bool quitterP = false;
            int choixP;
            while (!quitterP){
                int valeur;
                printf("\n===== VALEURS PRODUCTION =====(en MW, float)\n");
                printf("1  Modifier valeur de production lors d'un vent nul\n");
                printf("2  Modifier valeur de production lors d'un vent moyen\n");
                printf("3  Modifier valeur de production lors d'un vent fort\n");
                printf("4  Quitter\n");
                printf("Choix : ");
                scanf("%d", &choixP);
                
                switch (choixP){
                    case 1 :
                    printf("\nValeur : ");
                    scanf("%f", &valeur);
                    param->prodN=valeur;
                    break;
                    case 2 :
                    printf("\nValeur : ");
                    scanf("%f", &valeur);
                    param->prodM=valeur;
                    break;
                    case 3 :
                    printf("\nValeur : ");
                    scanf("%f", &valeur);
                    param->prodF=valeur;
                    break;
                    case 4 :
                    quitterP = true;
                    break;
                    default :
                    printf("Merci d'entrer un numéro valide\n");
                    break;
                }
            }

            break;
            case 3 :
            int valeurP;
            printf("\nValeur (en pourcents) : ");
            scanf("%d", &valeurP);
            param->p=valeurP;
            break;
            case 4 :
            int valeurD;
            printf("\nValeur (en jours) : ");
            scanf("%d", &valeurD);
            param->dureeIntervention=valeurD;
            break;
            case 5 :
            int valeurC;
            printf("\nValeur (en euros) : ");
            scanf("%d", &valeurC);
            param->coutIntervention=valeurC;
            break;
            case 6 :
            quitter = true;
            break;
            default :
            printf("Merci d'entrer un numéro valide\n");
            break;
        }
    }

}

// Fonction pour initialiser les paramètres par défaut
void initialiserParametres(Parametres *param){
    param->ventNN=VENTNN;
    param->ventNM=VENTNM;
    param->ventNF=VENTNF;
    param->ventMN=VENTMN;
    param->ventMM=VENTMM;
    param->ventMF=VENTMF;
    param->ventFN=VENTFN;
    param->ventFM=VENTFM;
    param->ventFF=VENTFF;

    param->prodF=PRODF;
    param->prodM=PRODM;
    param->prodF=PRODF;
    param->p=P;
    param->coutIntervention=COUT_INTERVENTION;
    param->dureeIntervention=DUREE_INTERVENTION;
}