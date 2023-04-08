#include "LineFailures.h"
#include <iostream>
#include <tuple>
#include <algorithm>
#include <cmath>

/**
 * Computes the maximum number of trains that can be transported from src to dst after removing segments of the network
 * Time Complexity: O(n) being n the number of segments to remove
 * @param graph The graph representing the network
 * @param segmentsToRemove The segments to remove
 * @param src A pointer to the source vertex
 * @param dst A pointer to the destination vertex
 * @return The maximum number of trains that can be transported from src to dst after removing segments of the network
 */
int maximumTrainsReducedConnectivity(Graph *graph, std::vector<Edge *> segmentsToRemove, Vertex * src, Vertex * dst) {
    graph->resetVisited();
    graph->resetFlow();

    std::vector<std::tuple<std::string, std::string, int, std::string>> segments;
    segments.reserve(segmentsToRemove.size());
    for (auto segment : segmentsToRemove) {
        segments.emplace_back(
            segment->getOrigin()->getStation().getName(),
            segment->getDest()->getStation().getName(),
            segment->getWeight(),
            segment->getService());

        segment->getDest()->removeEdge(segment->getOrigin()->getStation());
        segment->getOrigin()->removeEdge(segment->getDest()->getStation());
    }

    int maxTrains = graph->edmondsKarp(src, dst);

    for (auto segment : segments) {
        graph->addBidirectionalEdge(
            std::get<0>(segment), 
            std::get<1>(segment), 
            std::get<2>(segment), 
            std::get<3>(segment)
            );
    }
    return maxTrains;
}

/**
 * Computes the maximum number of trains that every station can receive after removing segments of the network using Edmonds-Karp algorithm
 * Time Complexity: O(|V|²|E|²) being |V| the number of vertices and |E| the number of edges
 * @param graph The graph representing the network
 * @param segmentToRemove The segment to remove
 * @return A map with the maximum number of trains that every station can receive after removing segments of the network
 */
std::unordered_map<Vertex*, int> capacityOnFailureAllStations(Graph * graph, Edge * segmentToRemove){
    graph->resetVisited();
    graph->resetFlow();

    std::tuple<std::string, std::string, int, std::string> segment = std::make_tuple(
            segmentToRemove->getOrigin()->getStation().getName(),
            segmentToRemove->getDest()->getStation().getName(),
            segmentToRemove->getWeight(),
            segmentToRemove->getService());

    segmentToRemove->getDest()->removeEdge(segmentToRemove->getOrigin()->getStation());
    segmentToRemove->getOrigin()->removeEdge(segmentToRemove->getDest()->getStation());

    std::unordered_map<Vertex*, int> result_map;

    for (Vertex * vertex : graph->getVertexSet()) {
        int result = graph->edmondsKarpSinkOnly(vertex);
        result_map.insert({vertex, result});
        graph->resetVisited();
        graph->resetFlow();
    }

    graph->addBidirectionalEdge(
        std::get<0>(segment), 
        std::get<1>(segment), 
        std::get<2>(segment), 
        std::get<3>(segment)
        );

    return result_map;
}

/**
 * Computes the most affected stations on segment failure, i.e. the stations that lose the most trains after removing a segment
 * Time Complexity: O(|V|²|E|²) being |V| the number of vertices and |E| the number of edges
 * @param graph The graph representing the network
 * @param segmentToRemove The segment to remove
 * @return A vector of pairs of pairs of pointers to vertices and pairs of integers, where the first pair is the vertex and the second pair is the number of trains that the station can receive before and after removing the segment
 */
std::vector<std::pair<Vertex *, std::pair<int,int>>> mostAffectedStationsOnSegmentFailure(Graph * graph, Edge * segmentToRemove){
    std::vector<std::pair<Vertex *, std::pair<int,int>>> result;
    
    std::unordered_map<Vertex*,int> normalNetworkFlows;

    for (Vertex * vertex : graph->getVertexSet()){
        normalNetworkFlows.insert({vertex, graph->edmondsKarpSinkOnly(vertex)});
    }

    std::unordered_map<Vertex*,int> reducedNetwork = capacityOnFailureAllStations(graph, segmentToRemove);

    for (auto it : reducedNetwork) {
        auto it2 = normalNetworkFlows.find(it.first);
        if (it2 == normalNetworkFlows.end()) {
            std::cout << "Something went wrong while calculating differences...\n";
            continue;
        }
        int value_before = (*it2).second;
        int value_after = it.second;

        result.push_back({it.first, {value_before, value_after}});
    }
    std::sort(result.begin(), result.end(), [](const auto& it1, const auto& it2){
        return abs(it1.second.first - it1.second.second) > abs(it2.second.first - it2.second.second);
    });
    
    return result;
}