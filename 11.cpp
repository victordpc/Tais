// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "GrafoDirigido.h"

class Arborescencias {
public:
	Arborescencias(GrafoDirigido const& G) : gr(G),grInverso(G.reverse()),_count(0), _marked(G.V(), false), _solucion(true), _raiz(0), _encontrada(false) {
		recorredor();
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
		std::string resultado;
		if (_solucion && _encontrada)
			resultado = "SI " + std::to_string(_raiz);
		else
			resultado = "NO";
		return resultado;
	}

private:
	std::vector<bool> _marked;		// para no repetir nodos
	std::vector<size_t> _edgeTo;		// edgeTo[v] = último vértice antes de llegar a v
	size_t _count;					// número de vértices conectados a s
	bool _solucion;					// indica si el grafo es bipartito
	size_t _raiz;					// nodo raiz
	bool _encontrada;				// hemos llegado a una raiz candidata
	GrafoDirigido grInverso;
	GrafoDirigido gr;

	void recorredor() {
		// Encontramos la raiz candidata, en el grafo inverso es la que tiene la matriz de adyacencia vacia
		for (size_t i = 0; !_encontrada && i < grInverso.V(); i++)
			if (grInverso.adj(i).size() == 0) {
				_raiz = i;
				_encontrada = true;
			}
		
		// Comprobamos que la raiz candidata llega a todos los vértices con un camino único
		dfs(_raiz);
		
		// si el numero de nodos visitados es igual al de vértices, hemos encontrado una raiz candidata
		// y no hemos encontrado ciclos hay solucion
		if (_encontrada && _solucion && _count == gr.V())
			_solucion = true;
		else
			_solucion = false;
	
	}

	// recorrido en profuncidad del grafo
	void dfs(size_t v) {
		++_count;
		_marked[v] = true;
		if (_solucion)
			for (size_t w : gr.adj(v)) {
				if (!_marked[w]) {
					dfs(w);
				}
				else {
					// hemos visitado este nodo mas de una vez luego hay ciclo y no es válido
					_solucion = false;
				}
			}
	}

	//// recorrido en profundidad desde v
	//void dfs(size_t v) {
	//	_marked[v] = true; // para no repetir vértices
	//	++_count;
	//
	//	if (.adj(v).size() == 0) //si no hay adjuntos es una raiz candidata
	//		if (!_encontrada) { //si no he encontrado una raiz antes la almaceno como posible raiz
	//			_encontrada = true;
	//			_raiz = v;
	//		}
	//		else //si ya he encontrado una raiz candidata antes
	//			if (_raiz != v) // y no es la misma que este nodo he encontrado dos raices y no hay solucion
	//				_solucion = false;
	//
	//	if (_solucion) {
	//		for (auto w : .adj(v)) { // recorremos todos los adyacentes a v
	//			if (!_marked[w]) {
	//				dfs( w);
	//			}
	//		}
	//	}
	//}
};

void leer(GrafoDirigido& gr,unsigned long int aristas) {
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

	GrafoDirigido gr(vertices);
	leer(gr, aristas);
	Arborescencias resolvedor(gr);
	std::cout << resolvedor.solucion() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos11.txt");
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