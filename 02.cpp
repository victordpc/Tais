// Grupo TAIS37, Victor del Pino Casilla
 
// Construye un árbol binario a partir de la entrada y después
// calcula su altura de forma recursiva
#include <algorithm>
#include <iostream>
#include <fstream>
#include "bintree_eda.h"

// lee un árbol binario de la entrada estándar
template <typename T>
bintree<T> leerArbol(T vacio) {
	T raiz;
	std::cin >> raiz;
	if (raiz == vacio) { // es un árbol vacío
		return{};
	}
	else { // leer recursivamente los hijos
		auto iz = leerArbol(vacio);
		auto dr = leerArbol(vacio);
		return{ iz, raiz, dr };
	}
}

// dado un árbol binario, calcula las alturas de los hijos y los compara
// calcula si el valor de clave esta corretamente colocada
// lineal en el número N de nodos del árbol, O(N)
bool avl(bintree<int>arbol, unsigned int &altura, int& maximo, int& minimo){
	if (arbol.empty())
	{ altura = 0; maximo = 0; minimo = 0; return true; }
	else{
		unsigned int iz = 0, dr = 0;
		int maxIz = 0, minIz = 0, maxDr = 0, minDr = 0;

		if (avl(arbol.left(), iz, maxIz, minIz) 
		 && avl(arbol.right(), dr, maxDr, minDr)){
			altura = 1 + std::max(iz, dr); 
			int diferencia = iz - dr;
			
			if (std::abs(diferencia) <= 1){
				if (iz == 0 && dr == 0){
					maximo = arbol.root();
					minimo = arbol.root();
					return true;
				}
				else if (iz == 0 && arbol.root() < minDr){
					maximo = maxDr;
					minimo = arbol.root();
					return true;
				}
				else if (dr == 0 && arbol.root() > maxIz){
					maximo = arbol.root();
					minimo = minIz;
					return true;
				}
				else if(maxIz< arbol.root() && arbol.root()<minDr){
					maximo = maxDr;
					minimo = minIz;
					return true;
				}
			}
		}
		return false;
	}
}

// resuelve un caso de prueba
void resuelveCaso() {
	auto arbol = leerArbol(-1);
	unsigned int altura = 0;
	int max = 0, min = 0;
	bool sol = avl(arbol, altura,max,min);
	if (sol) std::cout << "SI" << std::endl; 
	else std::cout << "NO" << std::endl;
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;

}