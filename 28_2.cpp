////Victor del Pino
////TAIS37
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <algorithm>
//#include <functional>
//#include <vector>
//#include "Matriz.h"
//
//using namespace std;
//
//class Cometa
//{
//public:
//	Cometa(std::vector<long long int>& tam, std::vector<long long int> const& precios
//		, long long int longitudMax) : sePuede(true), precioMinimo(0), cuerdasMinimas(0), formas(0) {
//
//		// calculamos las formas posibles
//		calcFormas(tam, longitudMax);
//		if (formas > 0) {
//			// calculamos las cuerdas minimas
//			calcMinCuerdas(tam, longitudMax);
//			// calculamos el precio minimo
//			calcPrecio(tam, precios, longitudMax);
//		}
//		else {
//			sePuede = false;
//		}
//	};
//
//	void Resultado() {
//		if (sePuede)
//			std::cout << "SI " << formas << " " << cuerdasMinimas << " " << precioMinimo << std::endl;
//		else
//			std::cout << "NO" << std::endl;
//	}
//
//private:
//	long long int INF = 1000000000000000000;
//	bool sePuede;
//	long long int formas;
//	long long int cuerdasMinimas;
//	long long int precioMinimo;
//
//	void calcFormas(std::vector<long long int> const& tam, long long int longitudMax) {
//		long long int n = tam.size() - 1;
//		Matriz<long long int> mochila(n + 1, longitudMax + 1, 0);
//		mochila[0][0] = 1;
//
//		// rellenar la matriz
//		for (long long int i = 1; i <= n; ++i) {
//			mochila[i][0] = 1;
//			for (long long int j = 1; j <= longitudMax; ++j) {
//				if (tam[i] > j)
//					mochila[i][j] = mochila[i - 1][j];
//				else
//					mochila[i][j] = mochila[i - 1][j] + mochila[i - 1][j - tam[i]];
//			}
//		}
//		formas = mochila[n][longitudMax];
//	}
//
//	void calcMinCuerdas(std::vector<long long int> const& tam, long long int longitudMax) {
//		long long int n = tam.size() - 1;
//		Matriz<long long int> mochila(n + 1, longitudMax + 1, INF);
//		mochila[0][0] = 0;
//
//		// rellenar la matriz
//		for (long long int i = 1; i <= n; ++i) {
//			mochila[i][0] = 0;
//			for (long long int j = 1; j <= longitudMax; ++j) {
//				if (tam[i] > j)
//					mochila[i][j] = mochila[i - 1][j];
//				else
//					mochila[i][j] = min(mochila[i - 1][j], mochila[i - 1][j - tam[i]] + 1);
//			}
//		}
//		cuerdasMinimas = mochila[n][longitudMax];
//	}
//
//	void calcPrecio(std::vector<long long int> const& tam, std::vector<long long int> const& precios, long long int longitudMax) {
//		long long int n = tam.size() - 1;
//		Matriz<long long int> mochila(n + 1, longitudMax + 1, INF);
//		// rellenar la matriz
//		mochila[0][0] = 0;
//		for (long long int i = 1; i <= n; ++i) {
//			mochila[i][0] = 0;
//			for (long long int j = 1; j <= longitudMax; ++j) {
//				if (tam[i] > j)
//					mochila[i][j] = mochila[i - 1][j];
//				else
//					mochila[i][j] = min(mochila[i - 1][j], mochila[i - 1][j - tam[i]] + precios[i]);
//			}
//		}
//		precioMinimo = mochila[n][longitudMax];
//	}
//};
//
//// Resuelve un caso de prueba, leyendo de la entrada la
//// configuración, y escribiendo la respuesta
//bool resuelveCaso() {
//	long long int num = 0;
//	long long int longitudMax = 0;
//
//	std::cin >> num;
//	std::cin >> longitudMax;
//
//	if (std::cin.fail()) return false;
//	//if (numero == 0) return false;
//
//	std::vector<long long int>tam(num + 1);
//	std::vector<long long int>precios(num + 1);
//
//	long long int longitud = 0, precio = 0;
//
//	for (long long int i = 1; i <= num; i++) {
//		std::cin >> longitud;
//		std::cin >> precio;
//
//		tam[i] = longitud;
//		precios[i] = precio;
//	}
//
//	Cometa com(tam, precios, longitudMax);
//	com.Resultado();
//
//	return true;
//}
//
//int main() {
//
//	// ajustes para que cin extraiga directamente de un fichero
//#ifndef DOMJUDGE
//	std::ifstream in("Casos28.txt");
//	auto cinbuf = std::cin.rdbuf(in.rdbuf());
//#endif
//
//	//size_t casos = 0;
//	//std::cin >> casos;
//
//	while (resuelveCaso()) {}
//
//	// para dejar todo como estaba al principio
//#ifndef DOMJUDGE
//	std::cin.rdbuf(cinbuf);
//	system("PAUSE");
//#endif
//
//	return 0;
//}