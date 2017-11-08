//Victor del Pino
//TAIS37

#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using Mapa = std::vector<std::string>;
using Punto = std::pair<int, int>;

class BreadthFirstPaths
{
public:
	// O(E+V) encontramos el camino mas corto si existe pasando por los vertices y aristas existentes.
	BreadthFirstPaths(Mapa const& G, int filas, int columnas, Punto inicio) :i(inicio),
		marked(filas, std::vector<bool>(columnas, false)), distTo(filas, std::vector<int>(columnas)) 
	{
		bfs(G, i, filas, columnas);
	}

	// ¿Hay camino del origen a v?
	bool hasPathTo(Punto v) const {
		return marked[v.first][v.second];
	}

	// Devuelve el número de aristas en el camino más corto a v
	int distance(Punto v) const {
		return distTo[v.first][v.second];
	}

private:
	std::vector<std::vector<bool>> marked;		// marked[v] = ¿hay camino de s a v?
	std::vector<std::vector<int>> distTo;		// distTo[v] = número de aristas en el camino s-v más corto
	Punto i;									// vértice origen
	Punto dir[4] = { Punto(1,0), Punto(0,1), Punto(0,-1),Punto(-1,0) };	//vector de direcciones

	// O(E+V) encontramos el camino mas corto si existe pasando por los vertices y aristas existentes.
	void bfs(Mapa const& G, Punto s, int filas, int columnas) {
		std::queue<Punto> q;
		if (G[s.first][s.second] == '#')
			return;
		marked[s.first][s.second] = true;
		q.push(s);
		while (!q.empty()) {
			auto v = q.front(); q.pop();
			for (int i = 0; i < 4; i++) {
				Punto w = Punto(v.first + dir[i].first, v.second + dir[i].second);
				if (w.first >= 0 && w.second >= 0 && w.first < filas && w.second < columnas
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

class FreeLove
{
public:
	//O(E+V) 
	FreeLove(Mapa ma, int filas, int columnas) : m(ma), esP(false), distancia(0) {
		// Calculamos el mapa O(V), aunque en el caso peor podriamos tener un coste exponencial si todas las casillas del mapa
		// están rellenas con sensores y cubren a su vez todas las casillas del mapa
		for (int f = 0; f < filas; f++)
		{
			for (int c = 0; c < columnas; c++)
			{
				if (ma[f][c] >= '0' && ma[f][c] <= '9') {
					int	longitud = ma[f][c] - '0' + 1;
					//izquierda
					int i = f;
					int destino = f - longitud;
					for (; i > destino && i >= 0; i--)
					{
						if (ma[i][c] != '#')
							m[i][c] = '#';
						else
							break;
					}
					//abajo
					i = f;
					for (; i < f + longitud && i < filas; i++)
					{
						if (ma[i][c] != '#')
							m[i][c] = '#';
						else
							break;
					}
					//izquierda
					i = c;
					for (; i > c - longitud && i >= 0; i--)
					{
						if (ma[f][i] != '#')
							m[f][i] = '#';
						else
							break;
					}
					//derecha
					i = c;
					for (; i < c + longitud && i < columnas; i++)
					{
						if (ma[f][i] != '#')
							m[f][i] = '#';
						else
							break;
					}
				}
				else if (ma[f][c] == 'E') {
					entrada.first = f;
					entrada.second = c;
				}
				else if (ma[f][c] == 'P') {
					salida.first = f;
					salida.second = c;
				}
			}
		}

		//Recorremos usandos bfs para recorrer el mapa O(E+V)
		BreadthFirstPaths recorrido = BreadthFirstPaths(m, filas, columnas, entrada);
		esP = recorrido.hasPathTo(salida);
		distancia = recorrido.distance(salida);
	};

	bool esPosible() {
		return	esP;
	};

	size_t camino() {
		return distancia;
	}

private:
	Mapa m;
	bool esP;
	size_t distancia;
	Punto entrada;
	Punto salida;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int filas = 0, columnas = 0;

	std::cin >> columnas;
	std::cin >> filas;

	Mapa mp = Mapa(filas, ".");

	//Quitamos el salto de línea de las filas y columnas
	std::cin.get();

	for (int i = 0; i < filas; i++) {
		getline(std::cin, mp[i]);
	}

	FreeLove fl = FreeLove(mp, filas, columnas);

	if (fl.esPosible())
		std::cout << fl.camino();
	else
		std::cout << "NO";

	std::cout << std::endl;

	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	size_t casos = 0;
	std::cin >> casos;

	for (size_t i = 0; i < casos; i++)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}