// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

#include "VertexEdge.h"

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a Station with a given ID.
    */
    Station *findStation(const int &id) const;
    /*
     *  Adds a Station with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a Station with that content already exists.
     */
    bool addStation(const int &id);

    /*
     * Adds a Segment to a graph (this), given the contents of the source and
     * destination vertices and the Segment weight (w).
     * Returns true if successful, and false if the source or destination Station does not exist.
     */
    bool addSegment(const int &sourc, const int &dest, double w, int serv);
    bool addBidirectionalSegment(const int &sourc, const int &dest, double w, int serv);

    int getNumStation() const;
    std::vector<Station *> getStationSet() const;
protected:
    std::vector<Station *> StationSet;    // Station set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the Station with a given content.
     */
    int findStationIdx(const int &id) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif /* DA_TP_CLASSES_GRAPH */