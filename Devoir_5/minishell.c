#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
void execute(char ** argv);


int main(int argc, char const *argv[])
{
	

	char cmd[255];
	char **argvCmd=malloc(255*sizeof(char*));
	char **argvCmdprog=malloc(255*sizeof(char*));
	int pid_fils;

	for (int i = 0; i < 255; ++i)
	{
		argvCmd[i]=NULL;
		argvCmdprog[i]=NULL;
	}

	printf("Saisissez des commandes et taper quit pour quitter \n");
	while(1)
	{
		printf("Minishell >");
		gets(cmd);
		if (strcmp(cmd,"quit")==0)
		{
			return 0;
		}
		 //etape 1: on decoupe chaque commande separer par ;
		argvCmd[0]=strtok(cmd,";");
		int i=1;
		while((argvCmd[i]=strtok(NULL,";"))!=NULL)
			i++;
		/* On pouvait fournir a la focntion execute la variable argvCm
			si l'objetif été de donner une commande suivi de ces argument 
			mais l'objetif ici , c'est de fournir plusieur commande separer par ;
			et pour chaque commande ces arguments sont separer par un sspace .
		*/
		//Etape 2:  pour chaque commande on separe les arguments 
		int j=0;
		while(j<i){
			argvCmdprog[0]=strtok(argvCmd[j]," ");
			int k=1;
			while((argvCmdprog[k]=strtok(NULL," "))!=NULL)
				k++;
			// Etape 4:apre separation on donne a la fonction execute les commande

			printf("Execution du commande %s",argvCmdprog[0]);
			for (int i = 1; i <k; ++i)
			{
				printf("%s",argvCmdprog[i] );
			}
			printf("\n");
			execute(argvCmdprog);
			j++;

		}
	}

	return 0;
}

void execute(char **argv){
	int pid_fils;
	pid_fils=fork();
	switch(pid_fils)
	{
		case -1:
			perror("Erreur de creation du fils\n");
			return ;
		case 0:
			execvp(argv[0],argv);
			perror("Erreur d'execution de la commande\n");
			return ;
		default:
			wait(NULL);
	}
}