//Victor del Pino
//TAIS37

#include <algorithm>
#include <iostream>
#include <fstream>
#include"myTreeMap_AVL.h"

bool resuelveCaso() {
	int n;
	std::cin >> n;
	if (n == 0) return false;
	map<int, int> tree;
	int num;
	for (int i = 0; i < n; ++i) {
		std::cin >> num;
		tree.insert({ num,0 });
	}
	int n2;
	std::cin >> n2;
	int sol;
	int posicion;
	for (int i = 0; i < n2; ++i) {
		std::cin >> posicion;
		sol = tree.buscarPos(posicion);
		if (sol != -1) std::cout << sol << "\n";
		else std::cout << "??\n";
	}
	std::cout << "----\n";
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
