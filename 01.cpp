// Grupo TAIS37, Victor del Pino Casilla
 
// Construye un árbol binario a partir de la entrada y después
// calcula su altura de forma recursiva
#include <algorithm>
#include <iostream>
#include <fstream>
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

// dado un árbol binario, calcula las alturas de los hijos y los compara
// lineal en el número N de nodos del árbol, O(N)
bool equilibrado(bintree<char>arbol, unsigned int &altura){
	if (arbol.empty()){ altura = 0; return true; }
	else{
		unsigned int iz = 0, dr = 0;
		if (equilibrado(arbol.left(), iz) && equilibrado(arbol.right(), dr)){
			altura = 1 + std::max(iz, dr); int diferencia = iz - dr;
			if (std::abs(diferencia) <= 1)
				return true;
		}
		return false;
	}
}

// resuelve un caso de prueba
void resuelveCaso() {
	auto arbol = leerArbol('.');
	unsigned int altura;
	bool sol = equilibrado(arbol,altura);
	if (sol) std::cout << "SI" << std::endl; 
	else std::cout << "NO" << std::endl;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;

}