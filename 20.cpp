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

class Jardin {
public:
	Jardin(std::vector<size_t>& manguera, size_t agujeros, size_t parche)
		: _resultado(0), _agujeros(agujeros), _parches(parche) {
		calcular(manguera);
	}

	std::string solucion() {
		return std::to_string(_resultado);
	}

private:
	size_t _resultado;
	size_t _agujeros;
	size_t _parches;

	void calcular(std::vector<size_t>& manguera) {
		size_t acumulada = 0;
		size_t tapados = 0;
		for (size_t i = 0; i < _agujeros; i++)
		{
			if (acumulada < manguera[i]) {
				acumulada = manguera[i] + _parches;
				++_resultado;
			}
		}
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t agujeros = 0;
	std::cin >> agujeros;

	size_t parche = 0;
	std::cin >> parche;

	if (!std::cin) // fin de la entrada
		return false;

	std::vector<size_t> manguera(agujeros, 0);
	size_t datos;
	for (size_t i = 0; i < agujeros; i++) {
		std::cin >> datos;
		manguera[i] = datos;
	}

	Jardin resolvedor(manguera, agujeros, parche);
	std::cout << resolvedor.solucion() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos20.txt");
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