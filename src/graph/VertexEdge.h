#ifndef DA_RAILWAYMANAGEMENT_VERTEXEDGE_H
#define DA_RAILWAYMANAGEMENT_VERTEXEDGE_H

#include <vector>
#include "Station.h"

class Edge;

class Vertex {
private:
    Station station;
    std::vector<Edge*> edges;
    bool visited = false;
    bool processing = false;
    unsigned int inDegree;
    Edge* path = nullptr;
    std::vector<Edge*> incoming;

public:
    explicit Vertex(const Station& station);
    const Station& getStation() const;
    std::vector<Edge*> getEdges() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getInDegree() const;
    Edge* getPath() const;
    std::vector<Edge*> getIncoming() const;
    void setStation(const Station& _station);
    void setVisited(bool _visited);
    void setProcessing(bool _processing);
    void setInDegree(unsigned int _inDegree);
    void setPath(Edge* _path);
    Edge* addEdge(Vertex* dest, int weight, const std::string& service);
    bool removeEdge(const Station& dest);

};

class Edge {
private:
    Vertex* origin;
    Vertex* dest;
    int weight;
    Edge* reverse = nullptr;
    int flow;
    std::string service;

public:
    Edge(Vertex* origin, Vertex* dest, int weight, const std::string& service);
    Vertex* getOrigin() const;
    Vertex* getDest() const;
    int getWeight() const;
    Edge* getReverse() const;
    int getFlow() const;
    std::string getService() const;
    void setReverse(Edge* _reverse);
    void setFlow(int _flow);
};

#endif //DA_RAILWAYMANAGEMENT_VERTEXEDGE_H
