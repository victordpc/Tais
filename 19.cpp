//Victor del Pino
//TAIS37

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>

class Libreria
{
public:
	Libreria(std::vector<int>& m) :descuento(0) {

		std::sort(m.begin(),m.end(), std::greater<int>());

		int contador=0;
		int acumulado=0;

		for (int  w :m) {
			++contador;
			if (contador % 3 == 0) {
				descuento += w;
			}
		}
	}

	void resultado()const {
		std::cout << descuento<<std::endl;
	}

private:
	int descuento;

};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t Libros;

	std::cin >> Libros;

	if (std::cin.fail()) return false;

	std::vector<int>m(Libros, 0);
	int precio = 0;

	for (size_t i = 0; i < Libros; i++) {
		std::cin >> precio;
		m[i] = precio;
	}

	Libreria sol = Libreria(m);
	sol.resultado();

	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos19.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	//size_t casos = 0;
	//cin >> casos;
	//for (size_t i = 0; i < casos; i++)
	//{
	//	resuelveCaso();
	//}
	while (resuelveCaso()) {}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}