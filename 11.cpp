//Victor del Pino
//TAIS37

#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
#include "GrafoDirigido.h"

class Arborescente
{
public:
	Arborescente(GrafoDirigido const& g) :marcados(g.V(), false), res(false), contador(0), gPrima(g.reverse()) {

		//Primero intentamos llegar a la raiz del arbol
		//La raiz deberia ser el nodo que no tiene relaciones entrantes y si salientes
		// si invertimos el arbol es el hijo mas profundo
		nodo = masProfundo(0);

 		if (nodo >= 0) {
			//Una vez que llegamos a la raiz, recorremos todo el arbol
			//Si llevamos un contador de nodos visitados y:
			//	el numero es menor que el numero de vertices -> No hemos visitado todo el arbol
			//	el numero es mayor que el numero de vertices -> Hay al menos un camino multiple para llegar a una hoja
			//	el numero es igual que el numero de vertices -> Hemos visitado todo el arbol y cada nodo solo una vez
			contador = 0;

			todosHijos(g, nodo);

			contador = 0;
			res = true;
			dfs(g, nodo);

			if (res&&contador == g.V())
				res = true;
			else
				res = false;
		}
	}

	void resultado()const {
		if (res)
			std::cout << "SI " << nodo << std::endl;
		else
			std::cout << "NO" << std::endl;
	}
private:
	vector<bool> marcados;
	bool res;
	size_t contador;
	int nodo;
	GrafoDirigido gPrima;


	void dfs(GrafoDirigido const& g, size_t v) { //O(V)
		//visito el nodo
		marcados[v] = true;
		++contador;
		//recorro los adyacentes
		for (size_t w : g.adj(v))
		{
			if (!marcados[w]) {
				dfs(g, w);
			}
			else {
				res = false;
			}
		}
	}

	int masProfundo(int actual) {

		if (gPrima.adj(actual).size() == 0) return actual;

		if (contador > gPrima.V()) return -1;

		for (size_t w : gPrima.adj(actual))
		{
			++contador;
			return masProfundo(w);
		}
	}

	void todosHijos(GrafoDirigido const& g, int actual) {
		++contador;
		if (contador > g.V()) return;
		for (size_t w : g.adj(actual)) todosHijos(g, w);
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t vertices = 0, aristas = 0;

	std::cin >> vertices;
	std::cin >> aristas;

	if (std::cin.fail()) return false;

	GrafoDirigido gr(vertices);//O(v)

	int v = 0; int w = 0;
	for (int i = 0; i < aristas; i++) { //O(E)
		std::cin >> v;
		std::cin >> w;
		gr.ponArista(v, w);
	}

	Arborescente sol = Arborescente(gr);
	sol.resultado();
	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos11.txt");
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