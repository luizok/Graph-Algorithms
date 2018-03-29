#ifndef GRAPHALGS_H
#define GRAPHALGS_H

#include "graph.h"

void breadthFirstSearch(GRAPH* g, int vertex);
void depthFirstSearch(GRAPH* g, int vertex);
void minimumPath(GRAPH* g, int vertex);
void minimumSpanningTree(GRAPH* g, int vertex);

#endif
