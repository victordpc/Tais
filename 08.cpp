//Victor del Pino
//TAIS37

#include <algorithm>
#include <iostream>
#include <fstream>
#include"PriorityQueue.h"

//class datos
//{
//public:
//	datos() {};
//	datos(size_t m, size_t a):musicos(m),atriles(a) {};
//	~datos() {};
//	size_t division() {
//		if (musicos%atriles == 0)
//			return musicos / atriles;
//		else
//			return (musicos / atriles) + 1;
//	}
//	void sumaAtril() { ++atriles; }
//	/*bool operator>(datos const& b)const{
//		return(musicos / atriles) > (b.musicos / b.atriles);
//	}*/
//private:
//	size_t musicos;
//	size_t atriles;
//};

typedef struct {
	size_t musicos;
	size_t atriles;
}datos;

//Operacion constante
class Compara {
public:
	bool operator()(datos a, datos b) {
		size_t a1, b1;
		if (a.musicos % a.atriles == 0)
			a1 = a.musicos / a.atriles;
		else
			a1 = (a.musicos / a.atriles) + 1;
		if (b.musicos % b.atriles == 0)
			b1 = b.musicos / b.atriles;
		else
			b1 = (b.musicos / b.atriles) + 1;
		return a1 > b1;
	}
};

// El coste de esta operación pertenece a O(p-n) lineal en la diferencia de partituras y número de instrumentos
//size_t resolver(PriorityQueue<datos, std::greater<datos>> queue, size_t p, size_t n) {
size_t resolver(PriorityQueue<datos, Compara> queue, size_t p, size_t n) {
	if (queue.size() == 0) return 0;

	for (size_t i = 0; i < p - n; i++)
	{
		datos elemento = queue.top();
		queue.pop();

		++elemento.atriles;

		queue.push(elemento);
	}
	datos resultado = queue.top();

	if (queue.top().musicos%  queue.top().atriles == 0)
		return queue.top().musicos / queue.top().atriles;
	else
		return queue.top().musicos / queue.top().atriles + 1;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	size_t partituras, numinstrumentos, elem = 0;
	//PriorityQueue<datos, std::greater<datos>> queue;
	PriorityQueue<datos, Compara> queue;

	std::cin >> partituras;
	std::cin >> numinstrumentos;

	if (std::cin.fail()) return false;

	for (size_t i = 0; i < numinstrumentos; i++) {
		std::cin >> elem;
		datos in;
		in.musicos = elem;
		in.atriles = 1;
		queue.push(in);
	}

	size_t sol = resolver(queue, partituras, numinstrumentos);

	std::cout << sol << std::endl;

	return true;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso()) {}

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}