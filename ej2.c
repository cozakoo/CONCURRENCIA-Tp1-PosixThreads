#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


int ArregloDeEnteros[1000];


void *inicializarValores(void* arg) {

    int *p_longitud, longitud,i;
	
	p_longitud = (int *) arg;
	longitud = *p_longitud;
    
    srand(time(NULL)); //setea valor de random

    for(i=0; i<=longitud; i++){
        unsigned int r;
        r = rand() % 100;
        ArregloDeEnteros [i] = r;
   }
   pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    if (argc == 1) {
        return 0;
    }
    else {
        
        int longitud, rc, t;
        longitud = atoi(argv[1]);
        pthread_t hilo;

        rc= pthread_create(&hilo,NULL,&inicializarValores, &longitud);
	    
        if(rc != 0) {
            exit(1);
        } else {
            printf("VALORES \n");
            for(t=0; t<longitud; t++)
                printf("Posicion del arreglo %d tiene el valor de %d \n",t, ArregloDeEnteros[t]);

                
            printf("\n");
        
            }
            pthread_exit(NULL);
    }
}