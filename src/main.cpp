#include <iostream>
#include "DatasetLoader.h"

int main(){
    Graph * graph = loadDataset(DEFAULT_NETWORK_PATH, DEFAULT_STATIONS_PATH);
    Vertex* v1 = graph->findVertex("Lisboa Oriente");
    Vertex* v2 = graph->findVertex("Porto Campanhã");
    std::cout << graph->edmondsKarp(v1, v2);



}