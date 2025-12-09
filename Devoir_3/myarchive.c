#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "myarchive.h"



//-----------
	
	void ecrire(int fd,void *buf,int taille){
		int r=write(fd,buf,taille);
		if (r==-1)
		{
			printf("Ecriture impossible \n");
			exit(-1);
		}
	}
	

// ------
int extraction(char * nomarchive){
	
	int nbfich,nbLu,totalLu;
	char buffer[4096];
	// on ouvre le fichier;
	int fd=open(nomarchive,O_RDONLY);
	if (fd==-1)
	{
		printf("Erreur d'ouverture\n");
		exit(-1);
	}

	//  on recupere le nombre de fichier
	read(fd,&nbfich,sizeof(int));
	// recuperation des metadonnee
	metadonne T[nbfich];
	for (int i = 0; i < nbfich; ++i)
	{
		read(fd,T[i].nom,100);
		read(fd,&T[i].perme,sizeof(mode_t));
		read(fd,&T[i].taille,sizeof(long));
		
	}


	// creation de chaque fihier pour y ecrire les donnes
	for (int i = 0; i < nbfich; ++i)
	{
		int fd1=open(T[i].nom,O_CREAT|O_TRUNC|O_WRONLY,T[i].perme);
		if (fd1==-1)
		{
			printf("Erreur d'ouverture\n");
			return 0;
		}

		totalLu = 0;
		while (totalLu < T[i].taille) {

		    int k = T[i].taille - totalLu;  
		    if (k > sizeof(buffer)) 
		        k = sizeof(buffer);  

		    nbLu = read(fd, buffer,k);
		    if(nbLu <= 0){
		        printf("Erreur de lecture dans l’archive\n");
		        exit(-1);
		    }

		    write(fd1, buffer, nbLu);

		    totalLu += nbLu;
		}


		// -------------------------------------
		close(fd1);

	}
	close(fd);
	return 1;

}

// Archivage 


void archiver(int taille,int argc,char **argv){
	int r;
	char buffer[4096];
	metadonne T[taille];
	// extraction des metadonne;
	struct stat s;
	for (int i = 2; i < argc; ++i)
	{
		stat(argv[i],&s);
		strcpy(T[i-2].nom,argv[i]);
		T[i-2].taille=s.st_size;
		T[i-2].perme=	s.st_mode;
	}

	// Creation du fichier a mettre les archives 
	int fd=open(argv[1],O_CREAT|O_TRUNC|O_WRONLY,0644);

	if (fd==-1)
	{
		printf("Echec d'uverture du ficier\n");
		exit(-1);
	}

	// remplissage du fichier

	//1)ecriture  du nombre de fichier le composant:
	r=write(fd,&taille,sizeof(int));
	if (r==-1)
	{
		printf("Ecriture impossible \n");
		exit(-1);
	}
	//2) ecriture des metadonnees
	int j=0;
	while(j<taille){


		ecrire(fd,T[j].nom,100);
		ecrire(fd,&T[j].perme,sizeof(mode_t));
		ecrire(fd,&T[j].taille,sizeof(long));
		j++;
		
	}

	// 3) ecriture des donnéées

	j=0;
	while(j<taille){
		int nbLu,totalLu=0;
		// on ouvre un des fichier 
		int fd1=open(T[j].nom,O_RDONLY);
		if (fd1==-1)
		{
			printf("Erreur d'ouverture\n");
			exit(-1);
		}

		while((nbLu=read(fd1,buffer,4096))>0&&totalLu<T[j].taille){
			ecrire(fd,buffer,nbLu);
			totalLu+=nbLu;
		}
		close(fd1);
		j++;
	}

	close(fd);
	printf("Archivage avec succe\n");

}

// ----------------------
	

