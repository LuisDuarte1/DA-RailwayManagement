#ifndef DA_RAILWAYMANAGEMENT_GRAPH_H
#define DA_RAILWAYMANAGEMENT_GRAPH_H

#include <vector>
#include "VertexEdge.h"

class Graph {
private:
    std::vector<Vertex*> vertexSet;
public:
    Vertex* findVertex(const std::string& station) const;
    bool addVertex(const Station& station);
    bool addEdge(const std::string& origin, const std::string& dest, int weight, const std::string& service);
    bool addBidirectionalEdge(const std::string& origin, const std::string& dest, int weight, const std::string& service);
    int getNumVertex() const;
    std::vector<Vertex*> getVertexSet() const;

    // To apply Floyd-Warshall algorithm
    double **distMatrix = nullptr;
    int **pathMatrix = nullptr;
};


#endif //DA_RAILWAYMANAGEMENT_GRAPH_H
