// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "PriorityQueue.h"
#include "Grafo.h"

class bipartidor {
public:
	bipartidor(Grafo const& G) : _count(0), _marked(G.V(), false), _markedBlue(G.V(), false), _markedRed(G.V(), false), _solucion(true) {
		for (size_t i = 0; i < G.V(); i++)
		{
			if (!_marked[i])
				dfs(G, i, false);
		}
	}

	// ¿hay camino del origen a v?
	bool marked(size_t v) const {
		return _marked[v];
	}

	// número de vértices conectados a s (en la misma componente conexa que s)
	size_t count() const {
		return _count;
	}

	std::string solucion() const {
		return _solucion?"SI":"NO";
	}

private:
	std::vector<bool> _markedRed;	// marked[v] = ¿hay camino de s a v?
	std::vector<bool> _markedBlue;  // marked[v] = ¿hay camino de s a v?
	std::vector<bool> _marked;		// para no repetir nodos
	size_t _count;					// número de vértices conectados a s
	bool _solucion;					// indica si el grafo es bipartito

	// recorrido en profundidad desde v
	void dfs(Grafo const& G, size_t v, bool _alternancia) {
		_marked[v] = true; // para no repetir vértices
		++_count;
		if (_alternancia)
			_markedBlue[v] = true;
		else
			_markedRed[v] = true;
		_alternancia = !_alternancia;

		if(_solucion)
		for (auto w : G.adj(v)) // recorremos todos los adyacentes a v
			if (!_marked[w])
				dfs(G, w, _alternancia);
			else
				if (_alternancia && _markedRed[w] || !_alternancia && _markedBlue[w]) {
					_solucion = false;
					return;
				}
	}
};

//// función que resuelve el problema
//// comentario sobre el coste, O(f(N)), donde N es el numero de nodos del arbol ya que los recorre todos para averiguarlo.
//void resolver(Grafo amiguitos,unsigned long int personas) {
//}

void leer(Grafo& gr,unsigned long int aristas) {
	unsigned long int dato1,dato2;
	for (size_t i = 0; i < aristas; i++) {
		std::cin >> dato1;
		std::cin >> dato2;

		gr.ponArista(dato1, dato2);
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	unsigned long int vertices = 0;
	std::cin >> vertices;

	if (!std::cin) // fin de la entrada
		return false;

	unsigned long int aristas= 0;
	std::cin >> aristas;

	Grafo gr(vertices);
	leer(gr, aristas);
	bipartidor resolvedor(gr);
	std::cout << resolvedor.solucion() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos10.txt");
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