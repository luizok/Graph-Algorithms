#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphalgs.h"
#include "graph.h"


void intializeVector(int* f, int value, int n) {

	for(int i=0; i < n; i++)
		f[i] = value;
}

void printPairs(int* v, int n) {

	printf("  Node |  Father\n\n");
	for(int i=0; i < n; i++)
		printf("  %2d   |    %2d\n", i, v[i]);

	printf("\n* -1 = root\n* -2 = unreachable\n\n");
}

void breadthFirstSearch(GRAPH* g, int vertex) {

	int queue[g->vertexNum];
	int fatherOf[g->vertexNum];
	int* wasVisited = calloc(g->vertexNum, sizeof(int));
	int add = 0;
	int rem = 0;
	int curr; //Current Vertex

	intializeVector(queue, -2, g->vertexNum);	
	intializeVector(fatherOf, -2, g->vertexNum);

	fatherOf[vertex] = -1;
	queue[add++] = vertex;
	wasVisited[vertex] = 1;

	while(rem < g->vertexNum) {
		curr = queue[rem++];

		if(curr < 0)
			break;

		for(int j=0; j < g->vertexNum; j++) {
			if(0 < g->adjMatrix[curr][j] && g->adjMatrix[curr][j] < INFINITY) 
				if(!wasVisited[j]) {
					queue[add++] = j;
					wasVisited[j] = 1;
					fatherOf[j] = curr;
				}
		}
	}

	printPairs(fatherOf, g->vertexNum);	
}

void dfsRec(GRAPH* g, int vertex, int n, int* visited, int* father) {

	visited[vertex] = 1;

	for(int j=0; j < n; j++)
		if(0 < g->adjMatrix[vertex][j] && g->adjMatrix[vertex][j] < INFINITY)
			if(!visited[j]) { 
				father[j] = vertex;
				dfsRec(g, j, n, visited, father);
			}
}

void depthFirstSearch(GRAPH* g, int vertex) {

	int* wasVisited = calloc(g->vertexNum, sizeof(int));
	int fatherOf[g->vertexNum];

	intializeVector(fatherOf, -2, g->vertexNum);

	fatherOf[vertex] = -1;

	//for(int i=0; i < g->vertexNum; i++)
	dfsRec(g, vertex, g->vertexNum, wasVisited, fatherOf);

	printPairs(fatherOf, g->vertexNum);
}

int allInPartition(int* partition, int n) {

	for(int i=0; i < n; i++)
		if(partition[i] == 0)
			return 0;

	return 1;
}

int heapIsEmpty(int* heap, int n) {

	for(int i=0; i < n; i++)
		if(heap[i] == 1)
			return 0;

	return 1;
}

int extractMin(int* heap, double* dist, int n) {

	int minIndex = -1;
	double min = INFINITY;

	for(int i=0; i < n; i++)
		if(heap[i] == 1)
			if(dist[i] < min) {
				min = dist[i];
				minIndex = i;			
			}

	return minIndex;
}

int printPath(int dest, int* father) {

	if(father[dest] == -1)
		printf("%2d ", dest);
	else if(father[dest] == -2)
		printf("UNREACHABLE");
	else {
		printPath(father[dest], father);
		printf("  ->  %2d", dest);
	}
}

void minimumPathDijkstra(GRAPH* g, int vertex) {

	int heap[g->vertexNum];
	int fatherOf[g->vertexNum];
	double distance[g->vertexNum];
	int curr;

	intializeVector(heap, 1, g->vertexNum);
	intializeVector(fatherOf, -2, g->vertexNum);

	for(int i=0; i < g->vertexNum; i++)
		distance[i] = INFINITY;

	fatherOf[vertex] = -1;
	distance[vertex] = 0;

	while(!heapIsEmpty(heap, g->vertexNum)) {
		curr = extractMin(heap, distance, g->vertexNum);

		if(curr < 0) break;

		heap[curr] = 0;

		for(int j=0; j < g->vertexNum; j++)
			if(j != curr && 0 < g->adjMatrix[curr][j])
				if(distance[curr] + g->adjMatrix[curr][j] < distance[j]) {
					distance[j] = distance[curr] + g->adjMatrix[curr][j];
					fatherOf[j] = curr;
				}
	
	}
	
		for(int i=0; i < g->vertexNum; i++) {
			printf("d(%2d, %2d) = ", vertex, i);
			printf(" %6.2lf = ", distance[i]);
			printPath(i, fatherOf);
			printf("\n");
		}
}

void minimumPathFloydWarshall(GRAPH* g, int vertex) {

	double dist[g->vertexNum][g->vertexNum];

	for(int i=0; i < g->vertexNum; i++)
		for(int j=0; j < g->vertexNum; j++) {
			if(i == j)
				dist[i][j] = 0;
			else if(g->adjMatrix[i][j] == 0)
				dist[i][j] = INFINITY;
			else
				dist[i][j] = g->adjMatrix[i][j];
		}

	for(int k=0; k < g->vertexNum; k++)
		for(int i=0; i < g->vertexNum; i++)
			for(int j=0; j < g->vertexNum; j++)
				if(dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];

	for(int i=0; i < g->vertexNum; i++) {
		printf("d(%2d, %2d) = ", vertex, i);
		printf("%6.2f\n", dist[vertex][i]);	
	}
}

void minimumSpanningTree(GRAPH* g, int vertex) {

	int* inPartition = calloc(g->vertexNum, sizeof(int));
	int minRow, minCol;
	double min;
	double minSize = 0.;
	
	inPartition[vertex] = 1;

	while(!allInPartition(inPartition, g->vertexNum)) {
		min = INFINITY;
		minRow = -1;
		minCol = -1;
		
		for(int i=0; i < g->vertexNum; i++)
			if(inPartition[i])
				for(int j=0; j < g->vertexNum; j++)
					if(!inPartition[j])
						if(0 < g->adjMatrix[i][j] && g->adjMatrix[i][j] < min) {
							min = g->adjMatrix[i][j];
							minRow = i;
							minCol = j;
						}		

		if(minCol < 0) {
			printf("The graph has at least one node that is disconnected\n");
			break;
		}else {
			inPartition[minCol] = 1;
			printf("e(%2d, %2d) = %.2lf\n", minRow, minCol, g->adjMatrix[minRow][minCol]);
			minSize += g->adjMatrix[minRow][minCol];

			if(allInPartition(inPartition, g->vertexNum))
				printf("Minimum Spanning Tree value = %.2lf\n", minSize);
		}
	}
}

