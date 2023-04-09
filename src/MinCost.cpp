#include "MinCost.h"
#include <algorithm>

void graphInitCost(Graph* graph){
    for(auto vertex : graph->getVertexSet()){
        for(auto edge : vertex->getEdges()){
            if(edge->getService() == "ALFA"){
                edge->setCost(4);
            } else {
                edge->setCost(2);
            }
        }
    }
}

void findShortestPath(Graph * graph, Vertex* src, Vertex* dst){
    auto compare = [](const Vertex * v1, const Vertex * v2){
        return v1->getDistance() < v2->getDistance();
    };
    std::priority_queue<Vertex *, std::vector<Vertex*>, decltype(compare)> queue(compare);
    src->setDistance(0);
    for(auto vertex : graph->getVertexSet()){
        if(vertex != src){
            vertex->setPath(nullptr);
            vertex->setDistance(INT_MAX);
        }
    }
    queue.push(src);
    while (queue.size() != 0){
        auto vertex = queue.top();
        queue.pop();
        for (auto edge : vertex->getEdges()){
            if(edge->getCost() == INT_MAX) continue;
            int dist = vertex->getDistance() + edge->getCost();
            if(dist < edge->getDest()->getDistance() && edge->getFlow() < edge->getWeight()){
                edge->getDest()->setDistance(dist);
                edge->getDest()->setPath(edge);
                queue.push(edge->getDest());
            }
        }
    }
}

std::pair<std::vector<Edge*>, bool> getShortestPath(Vertex * dst, Vertex * src){
    std::vector<Edge*> res;
    Edge * path = dst->getPath();
    if(path == nullptr) return {res, false};
    while(path->getOrigin() != src){
        res.push_back(path);
        path = path->getOrigin()->getPath();
        if(path == nullptr) return {res, false};
    }
    res.push_back(path);
    return {res, true};
}

int calculateCostOfPath(std::vector<Edge*> path){
    int res = 0;
    for(auto edge : path){
        res += edge->getCost();
    }
    return res;
}

void reconstructPath(std::vector<Edge*> path){
    for(auto edge : path){
        edge->getDest()->setPath(edge);
    }
}


void sucessiveShortestPath(int & flow_Remaining, std::vector<std::pair<std::vector<Edge*>, int>> & res, std::vector<Edge*> path, 
    Graph * graph, Vertex * src, Vertex * dst, std::vector<std::vector<Edge*>> other_solutions){

    //if the required flow is superior to 1 we need to find the second shortest path and so on
    std::vector<std::vector<Edge*>> possible_paths;
    std::vector<int> path_cost;
    std::vector<int> path_flow;
    //calculate other solutions, again, this could be optimized but it doesnt make a big difference
    for(auto path : other_solutions){
        path_cost.push_back(calculateCostOfPath(path));
        reconstructPath(path);
        path_flow.push_back(graph->findMinResidualAlongPath(src, dst));
    }

    for(auto edge : path){
        int prev_cost = edge->getCost();
        edge->setCost(INT_MAX);
        findShortestPath(graph, src, dst);
        auto path = getShortestPath(dst, src);
        if(!path.second) {
            edge->setCost(prev_cost);
            continue;
        }
        possible_paths.push_back(path.first);
        path_cost.push_back(calculateCostOfPath(path.first));
        path_flow.push_back(graph->findMinResidualAlongPath(src, dst));
        edge->setCost(prev_cost);
    }

    int minIndex = std::distance(path_cost.begin(), std::min_element(path_cost.begin(), path_cost.end()));
    flow_Remaining -= path_flow[minIndex];
    auto minPath = possible_paths[minIndex];
    res.push_back({minPath, path_flow[minIndex]});
    if(flow_Remaining <= 0){
        return;
    }
    possible_paths.erase(possible_paths.begin() + minIndex);
    sucessiveShortestPath(flow_Remaining, res, minPath, graph, src, dst, possible_paths);


}


std::vector<std::pair<std::vector<Edge*>, int>> getMinCostPaths(Graph* graph, Vertex * src, Vertex * dst){
    graphInitCost(graph);
    int networkService = graph->edmondsKarp(src, dst);
    if(networkService == 0) return {};
    graph->resetFlow();
    graph->resetVisited();

    int flow_remaining = networkService;
    std::vector<std::pair<std::vector<Edge*>, int>> res;
    findShortestPath(graph, src, dst);
    auto path = getShortestPath(dst, src);
    int flow = graph->findMinResidualAlongPath(src, dst);
    graph->augmentFlowAlongPath(src, dst, flow);
    flow_remaining -= flow;
    res.push_back({path.first, flow});
    if(flow_remaining <= 0){
        return res;
    }
    sucessiveShortestPath(flow_remaining, res, path.first, graph, src, dst, {});
    return res;
}