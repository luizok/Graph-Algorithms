#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "graphalgs.h"

int main(int argc, char* argv[]) {

	if(argc < 4) {
		printf("Usage: %s <vertexNum> <isOriented> <hasCycles>\n", argv[0]);
		printf("<vertexNum>     -   positive integer   - Number of vertices of graph\n");
		printf("<isOriented>    -        0 or 1        - Defines if the edges(arcs) of the graph has orientation\n");
		printf("<source vertex> -  0 <= N < vertexNum  - Source for search algorithms\n");
		//printf("<hasLoop>  -  0 or 1 - Defines if the graph allows loop edges\n");
		return EXIT_FAILURE;
	}

	GRAPH* g = newGraph((int) atoi(argv[1]), (int) atoi(argv[2]), 0);
	
	printAdjMatrix(g);
	scanMatrixInputs(g);
	printAdjMatrix(g);

	minimumPathFloydWarshall(g, (int) atoi(argv[3]));


	return EXIT_SUCCESS;
}
