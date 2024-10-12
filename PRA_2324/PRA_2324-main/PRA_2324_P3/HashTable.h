#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"  

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
	int max;
	ListLinked<TableEntry<V>>* table;
	int h(std::string key) {
		int suma = 0;
		for(int i = 0; i < key.size(); i++) {
			suma += key[i];
		}
		return suma % max;
	}
    public:
	HashTable(int size) {
		table = new ListLinked<TableEntry<V>>[size];
		max = size;
		n = 0;
		/*for(int i=0;i<size;i++) {
			table[i] = nullptr;
		}*/
	}
	~HashTable() {
		delete[] table;
	}
	int capacity() {
		return max;
	}
	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
		out<<"HashTable [entries: "<<th.n<<", capacity: "<<th.max<<"]\n";
	        out << "==============\n\n";	
		int j = 0;
		for(int i = 0; i < th.max; i++) {
			/*while(th.table[j].first == nullptr) {
				j++;
			}*/
			out << "== Cubeta " << i << " ==\n\n" << th.table[i];
		}
		out << "==============";
		return out;
	}
	V operator[](std::string key) {
		return search(key);
	}
 	void insert(std::string key, V value) override; 
        V search(std::string key) override;
        V remove(std::string key) override;
        int entries() override;
 
};
template <typename V>
void HashTable<V>::insert(std::string key, V value) {
        int post = h(key);
	int posl = table[post].search(TableEntry<V>(key));
	if(posl != -1)
        	throw std::runtime_error("La clave ya existe en el diccionario\n");
	else {
		n++;
		table[post].append(TableEntry(key, value));	
	}
}
template <typename V>
V HashTable<V>::search(std::string key) {
	int post = h(key);
	int posl = table[post].search(TableEntry<V>(key));
	if(posl == -1)
        	throw std::runtime_error("La clave no existe en el diccionario\n");
	else
		return table[post].get(posl).value;
}
template <typename V>
V HashTable<V>::remove(std::string key) {
	int post = h(key);
	int posl = table[post].search(TableEntry<V>(key));
	if(posl == -1)
        	throw std::runtime_error("La clave no existe en el diccionario\n");
	else {
		n--;
		return table[post].remove(posl).value;
	}
}
template <typename V>
int HashTable<V>::entries() {
	return n;
}

#endif


