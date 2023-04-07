// By: Gonçalo Leão

#include "StationSegment.h"

/************************* Station  **************************/

Station::Station(std::string name, std::string district, std::string municipality, std::string township, std::string line): name(name), district(district),
municipality(municipality), township(township), line(line){}



/*
 * Auxiliary function to add an outgoing Segment to a Station (this),
 * with a given destination Station (d) and Segment weight (w).
 */
Segment * Station::addSegment(Station *d, double w, int serv) {
    auto newSegment = new Segment(this, d, w, serv);
    adj.push_back(newSegment);
    d->incoming.push_back(newSegment);
    return newSegment;
}

/*
 * Auxiliary function to remove an outgoing Segment (with a given destination (d))
 * from a Station (this).
 * Returns true if successful, and false if such Segment does not exist.
 */
bool Station::removeSegment(std::string destName) {
    bool removedSegment = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Segment *Segment = *it;
        Station *dest = Segment->getDest();
        if (dest->getName() == destName) {
            it = adj.erase(it);
            // Also remove the corresponding Segment from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getName() == name) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete Segment;
            removedSegment = true; // allows for multiple Segments to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedSegment;
}

bool Station::operator<(Station & Station) const {
    return this->cost < Station.cost;
}


std::string Station::getName() const {return this->name;}
std::string Station::getDistrict() const {return this->district;}
std::string Station::getMunicipality() const {return this->municipality;}
std::string Station::getTownship() const {return this->township;}
std::string Station::getLine() const {return this->line;}

std::vector<Segment*> Station::getAdj() const {
    return this->adj;
}

bool Station::isVisited() const {
    return this->visited;
}

bool Station::isProcessing() const {
    return this->processing;
}

unsigned int Station::getIndegree() const {
    return this->indegree;
}

int Station::getCost() const {
    return this->cost;
}

int Station::getFlow() const {
    return this->flow;
}

Segment *Station::getPath() const {
    return this->path;
}

std::vector<Segment *> Station::getIncoming() const {
    return this->incoming;
}


void Station::setVisited(bool visited) {
    this->visited = visited;
}

void Station::setProcesssing(bool processing) {
    this->processing = processing;
}

void Station::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Station::setCost(int cost) {
    this->cost = cost;
}

void Station::setFlow(int flow) {
    this->flow = flow;
}

void Station::setPath(Segment *path) {
    this->path = path;
}

/********************** Segment  ****************************/

Segment::Segment(Station *orig, Station *dest, double w, int service): orig(orig), dest(dest), capacity(w) , service(service){}

Station * Segment::getDest() const {
    return this->dest;
}

double Segment::getCapacity() const {
    return this->capacity;
}

Station * Segment::getOrig() const {
    return this->orig;
}

Segment *Segment::getReverse() const {
    return this->reverse;
}

bool Segment::isSelected() const {
    return this->selected;
}

double Segment::getFlow() const {
    return flow;
}

int Segment::getService() const {
    return service;
}

string Segment::getServiceName() const {
    switch (service) {
        case 2: {return "STANDARD";}
        case 4: {return "ALFA PENDULAR";}
    }
    return "";
}

double Segment::getCost() const {
    return cost;
}

void Segment::setSelected(bool selected) {
    this->selected = selected;
}

void Segment::setReverse(Segment *reverse) {
    this->reverse = reverse;
}

void Segment::setFlow(int flow) {
    this->flow = flow;
}

void Segment::setCost(double cost) {
    this->cost = cost;
}
