//============================================================================
// Name        : Grafo.cpp
// Author      : David Trujillo Torres y Jorge Galiana Nieves
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : ADA 22/23 Actividad de Grafos
//============================================================================

#include <iostream>
#include <fstream>
#include <cstring>
#include "Grafo.h"
using namespace std;

typedef struct {
	string origen;
	string destino;
} Pregunta;

void cargarConfiguracion(string ficheroConf, int &nVertices, string *&vertices,
		int &nAristas, Arista *&aristas, int &nPreguntas,
		Pregunta *&preguntas) {

	ifstream archivo(ficheroConf.c_str());
	string linea;

	getline(archivo, linea);
	nVertices = atoi(linea.c_str());
	if (nVertices < 2 || nVertices > 20) { //el num. de vertices debe estar entre 2 y 20
		cout << "Error: el nº. de vertices es incorrecto" << endl;
		archivo.close();
		exit(1);
	}

	vertices = new string[nVertices];

	for (int i = 0; i < nVertices; i++) {
		getline(archivo, linea);
		if (linea.length() <= 15) { //el nombre de los vertices debe ser menor a 15 caracteres
			vertices[i] = linea;
		} else {
			cout << "Error: el nombre de algún vértice es incorrecto" << endl;
			archivo.close();
			exit(1);
		}
	}

	getline(archivo, linea);
	nAristas = atoi(linea.c_str());
	if (nAristas < 1 || nAristas > (nVertices * nVertices)) { //comprobamos el nº de aristas
		cout << "Error: el nº de aristas es incorrecto" << endl;
		archivo.close();
		exit(1);
	}
	aristas = new Arista[nAristas];
	Arista arista;

	for (int i = 0; i < nAristas; i++) {
		getline(archivo, linea);

		arista.origen = strtok((char*) linea.c_str(), " ");
		arista.destino = strtok(NULL, " ");
		arista.coste = atof(strtok(NULL, " "));
		aristas[i] = arista;
	}

	getline(archivo, linea);
	nPreguntas = atoi(linea.c_str());
	if (nPreguntas < 1 || nPreguntas > 10) { //comprobamos el nº de caminos
		cout << "Error: el nº de caminos solicitados es incorrecto" << endl;
		archivo.close();
		exit(1);
	}

	Pregunta pregunta;
	preguntas = new Pregunta[nPreguntas];
	for (int i = 0; i < nPreguntas; i++) {
		getline(archivo, linea);
		pregunta.origen = strtok((char*) linea.c_str(), " ");
		pregunta.destino = strtok(NULL, " ");
		preguntas[i] = pregunta; // Caminos leidos del fichero
	}

	archivo.close();

}

int main() {

	cout << "ADA - Actividad de Grafos 22/23" << endl;

	ofstream salida("datos.out", ios::binary);

	int nVertices;
	string *vertices;

	int nAristas;
	Arista *aristas;

	int nPreguntas;
	Pregunta *preguntas;

	list<string> camino;
	float costeCamino;

	cargarConfiguracion("conexiones.in", nVertices, vertices, nAristas, aristas,
			nPreguntas, preguntas);

	Grafo grafo = Grafo(nVertices, vertices, nAristas, aristas); // @suppress("Ambiguous problem")
	//grafo.mostrarGrafo();

	for (int i = 0; i < nPreguntas; i++) {
		camino = grafo.camino(preguntas[i].origen, preguntas[i].destino);

		for (string vertice : camino) {
			cout << vertice << " ";	// Salida en la consola
			salida << vertice << " ";	// Salida en el fichero
		}

		costeCamino = grafo.costeTotal(camino.front(), camino.back());

		cout << costeCamino << endl;
		salida << costeCamino << endl;
	}

	cout << endl;
	salida << endl;

	Grafo gprim = grafo.prim();
	//gprim.mostrarGrafo();

	float sumaAristas = gprim.costeAristas();
	cout << sumaAristas << endl;
	salida << sumaAristas << endl;

	cout << endl;
	salida << endl;

	for (int i = 0; i < nPreguntas; i++) {
		camino = gprim.camino(preguntas[i].origen, preguntas[i].destino);

		for (string vertice : camino) {
			cout << vertice << " ";	// Salida en la consola
			salida << vertice << " ";	// Salida en el fichero
		}

		costeCamino = gprim.costeTotal(camino.front(), camino.back());

		cout << costeCamino << endl;
		salida << costeCamino << endl;
	}

	salida.close();
	cout << "Fin de la ejecución" << endl;
	return 0;
}
