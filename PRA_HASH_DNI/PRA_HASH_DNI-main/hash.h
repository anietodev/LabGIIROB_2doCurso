#ifndef HASH_H
#define HASH_H

#include "Nodo.h"
#define ERROR -1
#define OK 0

class TablaHash {
	int hash(Nodo &n); // Devuelve la pocición de n en la tabla según su clave o ERROR
	int insert(Nodo &n); // Devuelve OK o ERROR
	int buscar(const int &clave); // Devuelve posición de la clave o ERROR
	int dlete(const int &clave); // Devuelve la posición borrada o ERROR
	int busca_hueco(); // Devuelve posición libre o ERROR
};
#endif
