/********************************************/
/* Auteur: Basri Mohamed		    */
/*					    */
/* Lieu: UVSQ à Versailles		    */
/* Année: 2014/2015		            */
/* Parcours: M1 INFO, Gr1	            */
/*					    */
/* Sujet:Projet de Simulation (Supermarché) */
/********************************************/

 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "etat_file_attente.h"
#include "evenement.h"

#define NB_BLOCS 5
#define NB_CAISSE 12
#define MAX_CLIENT_FILE_CAISSE 3

#define CST_C 1.5
#define DUREE_BLOCS_CAISSE 10*(CST_C-1)

#define UNIFORME_0_NB_BLOCS ( (double)rand()*NB_BLOCS/(double)RAND_MAX )

#define UNIFORME ( (double)random()/(double)RAND_MAX )

#define expo(x) ( -log((double)UNIFORME) / (x) )

#define DEBIT_SORTIE_CAISSE 0.01

#define DEBIT_PASSAGE_EN_CAISSE_BORNE_INF 0.01
#define DEBIT_PASSAGE_EN_CAISSE_BORNE_SUP 1.0

#define AC1 1   //arrivé  client represente le moment ou un client veut passer en caisse, on ne prend pas en compte le temps passé a faire les courses
#define AC2 2
#define DBC 3  /* Déplacement d'un bloc vers une caisse, On part du principe que d'un même bloc 
				plusieurs déplacements peuvent se faire en parallèles (dépend du nombre de place disponible) */
#define DS  4
#define FS  5



int main()
{ 5;  
srand(getpid());

FILE *fichier;
fichier=fopen("resultat.data","w");  
if(fichier==NULL) exit(1);



int i,j;
int cache;
REEL valeur_aleatoire;
int min;
int nb_client_arriver=0;
int type=0;
int aleatoire;
int caisse_choisie_par_client;  //le client choisi la caisse avec le moins de client
int num_blocs;
int num_caisse;
int blocs_servi;
int caisse_servi;
REEL time_echeancier=0.0;
REEL temps_sejour_moyen_blocs=0.0;
REEL temps_sejour_moyen_caisse=0.0;








file_blocs *ma_liste_de_blocs=NULL;
ma_liste_de_blocs=cree_caisse_par_blocs(NB_BLOCS,NB_CAISSE);

evenement *echeancier_client=NULL;
echeancier_client=add_event(echeancier_client,0.0,AC1,-1,-1);


REEL y;
for( y=DEBIT_PASSAGE_EN_CAISSE_BORNE_INF ; y<=DEBIT_PASSAGE_EN_CAISSE_BORNE_SUP ; y+=0.01 )

{
temps_sejour_moyen_blocs=0.0;
temps_sejour_moyen_caisse=0.0;
nb_client_arriver=0;
time_echeancier=0.0;
blocs_servi=0;
caisse_servi=0;
reinitialiser_blocs_caisse(ma_liste_de_blocs,NB_BLOCS,NB_CAISSE);

delete_all_event(echeancier_client);
echeancier_client=NULL;
echeancier_client=add_event(echeancier_client,0.0,AC1,-1,-1);


while(time_echeancier<86400.0)  // On suppose que notre unité de temps est la seconde, on simule l'equivalent de 24 heures
  {


        time_echeancier=echeancier_client->time;
        type=echeancier_client->type;
        num_blocs=echeancier_client->num_blocs;
        num_caisse=echeancier_client->num_caisse;
        echeancier_client=delete_first_event(echeancier_client);





        if(type==AC1){
		nb_client_arriver++;
		valeur_aleatoire=expo(y);

            echeancier_client=add_event(echeancier_client,time_echeancier+valeur_aleatoire,AC1,-1,-1);

            aleatoire=(int)UNIFORME_0_NB_BLOCS;

            ma_liste_de_blocs[aleatoire].nb_client_blocs++;
            ma_liste_de_blocs[aleatoire].fin=add_temps_debut_file( ma_liste_de_blocs[aleatoire].fin , time_echeancier ); // on sauvegarde son temps d'arrivé, pour pouvoir calculé son temps de sejour 

            if(ma_liste_de_blocs[aleatoire].nb_client_blocs==1) {
                    ma_liste_de_blocs[aleatoire].debut=ma_liste_de_blocs[aleatoire].fin;   // 1 seul client dans le bloc ==> notre liste des temps d'arrivés contient une seul valeur debut=fin
                    echeancier_client=add_event(echeancier_client,time_echeancier,DBC,aleatoire,-1); // on a fixé le num du bloc ou se trouve le client, mais on connais pas encore le num de la caisse d'ou la valeur -1
            }
        }





        else if(type==DBC){ // on choisit la caisse avec le moin de client dans le cas ou au moins une caisse a moins de  3 clients
                if(ma_liste_de_blocs[num_blocs].nb_client_blocs>0){
                        caisse_choisie_par_client=-1;
                        min=-1;
                                for(i=0;i<NB_CAISSE;i++){
                                        cache=ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[i].nb_client_caisse;
                                        if(cache<MAX_CLIENT_FILE_CAISSE){
                                            if(min==-1 || min>cache){
                                                        min=cache;
                                                        caisse_choisie_par_client=i;
                                                }
                                            }
                                        }


                    if(caisse_choisie_par_client!=-1){
                        ma_liste_de_blocs[num_blocs].nb_client_blocs--;
                        ma_liste_de_blocs[num_blocs].nb_client_servi++;



                ma_liste_de_blocs[num_blocs].temps_moyen_sejour+=time_echeancier-ma_liste_de_blocs[num_blocs].debut->time; 
                ma_liste_de_blocs[num_blocs].debut=delete_temps_debut_file(ma_liste_de_blocs[num_blocs].debut);

                if(ma_liste_de_blocs[num_blocs].debut==NULL) ma_liste_de_blocs[num_blocs].fin=NULL;

                echeancier_client=add_event(echeancier_client,time_echeancier,AC2,num_blocs,caisse_choisie_par_client); //ce client est localisé sur un bloc et une caisse bien definie 

                }
            }
        }




        else if(type==AC2){

                ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].nb_client_caisse++;
                ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].fin=add_temps_debut_file( ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].fin , time_echeancier );

                if(ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].nb_client_caisse==1){
                        ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].debut=ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].fin;
                        echeancier_client=add_event(echeancier_client,time_echeancier,DS,num_blocs,num_caisse);
                    }

	
		echeancier_client=add_event(echeancier_client,time_echeancier,DBC,num_blocs,-1);
        }




        else if(type==DS){
                    valeur_aleatoire=expo(DEBIT_SORTIE_CAISSE);

            echeancier_client=add_event(echeancier_client,time_echeancier+valeur_aleatoire,FS,num_blocs,num_caisse);
        }




        else if(type==FS){
            ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].nb_client_caisse--;
            ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].nb_client_servi++;

		// on recupére le temps d'arrivé du client pour calculé son temp de sejour
		// on somme le tout, on divise vers la fin pour recupéré le temps moyen de sejour réel
		ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].temps_moyen_sejour+=time_echeancier-ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].debut->time;
        ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].debut=delete_temps_debut_file(ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].debut);



          if(ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].debut==NULL) {
                    ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].fin=NULL;
            	}
            echeancier_client=add_event(echeancier_client,time_echeancier,DBC,num_blocs,num_caisse);
            if(ma_liste_de_blocs[num_blocs].debut_liste_de_caisse[num_caisse].nb_client_caisse>0){
                echeancier_client=add_event(echeancier_client,time_echeancier,DS,num_blocs,num_caisse);
            }
                
        }
    
}


for(i=0;i<NB_BLOCS;i++){// On calcule le temps moyen de sejour de chaque bloc/caisse puis on calcule le temps moyen de sejour de tout le systeme
		if(ma_liste_de_blocs[i].nb_client_servi!=0){
		cache=ma_liste_de_blocs[i].temps_moyen_sejour/ma_liste_de_blocs[i].nb_client_servi;
		temps_sejour_moyen_blocs+=cache; 
		blocs_servi++;

			}
			for(j=0;j<NB_CAISSE;j++){	
				if(ma_liste_de_blocs[i].debut_liste_de_caisse[j].nb_client_servi!=0){
				cache=ma_liste_de_blocs[i].debut_liste_de_caisse[j].temps_moyen_sejour/(ma_liste_de_blocs[i].debut_liste_de_caisse[j].nb_client_servi);
				temps_sejour_moyen_caisse+=cache;
				caisse_servi++;			
					}
				}

		}


fprintf(fichier,"%.2f  %.2f\n",y,temps_sejour_moyen_blocs/blocs_servi+temps_sejour_moyen_caisse/caisse_servi+DUREE_BLOCS_CAISSE);


//system("clear ");
//printf("%.0f %% terminer\n",(y/DEBIT_PASSAGE_EN_CAISSE_BORNE_SUP)*100);
}
//system("clear ");
printf("\nSimulation finie, veuillez consulter les fichiers crees \n\n");


fclose(fichier);
return 0;
}
