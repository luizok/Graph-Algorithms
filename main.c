#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char* argv[]) {

	if(argc < 3) {
		printf("Usage: %s <vertexNum> <isOriented> <hasCycles>\n", argv[0]);
		printf("<vertexNum>  - positive integer - Number of vertices of graph\n");
		printf("<isOriented> -      0 or 1      - Defines if the edges(arcs) of the graph has orientation\n");
		//printf("<hasLoop>  -  0 or 1 - Defines if the graph allows loop edges\n");
		return EXIT_FAILURE;
	}

	GRAPH* g = newGraph((int) atoi(argv[1]), (int) atoi(argv[2]),0);
	
	scanMatrixInputs(g);
	printAdjMatrix(g);

	return EXIT_SUCCESS;
}
