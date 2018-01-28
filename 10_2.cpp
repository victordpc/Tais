//Victor del Pino
//TAIS37

#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
#include "Grafo.h"

class Bipartito
{
public:
	Bipartito(Grafo const& g) :marcados(g.V(), false), res(true), colores(g.V(), false) {
		bool color = true;
		for (size_t v = 0; v < g.V() && res; v++)
		{

			//if (!marcados[v]) {
			//	colores[v] = principio;
			//	marcados[v] = true;
			//	principio= !principio
			//}
			//else {
			//	if
			//}

			if (!marcados[v]) {
				dfs(g, v, color);
			}
			else if (!marcados[v]) {
				res = false;
			}
		}
	}

	void resultado()const {
		if (res)
			std::cout << "SI" << std::endl;
		else
			std::cout << "NO" << std::endl;
	}
private:
	vector<bool> marcados;
	vector<bool> colores;
	bool res;

	void dfs(Grafo const& g, size_t v, bool color) { //O(V)
		//visito el nodo
		marcados[v] = true;

		//asigno el color
		colores[v] = color;
		color = !color;

		//recorro los adyacentes
		for (size_t w : g.adj(v))
		{
			if (!marcados[w]) {
				dfs(g, w, color);
			}
			else if (colores[w] != color) {
				res = false;
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

	if (std::cin.fail()) return false;

	Grafo gr(vertices);//O(v)

	int v = 0; int w = 0;
	for (int i = 0; i < aristas; i++) { //O(E)
		std::cin >> v;
		std::cin >> w;
		gr.ponArista(v, w);
	}

	Bipartito sol = Bipartito(gr);
	sol.resultado();
	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos10.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	//size_t casos = 0;
	//cin >> casos;
	//for (size_t i = 0; i < casos; i++)
	//{
	//	resuelveCaso();
	//}
	while (resuelveCaso()) {}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}