// By: Gonçalo Leão

#include "Graph.h"

int Graph::getNumStation() const {
    return StationSet.size();
}

std::vector<Station *> Graph::getStationSet() const {
    return StationSet;
}

/*
 * Auxiliary function to find a Station with a given content.
 */
Station* Graph::findStation(const int &id) const {
    for (auto v : StationSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

/*
 * Finds the index of the Station with a given content.
 */
int Graph::findStationIdx(const int &id) const {
    for (unsigned i = 0; i < StationSet.size(); i++)
        if (StationSet[i]->getId() == id)
            return i;
    return -1;
}
/*
 *  Adds a Station with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a Station with that content already exists.
 */
bool Graph::addStation(const int &id) {
    if (findStation(id) != nullptr)
        return false;
    StationSet.push_back(new Station(id));
    return true;
}

/*
 * Adds a Segment to a graph (this), given the contents of the source and
 * destination vertices and the Segment weight (w).
 * Returns true if successful, and false if the source or destination Station does not exist.
 */
bool Graph::addSegment(const int &sourc, const int &dest, double w, int serv) {
    auto v1 = findStation(sourc);
    auto v2 = findStation(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addSegment(v2, w, serv);
    return true;
}

bool Graph::addBidirectionalSegment(const int &sourc, const int &dest, double w, int serv) {
    auto v1 = findStation(sourc);
    auto v2 = findStation(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addSegment(v2, w);
    auto e2 = v2->addSegment(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, StationSet.size());
    deleteMatrix(pathMatrix, StationSet.size());
}