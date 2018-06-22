// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"
#include "Grafo.h"

typedef struct {
	unsigned long int musicos;
	unsigned long int tiene;
}datos;

class ComparaDatos {
public:
	bool operator()(datos a, datos b) {
		unsigned long int datoA, datoB;
		datoA = a.musicos / a.tiene;
		if (a.musicos % a.tiene != 0)
			datoA++;

		datoB = b.musicos / b.tiene;
		if (b.musicos%b.tiene != 0)
			datoB++;

		return datoA > datoB;
	}
};

class encuentraAmigos {
public:
	encuentraAmigos(Grafo const& G) : _count(0), _marked(G.V(), false),_solucion(0) {
		dfs(G,0);
	}

	// ¿hay camino del origen a v?
	bool marked(size_t v) const {
		return _marked[v];
	}

	// número de vértices conectados a s (en la misma componente conexa que s)
	size_t count() const {
		return _count;
	}

	size_t solucion() const {
		return _solucion;
	}

private:
	std::vector<bool> _marked;  // marked[v] = ¿hay camino de s a v?
	size_t _count;              // número de vértices conectados a s
	size_t _solucion;			// numero de nodos en el mayor grupo de nodos conectados

								// recorrido en profundidad desde v
	void dfs(Grafo const& G, size_t v) {
		++_count;
		size_t amigos;

		for (size_t i = 0; i < G.V(); i++){ //recorremos todos los nodos del grafo
			amigos = 0;
			if (!_marked[i]) {
				dfs(G, i, amigos);
			}
			if (_solucion < amigos)
				_solucion = amigos;
		}
	}

	// recorrido en profundidad desde v
	void dfs(Grafo const& G, size_t v,size_t & amigos) {
		++amigos;
		_marked[v] = true; // para no repetir vértices
		for (auto w : G.adj(v)) { // recorremos todos los adyacentes a v
			if (!_marked[w]) {
				dfs(G, w,amigos);
			}
		}
	}
};

//// función que resuelve el problema
//// comentario sobre el coste, O(f(N)), donde N es el numero de nodos del arbol ya que los recorre todos para averiguarlo.
//void resolver(Grafo amiguitos,unsigned long int personas) {
//}

void leer(Grafo& amiguitos,unsigned long int amigos) {
	unsigned long int dato1,dato2;
	for (size_t i = 0; i < amigos; i++) {
		std::cin >> dato1;
		std::cin >> dato2;

		amiguitos.ponArista(dato1-1, dato2-1);
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	unsigned long int personas = 0;
	std::cin >> personas;

	unsigned long int amigos= 0;
	std::cin >> amigos;

	Grafo amiguitos(personas);
	leer(amiguitos, amigos);
	encuentraAmigos resolvedor(amiguitos);
	std::cout << resolvedor.solucion() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos09.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	//while (resuelveCaso()) {}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}