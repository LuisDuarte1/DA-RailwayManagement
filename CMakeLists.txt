cmake_minimum_required(VERSION 3.24)
project(DA_RailwayManagement)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/graph)

add_executable(DA_RailwayManagement
        src/graph/Graph.cpp
        src/graph/Graph.h
        src/graph/VertexEdge.cpp
        src/graph/VertexEdge.h
        src/DatasetLoader.cpp
        src/DatasetLoader.h
        src/main.cpp
        src/Station.cpp
        src/Station.h)
