//Diego Acuña Berger
//TAIS03
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <climits>
#include <queue>
#include "PriorityQueue.h"
using namespace std;


class Conferencia{
public:
    Conferencia(){}
    
    Conferencia(int i, int f){
        ini = i;
        fin = f;
    }
    bool operator<(Conferencia const & b) const{
        return ini < b.ini;
    }
    bool operator>(Conferencia const & b) const {
        return fin > b.fin;
    }
    int getFin() const {
        return fin;
    }
    int getIni() const {
        return ini;
    }
private:
    int ini;
    int fin;
};

// O(n)
int resolver(vector<Conferencia> const & v_conferencia){
    PriorityQueue<int, std::less<int>> salas;
    for(int i = 0; i < v_conferencia.size(); ++i){
        if(salas.empty() || salas.top() > v_conferencia[i].getIni()){
            salas.push(v_conferencia[i].getFin());
        }
        else if(salas.top() <= v_conferencia[i].getIni()){
            salas.pop();
            salas.push(v_conferencia[i].getFin());
        }
        
    }
    return salas.size();
}

// Orden O(n·log(n))
bool resuelveCaso() {
	int n;
	cin >> n;
	if (n == 0) return false;
	int ini, fin;
	vector<Conferencia> v_conferencia;
	for (int i = 0; i < n; ++i) {
		cin >> ini >> fin;
		Conferencia c = Conferencia(ini, fin);
		v_conferencia.push_back(c);
	}
	std::less<Conferencia> l;
	sort(v_conferencia.begin(), v_conferencia.end(), l);// O(n·log(n))
	int sol = resolver(v_conferencia);// O(n)
	cout << sol << '\n';
	return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("/Users/usuario/Documents/EDA/EDA/casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while(resuelveCaso());
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

