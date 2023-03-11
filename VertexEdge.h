// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_VERTEX_EDGE
#define DA_TP_CLASSES_VERTEX_EDGE

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

class Segment;

#define INF std::numeric_limits<double>::max()

/************************* Station  **************************/

class Station {
public:
    Station(int id, );
    bool operator<(Station& Station) const; // // required by MutablePriorityQueue

    int getId() const;
    std::vector<Segment *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Segment *getPath() const;
    std::vector<Segment *> getIncoming() const;

    void setId(int info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Segment *path);
    Segment * addSegment(Station *dest, double w, int serv);
    bool removeSegment(int destID);

    friend class MutablePriorityQueue<Station>;
protected:
    int id;                // identifier
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::vector<Segment *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Segment *path = nullptr;

    std::vector<Segment *> incoming; // incoming edges

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

    void setSelected(bool selected);
    void setReverse(Segment *reverse);
    void setFlow(double flow);
protected:
    Station* dest; // destination vertex
    double capacity; // edge weight, can also be used for capacity
    int service;

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Station *orig;
    Segment *reverse = nullptr;

    double flow; // for flow-related problems
};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */