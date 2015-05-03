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
typedef struct temps_debut_file temps_debut_file;

temps_debut_file *add_temps_debut_file(temps_debut_file *temps_df,REEL time);
temps_debut_file *delete_temps_debut_file(temps_debut_file *temps_df);
void delete_all_temps(temps_debut_file *temps_df);


struct temps_debut_file{
    REEL time;
    temps_debut_file *next;
};
