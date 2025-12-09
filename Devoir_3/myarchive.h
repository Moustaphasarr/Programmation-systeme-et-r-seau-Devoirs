#ifndef ARCHIVE_H
#define ARCHIVE_H


typedef struct {
	char nom[100];
	mode_t perme;
	long taille;

}metadonne;

int extraction(char * nomarchive);
void archiver(int taille,int argc,char **argv);
void ecrire(int fd,void *buf,int taille);

#endif