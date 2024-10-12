#include <vector>
#include <iostream>
//#include <stdlib.h>

void merge(std::vector<int> &v, int ini, int mid, int end) {
	int i = ini; int j = mid; 
	std::vector<int> v1;
	std::vector<int> v2;
	while(i < j) { 
		v1.emplace_back(v[i]);
		i++;
	} 
	std::cout << "Llego aquí\n";
	i = ini;
	while(j <= end) { 
		v2.emplace_back(v[j]);
		j++;
	} 
	std::cout << "Y aquí\n";
	j = mid;
	int k = 0;
	while(i < mid && j < (end+1)) {
		if(v1[i] <= v2[j]) {
			v[k] = v1[i];
			i++;
		} else {
			v[k] = v2[j];
			j++;
		}
		k++;
	}
	if(i > mid) {
		while(j < (end+1)) {
			v[k] = v2[j];
			k++; j++;
		}
	} else {
		while(i < mid) {
			v[k] = v1[i];
			k++; i++;
		}
	}	
	std::cout << "Y aquí también\n";
	/*for(int k = 0; k < (end+1) ; k++) {
		if(i == (mid+1)) {
			while(j < (end+1)){
				v[k] = v2[j];
				j++;
				k++;
			}
		} else if(j == (end+1)) {
			while(i < (mid+1)){
				v[k] = v1[i];
				i++;
				k++;
			}
		} else {
			if(v1[i] < v2[j]) {
				v[k] = v1[i];
				i++;
			} else {
				v[k] = v2[j];
				j++;
			}
		}
	}*/
}
void mergeSort(std::vector<int> &v, int ini, int end) {
	int dif = end - ini;
	if(dif < 1) {
		return;
	}
	if(dif%2 == 0) {
		dif /= 2; //Dividir por 2 la diferencia
		mergeSort(v, ini, dif-1);
		mergeSort(v, end-dif, end);
		merge(v, ini, end-dif, end);
	} else {
		mergeSort(v, ini, dif-1);
		mergeSort(v, dif, end);
		merge(v, ini, dif, end);	
	}
}

int main() {
	std::vector<int> v = {2,6,7,9};
	int n = v.size();
	mergeSort(v, 0, n-1);
	for(int i = 0; i < n; i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;
	return 0; 
}
