#include "Graph.h"

Vertex* Graph::findVertex(const std::string &station) const {
    for (Vertex* v : vertexSet) {
        if (v->getStation().getName() == station) {
            return v;
        }
    }
    return nullptr;
}

bool Graph::addVertex(const Station &station) {
    if (findVertex(station.getName()) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(station));
    return true;
}

bool Graph::addEdge(const std::string &origin, const std::string &dest, int weight, const std::string &service) {
    Vertex* v1 = findVertex(origin);
    Vertex* v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, weight, service);
    return true;
}

bool Graph::addBidirectionalEdge(const std::string &origin, const std::string &dest, int weight,
                                 const std::string &service) {
    Vertex* v1 = findVertex(origin);
    Vertex* v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;

    Edge* e1 = v1->addEdge(v2, weight, service);
    Edge* e2 = v2->addEdge(v1, weight, service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex*> Graph::getVertexSet() const {
    return vertexSet;
}