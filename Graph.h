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
    Graph()= default;
    Graph(const Graph &graph);
    ~Graph();
    [[nodiscard]] Station *findStation(const string &name) const;
    [[nodiscard]] int findStationIdx(const string &name) const;
    [[nodiscard]] int getNumStation() const;
    [[nodiscard]] vector<Station *> getStationSet() const;
    [[nodiscard]] int getSegmentCapacity(string source, string target) const;
    int getSegmentService(string source, string target) const;

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
    void testVisit(std::queue<Station*> &q, Segment* e, Station* w, double residual);
    vector<Station*> kruskal();
    vector<Station*> dijkstra(string source, string dest);

    void maxTrains(string source, string target); //edmondskarp 2.1
    void stationPairs(); // 2.2
    void printTopKHigherBudget(const string &filter, int k); //2.3
    int maxTrainsInStation(string station); //capacidade 2.4
    void maxTrainsMinCost(string source, string target); //edmondskarp dijkstra 3.1
    void maxTrainsFailure(string source, string target, stack<pair<string, string>> failedSegments); //not tested 4.1
    void printTopKMostAffected(string source, string target, stack<pair<string, string>> failedSegments, int k); //4.2

    void topKIncoming(int k);

    vector<Station*> oneGetAdjLine(string line);
    vector<Station*> oneGetAdj();
    void createSuperSource(vector<Station*> nascentes);

    double edmondsKarpArea(string source);
    bool edmondsKarpBFSArea(Station* source, stack<Station*>* end);
    void testVisitArea(std::queue<Station*> &q, Segment* e, Station* w, double residual, stack<Station*>* end);
    double findMinResidualandUpdateFlowArea(Station* s, stack<Station*>* end);
protected:
    vector<Station *> StationSet;    // Station set
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //PROJETO_DA_1_GRAPH_H