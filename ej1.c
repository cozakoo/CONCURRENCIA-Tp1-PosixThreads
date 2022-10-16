#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_HILOS 2
 
int contador=0;

void *decrementarContador(void *arg)
{
    //Id del hilo
    long numHilo;
    numHilo= (long)arg;

    //decrementa el contador
    contador--; 
    printf("El hilo %ld decremento el contador a %d \n",numHilo,contador);

    pthread_exit(NULL);
}

void *incrementarContador(void *arg)
{
	long numHilo;
    numHilo= (long)arg;
    
    //incrementa dos veces
    contador+=2;
    printf("El hilo %ld incremento el contador a %d \n", numHilo,contador);
    pthread_exit(NULL);
}


int main()
{

    //Arreglo de Hilos
    pthread_t hilos[NUM_HILOS];
    int rc1,rc2,rc3;
    long t,k;
    for(k=0; k<10; k++){
        for(t=0; t<NUM_HILOS; t++){

            if (t==0){
                rc1 = pthread_create(&hilos[t], NULL, incrementarContador, (void *)t+1);
            }else{
                rc2 = pthread_create(&hilos[t+1], NULL, decrementarContador, (void *)t+1);
                rc3 = pthread_create(&hilos[t+1], NULL, decrementarContador, (void *)t+2);
            }
        }
    }

  //Forma correcta de finalizar el Hilo
  pthread_exit(NULL);
}