/********************************************/
/* Auteur: Basri Mohamed		    */
/*					    */
/* Lieu: UVSQ à Versailles		    */
/* Année: 2014/2015		            */
/* Parcours: M1 INFO, Gr1	            */
/*					    */
/* Sujet:Projet de Simulation (Supermarché) */
/********************************************/

#include "temps_sejour.h" 

typedef double REEL;
typedef struct file_blocs file_blocs;
typedef struct file_caisse file_caisse;

file_caisse *cree_liste_de_caisse(int nb_caisse);
file_blocs *cree_caisse_par_blocs(int nb_blocs,int nb_caisse_par_blocs); 
void *reinitialiser_blocs_caisse(file_blocs *ma_liste_de_blocs,int nb_blocs,int nb_caisse_par_blocs);





struct file_blocs{
int nb_client_blocs;
int nb_client_servi;
REEL temps_moyen_sejour;
file_caisse *debut_liste_de_caisse;
temps_debut_file *debut;
temps_debut_file *fin;
};


struct file_caisse{
int nb_client_caisse;
int nb_client_servi;
REEL temps_moyen_sejour;
temps_debut_file *debut;
temps_debut_file *fin;
};
