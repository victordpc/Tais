//Victor del Pino
//TAIS37

#include <algorithm>
#include <iostream>
#include <fstream>
#include"PriorityQueue.h"

// Esta operación tiene coste O(n) siendo n el numero de nodos del problema
void resolver(PriorityQueue<size_t, std::less<size_t>> &queue, size_t &acumulado) {
	if (queue.size() != 1) {

		size_t fans = queue.top();
		queue.pop();
		fans += queue.top();
		queue.pop();

		queue.push(fans);

		acumulado += fans;
		
		resolver(queue, acumulado);
	}
}

bool resuelveCaso() {
	size_t n;
	std::cin >> n;
	if (n == 0) return false;
	size_t elem = 0;
	if (n == 1) {
		std::cin >> elem;
		std::cout << "0" << std::endl;
		return true;
	}
	PriorityQueue<size_t, std::less<size_t>> queue = PriorityQueue<size_t, std::less<size_t>>();
	for (size_t i = 0; i < n; ++i) {
		std::cin >> elem;
		queue.push(elem);
	}
	size_t acumulado = 0;
	 resolver(queue,acumulado);
	std::cout << acumulado<<std::endl;
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
