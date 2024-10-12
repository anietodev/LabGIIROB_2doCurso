#ifndef NODO_H
#define NODO_H
#include <string>

class Nodo {
	public:
		int clave;
		string dato;
		Nodo(int clav, string dat) : clave{clav}, dato{dat};
};

#endif
