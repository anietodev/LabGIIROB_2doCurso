#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_L  3
#define MAX_E  2

// Semáforo para proteger las secciones críticas 
sem_t mutex; // Sirve para acceder a la var global nlectores en los lectores. Si 1 lector accede/modifica nlectores, ninguno más puede hacerlo a la vez

// Semáforo para controlar el acceso de los escritores
sem_t mutex_escritor; // Sirve para permitir/bloquear la ejecución de escritores. Si hay 1 lector, bloquea; si no, permite. Si hay 1 escritor y 0 lectores, bloquea al siguiente escritor que intente acceder hasta que acabe el actual escritor

// Variable que indica el número de lectores leyendo
int nlectores = 0;

// Variable que indica el número de escritores escribiendo
int nesc_activos = 0;

// Varible que indica si hay escritores esperando
int nesc_esperando = 0;

// Varible global que se emplea para leer y escribir
int dato = 0;

void *lector(void *arg) {
    int id = *((int *)arg);
    while (1) {
	// COMP ENTRADA 
	sem_wait(&mutex);
        nlectores++;
	if(nlectores == 1) {
		sem_wait(&mutex_escritor);
	}
	printf("\033[1;33mLectores activos %d\033[0m\n", nlectores);
	sem_post(&mutex);

        // Leer datos, SECCION CRITICA
	usleep(10); // Compensa la rapidez de la lectura frente a la escritura
	printf("\033[1;33mLECTOR %d leyendo: %d\033[0m\n", id, dato);

	// SALIDA SC
	sem_wait(&mutex);
	printf("\033[1;33mLECTOR %d acaba\033[0m\n", id);
	nlectores--;
	// Si es el último escritor, desbloque al posible escritor que esté esperando
	if(nlectores == 0) {
		sem_post(&mutex_escritor);
	}
	sem_post(&mutex);
        usleep(rand() % 1000000); // Retraso aleatorio de hasta 2 segundos (en microsegundos)
    }
}

void *escritor(void *arg) {
    int aux;
    int id = *((int *)arg);
    while (1) {
	// COMP ENTR
	nesc_esperando++;
	printf("\033[1;36mESCRITOR %d espera\033[0m\n", id);
	sem_wait(&mutex_escritor);
	nesc_esperando--, nesc_activos++;
	printf("\033[1;36mESCRITOR %d despierta\033[0m\n", id);
        // Escribir datos SC
        aux = dato;
	usleep(5000); // usleep pequeños para alargar el tiempo en el que se modifica la variable y haya + prob para CC
	aux++; 
	usleep(600000); 
	dato = aux; // hace lo mismo que dato++ pero con más instrucciones máquina (+ prob de CC)
        
	printf("\033[1;36mEscritores activos %d\033[0m\n", nesc_activos);
	printf("\033[1;36mEscritores esperando %d\033[0m\n", nesc_esperando);
        printf("\033[1;36mESCRITOR %d escribiendo: %d\033[0m\n", id, dato);

	// POST SC
	nesc_activos--; 	
        printf("\033[1;36mESCRITOR %d acaba\033[0m\n", id);
	sem_post(&mutex_escritor);
        usleep(rand() % 2000000); // Retraso aleatorio de hasta 2 segundos (en microsegundos)
    }
}

int main() {
   // Inicializo semáforos
    sem_init(&mutex, 0, 1);
    sem_init(&mutex_escritor, 0, 1);

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
// 4. Lo detectamos al comprobar que en la terminal aparece la variable dato sin aumentar secuencialmente.include <unistd.h>
