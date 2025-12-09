#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_NB_FILS 2


int main(int argc, char const *argv[])
{
	
	if (argc<2)
	{
		printf("Argument insiffisant\n");
		printf("Usage: %s niveau\n",argv[0]);
	}
	int profondeur=0,nombreFils=0;
	int profondeur_max=atoi(argv[1]);
	int pid_fils;


	while(profondeur<profondeur_max)
	{

		pid_fils=fork();

		switch(pid_fils)
		{
			case -1:
				perror("Erreur de création du processus\n");
				return 0;
			case 0:
				printf("%d->%d;\n",getppid(),getpid());
				profondeur++;
				if (profondeur>=profondeur_max)
					return 0; 
				nombreFils=0;
				break;
			default:
				nombreFils++;
				wait(NULL);
				if (nombreFils>=2)
				{
					return 0;
				}

		}
	}



	return 0;
}