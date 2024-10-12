#include "bits/stdc++.h"
#define SIZEHASH 100

class Perro {
	public:
	int n_patas;
	std::string nombre;
	char nota;
	Perro(int n, std::string nom, char ca) : n_patas{n}, nota{ca} {
		nombre = nom;
	}
};
template<>
struct std::hash<Perro> {
	size_t operator()(const Perro& p) const {
		std::hash<int> int_hash;
		std::hash<char> ch_hash;
		std::hash<std::string> str_hash;
		return int_hash(p.n_patas) + ch_hash(p.nota) + str_hash(p.nombre);
	}
};

int main() {
	std::hash<int> int_hash;
	std::hash<char> ch_hash;
	std::hash<float> fl_hash;
	std::hash<double> db_hash;
	std::hash<std::string> str_hash;
	std::hash<Perro> perro_hash;
	int i = 24;
	char c = '0';
	float f = 2.2;
	double d = 1.223233414;
	std::string s = "Halo";
	Perro p(4, "Max", 'A');
	//size_t hash_vali = int_hash(i);
	std::cout << "Hash value for " << i << ": " << int_hash(i) << "[Hash index: " << int_hash(i) % SIZEHASH << "]\n";  
	std::cout << "Hash value for " << c << ": " << ch_hash(c) << "[Hash index: " << ch_hash(c) % SIZEHASH << "]\n";  
	std::cout << "Hash value for " << f << ": "  << fl_hash(f) << "[Hash index: " << fl_hash(f) % SIZEHASH << "]\n";  
	std::cout << "Hash value for " << d << ": " << db_hash(d) << "[Hash index: " << db_hash(d) % SIZEHASH << "]\n";  
	std::cout << "Hash value for " << s << ": " << str_hash(s) << "[Hash index: " << str_hash(s) % SIZEHASH << "]\n";  
	std::cout << "Hash value for [" << p.n_patas << ", " << p.nombre << ", "<< p.nota << "]: " << perro_hash(p) << "[Hash index: " << perro_hash(p) % SIZEHASH << "]\n";  

	return 0;
}
