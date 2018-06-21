// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"

typedef struct {
	unsigned long int musicos;
	unsigned long int tiene;
}datos;

class ComparaDatos {
public:
	bool operator()(datos a, datos b) {
		unsigned long int datoA, datoB;
		datoA = a.musicos / a.tiene;
		if (a.musicos % a.tiene != 0)
			datoA++;

		datoB = b.musicos / b.tiene;
		if (b.musicos%b.tiene != 0)
			datoB++;

		return datoA > datoB;
	}
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es el numero de nodos del arbol ya que los recorre todos para averiguarlo.
void resolver(unsigned long int partituras, PriorityQueue<datos, ComparaDatos>& cola, unsigned long int instrumentos) {

	datos dato;
	unsigned long int disponibles = partituras - instrumentos;

	for (unsigned long int i = 0; i < disponibles; i++) {
		dato = cola.top();
		cola.pop();
		dato.tiene++;
		cola.push(dato);
	}

	dato = cola.top();

	unsigned long int datoA;
	datoA = dato.musicos / dato.tiene;
	if (dato.musicos % dato.tiene != 0)
		datoA++;

	std::cout << datoA << "\n";
}

void leer(PriorityQueue<datos, ComparaDatos>& cola, unsigned long int instrumentos) {
	unsigned long int dato;
	for (size_t i = 0; i < instrumentos; i++) {
		std::cin >> dato;

		datos d;
		d.musicos = dato;
		d.tiene = 1;

		cola.push(d);
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	unsigned long int partituras = 0;
	std::cin >> partituras;

	unsigned long int instrumentos= 0;
	std::cin >> instrumentos;

	if (!std::cin) // fin de la entrada
		return false;	PriorityQueue<datos, ComparaDatos> cola;
	leer(cola,instrumentos);
	resolver(partituras,cola,instrumentos);

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos08.txt");
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