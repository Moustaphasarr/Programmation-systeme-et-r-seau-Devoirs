#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "myarchive.h"




int main(int argc, char *argv[])
{	
	extern char *optarg;
	extern int optind,opterr,optopt;
	int opt,r;
	char buffer[4096];
	if(argc<3){
		printf("Argument insuffisant usage:\n");
		printf("Archivage->");
		printf("%s nomAchive fichier1 fichier2 ..\n",argv[0]);
		printf("Ou\n");
		printf("Extraction->");
		printf("%s -e nomAchive\n",argv[0]);
		exit(-1);
	}

	while((opt=getopt(argc,argv,":e:"))!=-1){
		switch(opt){
		case 'e':
			// on extracte
			if (extraction(optarg))
			{
				printf("Extraction reussi\n");
			}else{
				printf("essec de l'extraction\n");
			}
			return 0;
		case ':':
			printf("option %c necessite d'argument\n",opt);
			break;
		case '?':
			printf("option inconnu\n");
			exit(-1);
		}
	}


	archiver(argc-2,argc,argv);
	
	printf("Archivage avec succe\n");
	return 0;
}