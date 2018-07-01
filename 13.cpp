// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <queue>
#include <vector>

using Pradera = std::vector<std::string>;
using Punto = std::pair<int, int>;

class CuentaOvejas {
public:
	CuentaOvejas(Pradera campo, int filas, int columnas) : _jardin(campo), _solucion(0), _filas(filas), _columnas(columnas),
		_marcado(filas, std::vector<bool>(columnas, false)) {
		for (size_t i = 0; i < _filas; i++)
		{
			for (size_t j = 0; j < _columnas; j++)
			{
				if (!_marcado[i][j] && _jardin[i][j] != 'X') {
					++_solucion;
					Punto _inicio(i, j);
					dfs(_inicio);
				}
			}
		}
		--_solucion;
	}

	size_t solucion() const {
		return _solucion;
	}

private:
	std::vector<std::vector<bool>> _marcado;	// marcado de posicion visitada
	Pradera _jardin;
	size_t _filas;
	size_t _columnas;
	size_t _solucion;	// indica el número de ovejas blancas
	Punto _dir[4] = { Punto(1,0), Punto(0,1), Punto(0,-1), Punto(-1,0) };	//vector de direcciones

	// recorrido en profundidad desde v
	void dfs(Punto v) {
		_marcado[v.first][v.second] = true; // para no repetir vértices
		for (size_t i = 0; i < 4; i++) {// recorremos todos los adyacentes a v
			Punto w(v.first + _dir[i].first, v.second + _dir[i].second);
			if (w.first >= 0 && w.first < _filas && w.second >= 0 && w.second < _columnas
				&& !_marcado[w.first][w.second]
				&& _jardin[w.first][w.second] != 'X') {
				dfs(w);
			}
		}
	}

};

void leer(Pradera& jardin, size_t filas) {
	// quitamos un salto de linea
	getline(std::cin, jardin[0]);
	for (size_t i = 0; i < filas; i++) {
			getline(std::cin, jardin[i]);
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	unsigned long int columnas = 0;
	std::cin >> columnas;

	if (!std::cin) // fin de la entrada
		return false;

	unsigned long int filas= 0;
	std::cin >> filas;

	Pradera campo(filas, ".");
	leer(campo,filas);
	CuentaOvejas resolvedor(campo,filas,columnas);
	std::cout << resolvedor.solucion() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos13.txt");
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