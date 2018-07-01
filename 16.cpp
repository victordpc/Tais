// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <queue>
#include <vector>
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"

class Comparador {
public:
	bool operator()(Arista<size_t> a,Arista<size_t>b){
		return a.valor() < b.valor();
	}
};

class Pavimentar {
public:
	Pavimentar(GrafoValorado<size_t>& ciudad, size_t intersecciones, size_t calles)
		:_intersecciones(intersecciones), _calles(calles), _veces(0)
	{
		_resultado = 0;
		--_resultado;
		ponerCalles(ciudad, calles);
		calcular(ciudad);
	}


	void ponerCalles(GrafoValorado<size_t>& ciudad, size_t calles) {
		size_t de = 0, hasta = 0, precio = 0;

		for (size_t i = 0; i < calles; i++) {
			std::cin >> de;
			std::cin >> hasta;
			std::cin >> precio;
			Arista<size_t> calle(--de, --hasta, precio);

			ciudad.ponArista(calle);
		}
	}

	std::string solucion() {
		return std::to_string(_veces);
	}
private:
	size_t _intersecciones;
	size_t _calles;
	size_t _resultado;
	size_t _veces;

	void calcular(GrafoValorado<size_t> const& ciudad, size_t nodo, size_t parcial, std::vector<bool> marcados) {
		for(auto var : ciudad.adj(nodo))
		{
			size_t llegada = var.otro(nodo);
			size_t tam = parcial + var.valor();

			if (!marcados[llegada] && tam<=_resultado)
				if (llegada == _intersecciones - 1) {/* Hemos llegado al final */
					if (_resultado == 0 || tam < _resultado) {
						_resultado = tam;
						_veces = 1;
					}
					else if (tam == _resultado) {
						++_veces;
					}
				}
				else { /* Continuamos buscando */
					marcados[llegada] = true;
					calcular(ciudad, llegada, tam, marcados);
				}
		}
	}

	void calcular(GrafoValorado<size_t> const& ciudad) {
		//inicio -> 0, fin -> intersecciones-1

		std::vector<bool> marcados(_intersecciones, false);
		marcados[0] = true;
		calcular(ciudad, 0,0,marcados);



		//while (!pq.empty() && q.size() < _intersecciones - 1) {
		//	Arista<size_t> e = pq.top();
		//	pq.pop();

		//	size_t uno = e.uno();
		//	size_t otro = e.otro(e.uno());

		//	if (!cd.unidos(uno, otro)) {
		//		cd.unir(uno, otro);
		//		q.push(e);
		//		_resultado += e.valor();
		//	}
		//}
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	unsigned long int intersecciones= 0;
	std::cin >> intersecciones;

	if (!std::cin) // fin de la entrada
		return false;
	
	unsigned long int calles = 0;
	std::cin >> calles;

	GrafoValorado<size_t> ciudad(intersecciones);
	//leer(ciudad,calles);
	Pavimentar resolvedor(ciudad, intersecciones, calles);
	std::cout << resolvedor.solucion() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos16.txt");
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