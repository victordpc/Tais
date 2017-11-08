//Victor del Pino
//TAIS37

#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "GrafoValorado.h"
#include "PriorityQueue.h"

//class CuentaOvejas
//{
//public:
//	CuentaOvejas(Mapa const& ma, int filas, int columnas) : marcados(filas, std::vector<bool>(columnas, false)), ovejasBlancas(-1),
//		filas(filas), columnas(columnas) {
//
//		//Recorremos usandos dfs para recorrer el mapa
//		//Cada llamada efectiva desde aqui descubre una componente conexa del grafo
//		//El número de ovejas blancas es el numero de componentes conexas del grafo menos uno (el borde)
//		// Coste O(n) n=número de nodos
//		for (int i = 0; i < filas; i++) {
//			for (int j = 0; j < columnas; j++) {
//				if (!marcados[i][j] && ma[i][j] != 'X') {
//					++ovejasBlancas;
//					Punto inicio = Punto(i, j);
//					dfs(ma, inicio);
//				}
//			}
//		}
//
//	};
//
//	int numeroOvejasBlancas() {
//		return ovejasBlancas;
//	}
//
//private:
//
//	std::vector<std::vector<bool>> marcados;
//	size_t ovejasBlancas;
//	Punto dir[4] = { Punto(1,0), Punto(0,1), Punto(0,-1),Punto(-1,0) };	//vector de direcciones
//	int filas;
//	int columnas;
//
//	//función dfs
//	void dfs(Mapa const& G, Punto v) {
//		marcados[v.first][v.second] = true;
//		for (int i = 0; i < 4; i++) {
//			Punto w = Punto(v.first + dir[i].first, v.second + dir[i].second);
//			if (w.first >= 0 && w.second >= 0 && w.first < filas && w.second < columnas
//				&& !marcados[w.first][w.second]
//				&& G[w.first][w.second] != 'X') {
//				dfs(G, w);
//			}
//		}
//	}
//};


class Pavimenta
{
public:
	Pavimenta(GrafoValorado<size_t> const&gv, size_t vertices, size_t aristas) :coste(0),todos(false){
	
		//Obtenemos el arbol mínimo de espansión
		std::vector<bool> marcados= std::vector<bool>(vertices, false);
		size_t contadorMarcados=0;
		PriorityQueue<size_t, std::less<size_t>> pq; 

		for (size_t i = 0; i < vertices; i++){
			AdysVal<size_t> adjuntos = gv.adj(i);
			for (size_t j = 0; j < adjuntos.size(); j++) {
				
			}
		}

		//comprobamos si todo pertenece a la misma componente conexa.


	};
	bool puede() {
		return todos;
	}
	size_t metros() {
		return coste;
	}
private:
	size_t coste;
	bool todos;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t intersecciones= 0, calles= 0;


	std::cin >> intersecciones;
	std::cin >> calles;

	if (std::cin.fail()) return false;

	GrafoValorado <size_t> gv = GrafoValorado<size_t>(intersecciones);

	////Quitamos el salto de línea 
	//std::cin.get();

	size_t lado1 = 0, lado2 = 0, valor = 0;
	for (size_t i = 0; i < calles; i++) {
		std::cin >> lado1 >> lado2 >> valor;
		Arista<size_t> a = Arista<size_t>(lado1, lado2, valor);
	}

	Pavimenta pv = Pavimenta(gv, intersecciones, calles);

	if (pv.puede())
		std::cout << pv.metros();
	else
		std::cout << "Imposible";
	std::cout << std::endl;

	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	//size_t casos = 0;
	//std::cin >> casos;

	while (resuelveCaso()) {}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}