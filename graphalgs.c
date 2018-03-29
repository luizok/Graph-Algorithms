#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphalgs.h"
#include "graph.h"

void intializeFather(int* father, int n) {

	for(int i=0; i < n; i++)
		father[i] = -1;
}

void printVector(char* vName,int* v, int n) {

	printf("%s = { ", vName);
	for(int i=0; i < n-1; i++)
		printf("%2d, ",v[i]);
	
	printf("%2d }\n", v[n-1]);
}

void breadthFirstSearch(GRAPH* g, int vertex) {

	int queue[g->vertexNum];
	int* wasVisited = calloc(g->vertexNum, sizeof(int));
	int* fatherOf = malloc(g->vertexNum * sizeof(int));
	int add = 0;
	int rem = 0;
	int curr; //Current Vertex
	
	intializeFather(fatherOf, g->vertexNum);
	queue[add++] = vertex;
	wasVisited[vertex] = 1;

	while(rem < g->vertexNum) {
		curr = queue[rem++];

		for(int j=0; j < g->vertexNum; j++) {
			if(0 < g->adjMatrix[curr][j] && g->adjMatrix[curr][j] < INFINITY) 
				if(!wasVisited[j]) {
					queue[add++] = j;
					wasVisited[j] = 1;
					fatherOf[j] = curr;
				}
		}
	}

	printVector("Fila     ", queue, g->vertexNum);
	printVector("Visitado?", wasVisited, g->vertexNum);
	printVector("Pai      ", fatherOf, g->vertexNum);	
}

void depthFirstSearch(GRAPH* g, int vertex) {

}

void minimumPath(GRAPH* g, int vertex) {

}

void minimumSpanningTree(GRAPH* g) {

}
