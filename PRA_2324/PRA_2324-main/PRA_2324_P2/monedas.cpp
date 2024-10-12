#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#define ROWS 3 // N
#define COLS 9 // M + 1

int infinito = std::numeric_limits<int>::max() - 1;
std::vector<std::vector<int>> matrix(ROWS, std::vector<int>(COLS));
/*std::vector<std::vector<int>> matrix = {
    {0, -1, -1},
    {0, -1, -1},
    {0, -1, -1}
};*/

/*V-> vector de enteros que contiene laa monedas que se pueden utilizar para el cambio.
  N->tamaño del array V.
  M->cantidad a devolver. 
*/
int cambio(std::vector<int> &V, int N, int M){
	if(N < 0 || M < 0)
		return infinito;
	if(matrix[N][M] > -1) 
		return matrix[N][M];
	else 
		matrix[N][M] = std::min(cambio(V,N-1,M), 1 + cambio(V,N, (M - V[N]))); 
	return matrix[N][M];
}
void printsol(std::vector<int> &V) {
	int M = COLS - 1;
	int N = ROWS - 1;
	std::cout << "Monedas utilizadas: ";
	while(M) {
		for(int i = N; i > 0; i--) 
			if(matrix[i-1][M] <= matrix[i][M]) 
				N -= 1;
		std::cout << V[N] << " ";
		M -= V[N];
	}
	std::cout << std::endl;
}
int main(){
	for(int i = 0; i < ROWS; i++) {
		matrix[i][0] = 0;
		for(int j = 1; j < COLS; j++) 
			matrix[i][j] = -1;
	}
	std::vector<int> V = {1, 4, 6};
	std::cout << "Monedas: ";
	for(int i = 0; i < ROWS; i++)
		std::cout << V[i] << " ";
	int M;
	for(M = COLS -1; M > 0; M--) {
		std::cout << std::endl << "Cantidad a devolver: " << M << std::endl;
		std::cout << "Cambio: " << cambio(V, ROWS - 1, M) << std::endl;
	}
	std::cout << "Tabla:" << "\n";
	for(int i = 0; i < ROWS; i++) {
		for(int j=0;j<COLS;j++)
			std::cout << matrix[i][j] << " ";
		std::cout << std::endl;
	}
	printsol(V);
	return 0;
}	
