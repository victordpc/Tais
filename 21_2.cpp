//Victor del Pino
//TAIS37

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class ReparaMangueras
{
public:
	ReparaMangueras(std::vector<size_t> Manguera, size_t agujeros, size_t lParche) 
		:manguera(Manguera), agujeros(agujeros), parches(lParche) ,resultado(1)
	{
	};
	
	size_t Resultado() {
		return resultado;
	}
	
private:
	std::vector<size_t> manguera;
	size_t agujeros;
	size_t parches;
	size_t resultado;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t agujeros = 0;
	size_t parche = 0;

	std::cin >> agujeros >> parche;

	if (std::cin.fail()) return false;

	std::vector<size_t>mangera(agujeros);

	for (size_t i = 0; i < agujeros; i++)
		std::cin >> mangera[i];

	ReparaMangueras rm = ReparaMangueras(mangera, agujeros, parche);

	std::cout << rm.Resultado()<<std::endl;

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