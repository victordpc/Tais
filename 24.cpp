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

using namespace std;

class Pelicula{
public:
    Pelicula(int i, int f){
        ini = i;
        fin = f;
    }
    bool operator<(Pelicula const & b) const{
        return fin < b.fin;
    }
    bool operator>(Pelicula const & b) const {
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
int resolver(vector<Pelicula> const & peliculas){
    
    int contador = 0;
    int hora_fin = 0;

    for(int i = 0; i < peliculas.size(); ++i){
        if(peliculas[i].getIni() >= hora_fin){
            contador++;
            hora_fin = peliculas[i].getFin() + 10;
        }
    }
    return contador;
}

// Orden O(n·log(n))
bool resuelveCaso() {
    int n;
    cin >> n;
    if(n == 0) return false;
    int h, m, d;
    char puntos;
    vector<Pelicula> peliculas;
    for(int i = 0; i < n; ++i){
        cin >> h;
        cin >> puntos;
        cin >> m;
        cin >> d;
        int hora_ini = (h*60) + m;
        int hora_fin = hora_ini + d;
        Pelicula p = Pelicula(hora_ini, hora_fin);
        peliculas.emplace_back(p);
    }
//Primero las peliculas que empiezan antes
    sort(peliculas.begin(),peliculas.end()); // O(n·log(n))
    int sol = resolver(peliculas);// O(n)
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

