//Victor del Pino Castilla
//TAIS37

#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <climits>
#include <string>
#include "Matriz.h"
#include <stack>

struct Cofre
{
	int tiempo;
	int oro;
};

// Coste O(segundos*cofres) tanto en tiempo como en espacio
class CazaTesoros
{
public:
	CazaTesoros(int segundos, int cofres, std::vector<Cofre> &datos) :numResultado(0) {
		size_t n = cofres;
		size_t M = segundos;
		Matriz<int> mochila(n + 1, segundos + 1, 0);
		// rellenar la matriz
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= segundos; ++j)
				if (datos[i - 1].tiempo * 3 > j)
					mochila[i][j] = mochila[i - 1][j];
				else
					mochila[i][j] = std::max(mochila[i - 1][j],
						mochila[i - 1][j - datos[i - 1].tiempo * 3] + datos[i - 1].oro);

		valor = mochila[cofres][segundos];

		// cálculo de los objetos
		int resto = segundos;
		for (size_t i = cofres; i >= 1; --i) {
			if (mochila[i][resto] != mochila[i-1][resto]) { // sí cogemos objeto i
				++numResultado;
				resultado.push(datos[i-1]);
				resto = resto - (datos[i-1].tiempo*3);
			}
		}
	}

	void Resultado(std::ostream& sout) {
		sout << valor << std::endl;
		sout << numResultado << std::endl;
		for (int i = 0; i < numResultado; i++) {
			sout << resultado.top().tiempo << " " << resultado.top().oro << std::endl;
			resultado.pop();
		}
	}

private:
	int numResultado;
	int valor;
	std::stack<Cofre> resultado;
};

// Orden O()
bool resuelveCaso() {

	int segundos = 0;
	int cofres = 0;

	std::cin >> segundos >> cofres;

	if (std::cin.fail()) return false;

	std::vector<Cofre> datos = std::vector<Cofre>(cofres);

	for (int i = 0; i < cofres; i++)
	{
		Cofre dato;
		std::cin >> dato.tiempo >> dato.oro;
		datos[i] = dato;
	}

	CazaTesoros cT = CazaTesoros(segundos, cofres, datos);

	cT.Resultado(std::cout);
	std::cout << "----" << std::endl;

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos28.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCaso()) {};
	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}

