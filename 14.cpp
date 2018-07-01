// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <queue>
#include <vector>
#include "ConjuntosDisjuntos.h"

using Oceano = std::vector<std::vector<char>>;
using Punto = std::pair<int, int>;

//class CuentaOvejas {
//public:
//	CuentaOvejas(Pradera campo, int filas, int columnas) : _jardin(campo), _solucion(0), _filas(filas), _columnas(columnas),
//		_marcado(filas, std::vector<bool>(columnas, false)) {
//		for (size_t i = 0; i < _filas; i++)
//		{
//			for (size_t j = 0; j < _columnas; j++)
//			{
//				if (!_marcado[i][j] && _jardin[i][j] != 'X') {
//					++_solucion;
//					Punto _inicio(i, j);
//					dfs(_inicio);
//				}
//			}
//		}
//		--_solucion;
//	}
//
//	size_t solucion() const {
//		return _solucion;
//	}
//
//private:
//	std::vector<std::vector<bool>> _marcado;	// marcado de posicion visitada
//	Pradera _jardin;
//	size_t _filas;
//	size_t _columnas;
//	size_t _solucion;	// indica el número de ovejas blancas
//	Punto _dir[4] = { Punto(1,0), Punto(0,1), Punto(0,-1), Punto(-1,0) };	//vector de direcciones
//
//	// recorrido en profundidad desde v
//	void dfs(Punto v) {
//		_marcado[v.first][v.second] = true; // para no repetir vértices
//		for (size_t i = 0; i < 4; i++) {// recorremos todos los adyacentes a v
//			Punto w(v.first + _dir[i].first, v.second + _dir[i].second);
//			if (w.first >= 0 && w.first < _filas && w.second >= 0 && w.second < _columnas
//				&& !_marcado[w.first][w.second]
//				&& _jardin[w.first][w.second] != 'X') {
//				dfs(w);
//			}
//		}
//	}
//
//};

class GreenPeace {
public:
	GreenPeace(Oceano& _mar, int filas, int columnas) : _vertido(filas*columnas),
		_filas(filas), _columnas(columnas), _solucion(""), _manchurron(0) {
		int nuevasManchas = 0;
		int filMancha = 0;
		int colMancha = 0;
		std::cin >> nuevasManchas;

		// Calculamos la primera mancha mas grande
		encuentraManchurron(_mar);
		_solucion += std::to_string(_manchurron);

		for (size_t i = 0; i < nuevasManchas; i++)
		{
			// Leemos la nueva mancha
			std::cin >> filMancha;
			std::cin >> colMancha;

			_mar[--filMancha][--colMancha] = '#';

			// Recalculamos la mancha mas grande
			reEncuentraManchurron(_mar, filMancha, colMancha);
			_solucion += " ";
			_solucion += std::to_string(_manchurron);

			filMancha = 0;
			colMancha = 0;
		}
	}

	std::string solucion() {
		return _solucion;
	}
private:
	std::vector<std::vector<bool>> _marcado;	// Para no repetir nodos
	std::string _solucion;						// Resultado de la operación
	size_t _manchurron;							// Mancha mas grande
	size_t _manchita;							// Mancha del mapa
	int _filas;									// Filas
	int _columnas;								// Columnas
	Punto _dir[8] = { Punto(1,1), Punto(-1,-1), Punto(-1,1), Punto(1,-1), Punto(0,1), Punto(0,-1), Punto(1,0), Punto(-1,0) };
	ConjuntosDisjuntos _vertido;				// Conjunto de las manchas

	void encuentraManchurron(Oceano& _mar) {
		_marcado = std::vector<std::vector<bool>>(_filas, std::vector<bool>(_columnas, false));

		for (size_t i = 0; i < _filas; i++) {
			for (size_t j = 0; j < _columnas; j++) {
				if (!_marcado[i][j]) {
					if (_mar[i][j] == '#') {
						agrupaCoordenadas(i, j, '#');
					}
					else if (_mar[i][j] == ' ') {
						agrupaCoordenadas(i, j, ' ');
					}
				}
			}
		}
	}
						//_manchita = 0;
						//Punto cuadrante(i, j);
						//dfs(_mar, cuadrante);
						//if (_manchita > _manchurron) {
						//	_manchurron = _manchita;
						//}

	void reEncuentraManchurron(Oceano& _mar,int fila, int columna) {
		_marcado = std::vector<std::vector<bool>>(_filas, std::vector<bool>(_columnas, false));
		_manchita = 0;
		Punto cuadrante(fila, columna);
		dfs(_mar,cuadrante);
		if (_manchita > _manchurron) {
			_manchurron = _manchita;
		}
	}

	void dfs(Oceano& _mar,Punto v) {
		++_manchita;
		_marcado[v.first][v.second] = true; // para no repetir vértices

		//for (auto w : G.adj(v)) { // recorremos todos los adyacentes a v
		for (size_t i = 0; i < 8; i++) {
			Punto w(v.first + _dir[i].first, v.second + _dir[i].second);
			if (w.first >= 0 && w.first < _filas && w.second >= 0 && w.second < _columnas
				&& !_marcado[w.first][w.second] && _mar[w.first][w.second] == '#') {
				dfs(_mar,w);
			}
		}
	}
};

void leer(Oceano& mar, size_t filas) {
	// quitamos un salto de linea
	std::string cadena;
	getline(std::cin, cadena);

	for (size_t i = 0; i < filas; i++) {
		getline(std::cin, cadena);
		for (size_t j = 0; j < cadena.length(); j++) {
			if (cadena[j] == '#') {
				mar[i][j] = '#';
			}
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	unsigned long int filas= 0;
	std::cin >> filas;

	unsigned long int columnas = 0;
	std::cin >> columnas;

	if (!std::cin) // fin de la entrada
		return false;

	Oceano mar(filas, std::vector<char>(columnas,' '));
	leer(mar,filas);
	GreenPeace resolvedor(mar,filas,columnas);
	std::cout << resolvedor.solucion() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos14.txt");
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