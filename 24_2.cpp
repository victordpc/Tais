//Victor del Pino
//TAIS37

#include <iostream>
#include <fstream>
#include <algorithm>
#include <algorithm>
#include <functional>
#include <vector>

class Pelicula
{
public:
	Pelicula() :_inicio(0), _fin(0) {};
	Pelicula(size_t inicio, size_t fin) :_inicio(inicio), _fin(fin) {};
	size_t inicio() { return _inicio; }
	size_t fin() { return _fin; }
	bool operator<(Pelicula const & b) const { return _fin < b._fin; }
	bool operator>(Pelicula const & b) const { return _fin > b._fin; }
private:
	size_t _inicio;
	size_t _fin;
};

class Sitges
{
public:
	Sitges(std::vector<Pelicula>& peliculas) : resultado(0) {
		std::sort(peliculas.begin(), peliculas.end(), std::less<Pelicula>());
		size_t i = 0;
		size_t hora = 0;

		for (Pelicula w : peliculas) {
			if (w.inicio() >= hora) {
				++resultado;
				hora = 10 + w.fin();
			}
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
	size_t numero = 0;

	std::cin >> numero;

	//if (std::cin.fail()) return false;
	if (numero == 0) return false;

	std::vector<Pelicula>peliculas(numero);

	int hora = 0, minuto = 0, duracion = 0;
	char separador;
	size_t inicio = 0, fin = 0;

	for (size_t i = 0; i < numero; i++) {
		hora = 0;
		minuto = 0;
		duracion = 0;
		inicio = 0;
		fin = 0;

		std::cin >> hora;
		std::cin >> separador;
		std::cin >> minuto;
		std::cin >> duracion;
		inicio = (hora * 60) + minuto;
		fin = inicio + duracion;

		peliculas[i] = Pelicula(inicio, fin);
	}

	Sitges st(peliculas);
	st.Resultado();

	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos24.txt");
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