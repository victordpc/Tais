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

//public class DijkstraSP
//{
//	private DirectedEdge[] edgeTo;
//	private double[] distTo;
//	private IndexMinPQ<Double> pq;
//	public DijkstraSP(EdgeWeightedDigraph G, int s)
//	{
//		edgeTo = new DirectedEdge[G.V()];
//		distTo = new double[G.V()];
//		pq = new IndexMinPQ<Double>(G.V());
//		for (int v = 0; v < G.V(); v++)
//			distTo[v] = Double.POSITIVE_INFINITY;
//		distTo[s] = 0.0;
//		pq.insert(s, 0.0);
//		while (!pq.isEmpty())
//		{
//			int v = pq.delMin();
//			for (DirectedEdge e : G.adj(v))
//				relax(e);
//		}
//	}
//
//	private void relax(DirectedEdge e)
//	{
//		int v = e.from(), w = e.to();
//		if (distTo[w] > distTo[v] + e.weight())
//		{
//			distTo[w] = distTo[v] + e.weight();
//			edgeTo[w] = e;
//			if (pq.contains(w)) pq.decreaseKey(w, distTo[w]);
//			else pq.insert(w, distTo[w]);
//		}
//	}
//}

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
			//if (pq.contains(w))pq.update(w, distTo[w]);
			//else pq.push(w, distTo[w]);
		}
	}
};

class RepartirCorreo {
public:
	RepartirCorreo(GrafoDirigidoValorado<size_t>& ciudad, size_t intersecciones, size_t calles)
		:_intersecciones(intersecciones), _calles(calles), _resultado(0), _solucion(true) {
		ponerCalles(ciudad, calles);
		std::cin >> _oficina;
		std::cin >> _paquetes;

		size_t dato = 0;
		_entregas = std::vector<size_t>(_paquetes);
		for (size_t i = 0; i < _paquetes; i++) {
			std::cin >> dato;
			_entregas[i] = dato;
		}

		calcular(ciudad);
	}

	void ponerCalles(GrafoDirigidoValorado<size_t>& ciudad, size_t calles) {
		size_t de = 0, hasta = 0, precio = 0;

		for (size_t i = 0; i < calles; i++) {
			std::cin >> de;
			std::cin >> hasta;
			std::cin >> precio;
			AristaDirigida<size_t> calle(--de, --hasta, precio);

			ciudad.ponArista(calle);
		}
	}

	std::string solucion() {
		if (_solucion)
			return std::to_string(_resultado);
		else
			return "Imposible";
	}
private:
	size_t _intersecciones;
	size_t _calles;
	size_t _resultado;
	size_t _oficina;
	size_t _paquetes;
	bool _solucion;
	std::vector<size_t> _entregas;

	//void calcular(GrafoDirigidoValorado<size_t> const& ciudad, size_t nodo, size_t parcial, std::vector<bool> marcados) {
	//	for(auto var : ciudad.adj(nodo))
	//	{
	//		size_t llegada = var.to();
	//		size_t tam = parcial + var.valor();
	//
	//		if (!marcados[llegada] && tam<=_resultado)
	//			if (llegada == _intersecciones - 1) {/* Hemos llegado al final */
	//				if (_resultado == 0 || tam < _resultado) {
	//					_resultado = tam;
	//					_veces = 1;
	//				}
	//				else if (tam == _resultado) {
	//					++_veces;
	//				}
	//			}
	//			else { /* Continuamos buscando */
	//				marcados[llegada] = true;
	//				calcular(ciudad, llegada, tam, marcados);
	//			}
	//	}
	//}

	void calcular(GrafoDirigidoValorado<size_t>& ciudad) {
		Dijkstra dj(ciudad, _oficina);
		size_t valor;
		size_t max = 0;
		--max;
		for (size_t e : _entregas) {
			valor = dj.distancia(e);
			if (valor == max)
				_solucion = false;
			else
				_resultado += valor;
		}
		// Si aplicamos Dijkstra sobre el grafo invertido convertimos las vueltas en idas, y nos vale con solo una llamada
		GrafoDirigidoValorado<size_t> ciudadInvertida = ciudad.reverse();
		dj = Dijkstra(ciudadInvertida, _oficina);
		for (size_t e : _entregas) {
			valor = dj.distancia(e);
			if (valor == max)
				_solucion = false;
			else
				_resultado += valor;
		}
	}

};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	unsigned long int intersecciones = 0;
	std::cin >> intersecciones;

	if (!std::cin) // fin de la entrada
		return false;

	unsigned long int calles = 0;
	std::cin >> calles;

	GrafoDirigidoValorado<size_t> ciudad(intersecciones);
	RepartirCorreo resolvedor(ciudad, intersecciones, calles);
	std::cout << resolvedor.solucion() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos17.txt");
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