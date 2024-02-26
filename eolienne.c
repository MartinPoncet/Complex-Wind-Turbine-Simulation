#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "eolienne.h"
#include "vent.h"
#include "menu.h"

// Fonction principale du programme
int main(){
    srand(time(NULL)); // Commande trouvée sur internet pour avoir un 'vrai' random : Initialise le générateur de nombres aléatoires avec une graine basée sur le temps actuel
    Parametres *param;
    param=malloc(sizeof(Parametres)); // Alloue dynamiquement de la mémoire pour les paramètres
    initialiserParametres(param);
    menu(param); // Appelle la fonction de menu pour l'interaction avec l'utilisateur
}

// Fonction de réparation d'une éolienne en fonction du vent
void reparationEolienne(Parametres *param,Vent vent,EtatEolienne *etat,int *cout){
    if(!(etat->isWorking)){
        if(vent!=FORT){
            if (etat->tempsIntervention==0)
            {
                *cout+=param->coutIntervention;// Coût d'intervention appliqué une fois au début de l'intervention
            }
            if (etat->tempsIntervention==param->dureeIntervention-1)
            {
                etat->isWorking=1; // L'éolienne est réparée et redevient opérationnelle
                etat->tempsIntervention=0;
            }
            else{
                etat->tempsIntervention+=1; // Incrémente le temps d'intervention
            }
        }   
    }
}

// Initialise l'état initial d'une éolienne
void initialiserEolienne(EtatEolienne *eolienne){
    eolienne->isWorking=1;
    eolienne->tempsIntervention=0;
    eolienne->prodEolienne=0.0;
}

// Simule le fonctionnement des éoliennes
void simulationEolienne(Parametres *param,Vent ventActuel,float *energieProduite,int tempsSimulation,int nombreEolienne, int *cout,bool afficherLogs,bool saveFile,bool afficherMinMax){
    EtatEolienne *eolienne;
    eolienne=malloc(nombreEolienne*sizeof(EtatEolienne*)); // Alloue dynamiquement de la mémoire pour les états des éoliennes
    FILE *fp;
    if(saveFile){    
        fp = fopen("simulation_eoliennes.txt", "w"); // Ouvre un fichier pour enregistrer les résultats de la simulation
    }


    for (int i = 0; i < nombreEolienne; i++)
    {
        initialiserEolienne(eolienne+i); // Initialise l'état de chaque éolienne
    }
    
    for(int i = 0; i < tempsSimulation; i++)
    {
        if(afficherLogs){ // Affiche les logs si nécessaire
            switch (ventActuel)
            {
            case NUL:
                printf("\nJour %d - Etat du vent : Vent Nul\n",i);
                break;
            case MOYEN:
                printf("\nJour %d - Etat du vent : Vent Moyen\n",i);
                break;
            case FORT:
                printf("\nJour %d - Etat du vent : Vent Fort\n",i);
                break;
            }
        }
        // Enregistre les informations dans le fichier si nécessaire
        if(saveFile){
            fprintf(fp, "Jour %d Vent %d\t",i,ventActuel);
        }

        // Simulation du fonctionnement de chaque éolienne
        for (int j = 0; j<nombreEolienne; j++)
        {
            if((eolienne+j)->isWorking){
                switch (ventActuel)
                {
                case FORT:
                    int random=rand()%100;
                    if (random<param->p) //eolienne cassée
                    {
                        if(afficherLogs){
                            printf("AIE ! Eolienne %d cassée (Cout total : %d (+%d))\n",j,*cout+param->coutIntervention,param->coutIntervention);
                        }
                        if(saveFile){
                            fprintf(fp, "Eolienne %d cassée\t",j);
                        } 
                        (eolienne+j)->isWorking=0; // L'éolienne est hors service
                    }else{
                        *energieProduite+=param->prodF; // Production normale de l'éolienne
                        (eolienne+j)->prodEolienne+=param->prodF;
                        if(afficherLogs){
                            printf("Eolienne %d, nouvelle prod tot : %fMW (+%fMW)\n",j,*energieProduite,param->prodF);
                        }
                        if(saveFile){
                            fprintf(fp, "Eolienne %d +%fMW\t",j,param->prodF);
                        }
                    }
                    break;
                case MOYEN:
                    *energieProduite+=param->prodM;
                    (eolienne+j)->prodEolienne+=param->prodM;
                    if(afficherLogs){
                        printf("Eolienne %d, nouvelle prod tot : %fMW (+%fMW)\n",j,*energieProduite,param->prodM);
                    }
                    if(saveFile){
                        fprintf(fp, "Eolienne %d +%fMW\t",j,param->prodM);
                    }
                    break;
                case NUL:
                    *energieProduite+=param->prodN;
                    (eolienne+j)->prodEolienne+=param->prodN;
                    if(afficherLogs){
                        printf("Eolienne %d, nouvelle prod tot : %fMW (+%fMW)\n",j,*energieProduite,param->prodN);
                    }
                    if(saveFile){
                        fprintf(fp, "Eolienne %d +%fMW\t",j,param->prodN);
                    }
                    break;
                }
            }else{
                reparationEolienne(param,ventActuel,(eolienne+j),cout);
                if(afficherLogs){
                    if((eolienne+j)->tempsIntervention==0 && ventActuel!=2){
                        printf("Eolienne %d toujours cassée, jour %d/%d de réparation\n",j,param->dureeIntervention,param->dureeIntervention);
                    }else{
                        printf("Eolienne %d toujours cassée, jour %d/%d de réparation\n",j,(eolienne+j)->tempsIntervention,param->dureeIntervention);
                    }
                }
                if(saveFile){
                    if((eolienne+j)->tempsIntervention==0 && ventActuel!=2){
                        fprintf(fp,"Eolienne %d cassée %d/%d\t",j,param->dureeIntervention,param->dureeIntervention);
                    }else{
                        fprintf(fp,"Eolienne %d cassée %d/%d\t",j,(eolienne+j)->tempsIntervention,param->dureeIntervention);
                    }
                }
            }
        }
        if(saveFile){
            fprintf(fp,"\nProduction %f\tCout %d\n",*energieProduite,*cout);
        }
        ventActuel=vent(param,ventActuel);
    }
    printf("\nProduction totale de %d éoliennes sur %d jours : %fMW pour un total de %d euros.\n",nombreEolienne,tempsSimulation,*energieProduite,*cout);

    if(saveFile){
        fprintf(fp,"\nProduction totale %f\tCout total %d",*energieProduite,*cout);
        fclose(fp);
    }
    if(afficherMinMax){
        int indexMin, indexMax;
        trouverMinMaxProduction(eolienne, nombreEolienne, &indexMin, &indexMax);
        printf("L'éolienne %d produit le moins : %f MW\n", indexMin, eolienne[indexMin].prodEolienne);
        printf("L'éolienne %d produit le plus : %f MW\n", indexMax, eolienne[indexMax].prodEolienne);
    }
}

void trouverMinMaxProduction(EtatEolienne *eolienne, int nombreEolienne, int *indexMin, int *indexMax){
    float minProduction = eolienne[0].prodEolienne;
    float maxProduction = eolienne[0].prodEolienne;

    *indexMin = 0;
    *indexMax = 0;

    for (int i = 1; i < nombreEolienne; i++)
    {
        if (eolienne[i].prodEolienne < minProduction)
        {
            minProduction = eolienne[i].prodEolienne;
            *indexMin = i;
        }

        if (eolienne[i].prodEolienne > maxProduction)
        {
            maxProduction = eolienne[i].prodEolienne;
            *indexMax = i;
        }
    }
}
