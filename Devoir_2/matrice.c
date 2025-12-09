#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main(int argc ,char * argv[])
{	
	extern char * optarg;
	extern int optind , opterr,optopt;
	int c=0,
		a=0,
		dim,
		b=0,
		t=0;
	int test,x;
	int fd;
	char buff[100]={0};
	// inialisation rand pour les valeur aleatoir
	srand(time(NULL));
	char name[100];

	int opt;
	while((opt = getopt(argc, argv, ":cad:btf:")) != -1)
	{
	    switch(opt)
	    {
	        case 'c':
	        	c=1;
	        	break;
	        case 'a':
	        	a=1;
	        	break;
	        case 'd':
	        	dim=atoi(optarg);
	        	break;
	        case 'b':
	        	b=1;
	        	break;
	        case 't':
	        	t=1;
	        	break;
	        case 'f': 
	        	strcpy(name,optarg);
	        	break;
	        case ':': 
	        	exit(-1);
	        	break;
	        case '?':
	        	exit(-1);
	        	break;
	    }
	}

	//On verifie si on doit affichier ou creer la matrice

	if (c&&a)
	{
		printf("Les option a et c ne peuvent pas etre present en meme temp\n");
		return 0;
	}

	// si c'est la creation
	if (c)
	{
		fd=open(name,O_CREAT|O_WRONLY|O_TRUNC,0644);
		if(fd==-1){
			printf("Erreur d'ouverture du fichier\n");
			return 0;
		}

		// on verifie si c'est la creation en binaire ou pas 
		if (!t)
		{
			for (int i = 0; i < dim; ++i)
			{
				for (int j = 0; j < dim; ++j)
				{
					x=rand()%100;
					test=write(fd,&x,sizeof(int));
					if(test<0)
					{
						printf("Erreur d'ecriture\n");
						return 0;
					}
				}
			}
		}else{ // dans le cas de creation format texte
			for (int i = 0; i < dim; ++i)
			{
				for (int j = 0; j < dim; ++j)
				{	
					x=rand()%100;
					sprintf(buff,"%d ",x);
					test=write(fd,buff,strlen(buff));
					if(test<0)
					{
						printf("Erreur d'ecriture\n");
						return 0;
					}
				}
				write(fd,"\n",1);
			}
		}
		
	}else{
		// affichage d'un matrice:
		fd=open(name,O_RDONLY);
		if (fd==-1)
		{
			printf("Erreur d'ouverture du fichier\n");
			return 0;
		}

		//On verifie si le fichier fourni est forumat text ou binaire

		if(!t) // dans le cas ou c'est binaire
		{	
			for (int i = 0; i < dim; ++i)
			{
				for (int j = 0; j < dim; ++j)
				{
					int r=read(fd,&x,sizeof(int));
					if(r>0)
					{
						printf("%d ",x);
					}
				}
				printf("\n");
			}
			
		}else{

			int n;
			while((n = read(fd, buff, sizeof(buff)-1)) > 0) {
			    buff[n] = '\0';
			    printf("%s", buff);
			}
		}
	}


	close(fd);

	return 0;
	

}


