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
	bool operator()(AristaDirigida<size_t> a,AristaDirigida<size_t>b){
		return a.valor() < b.valor();
	}
};

class Dijkstra {
public:
	Dijkstra(GrafoDirigidoValorado<size_t>& G, size_t inicio)
		: distTo(G.V())
		, edgeTo(G.V())
		, pq(G.V()) {
		size_t a = 0;
		--a;
		for (size_t i = 0; i < G.V(); i++)
			distTo[i] = a;
		distTo[inicio - 1] = 0;
		pq.push(inicio - 1, 0);

		while (!pq.empty())
		{
			auto cola = pq.top(); pq.pop();
			for (auto e : G.adj(cola.elem))
				relax(e);
		}
	}

	size_t distancia(size_t destino) {
		return distTo[destino - 1];
	}

private:
	std::vector<AristaDirigida<size_t>> edgeTo;
	std::vector<size_t> distTo;
	IndexPQ<size_t, std::less<size_t>> pq;

	void relax(AristaDirigida<size_t> e) {
		size_t v = e.from();
		size_t w = e.to();
		if (distTo[w] > distTo[v] + e.valor()) {
			distTo[w] = distTo[v] + e.valor();
			edgeTo[w] = e;
			pq.update(w, distTo[w]);
		}
	}
};

class Libreria {
public:
	Libreria(PriorityQueue<size_t, std::greater<size_t>>& compras, size_t libros)
		: _resultado(0), _libros(libros) {
		calcular(compras);
	}

	std::string solucion() {
		return std::to_string(_resultado);
	}

private:
	size_t _resultado;
	size_t _libros;

	void calcular(PriorityQueue<size_t,std::greater<size_t>>& compras) {
		size_t indice=0;
		while (!compras.empty())
		{
			if (++indice % 3 == 0) {
				_resultado += compras.top();
			}
			compras.pop();
		}
	}

};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t libros = 0;
	std::cin >> libros;

	if (!std::cin) // fin de la entrada
		return false;

	PriorityQueue<size_t,std::greater<size_t>> compras;
	size_t datos;
	for (size_t i = 0; i < libros; i++) {
		std::cin >> datos;
		compras.push(datos);
	}

	Libreria resolvedor(compras,libros);
	std::cout << resolvedor.solucion() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos19.txt");
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