//Victor del Pino
//TAIS37

#include <iostream>
#include <fstream>
#include <algorithm>
#include <algorithm>
#include <functional>
#include <vector>

class BroncosBoston
{
public:
	BroncosBoston(std::vector<size_t>& contrarios, std::vector<size_t>&broncos) : resultado(0) {

		std::sort(contrarios.begin(), contrarios.end(), std::less<size_t>());
		std::sort(broncos.begin(), broncos.end(), std::greater<size_t>());

		for (size_t i = 0; i < broncos.size() && contrarios[i] < broncos[i]; i++){
				resultado += broncos[i] - contrarios[i];
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
	size_t partidos = 0;

	std::cin >> partidos;

	//if (std::cin.fail()) return false;
	if (partidos == 0) return false;

	std::vector<size_t>contrarios(partidos);
	std::vector<size_t>broncos(partidos);

	for (size_t i = 0; i < partidos; i++)
		std::cin >> contrarios[i];
	for (size_t i = 0; i < partidos; i++)
		std::cin >> broncos[i];

	BroncosBoston bb(contrarios, broncos);
	bb.Resultado();

	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos22.txt");
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