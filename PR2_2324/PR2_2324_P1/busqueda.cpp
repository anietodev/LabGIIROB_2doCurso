#include <iostream>
#include <chrono>
#define SIZE 10

template<typename T>
class Busqueda {
	public:
		static int iterativa(T x, T a[], int size);
		static int binaria(T x, T a[], int ini, int end);
};
template<typename T>
int Busqueda<T>::iterativa(T x, T a[], int size) {
	int i;
	for(i = 0; i < size; i++) 
		if(a[i] == x) 
			return i;
	return -1;
}
template<typename T>
int Busqueda<T>::binaria(T x, T a[], int ini, int end) {
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
}

int main(int argc, char* argv[]) {	
	if(argc < 2) {	 	
		std::cerr << "Error: Número insuficiente de argumentos. Al ejecutar indicar: ./busqueda x size" << std::endl;
		return -1;
	}
	int n = 0;
	std::string arg = argv[1];
    	try {
        n = std::stoi(arg);
        	std::cout << "El número entero a buscar es: " << n << std::endl;
    	} catch (const std::invalid_argument& e) {
        	std::cerr << "Error: El argumento no es un número entero válido." << std::endl;
    	} catch (const std::out_of_range& e) {
        	std::cerr << "Error: El argumento está fuera del rango de un entero." << std::endl;
    	}	

	int a[SIZE] = {3,8,15,23,56,60,72,75,81,92};
	auto start = std::chrono::system_clock::now(); //Guarda el instante
	std::cout << "Posición: " << Busqueda<int>::iterativa(n,a,SIZE) << std::endl;
	auto end = std::chrono::system_clock::now(); //Guarda el instante
	std::chrono::duration<float, std::milli> duration = end - start; //Diferencia
	std::cout << "Time iterativa: " << duration.count() << "s" << std::endl; //Resultado
	start = std::chrono::system_clock::now(); //Guarda el instante
	std::cout << "Posición: " << Busqueda<int>::binaria(n,a,0,SIZE) << std::endl;
	end = std::chrono::system_clock::now(); //Guarda el instante
	duration = end - start; //Diferencia
	std::cout << "Time binaria: " << duration.count() << "s" << std::endl; //Resultado
	return 0;
}
