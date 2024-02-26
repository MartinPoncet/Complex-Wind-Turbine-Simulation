#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "eolienne.h"
#include "vent.h"


// Fonction pour simuler le changement de vent selon la matrice de transition
Vent vent(Parametres *param,Vent ventActuel){
    switch (ventActuel)
    {
    case NUL:
    // Matrice de transition pour le vent nul
        int transiN[3]={param->ventNN,param->ventNM,param->ventNF};
        return randomVent(ventActuel,transiN);
        break;
    case MOYEN:
    // Matrice de transition pour le vent moyen
        int transiM[3]={param->ventMN,param->ventMM,param->ventMF};
        return randomVent(ventActuel,transiM);
        break;
    case FORT:
    // Matrice de transition pour le vent fort
        int transiF[3]={param->ventFN,param->ventFM,param->ventFF};
        return randomVent(ventActuel,transiF);
        break;
    }
}

// Fonction pour générer un vent aléatoire selon la matrice de transition
Vent randomVent(Vent ventActuel, int matTransi[]){
    int random=rand()%100;
    if(random<matTransi[0]){
            return NUL;
        }
        else if(random>=matTransi[0]&&random<matTransi[1]+matTransi[0]){
            return MOYEN;
        }
        else if(random>=matTransi[0]+matTransi[1]&&random<matTransi[1]+matTransi[0]+matTransi[2]){
            return FORT;
        }
}