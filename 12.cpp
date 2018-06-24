// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <queue>
#include <vector>

using Jardin = std::vector<std::string>;
using Punto = std::pair<int, int>;

/**
* Recorrido en anchura de un grafo a partir de un vértice origen.
* Permite recuperar los caminos más cortos desde el origen a todos los vértices alcanzables.
*/
class BreadthFirstPaths {
public:
	BreadthFirstPaths(Jardin const& G, Punto s, int filas, int columnas)
		:i(s), marked(filas, std::vector<bool>(columnas, false)), distTo(filas, std::vector<size_t>(columnas)) {
		bfs(G, i, filas, columnas);
	}

	// ¿Hay camino del origen a v?
	bool hasPathTo(Punto v) const {
		return marked[v.first][v.second];
	}

	// Devuelve el número de aristas en el camino más corto a v
	size_t distance(Punto v) const {
		return distTo[v.first][v.second];
	}

private:
	std::vector<std::vector<bool>> marked;     // marked[v] = ¿hay camino de s a v?
	std::vector<std::vector<size_t>> distTo;   // distTo[v] = número de aristas en el camino s-v más corto
	Punto i;                     // vértice origen
	Punto dir[4] = { Punto(1,0), Punto(0,1), Punto(0,-1),Punto(-1,0) };	//vector de direcciones

	void bfs(Jardin const& G, Punto s, int filas, int columnas) {
		std::queue<Punto> q;
		if (G[s.first][s.second] == '#')
			return;
		marked[s.first][s.second] = true;
		q.push(s);
		while (!q.empty()) {
			auto v = q.front(); q.pop();
			for (int i = 0; i < 4; i++) {
				Punto w = Punto(v.first + dir[i].first, v.second + dir[i].second);
				if (w.first >= 0 && w.first < filas && w.second >= 0 && w.second < columnas
					&& !marked[w.first][w.second]
					&& G[w.first][w.second] != '#') {
					distTo[w.first][w.second] = distTo[v.first][v.second] + 1;
					marked[w.first][w.second] = true;
					q.push(w);
				}
			}
		}
	}
};

class FreeLove {
public:
	FreeLove(Jardin jardin, int filas, int columnas) : _mapa(jardin), _jardin(jardin),
		_filas(filas), _columnas(columnas)
	{
		asaltarElJardin();
	}

	std::string solucion() const {
		std::string resultado;
		if (_solucion)
			resultado = std::to_string(_distancia);
		else
			resultado = "NO";
		return resultado;
	}

private:
	Jardin _jardin;
	Jardin _mapa;
	size_t _filas;
	size_t _columnas;
	Punto _entrada;
	Punto _salida;
	bool _solucion;					// indica si hay solucion
size_t _distancia;

	// Usamos BFS para encontrar el camino mas corto entre la entrada y salida
	// Primero tratamos el mapa para marcar las casillas por las que no se puede pasar
	void asaltarElJardin() {
		encuentraLaser();
		encuentraElAmor();
	}

	// Marca en el mapa las casillas que cubren los laser
	// Encontramos las coordenadas de entrada y salida
	void encuentraLaser() {
		for (int f = 0; f < _filas; f++)
		{
			for (int c = 0; c < _columnas; c++)
			{
				if (_jardin[f][c] == '#') {
					_mapa[f][c] = '#';
				}
				if (_jardin[f][c] == 'E') {
					_entrada.first = f; _entrada.second = c;
				}
				if (_jardin[f][c] == 'P') {
					_salida.first = f; _salida.second = c;
				}
				if (_jardin[f][c] >= '0' && _jardin[f][c] <= '9') {
					laserEncontrado(f, c);
				}
			}
		}
	}

	void laserEncontrado(int f, int c) {
		// el valor del numero en el mapa lo obtenemos restandole el valor del char '0' y sumandole 1
		int _laser = _jardin[f][c] - '0' + 1;
		bool _arriba = true, _abajo = true, _izquierda = true, _derecha = true;

		for (int i = 0; i < _laser; i++)
		{
			// Arriba
			if ((f - i) >= 0 && _arriba) {
				if (_jardin[f - i][c] != '#')
					_mapa[f - i][c] = '#';
				else
					_arriba = false;
			}
			// Abajo
			if ((f + i) < _filas && _abajo) {
				if (_jardin[f + i][c] != '#')
					_mapa[f + i][c] = '#';
				else
					_abajo = false;
			}
			// Izquierda
			if ((c - i )>= 0 && _izquierda) {
				if (_jardin[f][c - i] != '#')
					_mapa[f][c - i] = '#';
				else
					_izquierda = false;
			}
			// Derecha
			if ((c + i )< _columnas && _derecha) {
				if (_jardin[f][c + i] != '#')
					_mapa[f][c + i] = '#';
				else
					_derecha = false;
			}
		}
	}

	void encuentraElAmor() {
		BreadthFirstPaths camino = BreadthFirstPaths(_mapa, _entrada, _filas, _columnas);
		_solucion = camino.hasPathTo(_salida);
		_distancia = camino.distance(_salida);
	}
};

void leer(Jardin& jardin, size_t filas) {
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

	//if (!std::cin) // fin de la entrada
	//	return false;

	unsigned long int filas= 0;
	std::cin >> filas;

	Jardin jardin(filas, ".");
	leer(jardin,filas);
	FreeLove resolvedor(jardin,filas,columnas);
	std::cout << resolvedor.solucion() << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos12.txt");
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