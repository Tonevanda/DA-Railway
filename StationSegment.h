// By: Gonçalo Leão

#ifndef PROJETO_DA_1_STATIONSEGMENT_H
#define PROJETO_DA_1_STATIONSEGMENT_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

using namespace std;

class Segment;

#define INF std::numeric_limits<double>::max()

/************************* Station  **************************/

class Station {
public:
    Station(std::string name, std::string district, std::string municipality, std::string township, std::string line);
    bool operator<(Station& Station) const; // // required by MutablePriorityQueue

    //int getId() const;
    string getName() const;
    string getDistrict() const;
    string getMunicipality() const;
    string getTownship() const;
    string getLine() const;

    vector<Segment *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    int getCost() const;
    int getFlow() const;
    Segment *getPath() const;
    vector<Segment *> getIncoming() const;

    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setCost(int cost);
    void setFlow(int flow);
    void setPath(Segment *path);
    Segment* addSegment(Station *dest, double w, int serv);
    bool removeSegment(std::string destName);

    friend class MutablePriorityQueue<Station>;
protected:
    //int id;                // identifier
    string name;
    string district;
    string municipality;
    string township;
    string line;
    vector<Segment *> adj;  // outgoing edges
    vector<Segment *> incoming; // incoming edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    int cost = 0;
    int flow = 0;
    Segment *path = nullptr;


    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS
};

/********************** Segment  ****************************/

class Segment {
public:
    Segment(Station *orig, Station *dest, double w, int service);

    Station* getDest() const;
    double getCapacity() const;
    bool isSelected() const;
    Station* getOrig() const;
    Segment *getReverse() const;
    double getFlow() const;
    int getService() const;
    string getServiceName() const;
    double getCost() const;
    void setSelected(bool selected);
    void setReverse(Segment *reverse);
    void setFlow(int flow);
    void setCost(double cost);
protected:
    Station* dest; // destination vertex
    double capacity; // edge weight, can also be used for capacity
    int service;
    bool selected = false;
    Station *orig;
    Segment *reverse = nullptr;
    int flow; // for flow-related problems
    double cost; // flow * service
};

#endif //PROJETO_DA_1_STATIONSEGMENT_H