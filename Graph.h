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
    std::vector<Station *> getStationSet() const;
    void printStations() const;
    void printNetwork() const;
    int findStationIdx(const string &name) const;
    void printTopK(const string &filter, int k);
    int edmondsKarp(string source, string target);
    bool edmondsKarpBFS(string s, string t);
    int maxTrainsInStation(string station);
    void pairs();
    void sinks();

    //Test
    void DFS(string node);
    void DFSUtil(string station, unordered_map<string, bool>& visited);
    double dinicMaxFlow(const string& source, const string& sink);

    void testAndVisit(std::queue<Station*> &q, Segment *e, Station *w, double residual);
    bool findAugmentingPath(Station *s, Station *t);
    double findMinResidualAlongPath(Station *s, Station *t);
    void augmentFlowAlongPath(Station *s, Station *t, double f);
    double edmondsKarpStor(string source, string target);


protected:
    vector<Station *> StationSet;    // Station set
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //PROJETO_DA_1_GRAPH_H