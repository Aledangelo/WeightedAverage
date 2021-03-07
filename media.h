#include <unistd.h>
#import <iostream>
#include <stdlib.h>

#define MAX_ESAMI 30

double mediaPonderata(int*,int*,int);
double mediaAritmetica(int*,int);
void stampaLista(int*,int*,int,bool);
int cancellaVoto(int*,int*,int,bool);
void previsioniMedia(int*,int*,int,int,bool);
void copiaArray(int*,int*,int);
int insertVoto(int*,int*,int,bool);
void maxMedia(int*,int*,int,bool);
void minMedia(int*,int*,int,bool);
