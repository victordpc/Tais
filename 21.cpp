
//Victor del Pino
//TAIS37

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <functional>

#include <stdlib.h>
#include <stdio.h>
#include <climits>
#include <queue>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <climits>
#include <queue>


class ReparteSitios
{
public:
	// Estrategia:
	// Como mucho hay que hacer tantos viajes como pasajeros
	// emparejamos el mayor con el menor y si se pasa de peso avanzamos el mayor
	ReparteSitios(std::vector<int> pesos, int pesoMaximo, int numPasajeros)
		: max(pesoMaximo), pasajeros(numPasajeros) ,resultado(0)
	{
		sort(pesos.begin(), pesos.end(), std::greater<int>()); // O(n·log n)

		int i = 0;
		int j = numPasajeros - 1;
		while (i <= j) {
			if (pesos[i] + pesos[j] <= max) {
				--j;
			}
			++i;
			++resultado;
		}
	};
	
	size_t Resultado() {
		return resultado;
	}
	
private:
	int max;
	int pasajeros;
	int resultado;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int pesoMaximo = 0, pasajeros = 0;

	std::cin >> pesoMaximo;
	std::cin >> pasajeros;

	if (std::cin.fail()) return false;

	std::vector<int> pesos = std::vector<int>(pasajeros);
	for (int i = 0; i < pasajeros; i++)
	{
		std::cin >> pesos[i];
	}
	
	ReparteSitios rM = ReparteSitios(pesos, pesoMaximo, pasajeros);

	std::cout << rM.Resultado();
	std::cout << std::endl;

	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos21.txt");
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