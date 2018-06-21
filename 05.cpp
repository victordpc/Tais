// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es el numero de nodos del arbol ya que los recorre todos para averiguarlo.
template<typename T>
T resolver(PriorityQueue<T> datos) {
	T resultado = 0;
	T dato1 = 0;
	T dato2 = 0;
	T dato3 = 0;
	while (datos.size() > 1) {
		dato1 = datos.top();
		datos.pop();
		dato2 = datos.top();
		datos.pop();
		dato3 = dato1 + dato2;
		resultado += dato3;
		datos.push(dato3);
	}

	return resultado;
}

template<typename T>
PriorityQueue<T> leer(T elementos) {
	PriorityQueue<T> resultado = PriorityQueue<T>();
	T dato;
	for (size_t i = 0; i < elementos; i++) {
		std::cin >> dato;
		resultado.push(dato);
	}
	return resultado;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	unsigned long int equipos = 0;
	std::cin >> equipos;

	if (equipos == 0)
		return false;

	auto cola = leer(equipos);
	unsigned long int resultado=resolver(cola);
	//auto sol = resolver(arbol);

	std::cout << resultado << "\n";
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos05.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	//int numCasos;
	//std::cin >> numCasos;
	//for (int i = 0; i < numCasos; ++i)
	//	resuelveCaso();

	while (resuelveCaso()) {}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}