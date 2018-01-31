//Victor del Pino
//TAIS37

#include <iostream>
#include <fstream>
#include <algorithm>
#include <algorithm>
#include <functional>
#include <vector>

class ClashRoyale
{
public:
	ClashRoyale(std::vector<size_t>& contrarios, std::vector<size_t>&nosotros) : resultado(0) {

		std::sort(contrarios.begin(), contrarios.end(), std::greater<size_t>());
		std::sort(nosotros.begin(), nosotros.end(), std::greater<size_t>());
		size_t i = 0;
		size_t j = 0;

		while (j < nosotros.size() && i < contrarios.size()) {
			if (nosotros[j] >= contrarios[i]) {
				++resultado;
				++j;
			}
			++i;
		}
	};

	void Resultado() {
		std::cout << resultado << std::endl;
	}

private:
	size_t resultado;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t ciudades = 0;

	std::cin >> ciudades;

	if (std::cin.fail()) return false;
	//if (partidos== 0) return false;

	std::vector<size_t>contrarios(ciudades);
	std::vector<size_t>nosotros(ciudades);

	for (size_t i = 0; i < ciudades; i++)
		std::cin >> contrarios[i];
	for (size_t i = 0; i < ciudades; i++)
		std::cin >> nosotros[i];

	ClashRoyale cr(contrarios, nosotros);
	cr.Resultado();

	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos23.txt");
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