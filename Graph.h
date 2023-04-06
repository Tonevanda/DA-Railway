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
#include <unordered_set>
#include <map>

#include "StationSegment.h"

using namespace std;

class Graph {
public:
    /**
     * Default constructor for Graph class
     */
    Graph()= default;
    /**
     * Copy Graph constructor. Creates a new Graph object with the same StationSet as the parameter's StationSet
     * @param graph
     */
    Graph(const Graph &graph);
    /**
     * Graph destructor. Deletes the distMatrix and pathMatrix
     */
    ~Graph();
    /**
     * Iterates over the StationSet until it finds a Station with the same name as the parameter.
     * If it does not find such Station, it returns nullptr.
     * @param name
     * @return Station* if there exists a Station with the provided name, nullptr if not.
     * @note Time-complexity -> O(n)
     */
    [[nodiscard]] Station *findStation(const string &name) const;
    /**
     * Iterates over the StationSet until it finds a Station with the same name as the parameter.
     * If it does not find such a Station, it returns -1.
     * @param name
     * @return Index of the Station in the StationSet if there exists a Station with the provided name, -1 if not.
     * @note Time-complexity -> O(n)
     */
    [[nodiscard]] int findStationIdx(const string &name) const;
    /**
     * Return the size of the StationSet.
     * @return Size of StationSet.
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] int getNumStation() const;
    /**
     * Returns a vector equal to the StationSet.
     * @return StationSet
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] vector<Station *> getStationSet() const;
    /**
     * Iterates over the outgoing edges of the Station with the same name as the first parameter and returns its capacity if its destination is the Station with the same name as the second parameter.
     * @param source
     * @param target
     * @return Capacity of the segment, if such a segment exists, -1 otherwise.
     * @note Time-complexity -> O(n)
     */
    [[nodiscard]] int getSegmentCapacity(string source, string target) const;
    /**
     * Iterates over the outgoing edges of the Station with the same name as the first parameter and returns its service if its destination is the Station with the same name as the second parameter.
     * @param source
     * @param target
     * @return Service of the segment, if such a segment exists, -1 otherwise.
     * @note Time-complexity -> O(n)
     */
    [[nodiscard]] int getSegmentService(string source, string target) const;

    /**
     *  Checks if a Station with the name given in the parameter already exists, if not then creates a Station with the parameters given and adds it to the StationSet and adds the line to the set lines.
     * @param name
     * @param district
     * @param municipality
     * @param township
     * @param line
     * @return True if the Station wasn't in the StationSet before, false otherwise.
     * @note Time-complexity -> O(1)
     */
    bool addStation(const string &name, const string &district, const string &municipality, const string &township, const string &line);
    /**
     * Checks if the Station with the name given in the parameter exists, if it does then removes it from the
     * @param name
     * @return
     */
    bool removeStation(const string &name);
    bool addSegment(const string &sourc, const string &dest, double w, int serv);
    bool removeSegment(const string &sourc, const string &dest);
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
    void printTopKHigherBudget(string filter, int k); //2.3
    int maxTrainsInStation(string station); // 2.4
    void maxTrainsMinCost(string source, string target); //edmondskarp dijkstra 3.1
    void maxTrainsFailure(string source, string target, stack<pair<string, string>> failedSegments); //not tested 4.1
    void printTopKMostAffected(string source, string target, stack<pair<string, string>> failedSegments, int k); //4.2

    void topKIncoming(int k);

    vector<Station*> oneGetAdjLine(string line);
    vector<Station*> oneGetAdj();
    void createSuperSource(vector<Station*> sources);
    void removeSuperSource();

    double edmondsKarpArea(string source);
    bool edmondsKarpBFSArea(Station* source, stack<Station*>* end);
    void testVisitArea(std::queue<Station*> &q, Segment* e, Station* w, double residual, stack<Station*>* end);
    double findMinResidualandUpdateFlowArea(Station* s, stack<Station*>* end);
protected:
    vector<pair<string, int>> districtBudget;
    vector<pair<string, int>> municipalityBudget;
    vector<pair<string, int>> townshipBudget;
    vector<Station *> StationSet;    // Station set
    unordered_set<string> lines;         // Different lines
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //PROJETO_DA_1_GRAPH_H