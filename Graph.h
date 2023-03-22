// By: Gonçalo Leão

#ifndef PROJETO_DA_1_GRAPH_H
#define PROJETO_DA_1_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"
#include <stack>

#include "StationSegment.h"

using namespace std;

class Graph {
public:
    Graph(){};
    Graph(const Graph &graph);
    ~Graph();
    Station *findStation(const string &name) const;
    int findStationIdx(const string &name) const;
    int getNumStation() const;
    vector<Station *> getStationSet() const;

    bool addStation(const string &name, const string &district, const string &municipality, const string &township, const string &line);
    bool addSegment(const string &sourc, const string &dest, double w, int serv);
    bool removeBidirectionalSegment(const string& source, const string &dest);
    bool addBidirectionalSegment(const string &sourc, const string &dest, double w, int serv);

    /*Algoritmos*/
    double edmondsKarp(string source, string target);
    bool edmondsKarpBFS(Station* v, Station* sink);
    void updateFlow(Station* source, Station* target, double bottleneck);
    double edmondsKarpMoney(string source, string target);
    void updateFlowMoney(Station* source, Station* target, double bottleneck);
    double findMinResidual(Station* source, Station* target);
    void testVisit(std::queue<Station*> &q, Segment* e, Station* w, Station* sink, double residual);
    vector<Station*> kruskal();
    vector<Station*> dijkstra(string source, string dest);

    void maxTrains(string source, string target); //edmondskarp
    void maxTrainsMinCost(string source, string target); //edmondskarp dijkstra
    void maxTrainsFailure(string source, string target, stack<pair<string, string>> failedSegments); //not tested
    int maxTrainsInStation(string station); //capacidade
    void stationPairs();
    void printTopKHigherBudget(const string &filter, int k);
    ///TODO
    void printTopKMostAffected(stack<Segment*> failedSegments, int k);
protected:
    vector<Station *> StationSet;    // Station set
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //PROJETO_DA_1_GRAPH_H