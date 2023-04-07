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
#include <map>
#include <set>


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
     * Checks if the Station with the name given in the parameter exists, if it does then removes it from the StationSet.
     * @param name
     * @return True if the Station was in the StationSet before and has been removed, false otherwise.
     * @note Time-complexity -> O(n)
     */
    bool removeStation(const string &name);
    /**
     * Adds a segment between the 2 Stations with the name given as parameters with capacity and service specified in the given parameters.
     * @param sourc
     * @param dest
     * @param w
     * @param serv
     * @return True if the segment was added successfully, false if there was no Station with the name given in the parameters.
     * @note Time-complexity -> O(n)
     */
    bool addSegment(const string &sourc, const string &dest, double w, int serv);
    /**
     * Removes a segment between the 2 Stations with the name given as parameters.
     * @param sourc
     * @param dest
     * @return True if the segment was removed successfully, false if there was no Station with the name given in the parameters.
     * @note Time-complexity -> O(n^2)
     */
    bool removeSegment(const string &sourc, const string &dest);
    /**
     * Removes a bidirectional segment between the 2 Stations with the name given as parameters.
     * @param source
     * @param dest
     * @return True if the segment was removed successfully, false if there was no Station with the name given in the parameters.
     * @note Time-complexity -> O(n)
     */
    bool removeBidirectionalSegment(const string& source, const string &dest);
    /**
     * Adds a bidirectional segment between the 2 Stations with the name given as parameters with capacity and service specified in the given parameters.
     * @param sourc
     * @param dest
     * @param w
     * @param serv
     * @return True if the segment was added successfully, false if there was no Station with the name given in the parameters.
     * @note Time-complexity -> O(n)
     */
    bool addBidirectionalSegment(const string &sourc, const string &dest, double w, int serv);

    /*Algoritmos*/
    /**
     * Implementation of the Edmonds-Karp algorithm. Calculates the maximum flow between two given Station with the name given in the parameters, and sets the flow of the edges accordingly.
     * @param source
     * @param target
     * @return Max Flow between the 2 Stations given in the parameters.
     * @note Time-complexity -> O(VE^2)
     */
    double edmondsKarp(string source, string target);
    /**
     * The Breadth-First Search algorithm used in the implementation of the Edmonds-Karp algorithm.
     * @param v
     * @param sink
     * @return True if the Station specified as the sink has been visited, false otherwise.
     * @note Time-complexity -> O(V+E)
     */
    bool edmondsKarpBFS(Station* v, Station* sink);
    /**
     * Iterates over the path of the target Station until it reaches the source and adds the bottleneck to the flow of every segment of that path.
     * @param source
     * @param target
     * @param bottleneck
     * @note Time-complexity -> O(n)
     */
    void updateFlow(Station* source, Station* target, double bottleneck);
    /**
     * A different implementation of the Edmonds-Karp algorithm. Calculates the maximum flow between two given Station with the name given in the parameters, and sets the flow and cost of the edges accordingly.
     * @param source
     * @param target
     * @return Max Flow between the 2 Station given in the parameters.
     * @note Time-complexity -> O(VE^2)
     */
    double edmondsKarpMoney(string source, string target);
    /**
     * Iterates over the path of the target Station until it reaches the source and adds the bottleneck to the flow of every segment of that path and adds the bottleneck * service of that segment to the cost of said segment.
     * @param source
     * @param target
     * @param bottleneck
     * @note Time-complexity -> O(n)
     */
    void updateFlowMoney(Station* source, Station* target, double bottleneck);
    /**
     * Iterates through the path between the source and the target to determine the bottleneck of said path.
     * @param source
     * @param target
     * @return Bottleneck of the path between the source and the target
     * @note Time-complexity -> O(n)
     */
    double findMinResidual(Station* source, Station* target);
    /**
     * Checks if the Station passed as parameter is not visited and if the residual is greater than 0. If true then adds segment e to w's path, sets w as visited and pushes w to the queue passed as parameter.
     * @param q
     * @param e
     * @param w
     * @param residual
     * @note Time-complexity -> O(1)
     */
    void testVisit(std::queue<Station*> &q, Segment* e, Station* w, double residual);
    /**
     * Implementation of Dijkstra's algorithm to find the minimum costing path between the 2 Station with the name as the given parameters.
     * @param source
     * @param dest
     * @return Vector of Stations that make up the minimum costing path between the specified Stations.
     * @note Time-complexity -> O(V^2)
     */
    vector<Station*> dijkstra(string source, string dest);

    /**
     * Calculates the maximum flow between the 2 Station specified by the names given as parameters and prints the result
     * @param source
     * @param target
     * @note Time-complexity -> O(VE^2)
     */
    void maxTrains(string source, string target); //edmondskarp 2.1
    /**
     * Calculates the flow between every pair of Stations (except its symmetrical) and prints the pairs with the largest flow.
     * @note Time-complexity -> O(V^3E^2)
     */
    void stationPairs(); // 2.2
    /**
     * Links a super-source to every Station that only has one adjacent segment of a single line, for every line. Calls the EdmondsKarpArea class method with each super-source created. Iterates through every segment and adds the cost of each segment to the respective district, municipality and township maps.
     * Creates a vector for each map and sorts them. In the end, prints the first k elements of the desired vector, specified by the filter argument.
     * @param filter
     * @param k
     * @note Time-complexity -> O(n(*VE^2))
     */
    void printTopKHigherBudget(string filter, int k); //2.3
    /**
     * Creates a super-source linked to every station with a single adjacent segment, call the EdmondsKarpArea method with said super-source and counts the flow of the incoming edges to the Station given as parameter.
     * @param station
     * @return Maximum flow to a single station
     * @note Time-complexity -> O(VE^2)
     */
    int maxTrainsInStation(string station); // 2.4
    /**
     * Calls the EdmondsKarpMoney method to set the flow of the segments between the Station source and the Station target. With the flows now set, uses the Dijkstra algorithm to determine the minimum costing path and prints the path and cost.
     * @param source
     * @param target
     * @note Time-complexity -> O(VE^2)
     */
    void maxTrainsMinCost(string source, string target); //edmondskarp dijkstra 3.1
    /**
     * Removes the segments from the graph, specified in the given parameter, calls the edmondsKarp function with source and target specified in the given parameter and adds the removed segments back to the graph.
     * @param source
     * @param target
     * @param failedSegments
     * @note Time-complexity -> O(VE^2)
     */
    void maxTrainsFailure(string source, string target, stack<pair<string, string>> failedSegments); //not tested 4.1
    /**
     * Calls the edmondsKarp method before and after removing the failed segments and compares the difference in incoming flow of every station.
     * @param source
     * @param target
     * @param failedSegments
     * @param k
     * @note Time-complexity -> O(VE^2)
     */
    void printTopKMostAffected(string source, string target, stack<pair<string, string>> failedSegments, int k); //4.2
    /**
     * Iterates though every Station to check which ones, belonging to the line specified in the parameter, only have 1 adjacent segment of that line.
     * @param line
     * @return Vector of Station with no more than 1 adjacent segment of the specified line
     * @note Time-complexity -> O(E)
     */
    vector<Station*> oneGetAdjLine(string line);
    /**
     * The Breadth-First Search algorithm used in the implementation of the Edmonds-Karp Multiple Sources algorithm where it can be given (or not) a target. If it isn't given a target it will search for one and set it as a target
     * @param source
     * @param target
     * @return True if the Station specified as the sink has been visited, false otherwise.
     * @note Time-complexity -> O(V+E)
     */
    bool edmondsKarpBFSArea(Station* source, string* target);
    /**
     * A different implementation of the Edmonds-Karp algorithm. Calculates the maximum flow between a given station and will find the most far-away station and set it as a target. Sets the flow of the edges accordingly.
     * @param s
     * @note Time-complexity -> O(VE^2)
     */
    void edmondsKarpMultipleSources(Station* s);
protected:
    vector<pair<string, int>> districtBudget;
    vector<pair<string, int>> municipalityBudget;
    vector<pair<string, int>> townshipBudget;
    vector<Station *> StationSet;    // Station set
    set<string> lines;         // Different lines
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //PROJETO_DA_1_GRAPH_H