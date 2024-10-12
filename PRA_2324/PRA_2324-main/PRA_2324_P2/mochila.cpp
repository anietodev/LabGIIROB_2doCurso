#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#define M 16 // Peso máximo de la mochila + 1
#define N 4 // Número de objetos + 1

std::vector<std::vector<int>> matrix(N, std::vector<int>(M)); // Matriz para guardar resultados

/*					Función mochila
  b-> vector de enteros que contiene los valores de los objetos que se pueden meter en la mochila
  p-> vector de enteros que contiene los pesos de los objetos
  N-> número de objetos
  M-> peso que cabe en la mochila
*/
int mochila(std::vector<int> &b, std::vector<int> &p,int n, int m) {
	if(matrix[n][m] > -1) 
		return matrix[n][m];
	if((m <= 0) || (n < 0)) 
		return 0;
	if(p[n] > m)
		matrix[n][m] = mochila(b, p, n-1, m);
	else
		matrix[n][m] = std::max(mochila(b, p, n-1, m), b[n] + mochila(b, p, n-1, m-p[n]));
	return matrix[n][m];
}
void printsol(std::vector<int> &p, std::vector<bool> &s) {
	int m = M - 1;
	int n = N - 1;
	std::cout << "Objetos utilizados: ";
	while(m) {
		for(int i = n; i > 0; i--) 
			if(matrix[i-1][m] >= matrix[i][m]) 
				n -= 1;
		std::cout << n << " ";
		m -= p[n];
		n -= 1;
		s[n] = true; 
	}
	std::cout << std::endl << "Vector solución: ";
	for(int i = 0; i < N-1; i++)
		std::cout << s[i] << " ";
	std::cout << std::endl;
}
int main() {
	for(int j = 0; j < M; j++) 
		matrix[0][j] = 0;
	for(int i = 1; i < N; i++) {
		matrix[i][0] = 0;
		for(int j = 1; j < M; j++) 
			matrix[i][j] = -1;
	} // Inicializamos matriz solución
	std::vector<int> b = {0, 38, 40, 24}; // 1 + Beneficios de los objetos
	std::vector<int> p = {0, 9, 6, 5}; // 1 + Pesos de los objetos
	std::vector<bool> s = {0, 0, 0}; // Vector solución
	std::cout << "Beneficios de los objetos: ";
	for(int i = 1; i < N; i++)
		std::cout << b[i] << " ";
	std::cout << "\nPesos de los objetos: ";
	for(int i = 1; i < N; i++)
		std::cout << p[i] << " ";
	int aux;
	for(aux = M - 1; aux > 0; aux--) {
		std::cout << std::endl << "Peso máximo: " << aux << std::endl;
		std::cout << "Valor máximo: " << mochila(b, p, N-1, aux) << std::endl;
	} // Rellenamos toda la tabla
	std::cout << "Tabla:" << "\n";
	for(int i = 0; i < N; i++) {
		for(int j=0;j<M;j++)
			std::cout << std::setw(3) << matrix[i][j] << " ";
		std::cout << std::endl;
	}
	printsol(p, s); // Rellenamos vector solución y printeamos 
	return 0;
}
