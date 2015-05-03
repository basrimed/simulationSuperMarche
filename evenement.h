/********************************************/
/* Auteur: Basri Mohamed		    */
/*					    */
/* Lieu: UVSQ à Versailles		    */
/* Année: 2014/2015		            */
/* Parcours: M1 INFO, Gr1	            */
/*					    */
/* Sujet:Projet de Simulation (Supermarché) */
/********************************************/ 


typedef double REEL;
typedef struct evenement evenement;

evenement *add_event(evenement *E,REEL time,int type,int num_blocs,int num_caisse);
evenement *delete_first_event(evenement *E);
void delete_all_event(evenement *E);


struct evenement{
    REEL time;
    int type;
    int num_blocs;
    int num_caisse;
    evenement *next;
};
