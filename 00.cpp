// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include "bintree_eda.h"

template<typename T>
bintree<T> leerArbol(T arbolVacio) {
	T raiz;
	std::cin >> raiz;
	if (raiz == arbolVacio) {
		return{};
	}
	else {
		bintree<T>iz = leerArbol(arbolVacio);
		bintree<T>dr = leerArbol(arbolVacio);
		return { iz,raiz,dr };
	}
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es el numero de nodos del arbol
int resolver(bintree<char> datos) {
	if (datos.empty())
		return 0;
	else
		return 1 + std::max(resolver(datos.right()), resolver(datos.left()));
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	auto arbol = leerArbol('.');
	int sol = resolver(arbol);
	std::cout << sol << "\n";
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos00.txt");
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