// By: Gonçalo Leão

#ifndef PROJETO_DA_1_GRAPH_H
#define PROJETO_DA_1_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

#include "StationSegment.h"

using namespace std;

class Graph {
public:
    ~Graph();
    Station *findStation(const string &name) const;
    bool addStation(const string &name, const string &district, const string &municipality, const string &township, const string &line);
    bool addSegment(const string &sourc, const string &dest, double w, int serv);
    bool addBidirectionalSegment(const string &sourc, const string &dest, double w, int serv);
    int getNumStation() const;
    vector<Station *> getStationSet() const;
    void printStations() const;
    void printNetwork() const;
    int findStationIdx(const string &name) const;

    void printTopK(const string &filter, int k);

    double edmondsKarp(string source, string target);
    bool edmondsKarpBFS(Station* v, Station* sink);
    void updateFlow(Station* source, Station* target, double bottleneck);
    double findMinResidual(Station* source, Station* target);
    void testVisit(std::queue<Station*> &q, Segment* e, Station* w, Station* sink, double residual);

    double edmondsKarpMoney(string source, string target);
    void updateFlowMoney(Station* source, Station* target, double bottleneck);
    vector<Station*> kruskal();
    vector<Station*> dijkstra(string source, string dest);

    void maxTrainsMinCost(string source, string target);
    int maxTrainsInStation(string station);
    void pairs();
    void sinks();

protected:
    vector<Station *> StationSet;    // Station set
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //PROJETO_DA_1_GRAPH_H