#include <iostream>
#include <list>

class AdjacencyMatrix {
	private:
		int nvertex;
		int** matrix;
	public:
		AdjacencyMatrix(int nvertex) {
			this->nvertex = nvertex;
			matrix = new int*[nvertex];
			for(int i = 0; i < nvertex; i++) {
				matrix[i] = new int[nvertex];
				for(int j = 0; j < nvertex; j++) {
					matrix[i][j] = 0;
                                }
			}
		}
		~AdjacencyMatrix() {
			for(int i = 0; i < nvertex; i++) {
                                delete[] matrix[i];
                        } 
			delete[] matrix;
		}
		int num_vertex() {
			return nvertex;
		}
		void create_arist(int i, int j) {
			matrix[i][j] = 1;
			matrix[j][i] = 1;
		}
		void remove_arist(int i, int j) {
			matrix[i][j] = 0;
			matrix[j][i] = 0;
		}
		void print_matrix() {
			std::cout << "\t";
			for(int j = 0; j < nvertex; j++)
			       std::cout << j << '\t';
			std::cout << std::endl;	
			for(int i = 0; i < nvertex; i++) {
				std::cout << i << "\t";
				for(int j = 0; j < nvertex; j++) {
					std::cout << matrix[i][j] << "\t"; 
				}
				std::cout << std::endl;
			}
		}
		void wide_path(int v = 0) {
			bool vert_alcanzados[nvertex] = {false};
			std::list<int> vert_actuales;
			vert_actuales.push_back(v);
			int vert;
			std::cout << "* Wide path: ";
				while(!vert_actuales.empty()) {
					vert = vert_actuales.front();
        				vert_actuales.pop_front();
					std::cout << vert << " - ";
					for(int i = 0; i < nvertex; i++) {
						if((matrix[vert][i] == 1) && (vert_alcanzados[i] == false)) {
							if(i < vert) 
								vert_actuales.push_front(i);
							else
								vert_actuales.push_back(i);
						}
					}
					vert_alcanzados[vert] = true;
				}
			std::cout << "\b\b  " << std::endl;
		}
		void deep_path_(bool *visited, int v = 0) {
			for(int i = 0; i < nvertex; i++) {
				if((matrix[v][i] == 1) && (visited[i] == false)) {
					std::cout << i << " - ";
					visited[i] = true;
					deep_path_(visited, i);
				}
			}
		}
		void deep_path(int v = 0) {
			bool visited[nvertex] = {false};
			std::cout << "* Deep path: " << v << " - ";
			visited[v] = true; 
			deep_path_(visited, v);
			std::cout << "\b\b  " << std::endl;
		}
};

int main() {
	AdjacencyMatrix m(5);
	m.create_arist(0,1);
	m.create_arist(0,2);
	m.create_arist(1,3);
	m.create_arist(2,4);
	m.print_matrix();
	m.wide_path(0);
	m.wide_path(1);
	m.wide_path(2);
	m.wide_path(3);
	m.wide_path(4);
	m.deep_path(0);
	m.deep_path(1);
	m.deep_path(2);
	m.deep_path(3);
	m.deep_path(4);
}
