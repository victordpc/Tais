// Grupo TAIS37, Victor del Pino Casilla
 
// Construye un árbol binario a partir de la entrada y después
// calcula su altura de forma recursiva
#include <algorithm>
#include <iostream>
#include "bintree_eda.h"

// lee un árbol binario de la entrada estándar
template <typename T>
bintree<T> leerArbol(T vacio) {
	T raiz;
	std::cin >> raiz;
	if (raiz == vacio) { // es un árbol vacío
		return{};
	}
	else { // leer recursivamente los hijos
		auto iz = leerArbol(vacio);
		auto dr = leerArbol(vacio);
		return{ iz, raiz, dr };
	}
}

// dado un árbol binario, calcula su altura
// lineal en el número N de nodos del árbol, O(N)
unsigned int altura(bintree<char> const& arbol) {
	if (arbol.empty())
		return 0;
	else
		return 1 + std::max(altura(arbol.left()), altura(arbol.right()));
}
// resuelve un caso de prueba
void resuelveCaso() {
	auto arbol = leerArbol('.');
	int sol = altura(arbol);
	std::cout << sol << "\n";
}
int main() {
	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();
	return 0;
}