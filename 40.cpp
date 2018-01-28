//Victor del Pino Castilla
//TAIS37

#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <climits>
#include <string>
#include "Matriz.h"
#include <stack>
#include "PriorityQueue.h"

struct Cancion {
	double tiempo;		//peso
	double puntuacion; //valor
};

bool operator<(Cancion const &a, Cancion const &b) {
	return (a.tiempo / a.puntuacion) < (b.tiempo / b.puntuacion);
}
struct Nodo {
	std::vector<bool> solA;
	std::vector<bool> solB;
	size_t k;
	int pesoA; // tiempo ocupado cara A
	int pesoB; // tiempo ocupado cara B
	int beneficio; // puntuaciones acumuladas
	int benef_est; // prioridad
	int cogidos;
};

bool operator>(Nodo const& a, Nodo const& b) {
	return a.benef_est > b.benef_est;
}

// Calculo voraz peretenece a O(n)
int calculo_voraz(std::vector<Cancion> const& objetos, int M, int k, int peso, int beneficio) {
	int hueco = 2*M - peso;
	int estimacion = beneficio;
	size_t j = k + 1;
	while (j < objetos.size() && objetos[j].tiempo <= hueco) {
		hueco-= objetos[j].tiempo;
		estimacion += objetos[j].puntuacion;
		++j;
	}
	if (j < objetos.size()) {
		estimacion += (hueco / objetos[j].tiempo) * objetos[j].puntuacion;
	}
	return estimacion;
}

// objetos ordenados de mayor a menor valor/peso
// mochila es O(n^2) ya que el while es lineal y dentro se llama a la operacion voraz que tambien es lineal
void mochila_rp(std::vector<Cancion> const& objetos, int M, int & benef_mejor, int & cogidos) /*, std::vector<bool> & sol_mejor*/{
	size_t N = objetos.size();

	Nodo Y;
	Y.solA = std::vector<bool>(N); // sol_mejor;
	Y.solB = std::vector<bool>(N); //sol_mejor;
	Y.k = -1;
	Y.pesoA = 0;
	Y.pesoB = 0;
	Y.beneficio = 0;
	Y.benef_est = calculo_voraz(objetos, M, Y.k, Y.pesoA+Y.pesoB, Y.beneficio);
	Y.cogidos = 0;

	PriorityQueue<Nodo, std::greater<Nodo>> cola;
	cola.push(Y);
	benef_mejor = -1;
	// búsqueda mientras pueda haber algo mejor
	while (!cola.empty() && cola.top().benef_est > benef_mejor) {
		Y = cola.top(); cola.pop();

			Nodo X(Y);
			++X.k;
				// probamos a meter el objeto en la mochila A
			if (Y.pesoA + objetos[X.k].tiempo <= M) {
				X.solA[X.k] = true;
				X.solB[X.k] = false;
				X.pesoA = Y.pesoA + objetos[X.k].tiempo;
				X.pesoB = Y.pesoB;
				X.beneficio = Y.beneficio + objetos[X.k].puntuacion;
				X.benef_est = Y.benef_est;
				X.cogidos = Y.cogidos + 1;
				if (X.k == N - 1) {
					//sol_mejor = X.solA; 
					benef_mejor = X.beneficio;
					cogidos = X.cogidos;
				}
				else { cola.push(X); }
			}
			// probamos a meter el objeto en la mochila B
			if (Y.pesoB + objetos[X.k].tiempo <= M) {
				X.solA[X.k] = false;
				X.solB[X.k] = true;
				X.pesoA = Y.pesoA;
				X.pesoB = Y.pesoB + objetos[X.k].tiempo;
				X.beneficio = Y.beneficio + objetos[X.k].puntuacion;
				X.benef_est = Y.benef_est;
				X.cogidos = Y.cogidos + 1;
				if (X.k == N - 1) {
					//sol_mejor = X.solB;
					benef_mejor = X.beneficio;
					cogidos = X.cogidos;
				}
				else { cola.push(X); }
			}
			// probar a no meter el objeto
			X.benef_est = calculo_voraz(objetos, M, X.k, Y.pesoA+Y.pesoB, Y.beneficio);
			if (X.benef_est > benef_mejor) {
				X.pesoA = Y.pesoA;
				X.pesoB = Y.pesoB;
				X.beneficio = Y.beneficio;
				X.solA[X.k] = false;
				X.solB[X.k] = false;
				if (X.k == N - 1) {
					//sol_mejor = X.sol; 
					benef_mejor = X.beneficio;
					cogidos = X.cogidos;
				}
				else { cola.push(X); }
			}
		}
	//}
}

class Casanova {
public:
	Casanova(int canciones, int minutos, std::vector<Cancion>  &datos) :resultado(0) {
		//std::vector<bool>cancionesElegidas = std::vector<bool>(canciones); 
		int beneficio = 0;
		int cogidos = 0;

		//ordenamos en funcion del beneficio por minuto de la cancion
		std::sort(datos.begin(), datos.end());

		mochila_rp(datos, minutos, beneficio,cogidos);/*, cancionesElegidas*/
		
		resultado = beneficio;
	}
	void Resultado(std::ostream& sout) {
		sout << resultado;
	}
private:
	int resultado;
};

// Orden O()
bool resuelveCaso() {

	int canciones = 0;
	int minutos = 0;

	std::cin >> canciones;
	if (canciones == 0) return false;

	std::cin >> minutos;

	//if (std::cin.fail()) return false;

	std::vector<Cancion> datos = std::vector<Cancion>(canciones);

	for (int i = 0; i < canciones; i++)
	{
		Cancion dato;
		std::cin >> dato.tiempo >> dato.puntuacion;
		datos[i] = dato;
	}

	Casanova cN =Casanova(canciones, minutos, datos);

	cN.Resultado(std::cout);
	std::cout << std::endl;

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos40.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCaso()) {};
	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}

