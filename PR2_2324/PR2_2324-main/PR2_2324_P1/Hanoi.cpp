#include <iostream>
#define ent std::cout << std::endl;

void mover(std::string a, std::string b) {
	std::cout << "Se mueve pieza de " << a << " a " << b;
	ent; 
}

/*Función que resuelve Hanoi de nivel lv de A(from) a C(dest) usando como auxiliar B(aux)*/
void hanoi(std::string from, std::string dest, std::string aux, int lv) {
	if(lv == 1) 
		mover(from, dest);
	else {
		hanoi(from,aux,dest,lv-1);
		mover(from,dest);
		hanoi(aux,dest,from,lv-1);
	}	
}


int main(int argc, char** argv) {
	hanoi("A","C","B",3);
	return 0;
}
