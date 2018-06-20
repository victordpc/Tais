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

bool esAvl(bintree<int> datos, int& min, int& max, int&altura) {
	if (datos.empty())
		return true;

	else {

		auto arbolLf = datos.left();
		auto arbolRh = datos.right();

		int yo = datos.root();

		int minLf, maxLf, alturaLf;
		int minRh, maxRh, alturaRh;
		bool resultadoLf = true, resultadoRh = true;
		bool entraLf = true, entraRh = true;

		if (arbolLf.empty()) {
			maxLf = minLf = yo;
			alturaLf = 0;
			entraLf = false;
		}
		else {
			resultadoLf = esAvl(arbolLf, minLf, maxLf, alturaLf);
		}

		if (arbolRh.empty()) {
			maxRh = minRh = yo;
			alturaRh = 0;
			entraRh = false;
		}
		else {
			resultadoRh = esAvl(arbolRh, minRh, maxRh, alturaRh);
		}

		if (entraLf && entraRh && resultadoLf && resultadoRh && abs(alturaLf - alturaRh) <= 1 && (minRh > yo) && (maxLf < yo)) {//&& resolver(datos.left()) && resolver(datos.right()))
			max = maxRh;
			min = minLf;
			altura = 1 + std::max(alturaLf, alturaRh);
			return true;
		}
		else if (entraLf && !entraRh && resultadoLf && resultadoRh && abs(alturaLf - alturaRh) <= 1 && (maxLf < yo)) {//&& resolver(datos.left()) && resolver(datos.right()))
			max = maxRh;
			min = minLf;
			altura = 1 + alturaLf;
			return true;
		}
		else if (!entraLf && entraRh && resultadoLf && resultadoRh && abs(alturaLf - alturaRh) <= 1 && (minRh > yo)) {//&& resolver(datos.left()) && resolver(datos.right()))
			max = maxRh;
			min = minLf;
			altura = 1 +  alturaRh;
			return true;
		}
		else if (!entraLf && !entraRh) {//&& resolver(datos.left()) && resolver(datos.right()))
			max = maxRh;
			min = minLf;
			altura = 1;
			return true;
		}
		else
			return false;
	}
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es el numero de nodos del arbol ya que los recorre todos para averiguarlo.
bool resolver(bintree<int> datos) {
	int min = 0;
	int max = 0;
	int altura = 0;
	return esAvl(datos, min, max, altura);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	auto arbol = leerArbol(-1);
	bool sol = resolver(arbol);
	if (sol)
		std::cout << "SI" << "\n";
	else
		std::cout << "NO" << "\n";
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos02.txt");
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