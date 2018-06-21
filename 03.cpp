// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include "BusquedaTreeMap_AVL.h"
//#include "bintree_eda.h"

template<typename T>
map<T, T> leer(T numeroNodos) {
	map<T, T> arbol = map<T, T>();
	T valor;
	for (size_t i = 0; i < numeroNodos; i++) {
		std::cin >> valor;
		arbol.insert({ valor,valor });
	}
	return arbol;
}

template<typename T>
void recorrido(map<T, T> datos, T ini, T fin) {
	bool continua = true;

	
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es el numero de nodos del arbol ya que los recorre todos para averiguarlo.
template<typename T>
void resolver(map<T, T> datos) {
	T ini = 0;
	T fin = 0;
	auto resultado= datos.recorrido(ini, fin);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	unsigned int nodos = 0;
	std::cin >> nodos;

	if (nodos == 0)
		return false;

	auto arbol = leer(nodos);
	resolver(arbol);
	//auto sol = resolver(arbol);

	//std::cout << sol.resultado() << "\n";
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos02.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	//int numCasos;
	//std::cin >> numCasos;
	//for (int i = 0; i < numCasos; ++i)
	//	resuelveCaso();

	while (resuelveCaso())
		return 0;

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}