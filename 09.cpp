//Victor del Pino
//TAIS37

#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
#include "Grafo.h"

class Amigos
{
public:
	Amigos(Grafo const& g) :marcados(g.V(), false), maxi(0) {
		for (size_t v = 0; v < g.V(); v++)
		{
			if (!marcados[v]) {
				size_t tam = 0;
				dfs(g, v, tam);
				if (maxi < tam) {
					maxi = tam;
				}
			}
		}
	}
	size_t resultado()const {
		return maxi;
	}
private:
	vector<bool> marcados;

	size_t maxi;

	void dfs(Grafo const& g, size_t v, size_t & tam) { //O(V)
		marcados[v] = true;
		++tam;
		for(size_t w : g.adj(v))
		{
			if (!marcados[w]) {
				dfs(g, w, tam);
			}
		}
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t vertices = 0, aristas = 0;

	std::cin >> vertices;
	std::cin >> aristas;

	//if (std::cin.fail()) return false;

	Grafo gr(vertices);//O(v)

	int v = 0; int w = 0;
	for (int i = 0; i < aristas; i++) { //O(E)
		std::cin >> v;
		std::cin >> w;
		gr.ponArista(v-1, w-1);
	}

	Amigos sol = Amigos(gr);
	std::cout << sol.resultado() << std::endl;
	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos09.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	size_t casos = 0;
	cin >> casos;
	for (size_t i = 0; i < casos; i++)
	{
		resuelveCaso();
	}
	//while (resuelveCaso()) {}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}