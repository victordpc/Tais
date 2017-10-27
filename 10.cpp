//Victor del Pino
//TAIS37

#include <algorithm>
#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;

class Bipartito
{
public:
	Bipartito(Grafo const& g) :marcados(g.V(), false), colores(g.V(), false), esBp(true) {
		for (size_t i = 0; i < g.V() && esBp; i++)
		{
			dfs(g, i);
		}
	};

	bool esBipartito() {
		return esBp;
	};

private:
	vector<bool> marcados;
	vector<bool> colores;
	bool esBp;

	void dfs(Grafo const& g, size_t v) { //O(V)
		marcados[v] = true;
		//for each (size_t w in g.adj(v))
		for (size_t w : g.adj(v))
		{
			if (!marcados[w]) {
				colores[w] = !colores[v];
				dfs(g, w);
			}
			else {
				if (colores[w] != !colores[v]) {
					esBp = false;
					return;
				}
			}
		}
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t vertices = 0, aristas = 0;

	if (std::cin.fail()) return false;

	std::cin >> vertices;
	std::cin >> aristas;

	if (std::cin.fail()) return false;

	Grafo gr = Grafo(vertices);

	for (size_t i = 0; i < aristas; i++) {
		size_t v = 0; size_t w = 0;
		std::cin >> v;
		std::cin >> w;
		gr.ponArista(v,w);
	}

	Bipartito bp = Bipartito(gr);

	if (bp.esBipartito())
		std::cout << "SI";
	else
		std::cout << "NO";

	std::cout << std::endl;

	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso()) {}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}