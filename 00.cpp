// Grupo TAIS37, Victor del Pino Casilla
 
// Construye un �rbol binario a partir de la entrada y despu�s
// calcula su altura de forma recursiva
#include <algorithm>
#include <iostream>
#include "bintree_eda.h"

// lee un �rbol binario de la entrada est�ndar
template <typename T>
bintree<T> leerArbol(T vacio) {
	T raiz;
	std::cin >> raiz;
	if (raiz == vacio) { // es un �rbol vac�o
		return{};
	}
	else { // leer recursivamente los hijos
		auto iz = leerArbol(vacio);
		auto dr = leerArbol(vacio);
		return{ iz, raiz, dr };
	}
}

// dado un �rbol binario, calcula su altura
// lineal en el n�mero N de nodos del �rbol, O(N)
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