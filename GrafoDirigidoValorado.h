//
//  GrafoDirigidoValorado.h
//
//  Implementación de grafos dirigidos valorados
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef GRAFODIRIGIDOVALORADO_H_
#define GRAFODIRIGIDOVALORADO_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

template <typename Valor>
class AristaDirigida_impl;

template <typename Valor>
class AristaDirigida {
public:
    AristaDirigida();
    AristaDirigida(size_t v, size_t w, Valor valor);
    size_t from() const;
    size_t to() const;
    Valor valor() const;
    void print(std::ostream & o = std::cout) const;
private:
    std::shared_ptr<AristaDirigida_impl<Valor>> pimpl;
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream & o, AristaDirigida<Valor> const& ar){
    ar.print(o);
    return o;
}

template <typename Valor>
inline bool operator<(AristaDirigida<Valor> const& a, AristaDirigida<Valor> const& b)
{
    return a.valor() < b.valor();
}


template <typename Valor>
using AdysDirVal = std::vector<AristaDirigida<Valor>>;  // lista de adyacentes a un vértice

template <typename Valor>
class GrafoDirigidoValorado {
public:
   
    /**
     * Crea un grafo con V vértices.
     */
    GrafoDirigidoValorado(size_t v) : _V(v), _E(0), _adj(_V) {}
    
    /**
     * Devuelve el número de vértices del grafo.
     */
    size_t V() const { return _V; }
    
    /**
     * Devuelve el número de aristas del grafo.
     */
    size_t E() const { return _E; }
    
    /**
     * Añade la arista dirigida v-w al grafo.
     * @throws invalid_argument si algún vértice no existe
     */
    void ponArista(AristaDirigida<Valor> arista);
    
    /**
     * Comprueba si hay arista de v a w.
     */
    bool hayArista(size_t v, size_t w) const;
    
    /**
     * Devuelve la lista de adyacencia de v.
     * @throws invalid_argument si v no existe
     */
    AdysDirVal<Valor> const& adj(size_t v) const;
    
	/**
	* Devuelve el grafo dirigido inverso.
	*/
	GrafoDirigidoValorado<Valor> reverse() const;

	/**
     * Muestra el grafo en el stream de salida o
     */
    void print(std::ostream& o = std::cout) const;
    
private:
    size_t _V;   // número de vértices
    size_t _E;   // número de aristas
    std::vector<AdysDirVal<Valor>> _adj;   // vector de listas de adyacentes
    
};

/**
 * Para mostrar grafos por la salida estándar.
 */
template <typename Valor>
inline std::ostream& operator<<(std::ostream& o,const GrafoDirigidoValorado<Valor>& g){
    g.print(o);
    return o;
}


// IMPLEMENTACIÓN

template <typename Valor>
AristaDirigida<Valor>::AristaDirigida()
: pimpl(nullptr) {}

template <typename Valor>
AristaDirigida<Valor>::AristaDirigida(size_t v, size_t w, Valor valor)
: pimpl(std::make_shared<AristaDirigida_impl<Valor>>(v, w, valor)) {}

template <typename Valor>
size_t AristaDirigida<Valor>::from() const { return pimpl->from(); }

template <typename Valor>
size_t AristaDirigida<Valor>::to() const { return pimpl->to(); }

template <typename Valor>
Valor AristaDirigida<Valor>::valor() const { return pimpl->valor(); }

template <typename Valor>
void AristaDirigida<Valor>::print(std::ostream & o) const { pimpl->print(o); }


template <typename Valor>
class AristaDirigida_impl {
public:
    AristaDirigida_impl(size_t v, size_t w, Valor valor) : v(v), w(w), _valor(valor) {};
    size_t from() const { return v; }
    size_t to() const { return w; }
    Valor valor() const { return _valor; }
    void print(std::ostream& o) const {
        o << "(" << v << ", " << w << ", " << _valor << ")";
    }
private:
    size_t v, w;
    Valor _valor;
};


template <typename Valor>
void GrafoDirigidoValorado<Valor>::ponArista(AristaDirigida<Valor> arista) {
    size_t v = arista.from();
    size_t w = arista.to();
    if (v >= _V || w >= _V) throw std::invalid_argument("Vertice inexistente");
    ++_E;
    _adj[v].push_back(arista);
}

template <typename Valor>
bool GrafoDirigidoValorado<Valor>::hayArista(size_t v, size_t w) const {
    for (auto a : _adj[v])
        if (a.to() == w) return true;
    return false;
}

template <typename Valor>
AdysDirVal<Valor>  const& GrafoDirigidoValorado<Valor>::adj(size_t v) const {
    if (v >= _V) throw std::invalid_argument("Vertice inexistente");
    return _adj[v];
}

template <typename Valor>
GrafoDirigidoValorado<Valor> GrafoDirigidoValorado<Valor>::reverse() const {
	GrafoDirigidoValorado R(_V);
	for (auto v = 0; v < _V; ++v) {
		for (auto a : _adj[v]) {
			R.ponArista(AristaDirigida<Valor>(a.to(), a.from(), a.valor()));
		}
	}
	return R;
}

template <typename Valor>
void GrafoDirigidoValorado<Valor>::print(std::ostream& o) const {
    o << _V << " vértices, " << _E << " aristas\n";
    for (auto v = 0; v < _V; ++v) {
        o << v << ": ";
        for(auto a : _adj[v]) {
            o << a << " ";
        }
        o << "\n";
    }
}


#endif /* GRAFODIRIGIDOVALORADO_H_ */
