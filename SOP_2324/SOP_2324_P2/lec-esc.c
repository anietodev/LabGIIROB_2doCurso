#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_L  3
#define MAX_E  2


int dato = 0;

void *lector(void *arg) {
    int id = *((int *)arg);
    while (1) {
       
        // Leer datos
        printf("\033[1;33mLector %d leyendo: %d\033[0m\n", id, dato);
        usleep(rand() % 1000000); // Retraso aleatorio de hasta 1 segundo (en microsegundos)

    }
 pthread_exit(0);
}

void *escritor(void *arg) {
    int id = *((int *)arg);
     int aux;
    while (1) {
        // Escribir datos
        aux = dato;
	usleep(5000); // usleep pequeños para alargar el tiempo en el que se modifica la variable y haya + prob para CC
	aux++; 
	usleep(600000); 
	dato = aux; // hace lo mismo que dato++ pero con más instrucciones máquina (+ prob de CC)
	 
        printf("\033[1;36mEscritor %d escribiendo: %d\033[0\n", id, dato);

        usleep(rand() % 2000000); // Retraso aleatorio de hasta 2 segundos (en microsegundos)
    }
     pthread_exit(0);
}

int main() {

    // MAX_L lectores y MAX_E escritores
    pthread_t lectores[MAX_L], escritores[MAX_E]; 
    int i;
    pthread_attr_t atrib;
    int id_l[MAX_L], id_r[MAX_E];

    // Inicializar la semilla del generador de números aleatorios
    srand(time(NULL)); 

    // Inicializar la estructura pthread_attr
    pthread_attr_init(&atrib); 

    // Crear lectores
    for(i = 0; i < MAX_L; i++) {
    	id_l[i] = i; // Para que, al pasarle la variable al hilo, no sobreescriba la misma variable y machaque su valor (el de la i)	
	pthread_create(&lectores[i], &atrib, lector, (void *)&id_l[i]);	    
    }
    // Crear escritores
    for(i = 0; i < MAX_E; i++) {
    	id_r[i] = i; 
	pthread_create(&escritores[i], &atrib, escritor, (void *)&id_r[i]);
    }	
    // Esperar a que los hilos terminen
    for(i = 0; i < MAX_L; i++)
	    pthread_join(lectores[i], NULL);
    for(i = 0; i < MAX_E; i++)
	    pthread_join(escritores[i], NULL);
    printf("Acaba el main\n");
    return 0;
}


// Respuestas pdf:
// 1. sí, ya que modifican toodos los hilos escritores modifican la variable dato practicamente a la vez (sin sleep antes).
// 2. Como hay pocas instrucciones al modificar el dato (dato++; tiene 3 instrucciones máquina), es más difícil que se produzca un cambio de contexto (termine un quantum y pase a ejecución otro hilo) y , por tanto, es menos probable que se produzca CC.
// 3. Aumentando el tiempo que pasa cada hilo escritor modificando el dato. Así, si añadimos una variable auxiliar, la modificamos, luego se la asignamos a la variable global y ponemos sleeps entre medias, ejecutará más instrucciones máquina y es más probable que se produzca el cambio de contexto, forzando así la CC.
// 4. Lo detectamos al comprobar que en la terminal aparece la variable dato sin aumentar secuencialmente.
