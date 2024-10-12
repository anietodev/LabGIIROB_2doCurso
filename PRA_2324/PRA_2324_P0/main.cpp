#include "brazoRobotico.h"

int main(void) {
	BrazoRobotico pepe;
	double x, y, z;
	std::cout << "A continuación, introduce una a una las coordenadas donde se encuentra el objeto que se desee manipular" << std::endl;
	std::cout << "Introduce coordenada x: ";
	std::cin >> x;
	std::cout << "Introduce coordenada y: ";
	std::cin >> y;
	std::cout << "Introduce coordenada z: ";
	std::cin >> z;
	pepe.mover(x,y,z);
	pepe.coger();
return 0;
}
