// By: Gonçalo Leão

#ifndef PROJETO_DA_1_STATIONSEGMENT_H
#define PROJETO_DA_1_STATIONSEGMENT_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

class Segment;

#define INF std::numeric_limits<double>::max()

/************************* Station  **************************/

class Station {
public:
    /**
     * Station constructor. Creates a Station object with the given parameters.
     * @param name
     * @param district
     * @param municipality
     * @param township
     * @param line
     */
    Station(std::string name, std::string district, std::string municipality, std::string township, std::string line);
    bool operator<(Station& Station) const; // // required by MutablePriorityQueue

    /**
     * Adds an outgoing segment to a Station (this) with a given destination Station (dest), capacity (w) and service (serv).
     * @param dest
     * @param w
     * @param serv
     * @return Segment with (this) as source and d as target.
     * @note Time-complexity -> O(1)
     */
    Segment* addSegment(Station *dest, double w, int serv);
    /**
     * Removes an outgoing segment with a given destination (destName) from a Station (this).
     * @param destName
     * @return True if successful, false if such Segment does not exist.
     * @note Time-complexity -> O(n^2)
     */
    bool removeSegment(std::string destName);

    /**
     * Getter method for the name field.
     * @return Name of (this) Station.
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] string getName() const;
    /**
     * Getter method for the district field.
     * @return District of (this) Station.
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] string getDistrict() const;
    /**
     * Getter method for the municipality field.
     * @return Municipality of (this) Station.
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] string getMunicipality() const;
    /**
     * Getter method for the township field.
     * @return Township of (this) Station.
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] string getTownship() const;
    /**
     * Getter method for the line field.
     * @return Line of (this) Station.
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] string getLine() const;
    /**
     * Getter method for the vector of adjacent segments field.
     * @return Vector of outgoing segments from (this) Station.
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] vector<Segment *> getAdj() const;
    /**
     * Getter method for the visited field.
     * @return True if visited, false otherwise.
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] bool isVisited() const;
    /**
     * Getter method for the processing field.
     * @return True if is processing, false otherwise.
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] bool isProcessing() const;
    /**
     * Getter method for the indegree field.
     * @return Indegree of a Station.
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] unsigned int getIndegree() const;
    /**
     * Getter method for the cost field.
     * @return Total cost of incoming segments to (this) Station.
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] int getCost() const;
    /**
     * Getter method for the flow field.
     * @return Total flow of incoming segments to (this) Station.
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] int getFlow() const;
    /**
     * Getter method for the current path to (this) Station.
     * @return Segment pertaining to the path to (this) Station.
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] Segment *getPath() const;
    /**
     * Getter method for the incoming field.
     * @return Vector of incoming segments to (this) Station
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] vector<Segment *> getIncoming() const;

    /**
     * Sets the visited field to correspond to the given parameter.
     * @param visited
     * @note Time-complexity -> O(1)
     */
    void setVisited(bool visited);
    /**
     * Sets the processing field to correspond to the given parameter.
     * @param processing
     * @note Time-complexity -> O(1)
     */
    void setProcesssing(bool processing);
    /**
     * Sets the indegree field to correspond to the given parameter.
     * @param indegree
     * @note Time-complexity -> O(1)
     */
    void setIndegree(unsigned int indegree);
    /**
     * Sets the cost field to correspond to the given parameter.
     * @param cost
     * @note Time-complexity -> O(1)
     */
    void setCost(int cost);
    /**
     * Sets the flow field to correspond to the given parameter.
     * @param flow
     * @note Time-complexity -> O(1)
     */
    void setFlow(int flow);
    /**
     * Sets the path field to correspond to the given parameter.
     * @param path
     * @note Time-complexity -> O(1)
     */
    void setPath(Segment *path);

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
};

/********************** Segment  ****************************/

class Segment {
public:
    /**
     * Segment constructor. Creates a Segment object with the given parameters.
     * @param orig
     * @param dest
     * @param w
     * @param service
     * @note Time-complexity -> O(1)
     */
    Segment(Station *orig, Station *dest, double w, int service);
    /**
     * Getter method for the dest field.
     * @return destination of (this) segment.
     * @note Time-complexity -> O(1)
     */
    Station* getDest() const;
    /**
     * Getter method for the capacity field.
     * @return capacity of (this) segment.
     * @note Time-complexity -> O(1)
     */
    double getCapacity() const;
    /**
     * Getter method for the selected field.
     * @return True if selected, false otherwise.
     * @note Time-complexity -> O(1)
     */
    bool isSelected() const;
    /**
     * Getter method for the orig field.
     * @return origin of (this) segment.
     * @note Time-complexity -> O(1)
     */
    Station* getOrig() const;
    /**
     * Getter method for the reverse field.
     * @return reverse of (this) segment.
     * @note Time-complexity -> O(1)
     */
    Segment *getReverse() const;
    /**
     * Getter method for the flow field.
     * @return flow of (this) segment.
     * @note Time-complexity -> O(1)
     */
    double getFlow() const;
    /**
     * Getter method for the service field.
     * @return service of (this) segment.
     * @note Time-complexity -> O(1)
     */
    int getService() const;
    /**
     * Getter method for the service name.
     * @return "STANDARD" if service is 2, "ALFA PENDULAR" if service is 4.
     * @note Time-complexity -> O(1)
     */
    string getServiceName() const;
    /**
     * Getter method for the cost field.
     * @return cost of (this) segment.
     * @note Time-complexity -> O(1)
     */
    double getCost() const;
    /**
     * Sets the selected field to correspond to the given parameter.
     * @param selected
     * @note Time-complexity -> O(1)
     */
    void setSelected(bool selected);
    /**
     * Sets the reverse field to correspond to the given parameter.
     * @param reverse
     * @note Time-complexity -> O(1)
     */
    void setReverse(Segment *reverse);
    /**
     * Sets the flow field to correspond to the given parameter.
     * @param flow
     * @note Time-complexity -> O(1)
     */
    void setFlow(int flow);
    /**
     * Sets the cost field to correspond to the given parameter.
     * @param cost
     * @note Time-complexity -> O(1)
     */
    void setCost(double cost);
    /**
     * Getter method for the Residual field
     * @return value of the residual flow of (this) segment
     * @note Time-complexity -> O(1)
     */
    double getResidual();
    /**
     * Sets the residual field to correspond to the given parameter.
     * @param residual
     * @note Time-complexity -> O(1)
     */
    void setResidual(double residual);
protected:
    Station* dest; // destination vertex
    double capacity; // edge weight, can also be used for capacity
    int service;
    bool selected = false;
    Station *orig;
    Segment *reverse = nullptr;
    int flow; // for flow-related problems
    double cost; // flow * service
    double residual=0;
};

#endif //PROJETO_DA_1_STATIONSEGMENT_H