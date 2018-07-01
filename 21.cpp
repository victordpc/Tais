// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <queue>
#include <vector>
#include "IndexPQ.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"
#include "GrafoDirigidoValorado.h"

class Comparador {
public:
	bool operator()(AristaDirigida<size_t> a, AristaDirigida<size_t>b) {
		return a.valor() < b.valor();
	}
};

class Telesilla {
public:
	Telesilla(std::vector<size_t>& esquiadores, size_t peso, size_t pasajeros)
		: _resultado(0), _peso(peso), _pasajeros(pasajeros) {
		calcular(esquiadores);
	}

	std::string solucion() {
		return std::to_string(_resultado);
	}

private:
	size_t _resultado;
	size_t _peso;
	size_t _pasajeros;

	void calcular(std::vector<size_t>& esquiadores) {
		size_t i = 0;
		size_t j = esquiadores.size() - 1;

		while (i <= j) {
			if (i != j && esquiadores[i] + esquiadores[j] < _peso)
				--j;
			++i;
			++_resultado;
		}
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t peso = 0;
	std::cin >> peso;

	size_t pasajeros = 0;
	std::cin >> pasajeros;

	if (!std::cin) // fin de la entrada
		return false;

	std::vector<size_t> esquiadores(pasajeros, 0);
	size_t datos;
	for (size_t i = 0; i < pasajeros; i++) {
		std::cin >> datos;
		esquiadores[i] = datos;
	}

	Telesilla resolvedor(esquiadores, peso, pasajeros);
	std::cout << resolvedor.solucion() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos21.txt");
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