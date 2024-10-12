#include <vector>
#include <random>

template<typename T>
void swap(T &a, T &b) {
	T aux = a;
	a = b;
	b = aux;
}
/*		Función Búsqueda Binaria		*/
template<typename T>
int binaria(T x, std::vector<T>& a, int ini, int end) {
	if(ini > end)
		return -1;
	int m = (end + ini)/2;
	if(a[m] == x) {
		return m;
	} else if(a[m] > x) {
		return binaria(x, a, ini, m - 1);
	} else { 
		return binaria(x, a, m + 1, end);
	}
} // Fin función búsqueda binaria
/*		Función QuickSort			*/
/*template<typename T>
int Partition(std::vector<T>& v, int ini, int fin) {
	T x = v[fin]; // x es el pivote
	int i = ini, j;
	for(j = ini; j < fin; j++) {
		if(v[j] <= x) {
			swap(v[i],v[j]);
			i += 1; // aumentamos el índice para no intercambiar la misma posición dos veces
		} // comparamos todos los elementos con el pivote
	}
	swap(v[i], v[j]); // coloca el pivote en su posición
	return i; // devuelve la posición del pivote
}
template<typename T>
void QuickSort(std::vector<T>& v, int ini, int fin) {
	if(ini < fin) {
		int pivot = Partition(v, ini, fin);
		QuickSort(v, ini, pivot - 1);
		QuickSort(v,pivot + 1, fin);
	}
}*/
template<typename T>
int Partition(std::vector<T>& v, int ini, int fin, const int &p) {
	T x; // x es el pivote
	int i, j;
	if(p == 1) { // el 1er elemento es el pivote
		x = v[ini];
		i = ini + 1;
		for(j = ini + 1; j <= fin; j++) {
			if(v[j] <= x) {  
				swap(v[i],v[j]);
				i += 1; // aumentamos el índice para no intercambiar la misma posición dos veces
			}
		} // comparamos todos los elementos con el pivote
		if(i >= j) {
			i = fin; 
		} else {
			i -= 1;
		} 
		swap(v[ini], v[i]);
	} else if(p == 2) { // el último elemento es el pivote
		x = v[fin];
		i = ini;
		for(j = ini; j < fin; j++) {
			if(v[j] <= x) {
				swap(v[i],v[j]);
				i += 1;
			} 
		}
		swap(v[i], v[j]); // coloca el pivote en su posición
	} else if(p == 3) { // la posición central es el pivote
		int posp = (ini+fin)/2;
		x = v[posp];
		i = ini - 1;
		j = fin + 1;
		while(true) {
			do {			
				i += 1;	
			} while(v[i] < x); // Hasta que v[i] >= x
			do {
				j -= 1;
			} while(v[j] > x); // Hasta que v[j] <= x
			if(i >= j) // Si i y j ya han sobrepasado o están en el pivote
				return posp;
			if (i == posp) 
				posp = j;
			else if(j == posp)
				posp = i;
			swap(v[i], v[j]); // Intercambia valores menores a la derecha por mayores a la izq del pivote
		}
	} else { // el pivote es un elemento random
		std::random_device rd; // Semilla para el generador de números aleatorios
   		std::mt19937 g(rd()); // Generador de números aleatorios
		std::uniform_int_distribution<int> dis(ini, fin); // Definir el rango de los números aleatorios
		int posp = dis(g);
		x = v[posp];
		i = ini - 1;
		j = fin + 1;
		while(true) {
			do {			
				i += 1;	
			} while(v[i] < x); // Hasta que v[i] >= x
			do {
				j -= 1;
			} while(v[j] > x); // Hasta que v[j] <= x
			if(i >= j)  // Si i y j ya han sobrepasado o están en el pivote
				return posp;
			if (i == posp) 
				posp = j;
			else if(j == posp)
				posp = i;

			swap(v[i], v[j]); // Intercambia valores menores a la derecha por mayores a la izq del pivote
		}
	} 
		return i; // devuelve la posición del pivote
}
template<typename T>
void QuickSort(std::vector<T>& v, int ini, int fin, const int &p) {
	if(ini < fin) {
		int pivot = Partition(v, ini, fin, p);
			QuickSort(v, ini, pivot - 1, p);
			QuickSort(v,pivot + 1, fin, p);
	}
} // Fin función QuickSort
