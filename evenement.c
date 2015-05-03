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
#include "evenement.h"


evenement *add_event(evenement *E,REEL time,int type,int num_blocs,int num_caisse){
    if(E==NULL){
        evenement *newE;
        newE=malloc( sizeof(evenement) );
        newE->time=time;
        newE->type=type;
        newE->num_blocs=num_blocs;
        newE->num_caisse=num_caisse;
        newE->next=NULL;
        return newE;
    }
    else if( E->time>time ){
        evenement *newE;
        newE=malloc( sizeof(evenement) );
        newE->time=time;
        newE->type=type;
        newE->num_blocs=num_blocs;
        newE->num_caisse=num_caisse;
        newE->next=E;
        return newE;
    }
    else {
        E->next=add_event(E->next,time,type,num_blocs,num_caisse);
        return  E;

    }

}



evenement *delete_first_event(evenement *E){
        if(E==NULL) {
            return NULL ;
    }
        evenement *newE=E->next;
        free(E);
        return newE;
}



void delete_all_event(evenement *E){

if(E!=NULL){
	evenement *T=E->next;
	free(E);
	delete_all_event(T);
	}

}

