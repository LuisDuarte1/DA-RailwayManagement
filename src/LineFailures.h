#ifndef LINE_FAILURES_H
#define LINE_FAILURES_H

#include "graph/Graph.h"
#include <unordered_map>

int maximumTrainsReducedConnectivity(Graph *graph, std::vector<Edge *> segmentsToRemove, Vertex *src, Vertex *dst);
std::unordered_map<Vertex *, int> capacityOnFailureAllStations(Graph *graph, Edge * segmentToRemove);
std::vector<std::pair<Vertex *, std::pair<int,int>>> mostAffectedStationsOnSegmentFailure(Graph * graph, Edge * segmentToRemove);

#endif