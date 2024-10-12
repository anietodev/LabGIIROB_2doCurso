#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"
#define rterror throw std::runtime_error("El elemento ya/no existe");

template <typename T> 
class BSTree {
    private:
    	int nelem;
	BSNode<T> *root;
	BSNode<T>* insert(BSNode<T>* n, T e) {
		if(n != nullptr) {
			if((n->elem) == e) {
				throw std::runtime_error("El elemento ya existe");
			} else if((n->elem) > e) {
				n->left = insert(n->left, e);
			} else {
				n->right = insert(n->right, e);
			}
			return n;
		} else {
			nelem++;
			return new BSNode<T>(e);
		}
	}
	BSNode<T>* search(BSNode<T>* n, T e) const {
		if(n != nullptr) {
			if((n->elem) == e) {
				return n;
			} else if((n->elem) > e) {
				return search(n->left, e);
			} else {
				return search(n->right, e);
			}
		} else {
			throw std::runtime_error("Elemento no existente");
		}
	}
	void print_inorder(std::ostream &out, BSNode<T> *n) const {
		if(n != nullptr) {
			print_inorder(out, n->left);
			out << n->elem << " ";
			print_inorder(out, n->right);
		}
	}
	BSNode<T>* remove(BSNode<T>* n, T e) {
		if(n == nullptr) {	
			throw std::runtime_error("Elemento no existente");
		} else {
			if((n->elem) == e) {
				nelem--;
				if((n->left != nullptr) && (n->right != nullptr)) {
					n->elem = max(n->left);
					n->left = remove_max(n->left);
				} else {
					n = (n->left != nullptr)? (n->left) : (n->right);
				}
			} else if((n->elem) > e) {
				n->left = remove(n->left, e);
			} else {
				n->right = remove(n->right, e);
			}
		}
		return n;
	}
	T max(BSNode<T>* n) const {
		if(n == nullptr) {	
			throw std::runtime_error("Elemento no existente");
		} else if((n->right) == nullptr) {
			return n->elem;
		} else {
			return max(n->right);
		}
	}
	BSNode<T>* remove_max(BSNode<T>* n) {
		if((n->right) == nullptr) {
			n = n->left;
			return n;	
		} else {
			n->right = remove_max(n->right);
			return n;
		}

	}
	void delete_cascade(BSNode<T>* n) {
		if(n != nullptr) {
			delete_cascade(n->left);
			delete_cascade(n->right);
			delete n;
		} 
	}
    public:
    	BSTree() : nelem(0), root(nullptr){}
	int size() const {
		return nelem;
	}
	~BSTree() {
		delete_cascade(root);
	}
	T search(T e) const {
		return search(root, e)->elem;
	}
	T operator[](T e) const {
		return search(e);
	}
	void insert(T e) {
		root = insert(root, e);
	}
	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
		bst.print_inorder(out, bst.root);
		return out;
	}
	void remove(T e) {
		root = remove(root, e);
	}

};

#endif
