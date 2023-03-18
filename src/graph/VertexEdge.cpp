#include "VertexEdge.h"

Vertex::Vertex(const Station& station) {
    this->station = station;
}

const Station& Vertex::getStation() const {
    return station;
}

std::vector<Edge*> Vertex::getEdges() const {
    return edges;
}

bool Vertex::isVisited() const {
    return visited;
}

bool Vertex::isProcessing() const {
    return processing;
}

unsigned int Vertex::getInDegree() const {
    return inDegree;
}

Edge* Vertex::getPath() const {
    return path;
}

std::vector<Edge*> Vertex::getIncoming() const {
    return incoming;
}

void Vertex::setStation(const Station& _station) {
    this->station = _station;
}

void Vertex::setVisited(bool _visited) {
    this->visited = _visited;
}

void Vertex::setProcessing(bool _processing) {
    this->processing = _processing;
}

void Vertex::setInDegree(unsigned int _inDegree) {
    this->inDegree = _inDegree;
}

void Vertex::setPath(Edge* _path) {
    this->path = _path;
}

Edge* Vertex::addEdge(Vertex* dest, int weight, const std::string& service) {
    Edge* edge = new Edge(this, dest, weight, service);
    edges.push_back(edge);
    dest->incoming.push_back(edge);
    return edge;
}

bool Vertex::removeEdge(const Station& dest) {
    bool removed = false;
    for (auto it = edges.begin(); it != edges.end();) {
        Edge* edge = *it;
        Vertex* v = edge->getDest();
        if (v->getStation() == dest) {
            it = edges.erase(it);
            for (auto it2 = v->incoming.begin(); it2 != v->incoming.end();) {
                if ((*it2)->getOrigin()->getStation() == station) {
                    it2 = v->incoming.erase(it2);
                }
                else it2++;
            }
            delete edge;
            removed = true;
        } else it++;
    }
    return removed;
}

Edge::Edge(Vertex *origin, Vertex *dest, int weight, const std::string &service) {
    this->origin = origin;
    this->dest = dest;
    this->weight = weight;
    this->service = service;
}

Vertex* Edge::getOrigin() const {
    return origin;
}

Vertex* Edge::getDest() const {
    return dest;
}

double Edge::getWeight() const {
    return weight;
}

Edge* Edge::getReverse() const {
    return reverse;
}

int Edge::getFlow() const {
    return flow;
}

std::string Edge::getService() const {
    return service;
}

void Edge::setReverse(Edge* _reverse) {
    this->reverse = _reverse;
}

void Edge::setFlow(int _flow) {
    this->flow = _flow;
}



