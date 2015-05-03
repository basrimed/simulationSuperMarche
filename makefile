#############################################
# Auteur: Basri Mohamed			    #
#					    #
# Lieu: UVSQ à Versailles	 	    #
# Année: 2014/2015			    #
# Parcours: M1 INFO, Gr1		    #
#					    #
# Sujet:Projet de Simulation (Supermarché)  # 
#############################################

all: run plot

run: compilation
	./main

etat_file_attente.o: etat_file_attente.h temps_sejour.h etat_file_attente.c
	gcc -c etat_file_attente.c -o etat_file_attente.o

evenement.o: evenement.h evenement.c
	gcc -c evenement.c -o evenement.o

temps_sejour.o: temps_sejour.h temps_sejour.c
	gcc -c temps_sejour.c -o temps_sejour.o

main.o: main.c etat_file_attente.h evenement.h
	gcc -c main.c -o main.o

compilation: temps_sejour.o etat_file_attente.o evenement.o main.o
	gcc main.o temps_sejour.o etat_file_attente.o evenement.o -lm -o main

plot: resultat.data
	gnuplot affiche.gplt
	evince courbe.pdf

clean:
	rm *.o *.data *.pdf main
