#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"

#ifdef _WIN64
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

void setInfinity(double** matrix, int n) {

	for(int i=0; i < n-1; i++)
		for(int j=i+1; j < n; j++) {
			matrix[i][j] = INFINITY;	
			matrix[j][i] = INFINITY;	
		}
}

double** newAdjMatrix(int n) {

	double** matrix = (double**) malloc(n * sizeof(double*));

	for(int i=0; i < n; i++)
		for(int j=0; j < n; j++)
			matrix[i] = (double*) malloc(n * sizeof(double));
	
	setInfinity(matrix, n);

	return matrix;
}

GRAPH* newGraph(int n, int isOriented, int hasLoop) {
	
	GRAPH* g = (GRAPH*) malloc(sizeof(GRAPH*));
	g->vertexNum = n;
	g->adjMatrix = newAdjMatrix(n);
	g->isOriented = isOriented;
	g->hasLoop = hasLoop;

	return g;
}

void scanMatrixInputs(GRAPH* g) {

	int n = g->vertexNum;
	
	for(int i=0; i < n-1 + g->isOriented; i++)
		for(int j = g->isOriented ? 0 : i+1; j < n; j++) { 
			if(i != j) {
				printf("E[%02d, %02d] = ", i, j);
				scanf("%lf", &g->adjMatrix[i][j]);

				if(!g->isOriented)
					g->adjMatrix[j][i] = g->adjMatrix[i][j];
			}
		}
}

void printAdjMatrix(GRAPH* g) {

	int n = g->vertexNum;

	system(CLEAR_SCREEN);
	for(int i=0; i < n; i++) {
		for(int j=0; j < n; j++)
			printf("%05.2lf      ", g->adjMatrix[i][j]);
		
		printf("\n\n");
	}
	getchar();
} 
