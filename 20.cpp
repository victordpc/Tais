//Victor del Pino
//TAIS37

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

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

class ReparaMangueras
{
public:
	// Estrategia:
	// Poner un parche siempre que haga falta
	ReparaMangueras(std::vector<size_t> manguera, size_t agujeros, size_t lParche) 
		:manguera(manguera), agujeros(agujeros), parches(lParche) ,resultado(1)
	{
		if (agujeros > 1)  {
			size_t avanzado = manguera[0];

			for (size_t i = 1; i < agujeros; i++)
			{
				if (avanzado + parches < manguera[i]) {
					++resultado;
					avanzado = manguera[i] ;
				}
			}
		}
	};
	
	size_t Resultado() {
		return resultado;
	}
	
private:
	std::vector<size_t> manguera;
	size_t agujeros;
	size_t parches;
	size_t resultado;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t agujeros= 0, lParche= 0;

	std::cin >> agujeros;
	std::cin >> lParche;

	if (std::cin.fail()) return false;

	std::vector<size_t> mangera=std::vector<size_t>(agujeros);
	for (size_t i = 0; i < agujeros; i++)
	{
		std::cin >> mangera[i];
	}

ReparaMangueras rM=	ReparaMangueras(mangera, agujeros, lParche);

std::cout << rM.Resultado();
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