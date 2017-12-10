//Victor del Pino
//TAIS37

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <functional>

class ReparteSitios
{
public:
	// Estrategia:
	// Como mucho hay que hacer tantos viajes como pasajeros
	// colocamos a los viajeros en el primer hueco que entren
	ReparteSitios(std::vector<size_t> pesoPasajero, size_t pesoMaximo, size_t numPasajeros) 
		:pesos(pesoPasajero), max(pesoMaximo), pasajeros(numPasajeros) ,resultado(1), ocupados(numPasajeros,0)
	{
		if (pasajeros > 1)  {
			ocupados[0] = pesos[0];
	
			for (size_t i = 1; i < pasajeros; i++)
			{
				for (size_t j = 0; j < pasajeros; j++)
				{
					if (pesos[i] + ocupados[j] <= max) {
						if (ocupados[j] == 0) {
							++resultado;
						}
						ocupados[j] += pesos[i];
						j = pasajeros;
					}
				}
			}
		}
	};
	
	size_t Resultado() {
		return resultado;
	}
	
private:
	std::vector<size_t> pesos;
	std::vector<size_t> ocupados;
	size_t max;
	size_t pasajeros;
	size_t resultado;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t pesoMaximo = 0, pasajeros = 0;

	std::cin >> pesoMaximo;
	std::cin >> pasajeros;

	if (std::cin.fail()) return false;

	std::vector<size_t> pesos = std::vector<size_t>(pasajeros);
	for (size_t i = 0; i < pasajeros; i++)
	{
		std::cin >> pesos[i];
	}
	std::sort(pesos.begin(),pesos.end(), std::greater<size_t>());

	ReparteSitios rM = ReparteSitios(pesos, pesoMaximo, pasajeros);

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