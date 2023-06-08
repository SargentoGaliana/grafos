/*
 * Grafo.cpp
 *
 *  Created on: 8 nov 2022
 *      Author: davidt
 */

#include "Grafo.h"

Grafo::Grafo(int nVertices, string *vertices, int nAristas, Arista *aristas) {
	this->nVertices = nVertices;
	for (int i = 0; i < nVertices; i++)
		this->vertices[i] = vertices[i];

	this->nAristas = nAristas;
	for (int i = 0; i < nAristas; i++)
		this->aristas[i] = aristas[i];

	generarMatrizAdyacencia();
	//mostrarGrafo();
}

int Grafo::indexOf(string vertice, string *vertices, int nVertices) {

	int index = -1;

	for (int i = 0; i < nVertices; i++) {
		if (vertices[i] == vertice)
			index = i;
	}

	return index;

}

void Grafo::generarMatrizAdyacencia() {

	for (int fil = 0; fil < nVertices; fil++)
		for (int col = 0; col < nVertices; col++) {
			if (fil == col)
				matrizAdy[fil][col] = 0;
			else
				matrizAdy[fil][col] = INFINITO;
		}

	for (int i = 0; i < this->nAristas; i++) {

		string orig = aristas[i].origen;
		string dest = aristas[i].destino;
		float coste = aristas[i].coste;

		int origIndex = indexOf(orig, vertices, nVertices);
		int destIndex = indexOf(dest, vertices, nVertices);

		matrizAdy[origIndex][destIndex] = coste;
		matrizAdy[destIndex][origIndex] = coste;

	}

}

void Grafo::mostrarGrafo() {

	cout << "Vertices: " << endl;
	for (int i = 0; i < nVertices; i++) {
		cout << vertices[i] << endl;
	}

	cout << endl;

	cout << "Aristas:" << endl;
	for (int i = 0; i < nAristas; i++) {
		Arista arista = aristas[i];
		cout << arista.origen << " " << arista.destino << " " << arista.coste
				<< endl;
	}

	cout << endl;

	cout << "Matriz de adyacencia:" << endl;
	for (int fil = 0; fil < nVertices; fil++) {
		for (int col = 0; col < nVertices; col++) {
			cout << matrizAdy[fil][col] << " ";
		}
		cout << endl;
	}

}

void Grafo::floyd() {

	//Copiamos la matriz de adyacencia en matrizC
	for (int fil = 0; fil < nVertices; fil++) {
		for (int col = 0; col < nVertices; col++) {
			matrizC[fil][col] = matrizAdy[fil][col];
		}
	}

	// Inicializamos la matriz P a -1 IMPORTANTE
	for (int fil = 0; fil < nVertices; fil++)
		for (int col = 0; col < nVertices; col++)
			matrizP[fil][col] = -1;

	for (int k = 0; k < nVertices; k++)
		for (int i = 0; i < nVertices; i++)
			for (int j = 0; j < nVertices; j++) {
				if (matrizC[i][k] + matrizC[k][j] < matrizC[i][j]) {
					matrizC[i][j] = matrizC[i][k] + matrizC[k][j];
					matrizP[i][j] = k;
				}
			}

}

list<string> Grafo::camino(string origen, string destino) {

	floyd();
	int i = indexOf(origen, vertices, nVertices);
	int j = indexOf(destino, vertices, nVertices);
	list<string> camino;
	camino.push_back(vertices[i]);
	caminoR(i, j, camino);
	camino.push_back(vertices[j]);

	return camino;
}

void Grafo::caminoR(int i, int j, list<string> &camino) {
	int k;
	k = matrizP[i][j];
	if (k != -1) {
		caminoR(i, k, camino);
		camino.push_back(vertices[k]);
		caminoR(k, j, camino);
	}
}

float Grafo::costeTotal(string origen, string destino) {

	int ori = indexOf(origen, vertices, nVertices);
	int dest = indexOf(destino, vertices, nVertices);
	return matrizC[ori][dest];
}

Grafo Grafo::prim() {

	Grafo gres;
	Arista arista;
	string vertice;
	float mAdy[MAX_VERTICES][MAX_VERTICES]; // Se usara para marcar las aristas ya seleccionadas

	// Inicializacion de mAdy
	for (int fil = 0; fil < nVertices; fil++)
		for (int col = 0; col < nVertices; col++)
			mAdy[fil][col] = matrizAdy[fil][col];

	gres.insertarVertice(vertices[0]); // Se inserta un vertice cualquiera

	while (gres.nVertices < nVertices) {
		arista = primSeleccion(gres, mAdy);
		gres.insertarArista(arista);
		gres.insertarVertice(arista.destino);
	}

	gres.generarMatrizAdyacencia();
	return gres;

}

Grafo::Grafo() {
	nAristas = 0;
	nVertices = 0;
}

void Grafo::insertarArista(Arista arista) {
	aristas[nAristas] = arista;
	nAristas++;
}

void Grafo::insertarVertice(string vertice) {
	vertices[nVertices] = vertice;
	nVertices++;
}

Arista Grafo::primSeleccion(Grafo gres, float mAdy[][MAX_VERTICES]) {

	Arista arista;
	arista.coste = INFINITO;

	for (int fil = 0; fil < nVertices; fil++) {

		if (indexOf(vertices[fil], gres.vertices, gres.nVertices) != -1) {

			for (int col = 0; col < nVertices; col++) {

				if (indexOf(vertices[col], gres.vertices, gres.nVertices) == -1
						&& arista.coste > mAdy[fil][col]) {

					arista.coste = mAdy[fil][col];
					arista.origen = vertices[fil];
					arista.destino = vertices[col];

				}

			}

		}

	}

	int i = indexOf(arista.origen, vertices, nVertices);
	int j = indexOf(arista.destino, vertices, nVertices);
	mAdy[i][j] = INFINITO;

	return arista;
}

float Grafo::costeAristas() {
	float total = 0;

	for (Arista a : aristas)
		total += a.coste;

	return total;
}

Grafo::~Grafo() {

}

