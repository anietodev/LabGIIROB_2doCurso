#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_L  3
#define MAX_E  2


// Mutex 
pthread_mutex_t m_monitor = PTHREAD_MUTEX_INITIALIZER; 

//Variables condicion para lectores y escritores
pthread_cond_t cond_lectores = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_escritores = PTHREAD_COND_INITIALIZER;


// Variable que indica el número de lectores leyendo
int nlectores = 0;
// Variables de escritores 
int nesc_activos = 0;
int nesc_esperando = 0;

int dato = 0;

void comenzar_lectura(int id) { 
	pthread_mutex_lock(&m_monitor); // Bloqueo acceso a nlectores
	while((nesc_activos != 0) || (nesc_esperando > 0)) { // Si hay escritores, espero. IMP while porque pueden haber varios lectores
		printf("\033[1;33mLECTOR %d espera\033[0m\n", id);
		pthread_cond_wait(&cond_lectores, &m_monitor);
	}
        nlectores++; 
	printf("\033[1;33mLECTOR %d despierta\033[0m\n", id);
	printf("\033[1;33mLectores activos %d\033[0m\n", nlectores);
	pthread_mutex_unlock(&m_monitor); // Libero acceso a nlectores
}
void terminar_lectura(int id) {	
	pthread_mutex_lock(&m_monitor); // Bloqueo acceso a nlectores
	nlectores--;
	// Si es el último escritor, desbloque al posible escritor que esté esperando
	printf("\033[1;33mLECTOR %d acaba\033[0m\n", id);
	if(nlectores == 0) {
		pthread_cond_signal(&cond_escritores); // Aviso simple para despertar solo a un escritor 	
	}	
	pthread_mutex_unlock(&m_monitor); // Libero acceso a nlectores
	sleep(1);// retraso suficiente para que entre un escritor 
}
void comenzar_escritura(int id) {
	pthread_mutex_lock(&m_monitor); // Bloqueo acceso a nlectores
	nesc_esperando++;
	if((nlectores != 0) || (nesc_activos != 0)) {
		printf("\033[1;36mESCRITOR %d espera\033[0m\n", id);
		pthread_cond_wait(&cond_escritores, &m_monitor);
	}
	nesc_esperando--; nesc_activos++; // Indico que hay un escritor activo
	printf("\033[1;36mESCRITOR %d despierta\033[0m\n", id);
	printf("\033[1;36mEscritores activos %d\033[0m\n", nesc_activos);
	pthread_mutex_unlock(&m_monitor); // Libero acceso a nlectores
}

void terminar_escritura(int id) {
	pthread_mutex_lock(&m_monitor); // Bloqueo acceso a nlectores
	nesc_activos--; // Indico que ya no hay escritores activos
	printf("\033[1;36mESCRITOR %d acaba\033[0m\n", id);
	if(nesc_esperando == 0)
		pthread_cond_broadcast(&cond_lectores); // Aviso a todos los posibles lectores suspendidos 
	else 
		pthread_cond_signal(&cond_escritores); // Aviso al escritor esperando
	pthread_mutex_unlock(&m_monitor); // Libero acceso a nlectores
	sleep(1); 
}

void *lector(void *arg) {
	int id = *((int *)arg);
	for (int i = 0; i < 5; i++) {
		comenzar_lectura(id);
 		printf("\033[1;33mLECTOR %d leyendo %d\033[0m\n", id, dato);
 		terminar_lectura(id);
 	}
 	pthread_exit(NULL);
}

void *escritor(void *arg) {
	int id = *((int *)arg);
	for (int i = 0; i < 5; i++) {
		comenzar_escritura(id);

		// Escribir datos SC
		int aux;
        	aux = dato;
		usleep(5000); // usleep pequeños para alargar el tiempo en el que se modifica la variable y haya + prob para CC
		aux++; 
		usleep(600000); 
		dato = aux; // hace lo mismo que dato++ pero con más instrucciones máquina (+ prob de CC)
		printf("\033[1;36mEscritores esperando %d\033[0m\n", nesc_esperando);
		printf("\033[1;36mESCRITOR %d escribiendo %d\033[0m\n", id, dato);

		terminar_escritura(id);
	}
	pthread_exit(NULL);
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
