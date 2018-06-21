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
void resolver(unsigned long int personas, PriorityQueue<datos, ComparaDatos> cola, unsigned long int envios) {
	datos dato1;
	for (unsigned long int i = 0; i < envios; i++) {
		dato1 = cola.top();
		cola.pop();
		std::cout << dato1.id << "\n";
		dato1.toca += dato1.periodo;
		cola.push(dato1);
	}
}

PriorityQueue<datos,ComparaDatos> leer(unsigned long int elementos) {
	PriorityQueue<datos,ComparaDatos> resultado = PriorityQueue<datos,ComparaDatos>();
	unsigned long int datoId=0;
	unsigned long int datoPeriodo=0;
	for (size_t i = 0; i < elementos; i++) {
		std::cin >> datoId; 
		std::cin >> datoPeriodo;
		
		datos d;
		d.id = datoId;
		d.periodo = datoPeriodo;
		d.toca = datoPeriodo;
		
		resultado.push(d);
	}
	return resultado;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	unsigned long int personas = 0;
	std::cin >> personas;

	if (personas == 0)
		return false;

	auto cola = leer(personas);
	unsigned long int envios;
	std::cin >> envios;
	resolver(personas,cola,envios);
	std::cout << "----\n";
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("Casos06.txt");
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