//Victor del Pino
//TAIS37

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "ConjuntosDisjuntos.h"

const std::pair<int, int> dirs[8] = { {1,1},{-1,-1},{-1,1},{1,-1},{0,1},{0,-1},{1,0},{-1,0} };

class Petroleros
{
public:
	Petroleros(std::vector<std::vector<bool>> const& m) :matriz(m), marcados(m.size(),
		std::vector<bool>(m[0].size(), false)),
		contador(0), cd(m.size()*m[0].size()),max(0)
	{
		for (int i = 0; i < matriz.size(); i++) {
			for (int j = 0; j < matriz[0].size(); j++) {
				if (!marcados[i][j] && matriz[i][j]) {

					marcados[i][j] = true;

					for (auto w : dirs) {
						int fprima = i + w.first;
						int cprima = j + w.second;

						if (fprima >= 0 && cprima >= 0 && fprima < matriz.size() && cprima < matriz[0].size() && matriz[fprima][cprima])
							cd.unir(fprima*matriz[0].size() + cprima, i*matriz[0].size() + j);
					}

					contador = cd.size((i)*matriz[0].size() + (j));
					if (contador > max)
						max = contador;
				}
			}
		}
	}

	void resultado()const {
		std::cout << max;
	}

	void nuevaMancha(int f1, int c1) {
		matriz[f1 - 1][c1 - 1] = true;
		contador = 0;
		calcularMancha(f1 - 1, c1 - 1);
	}

	void calcularMancha(int f, int c)
	{
		for (auto i : dirs) {
			int fprima = f + i.first;
			int cprima = c + i.second;

			if (fprima >= 0 && cprima >= 0 && fprima < matriz.size() && cprima < matriz[0].size() && matriz[fprima][cprima])
				cd.unir(fprima*matriz[0].size() + cprima, f*matriz[0].size() + c);
		}
		contador = cd.size((f)*matriz[0].size() + (c));
		if (max < contador)
			max = contador;
	}

private:
	std::vector<std::vector<bool>> marcados;
	std::vector<std::vector<bool>> matriz;
	int contador;
	int max;
	ConjuntosDisjuntos cd;

	//void dfs(int f, int c, int forigen, int corigen) {
	//	marcados[f][c] = true; // para no repetir vértices
	//	if (matriz[f][c]) {
	//		//unimos con el conjunto disjunto
	//		cd.unir(f*matriz[0].size() + c, forigen*matriz[0].size() + corigen);
	//		++contador;
	//		for (auto i : dirs)
	//		{
	//			int fprima = f + i.first;
	//			int cprima = c + i.second;
	//			if (fprima >= 0 && cprima >= 0 && fprima < matriz.size() && cprima < matriz[0].size() && !marcados[fprima][cprima])
	//				dfs(fprima, cprima, f, c);
	//		}
	//	}
	//}
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t F = 0, C = 0;

	std::cin >> F;
	std::cin >> C;

	if (std::cin.fail()) return false;

	std::vector<std::vector<bool>>m(F, std::vector<bool>(C, false));

	std::string entrada;
	getline(std::cin, entrada);//Leemos una linea para consumir el salto de linea de la matriz
	for (size_t i = 0; i < F; i++) {
		getline(std::cin, entrada);
		for (size_t j = 0; j < entrada.length(); j++) {
			if (entrada[j] == '#') {
				m[i][j] = true;
			}
		}
	}

	Petroleros sol = Petroleros(m);
	sol.resultado();

	size_t manchas = 0;
	std::cin >> manchas;
	int f1 = 0, c1 = 0;
	for (size_t i = 0; i < manchas; i++) {
		std::cin >> f1 >> c1;
		sol.nuevaMancha(f1, c1);
		std::cout << " ";
		sol.resultado();
	}

	std::cout << std::endl;

	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos14.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	//size_t casos = 0;
	//cin >> casos;
	//for (size_t i = 0; i < casos; i++)
	//{
	//	resuelveCaso();
	//}
	while (resuelveCaso()) {}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}