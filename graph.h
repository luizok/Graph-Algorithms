#ifndef GRAPHS_H 
#define GRAPHS_H

typedef struct graph {
	int vertexNum;
	double** adjMatrix;
	int isOriented;
	int hasLoop;
} GRAPH;

GRAPH* newGraph(int vertexNum, int isOriented, int hasLoop);
void scanMatrixInputs(GRAPH* g);
void printAdjMatrix(GRAPH* g);

#endif
