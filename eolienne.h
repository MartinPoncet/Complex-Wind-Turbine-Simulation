#define VENTNN 20
#define VENTNM 73
#define VENTNF 7

#define VENTMN 11
#define VENTMM 74
#define VENTMF 15

#define VENTFN 4
#define VENTFM 61
#define VENTFF 35

#define PRODN 0.0
#define PRODM 0.4
#define PRODF 0.65
    
#define P 15
#define COUT_INTERVENTION 150000
#define DUREE_INTERVENTION 3

// Définition de l'énumération Vent
typedef enum {
    NUL,MOYEN,FORT // Vent nul = 0, vent moyen = 1,vent fort = 2 
}Vent;

// Structure pour représenter l'état d'une éolienne
typedef struct
{
    bool isWorking; // Indique si l'éolienne est opérationnelle
    int tempsIntervention; // Temps restant d'intervention en cas de panne
    float prodEolienne;
}EtatEolienne;

// Structure pour représenter les paramètres du système éolien
typedef struct
{
    // Probabilités de vent pour chaque combinaison de l'état actuel et de l'état suivant
    int ventNN;
    int ventNM;
    int ventNF;
    int ventMN;
    int ventMM;
    int ventMF;
    int ventFN;
    int ventFM;
    int ventFF;

    // Productions éoliennes pour chaque niveau de vent
    float prodN;
    float prodM;
    float prodF;

    int p; // Probabilité qu'une éolienne soit endommagée par un vent fort
    int coutIntervention;
    int dureeIntervention;

}Parametres;


void reparationEolienne(Parametres *param,Vent vent,EtatEolienne *etat,int *cout);
void initialiserEolienne(EtatEolienne *eolienne);
void simulationEolienne(Parametres *param,Vent vent,float *energieProduite,int tempsSimulation,int nombreEolienne, int *cout,bool afficherLogs,bool saveFile,bool afficherMinMax);
void trouverMinMaxProduction(EtatEolienne *eolienne, int nombreEolienne, int *indexMin, int *indexMax);