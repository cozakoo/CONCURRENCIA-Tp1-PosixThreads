#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 16

int cont=0;
int contHilos=0;

int enteros[MAX];


void *sumatoria(void *num)
{
    //id del hilo
    long taskid;
    taskid= (long)num--;
    
    printf("El hilo %ld, usara el valor del arreglo que esta en la posicion %ld \n",taskid--, taskid);
    pthread_exit(NULL);
}

void *valoresAleatorios()
{
    //asignamos valores aleatorios al arreglo
    int i;
    for(i=0;i<MAX; i++){
        unsigned int r;
        r= rand() % 20;
        enteros[i] =r;
    }
}



int main(int argc, char *argv[])
{
    //arreglo de hilos
    pthread_t hilos[MAX];
    int t,rc;
    srand(time(NULL)); //setea valor de random, se ejecuta una sola vez

    valoresAleatorios();

    //creamos los hilos
    for(t=0; t < MAX; t++)
    {
        hilos[t]=t+1;
        // printf("Creando el hilo %d\n", hilos );
        rc = pthread_create(&hilos[t], NULL, &sumatoria, (void *)hilos[t]);

        if (rc){
            printf("ERROR: %d\n", rc);
            exit(-1);
        }
        cont+=enteros[t];
    }
    printf("VALOR TOTAL DE LA SUMATORIA: %d \n ", cont);
    pthread_exit(NULL);
}
