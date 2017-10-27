//Victor del Pino
//TAIS37

#include <algorithm>
#include <iostream>
#include <istream>
#include <fstream>
using namespace std;

using Mapa = std::vector<string>;

class ComponenteConexa
{
public:
	ComponenteConexa(Mapa const& m) :
		F(m.size()),
		C(m[0].size()),
		marcados(F, vector<bool>(C,false)), 
		maxi(0) 
	{
		for (size_t i = 0; i < F; i++)
		{
			for (size_t j = 0; j < C; j++)
			{
				if (m[i][j]=='#'&&!marcados[i][j]) {
				size_t tam = 0;
				dfs(m, i,j, tam);
				if (maxi < tam) {
					maxi = tam;
				}
			}
		}
		}
	};
	size_t resultado()const {
		return maxi;
	}
private:
	vector<vector<bool>> marcados;
	size_t maxi;
	int F, C;

	void dfs(Mapa const& g, size_t i,size_t j, size_t & tam) {
		marcados[i][j] = true;
		++tam;
		for (int v = i-1; v <= i+1; v++)
		{
			for (int w = j-1; w <= j+1; w++)
			{
				if (v >= 0 && v < F &&w >= 0 && w < C && !marcados[v][w] && marcados[v][w]=='#') {
					dfs(g, v, w, tam);
				}
			}
		}
	}
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int F = 0, C = 0;

	std::cin >> F;
	std::cin >> C;

	if (std::cin.fail()) return false;
	cin.ignore(1);

	Mapa mapa=Mapa(F);

	int v = 0; int w = 0;
	for (int i = 0; i < F; i++) { //O(E)
		istream::getline(cin, mapa[i]);
	}

	ComponenteConexa sol = ComponenteConexa(mapa);
	std::cout << sol.resultado() << std::endl;
	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

while (resuelveCaso()) {}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}