/*
 * Grafo.h
 *
 *  Created on: 8 nov 2022
 *      Author: davidt
 */

#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <list>
using namespace std;

typedef struct {
	string origen;
	string destino;
	float coste;
} Arista;

const int INFINITO = 999999;
const int MAX_VERTICES = 20;
const int MAX_ARISTAS = MAX_VERTICES * MAX_VERTICES;

class Grafo {

private:

	int nVertices;
	string vertices[MAX_VERTICES];

	int nAristas;
	Arista aristas[MAX_ARISTAS];

	float matrizAdy[MAX_VERTICES][MAX_VERTICES];
	float matrizC[MAX_VERTICES][MAX_VERTICES];
	int matrizP[MAX_VERTICES][MAX_VERTICES];

	int indexOf(string vertice, string *vertices, int nVertices);
	void floyd();
	void caminoR(int i, int j, list<string> &camino);
	Arista primSeleccion(Grafo gres, float mAdy[][MAX_VERTICES]);

public:
	Grafo();
	Grafo(int nVertices, string *vertices, int nAristas, Arista *aristas);
	float costeAristas();
	void generarMatrizAdyacencia();
	void insertarArista(Arista arista);
	void insertarVertice(string vertice);
	void mostrarGrafo();
	list<string> camino(string origen, string destino);
	Grafo prim();
	float costeTotal(string origen, string destino);
	virtual ~Grafo();
};

#endif /* GRAFO_H_ */
