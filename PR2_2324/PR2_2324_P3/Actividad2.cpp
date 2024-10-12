#include "bits/stdc++.h" 

void print_ht(std::unordered_map<std::string, int>& ht) {
	std::cout << "======= TABLA HASH =======\n";
	std::cout << "Num. buckets: " << bucket_count() << std::endl;
	std::cout << "Num. elementos: " << size() << std::endl;
	std::cout << "Max. load factor: " << max_load_factor() << std::endl;
	std::cout << "Current load factor: " << load_factor() << std::endl;
	for(long i = 0; i < (bucket_count() - 1); i++) {
		std::cout << "BUCKET " << i << ": " <<  << std::endl;
	}
}

int main() {
	std::unordered_map<std::string, int> ht;
	
	return 0;
}
