#ifndef MIN_COST_H
#define MIN_COST_H

#include "graph/Graph.h"

std::vector<std::pair<std::vector<Edge*>, int>> getMinCostPaths(Graph* graph, Vertex * src, Vertex * dst);

void reconstructPath(std::vector<Edge*> path);
int calculateCostOfPath(std::vector<Edge*> path);

#endif