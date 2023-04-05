#include "LineFailures.h"
#include <iostream>
#include <tuple>
#include <algorithm>
#include <math.h>

int maximumTrainsReducedConnectivity(Graph *graph, std::vector<Edge *> segmentsToRemove, Vertex * src, Vertex * dst)
{
    graph->resetVisited();
    graph->resetFlow();
    // first we remove every segment on the list
    std::vector<std::tuple<std::string, std::string, int, std::string>> segments;
    segments.reserve(segmentsToRemove.size()); // optimize allocs
    for (auto segment : segmentsToRemove)
    {
        segments.push_back(std::make_tuple(
            segment->getOrigin()->getStation().getName(),
            segment->getDest()->getStation().getName(),
            segment->getWeight(),
            segment->getService()));

        segment->getOrigin()->removeEdge(segment->getDest()->getStation());
    }

    // do the algorithm
    int maxTrains = graph->edmondsKarp(src, dst);

    // add the segments again
    for (auto segment : segments)
    {
        graph->addEdge(
            std::get<0>(segment), 
            std::get<1>(segment), 
            std::get<2>(segment), 
            std::get<3>(segment)
            );
    }
    return maxTrains;
}

std::unordered_map<Vertex*, int> capacityOnFailureAllStations(Graph * graph, Edge * segmentToRemove){
    //reset graph
    graph->resetVisited();
    graph->resetFlow();

    std::tuple<std::string, std::string, int, std::string> segment = std::make_tuple(
            segmentToRemove->getOrigin()->getStation().getName(),
            segmentToRemove->getDest()->getStation().getName(),
            segmentToRemove->getWeight(),
            segmentToRemove->getService());

    segmentToRemove->getOrigin()->removeEdge(segmentToRemove->getDest()->getStation());

    std::unordered_map<Vertex*, int> result_map;

    for(Vertex * vertex : graph->getVertexSet()){
        result_map.insert({vertex, graph->edmondsKarpSinkOnly(vertex)});
        graph->resetVisited();
        graph->resetFlow();
    }

    graph->addEdge(
        std::get<0>(segment), 
        std::get<1>(segment), 
        std::get<2>(segment), 
        std::get<3>(segment)
        );
    
    return result_map;
}

std::vector<std::pair<Vertex *, int>> mostAffectedStationsOnSegmentFailure(Graph * graph, Edge * segmentToRemove){
    std::vector<std::pair<Vertex *, int>> result;
    
    std::unordered_map<Vertex*,int> normalNetworkFlows;

    for(Vertex * vertex : graph->getVertexSet()){
        normalNetworkFlows.insert({vertex, graph->edmondsKarpSinkOnly(vertex)});
    }

    std::unordered_map<Vertex*,int> reducedNetwork = capacityOnFailureAllStations(graph, segmentToRemove);

    for(auto it : reducedNetwork){
        auto it2 = normalNetworkFlows.find(it.first);
        if(it2 == normalNetworkFlows.end()){
            std::cout << "Something went wrong while calculating differences...\n";
            continue;
        }
        result.push_back({it.first, abs((*it2).second - it.second)});
    }
    std::sort(result.begin(), result.end(), [](const auto& it1, const auto& it2){
        return it1.second > it2.second;
    });
    
    return result;
}