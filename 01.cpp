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

int altura(bintree<char> datos) {
	if (datos.empty())
		return 0;
	else
		return 1 + std::max(altura(datos.right()), altura(datos.left()));
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es el numero de nodos del arbol
bool resolver(bintree<char> datos) {
	if (datos.empty())
		return true;

	else {
		auto alturaLf = altura(datos.left());
		auto alturaRh = altura(datos.right());
		if (abs(alturaLf - alturaRh) <= 1 && resolver(datos.left()) && resolver(datos.right()))
			return true;
		else
			return false;
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	auto arbol = leerArbol('.');
	bool sol = resolver(arbol);
	if (sol)
		std::cout << "SI" << "\n";
	else
		std::cout << "NO" << "\n";
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos01.txt");
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