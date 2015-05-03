/********************************************/
/* Auteur: Basri Mohamed		    */
/*					    */
/* Lieu: UVSQ à Versailles		    */
/* Année: 2014/2015		            */
/* Parcours: M1 INFO, Gr1	            */
/*					    */
/* Sujet:Projet de Simulation (Supermarché) */
/********************************************/


#include <stdlib.h>  
#include <stdio.h>
#include "etat_file_attente.h"


file_blocs *cree_caisse_par_blocs(int nb_blocs,int nb_caisse_par_blocs){

int i;
file_blocs *ma_liste_de_blocs=NULL;
ma_liste_de_blocs=malloc(nb_blocs*sizeof(file_blocs));

for(i=0;i<nb_blocs;i++){
        ma_liste_de_blocs[i].nb_client_blocs=0;
        ma_liste_de_blocs[i].debut=NULL;
        ma_liste_de_blocs[i].fin=NULL;
        ma_liste_de_blocs[i].temps_moyen_sejour=0.0;
        ma_liste_de_blocs[i].nb_client_servi=0;
        ma_liste_de_blocs[i].debut_liste_de_caisse=cree_liste_de_caisse(nb_caisse_par_blocs);

		}
return ma_liste_de_blocs;
}







file_caisse *cree_liste_de_caisse(int nb_caisse){
    int i;
    file_caisse *ma_liste_de_caisse=NULL;
    ma_liste_de_caisse=malloc(nb_caisse*sizeof(file_caisse));

    for(i=0;i<nb_caisse;i++){
           ma_liste_de_caisse[i].nb_client_caisse=0;
           ma_liste_de_caisse[i].debut=NULL;
           ma_liste_de_caisse[i].fin=NULL;
           ma_liste_de_caisse[i].nb_client_servi=0;
           ma_liste_de_caisse[i].temps_moyen_sejour=0.0;
    }


return ma_liste_de_caisse;
}





void *reinitialiser_blocs_caisse(file_blocs *ma_liste_de_blocs,int nb_blocs,int nb_caisse_par_blocs){

int i,j;
for(i=0;i<nb_blocs;i++){
        ma_liste_de_blocs[i].nb_client_blocs=0;
	delete_all_temps(ma_liste_de_blocs[i].debut);
        ma_liste_de_blocs[i].debut=NULL;
        ma_liste_de_blocs[i].fin=NULL;
        ma_liste_de_blocs[i].temps_moyen_sejour=0.0;
        ma_liste_de_blocs[i].nb_client_servi=0;

	for(j=0;j<nb_caisse_par_blocs;j++){
	   ma_liste_de_blocs[i].debut_liste_de_caisse[j].nb_client_caisse=0;
	   delete_all_temps(ma_liste_de_blocs[i].debut_liste_de_caisse[j].debut);
           ma_liste_de_blocs[i].debut_liste_de_caisse[j].debut=NULL;
           ma_liste_de_blocs[i].debut_liste_de_caisse[j].fin=NULL;
           ma_liste_de_blocs[i].debut_liste_de_caisse[j].nb_client_servi=0;
           ma_liste_de_blocs[i].debut_liste_de_caisse[j].temps_moyen_sejour=0.0;

		}
	}



}
