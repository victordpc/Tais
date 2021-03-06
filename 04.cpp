// Grupo 37, V�ctor del Pino

// Comentario general sobre la soluci�n,
// explicando c�mo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include "NewTreeMap_AVL.h"
//#include "bintree_eda.h"

template<typename T>
newMap<T, T> leer(T numeroNodos) {
	newMap<T, T> arbol = newMap<T, T>();
	T valor;
	for (size_t i = 0; i < numeroNodos; i++) {
		std::cin >> valor;
		arbol.insert({ valor,0 });
	}
	return arbol;
}

template<typename T>
void recorrido(newMap<T, T> datos, T ini, T fin) {
	bool continua = true;

	while (continua) {

	}
	
}

// funci�n que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es el numero de nodos del arbol ya que los recorre todos para averiguarlo.
template<typename T>
void resolver(newMap<T, T> datos) {
	T ini = 0;
	T fin = 0;
	 recorrido(datos, ini, fin);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuraci�n, y escribiendo la respuesta
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