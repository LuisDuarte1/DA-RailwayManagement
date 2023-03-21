#include <iostream>
#include "DatasetLoader.h"

int main(){
    Graph * graph = loadDataset(DEFAULT_NETWORK_PATH, DEFAULT_STATIONS_PATH);
    for(auto i : graph->getVertexSet()){
        std::cout << i->getStation().getName() << "\n";
    }
    return 0; 
}