#include "DyV.h"
#include <iostream>
#include <chrono>

template<typename T>
void printv(std::vector<T> &v) {
	std::cout << "Vector: [";
	for(int i = 0; i < v.size(); i++) {
		std::cout << v[i] << " ";
	}
	std::cout << "]" << std::endl;
}

int main(int argc, char* argv[]) {	
	if(argc < 2) {	 	
		std::cerr << "Error: Número insuficiente de argumentos. Al ejecutar indicar: ./test_DyV opcion" << std::endl;
		std::cerr << "Opciones: 1.Enteros, 2.Floats, 3.Chars, 4.Probar todos los casos de QuickSort\n";
		return -1;
	}
	int o = 0;
	std::string arg = argv[1];
    	try {
        o = std::stoi(arg);
        	std::cout << "Opción elegida: " << o << std::endl;
    	} catch (const std::invalid_argument& e) {
        	std::cerr << "Error: El argumento no es un número entero válido." << std::endl;
    	} catch (const std::out_of_range& e) {
        	std::cerr << "Error: El argumento está fuera del rango de un entero." << std::endl;
    	}	
	switch(o) {
	case 1:{
		int n;
		std::vector<int> v = {4,2,4,5,1,99,11,21,12,41};
		std::cout << "Desordenado:\n";
		printv(v);
		int fin = v.size() - 1;
		QuickSort(v, 0, fin, 2);
		std::cout << "Ordenado:\n";
		printv(v);
		std::cout << "Introduzca un entero: ";
		std::cin >> n;
		std::cout << "Posición del número " << n << ": " << binaria(n, v, 0, fin) << std::endl;
		break;
	}
	case 2:{
		float f;
		std::vector<float> b = {4.12,1.43,13.28,15.0,7.56,9.02,21.1,56.98,32.01,4.12};
		std::cout << "Desordenado:\n";
		printv(b);
		int fin = b.size() - 1;
		QuickSort(b, 0, fin, 2);
		std::cout << "Ordenado:\n";
		printv(b);
		std::cout << "Introduzca un float: ";
		std::cin >> f;
		std::cout << "Posición del número " << f << ": " << binaria(f, b, 0, fin) << std::endl;
		break;
	}
	case 3:{
		char c;
		std::vector<char> s = {'f','w','c','d','d','q','a','h','l','o'};
		std::cout << "Desordenado:\n";
		printv(s);
		int fin = s.size() - 1;
		QuickSort(s, 0, fin, 2);
		std::cout << "Ordenado:\n";
		printv(s);
		std::cout << "Introduzca un caracter que buscar: ";
		std::cin >> c;
		std::cout << "Posición del caracter " << c << ": " << binaria(c, s, 0, fin) << std::endl;
		break;
	}
	case 4:{
		std::vector<int> v = {4,2,4,5,1,99,11,21,12,41};
		std::cout << "Desordenado:\n";
		printv(v);
		int p;
		std::cout << "Elige opción para pivote: 1.ini 2.fin 3.mid 4.random" << std::endl;
		std::cin >> p;
		auto start = std::chrono::system_clock::now();
		QuickSort(v, 0, v.size()-1, p);
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<float, std::milli> duration = end - start;	
		std::cout << "Time: " << duration.count() << "s" << std::endl;
		std::cout << "Ordenado con opcion " << p << ":\n";
		printv(v);
		break;
	}
	default:
		std::cerr << "ERROR. Opcion no valida\nOpciones: 1.Enteros, 2.Floats, 3.Chars, 4.Probar todos los casos de QuickSort\n";
		break;
	}
	return 0;
}
