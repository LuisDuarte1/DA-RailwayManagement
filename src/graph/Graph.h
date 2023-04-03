#ifndef DA_RAILWAYMANAGEMENT_GRAPH_H
#define DA_RAILWAYMANAGEMENT_GRAPH_H

#include <vector>
#include <queue>
#include <climits>
#include "VertexEdge.h"

class Graph {
private:
    std::vector<Vertex*> vertexSet;
public:
    Vertex* findVertex(const std::string& station) const;
    bool addVertex(const Station& station);
    bool addEdge(const std::string& origin, const std::string& dest, int weight, const std::string& service);
    bool addBidirectionalEdge(const std::string& origin, const std::string& dest, int weight, const std::string& service) ;
    int getNumVertex() const;
    std::vector<Vertex*> getVertexSet() const;
    void testAndVisit(std::queue<Vertex*>& q, Edge* e, Vertex* w, double residual);
    bool findAugmentingPath(Vertex* source, Vertex* dest);
    int findMinResidualAlongPath(Vertex* source, Vertex* dest);
    void augmentFlowAlongPath(Vertex* source, Vertex* dest, int minResidual);
    int edmondsKarp(Vertex* source, Vertex* dest);
    std::pair<std::vector<std::pair<Vertex*, Vertex*>>, int> moreDemandingPairOfStations();
    // To apply Floyd-Warshall algorithm
    double **distMatrix = nullptr;
    int **pathMatrix = nullptr;

    int edmondsKarpSinkOnly(Vertex *dest);
};


#endif //DA_RAILWAYMANAGEMENT_GRAPH_H
