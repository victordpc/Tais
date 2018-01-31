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
using namespace std;

class Aibofobia
{
public:
	Aibofobia(string palabra) :resultado(0) {
		size_t n = palabra.length();
		Matriz<int> datos(n + 1, n + 1, 0);

		//Valores iniciales a 0
		for (size_t x = 0; x <= n; x++) {
			for (size_t y = 0; y <= n; y++) {
				if (x >= y) {
					datos[x][y] = 0;
				}
			}
		}

		// recorrido por diagonales
		for (size_t d = 1; d <= n - 1; ++d) {// recorre diagonales
			for (size_t i = 1; i <= n - d; ++i) { // recorre elementos de diagonal
				size_t j = i + d;

				if (palabra[i - 1] == palabra[j - 1])
					datos[i][j] = datos[i + 1][j - 1];
				else {
					datos[i][j] = min(datos[i + 1][j] + 1, datos[i][j - 1] + 1);
				}
			}
		}
			resultado = datos[1][n];
	}

	void Resultado(std::ostream& sout) {
		sout << resultado << std::endl;
	}

private:
	int resultado;
};

bool resuelveCaso() {

	string palabra;
	std::cin >> palabra;

	if (std::cin.fail()) return false;

	Aibofobia bfb = Aibofobia(palabra);

	bfb.Resultado(std::cout);

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos30.txt");
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

