#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include<stdbool.h>


#define MAX 1000

//int index=0;

char buffer[MAX];

void *generarCaracteres(void* arg)
{
    srand(time(NULL)); 
    int i=0;
    printf("Generando caracteres... \n");

    while ((i<=MAX) && (buffer[i] == '-')) {
        
        char c;
        c = 'A' + (rand() % 26); //Letras mayusculas
        buffer[i]=c;
        i++;    
    }
    
    if(i==MAX){
        printf("El buffer ya esta completo con caracteres \n");
    }

    pthread_exit(NULL);
}



void *leerCaracteres(void* arg)
{
    bool noEstaVacio= true;
    int i=0;
    printf("INICIANDO A LEER CARACTERES \n");

    while ((noEstaVacio)&&(i<=MAX))
    {

        if (buffer[i]== '-'){
            noEstaVacio=false;
            printf("ERROR: El buffer no esta completo");
        }else{
            printf("%c-", buffer[i]);
            i++;
        }

    }
    printf("\n");
    pthread_exit(NULL);
}

void *inicializarBuffer(void)
{
    int i; 

    for(i=0; i<MAX; i++) {
        buffer[i] = '-';
    }
}



int main(int argc, char *argv[]){

    inicializarBuffer(); 

    int rc1,rc2;
    pthread_t hiloProductor, hiloConsumidor;

    rc1 = pthread_create(&hiloProductor, NULL, &generarCaracteres, NULL);
    rc2 = pthread_create(&hiloConsumidor, NULL, &leerCaracteres, NULL);

    
    if (rc1){
        printf("ERROR: %d\n", rc1);
        exit(-1);
    }else {
        if (rc2){
            printf("ERROR: %d\n", rc2);
            exit(-1);
        }
    }

    pthread_exit(NULL);
}