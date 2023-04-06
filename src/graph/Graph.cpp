#include <iostream>
#include <unordered_map>
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

void Graph::DFS(Vertex* source) {
    source->setVisited(true);
    for (auto e: source->getEdges()) {
        if (!e->getDest()->isVisited()) {
            DFS(e->getDest());
        }
    }
}

void Graph::resetVisited() {
    for (auto v: vertexSet) {
        v->setVisited(false);
    }
}

void Graph::testAndVisit(std::queue<Vertex *> &q, Edge *e, Vertex *w, double residual) {
    if (!w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

int Graph::findMinResidualAlongPath(Vertex *source, Vertex *dest) {
    int minResidual = INT_MAX;
    for (Vertex* v = dest; v != source;) {
        Edge* e = v->getPath();
        if (e->getDest() == v) {
            minResidual = std::min(minResidual, e->getWeight() - e->getFlow());
            v = e->getOrigin();
        }
        else {
            minResidual = std::min(minResidual, e->getFlow());
            v = e->getDest();
        }
    }
    return minResidual;
}


bool Graph::findAugmentingPath(Vertex *source, Vertex *dest) {
    for (Vertex* v : vertexSet) {
        v->setVisited(false);
    }
    source->setVisited(true);
    std::queue<Vertex*> q;
    q.push(source);
    while (!q.empty() && !dest->isVisited()) {
        Vertex* v = q.front();
        q.pop();
        for (Edge* e : v->getEdges()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        for (Edge* e : v->getIncoming()) {
            testAndVisit(q, e, e->getOrigin(), e->getFlow());
        }
    }
    return dest->isVisited();
}

void Graph::augmentFlowAlongPath(Vertex *source, Vertex *dest, int minResidual) {
    for (Vertex* v = dest; v != source;) {
        Edge* e = v->getPath();
        if (e->getDest() == v) {
            e->setFlow(e->getFlow() + minResidual);
            v = e->getOrigin();
        }
        else {
            e->setFlow(e->getFlow() - minResidual);
            v = e->getDest();
        }
    }
}

int Graph::edmondsKarp(Vertex *source, Vertex *dest) {
    if (source == nullptr || dest == nullptr || source == dest) {
        return -1;
    }

    resetFlow();

    int max_flow = 0;
    while (findAugmentingPath(source, dest)) {
        int pathFlow = INT_MAX;
        pathFlow = findMinResidualAlongPath(source, dest);
        augmentFlowAlongPath(source, dest, pathFlow);
        max_flow += pathFlow;
    }

    resetFlow();

    return max_flow;
}

int Graph::edmondsKarpSinkOnly (Vertex* dest) {
    Station superSourceStation("superSource", "", "", "", "");
    addVertex(superSourceStation);

    for (auto v: vertexSet) {
        if (v->getEdges().size() == 1 && v != dest)
            addEdge(superSourceStation.getName(), v->getStation().getName(), INT_MAX, "");
    }
    Vertex* superSource = findVertex(superSourceStation.getName());
    int maxFlow = edmondsKarp(superSource, dest);
    vertexSet.pop_back(); // delete super source

    return maxFlow;
}

std::pair<std::vector<std::pair<Vertex *, Vertex *>>, int> Graph::moreDemandingPairOfStations() {
    int max = INT_MIN;
    std::vector<std::pair<Vertex *, Vertex *>> maxStations;

    for (auto it1 = vertexSet.begin(); it1 != vertexSet.end(); it1++) {
        for (auto it2 = it1 + 1; it2 != vertexSet.end(); it2++) {
            Vertex *v1 = *it1;
            Vertex *v2 = *it2;
            resetVisited();
            DFS(v1);
            if (v2->isVisited()) {
                int thisFlow = edmondsKarp(v1, v2);
                if (thisFlow > max) {
                    max = thisFlow;
                    maxStations.clear();
                    maxStations.push_back(std::make_pair(v1, v2));
                } else if (thisFlow == max) {
                    maxStations.push_back(std::make_pair(v1, v2));
                }
            }
        }
    }
    return std::make_pair(maxStations, max);
}

void Graph::findTopKMunicipalities(std::vector<std::string> &municipalities, int k) {
    std::unordered_map<std::string, int> municipalityFlows;

    for (auto v1 : vertexSet) {
        for (auto v2 : vertexSet) {
            if (v1 == v2) continue;
            resetVisited();
            DFS(v1);
            if (v2->isVisited()) {
                int thisFlow = edmondsKarp(v1, v2);
                std::string municipality = v2->getStation().getMunicipality();

                municipalityFlows[municipality] += thisFlow;
            }
        }
    }

    auto compare = [](std::pair<std::string, int> &a, std::pair<std::string, int> &b) {
        return a.second > b.second;
    };

    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(compare)> pq(compare);

    for (const std::pair<std::string, int> municipality : municipalityFlows) {
        pq.push(municipality);
        if (pq.size() > k) pq.pop();
    }

    for (int i = 0; i < k; i++) {
        municipalities.push_back(pq.top().first);
        pq.pop();
    }
}

void Graph::findTopKDistricts(std::vector<std::string> &districts, int k) {
    std::unordered_map<std::string, int> districtFlows;

    for (auto v1 : vertexSet) {
        for (auto v2 : vertexSet) {
            if (v1 == v2) continue;
            resetVisited();
            DFS(v1);
            if (v2->isVisited()) {
                int thisFlow = edmondsKarp(v1, v2);
                std::string district = v2->getStation().getDistrict();

                districtFlows[district] += thisFlow;
            }
        }
    }

    auto compare = [](std::pair<std::string, int> &a, std::pair<std::string, int> &b) {
        return a.second > b.second;
    };

    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(compare)> pq(compare);

    for (const std::pair<std::string, int> district : districtFlows) {
        pq.push(district);
        if (pq.size() > k) pq.pop();
    }

    for (int i = 0; i < k; i++) {
        districts.push_back(pq.top().first);
        pq.pop();
    }
}

void Graph::resetFlow() {
    for (auto v : vertexSet) {
        for (auto e : v->getEdges()) {
            e->setFlow(0);
        }
    }
}








