// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <queue>
#include <vector>
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"

//class GreenPeace {
//public:
//	GreenPeace(Oceano& _mar, int filas, int columnas) : _vertido(filas*columnas),
//		_filas(filas), _columnas(columnas), _solucion(""), _manchurron(0) {
//		int nuevasManchas = 0;
//		int filMancha = 0;
//		int colMancha = 0;
//		std::cin >> nuevasManchas;
//
//		// Calculamos la primera mancha mas grande
//		encuentraManchurron(_mar);
//		_solucion += std::to_string(_manchurron);
//
//		for (size_t i = 0; i < nuevasManchas; i++)
//		{
//			// Leemos la nueva mancha
//			std::cin >> filMancha;
//			std::cin >> colMancha;
//
//			_mar[--filMancha][--colMancha] = '#';
//
//			// Recalculamos la mancha mas grande
//			reEncuentraManchurron(_mar, filMancha, colMancha);
//			_solucion += " ";
//			_solucion += std::to_string(_manchurron);
//
//			filMancha = 0;
//			colMancha = 0;
//		}
//	}
//
//	std::string solucion() {
//		return _solucion;
//	}
//private:
//	std::vector<std::vector<bool>> _marcado;	// Para no repetir nodos
//	std::string _solucion;						// Resultado de la operación
//	size_t _manchurron;							// Mancha mas grande
//	size_t _manchita;							// Mancha del mapa
//	int _filas;									// Filas
//	int _columnas;								// Columnas
//	Punto _dir[8] = { Punto(1,1), Punto(-1,-1), Punto(-1,1), Punto(1,-1), Punto(0,1), Punto(0,-1), Punto(1,0), Punto(-1,0) };
//	ConjuntosDisjuntos _vertido;				// Conjunto de las manchas
//
//	void encuentraManchurron(Oceano& _mar) {
//		_marcado = std::vector<std::vector<bool>>(_filas, std::vector<bool>(_columnas, false));
//
//		for (size_t i = 0; i < _filas; i++) {
//			for (size_t j = 0; j < _columnas; j++) {
//				if (!_marcado[i][j]) {
//					if (_mar[i][j] == '#') {
//						agrupaCoordenadas(i, j, '#');
//					}
//					else if (_mar[i][j] == ' ') {
//						agrupaCoordenadas(i, j, ' ');
//					}
//				}
//			}
//		}
//	}
//						//_manchita = 0;
//						//Punto cuadrante(i, j);
//						//dfs(_mar, cuadrante);
//						//if (_manchita > _manchurron) {
//						//	_manchurron = _manchita;
//						//}
//
//	void reEncuentraManchurron(Oceano& _mar,int fila, int columna) {
//		_marcado = std::vector<std::vector<bool>>(_filas, std::vector<bool>(_columnas, false));
//		_manchita = 0;
//		Punto cuadrante(fila, columna);
//		dfs(_mar,cuadrante);
//		if (_manchita > _manchurron) {
//			_manchurron = _manchita;
//		}
//	}
//
//	void dfs(Oceano& _mar,Punto v) {
//		++_manchita;
//		_marcado[v.first][v.second] = true; // para no repetir vértices
//
//		//for (auto w : G.adj(v)) { // recorremos todos los adyacentes a v
//		for (size_t i = 0; i < 8; i++) {
//			Punto w(v.first + _dir[i].first, v.second + _dir[i].second);
//			if (w.first >= 0 && w.first < _filas && w.second >= 0 && w.second < _columnas
//				&& !_marcado[w.first][w.second] && _mar[w.first][w.second] == '#') {
//				dfs(_mar,w);
//			}
//		}
//	}
//};

class Comparador {
public:
	bool operator()(Arista<size_t> a,Arista<size_t>b){
		return a.valor() < b.valor();
	}
};

class Pavimentar {
public:
	Pavimentar(GrafoValorado<size_t>& ciudad, size_t intersecciones, size_t calles)
		:_intersecciones(intersecciones), _calles(calles), cd(intersecciones),
		pq(calles), _resultado(0)
	{
		ponerCalles(ciudad, calles);
		calcular(ciudad);
	}

	void ponerCalles(GrafoValorado<size_t>& ciudad, size_t calles) {
		size_t de = 0, hasta = 0, precio = 0;

		for (size_t i = 0; i < calles; i++) {
			std::cin >> de;
			std::cin >> hasta;
			std::cin >> precio;
			Arista<size_t> calle(--de, --hasta, precio);

			ciudad.ponArista(calle);
			pq.push(calle);
		}
	}

	std::string solucion() {
		if (cd.count() > 1 || _intersecciones == 1)
			return "Imposible";
		return std::to_string(_resultado);
	}
private:
	size_t _intersecciones;
	size_t _calles;
	size_t _resultado;
	PriorityQueue<Arista<size_t>,Comparador> pq;
	std::queue<Arista<size_t>> q;
	ConjuntosDisjuntos cd;

	void calcular(GrafoValorado<size_t> const& ciudad) {
		
		while (!pq.empty() && q.size() < _intersecciones - 1) {
			Arista<size_t> e = pq.top();
			pq.pop();

			size_t uno = e.uno();
			size_t otro = e.otro(e.uno());

			if (!cd.unidos(uno, otro)) {
				cd.unir(uno, otro);
				q.push(e);
				_resultado += e.valor();
			}
		}
	}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	unsigned long int intersecciones= 0;
	std::cin >> intersecciones;

	if (!std::cin) // fin de la entrada
		return false;
	
	unsigned long int calles = 0;
	std::cin >> calles;

	GrafoValorado<size_t> ciudad(intersecciones);
	//leer(ciudad,calles);
	Pavimentar resolvedor(ciudad, intersecciones, calles);
	std::cout << resolvedor.solucion() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos15.txt");
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