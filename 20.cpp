//Victor del Pino
//TAIS37

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class ReparaMangueras
{
public:
	// Estrategia:
	// Poner un parche siempre que haga falta
	// O(n)
	ReparaMangueras(std::vector<size_t> Manguera, size_t agujeros, size_t lParche) 
		:manguera(Manguera), agujeros(agujeros), parches(lParche) ,resultado(1)
	{
		if (agujeros > 1)  {
			size_t avanzado = manguera[0];

			for (size_t i = 1; i < agujeros; i++)
			{
				if (avanzado + parches < manguera[i]) {
					++resultado;
					avanzado = manguera[i] ;
				}
			}
		}
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
	size_t agujeros = 0, lParche = 0;

	std::cin >> agujeros;
	std::cin >> lParche;

	if (std::cin.fail()) return false;

	std::vector<size_t> mangera = std::vector<size_t>(agujeros);

	for (size_t i = 0; i < agujeros; i++)
	{
		std::cin >> mangera[i];
	}

	ReparaMangueras rM = ReparaMangueras(mangera, agujeros, lParche);// O(n)

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