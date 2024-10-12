#include "brazoRobotico.h"

BrazoRobotico::BrazoRobotico() {
x = y = z = 0.0;
sujeta = false;
}
void BrazoRobotico::coger() {
if(sujeta == false) {
	sujeta = true;
	std::cout << "Se ha cogido el objeto correctamente." << std::endl;	
} else
	std::cout << "Error al coger objeto. El brazo ya sujeta otro objeto.\n";
}
void BrazoRobotico::soltar() {
if(sujeta == false)
	std::cout << "Error al soltar objeto. El brazo no sujeta ningún objeto.\n";
else {
	sujeta = false;
	std::cout << "Se ha soltado el objeto correctamente." << std::endl;
}
}
void BrazoRobotico::mover(double x_, double y_, double z_) {
x = x_;
y = y_;
z = z_;
std::cout << "El brazo robótico se ha desplazado correctamente a las coordenadas ("  << x << ", " << y << ", " << z << ")." << std::endl;
}

