cmake_minimum_required(VERSION 3.23)
project(Projeto_DA_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projeto_DA_1 main.cpp Graph.h Graph.cpp Heap.cpp Heap.h MutablePriorityQueue.h UFDS.cpp UFDS.h VertexEdge.cpp VertexEdge.h reads.h)
