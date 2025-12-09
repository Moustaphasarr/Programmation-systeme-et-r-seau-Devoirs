#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

	int f(int n)
	{
		if(n<=0)
			return 1;
		return 2*f(n-1);
	}
	int g(int m)
	{
		return 2*m;
	}
	int main(int argc ,char *argv[])
	{	
		extern char * optarg;
		extern int optind , opterr,optopt;
		int opt;
		int *n=NULL;
		int *m=NULL;
		int presencedes2;
		while((opt=getopt(argc,argv,":f:g:"))!=-1)
		{
			switch(opt)
			{
				case 'f':
					n=(int*)malloc(sizeof(int));
					*n=atoi(optarg);
					break;
				case 'g':
					m=(int*)malloc(sizeof(int));
					*m=atoi(optarg);
					break;
				case '?' :
					printf("Erreur : option -%c inconnue \n",optopt);
					return 0; 
			}
		}
		
		
		//ON VERIFIE SI LE NOMBRE D'ARGUMENT VAUT 3 POUR POUVOIR CALCULER F(N) OU G(M)
		if(argc<=3)
		{	if(n!=NULL &&n>=0)
				printf("f(n)=2^n=%d\n",f(*n));
			if(m!=NULL)
				printf("g(n)=2*m=%d\n",g(*m));
		}else{ //DANS LE CAS CONTRAIRE ON DOIT CALCULER FOG(N) OU GOF(M)
			if(argc==4)
			{	if(strcmp(argv[1],"-f")==0)
					printf("fog(%d)\n",f(g(*n)));
					
				if(strcmp(argv[1],"-g")==0)
					printf("gof(%d)\n",g(f(*m)));
			}
			
			}
			
		
		return 0;
		

	}
