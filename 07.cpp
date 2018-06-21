// Grupo 37, Víctor del Pino

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"

typedef struct {
	unsigned long int id;
	unsigned long int periodo;
	unsigned long int toca;
}datos;

class ComparaDatos {
public:
	bool operator()(datos a, datos b) {
		if (a.toca != b.toca)
			return a.toca < b.toca;
		else
			return a.id < b.id;
	}
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es el numero de nodos del arbol ya que los recorre todos para averiguarlo.
void resolver(unsigned long int primerPajaro, unsigned long int parejas) {
	PriorityQueue<unsigned long int, std::greater<unsigned long int>> menores;
	PriorityQueue<unsigned long int, std::less<unsigned long int>> mayores;

	unsigned long int cabecera=primerPajaro,pajaroNuevo;

	for (unsigned long int i = 0; i < parejas; i++) {
		//primer pajaro
		std::cin >> pajaroNuevo;
		if (pajaroNuevo < cabecera)
			menores.push(pajaroNuevo);
		else
			mayores.push(pajaroNuevo);
		//segundo pajaro
		std::cin >> pajaroNuevo;
		if (pajaroNuevo < cabecera)
			menores.push(pajaroNuevo);
		else
			mayores.push(pajaroNuevo);

		if (menores.size() > mayores.size()) {
			mayores.push(cabecera);
			cabecera = menores.top();
			menores.pop();
		}
		else if (mayores.size() > menores.size()) {
			menores.push(cabecera);
			cabecera = mayores.top();
			mayores.pop();
		}

		std::cout << cabecera;
		
		if (i!=parejas-1)
			std::cout << " ";
	}
}

//PriorityQueue<datos,ComparaDatos> leer(unsigned long int elementos) {
//	PriorityQueue<datos,ComparaDatos> resultado = PriorityQueue<datos,ComparaDatos>();
//	unsigned long int datoId=0;
//	unsigned long int datoPeriodo=0;
//	for (size_t i = 0; i < elementos; i++) {
//		std::cin >> datoId; 
//		std::cin >> datoPeriodo;
//		
//		datos d;
//		d.id = datoId;
//		d.periodo = datoPeriodo;
//		d.toca = datoPeriodo;
//		
//		resultado.push(d);
//	}
//	return resultado;
//}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	unsigned long int primerPajaro = 0;
	std::cin >> primerPajaro;

	unsigned long int parejas= 0;
	std::cin >> parejas;

	if (primerPajaro == 0 && parejas ==0)
		return false;

	resolver(primerPajaro,parejas);
	std::cout << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos07.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	//int numCasos;
	//std::cin >> numCasos;
	//for (int i = 0; i < numCasos; ++i)
	//	resuelveCaso();

	while (resuelveCaso()) {}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}