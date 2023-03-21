#ifndef DATASET_LOADER_H
#define DATASET_LOADER_H


#include "graph/Graph.h"
#include "Station.h"

#define DEFAULT_NETWORK_PATH "../dataset/network.csv"
#define DEFAULT_STATIONS_PATH "../dataset/stations.csv"

Graph* loadDataset(std::string network_path, std::string stations_path);

#endif