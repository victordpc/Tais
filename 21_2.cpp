//Victor del Pino
//TAIS37

#include <iostream>
#include <fstream>
#include <algorithm>
#include <algorithm>
#include <functional>
#include <vector>

class Telesilla
{
public:
	Telesilla(std::vector<size_t>& sillas, size_t peso) : resultado(0) {
		std::sort(sillas.begin(), sillas.end(), std::greater<size_t>());

		size_t i = 0;
		size_t j = sillas.size()-1;

		while (i <= j) {
			if (i != j && sillas[i] + sillas[j] <= peso)
				--j;
			++i;
			++resultado;
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
	size_t peso = 0;
	size_t gente = 0;

	std::cin >> peso >> gente;

	if (std::cin.fail()) return false;

	std::vector<size_t>sillas(gente);

	for (size_t i = 0; i < gente; i++)
		std::cin >> sillas[i];

	Telesilla rm(sillas, peso);
	rm.Resultado();

	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos21.txt");
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