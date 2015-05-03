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
#include "temps_sejour.h"


temps_debut_file *add_temps_debut_file(temps_debut_file *temps_df,REEL time){
    if(temps_df==NULL){
        temps_debut_file *new_temps_df;
        new_temps_df=malloc( sizeof(temps_debut_file) );
        new_temps_df->time=time;
        new_temps_df->next=NULL;
        return new_temps_df;
    }
    else {
        temps_debut_file *new_temps_df;
        new_temps_df=malloc( sizeof(temps_debut_file) );
        new_temps_df->time=time;
        new_temps_df->next=NULL;
        temps_df->next=new_temps_df;
        return new_temps_df;
    }

}



temps_debut_file *delete_temps_debut_file(temps_debut_file *temps_df){
    if(temps_df==NULL) {
            return NULL ;
    }
        temps_debut_file *new_temps_df=temps_df->next;
        free(temps_df);
        return new_temps_df;
}



void delete_all_temps(temps_debut_file *temps_df){

if(temps_df!=NULL){
	temps_debut_file *T=temps_df->next;
	free(temps_df);
	delete_all_temps(T);
	}
}

