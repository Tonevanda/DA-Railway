// By: Gonçalo Leão

#include "Graph.h"
#include <iostream>
#include <unordered_map>
#include <stack>

using namespace std;

Graph::~Graph() {
    deleteMatrix(distMatrix, StationSet.size());
    deleteMatrix(pathMatrix, StationSet.size());
}

int Graph::getNumStation() const {
    return StationSet.size();
}

std::vector<Station *> Graph::getStationSet() const {
    return StationSet;
}

/*
 * Auxiliary function to find a Station with a given content.
 */
Station* Graph::findStation(const string &name) const {
    for (auto v : StationSet)
        if (v->getName() == name)
            return v;
    return nullptr;
}

void Graph::printStations() const {
    for(auto Station : StationSet){
        cout << "Name: " << Station->getName() << ", \n" << "Municipality: " <<  Station->getMunicipality() << "\n";
    }
}

void Graph::printNetwork() const{
    int count = 0;
    for(auto Station : StationSet){
        for(auto seg : Station->getAdj()){
            cout << "Orig: " << seg->getOrig()->getName() << ", Dest: " << seg->getDest()->getName() << ", cap: "<< seg->getCapacity() << ", service: "<< seg->getServiceName() <<"\n";
            count++;
        }
    }
    cout << "Count: " << count << "\n";
}

/*
 * Finds the index of the Station with a given content.
 */
int Graph::findStationIdx(const string &name) const {
    for (unsigned i = 0; i < StationSet.size(); i++)
        if (StationSet[i]->getName() == name)
            return i;
    return -1;
}

bool Graph::edmondsKarpBFS(string s, string t){
    for(auto st : StationSet){
        st->setVisited(false);
    }

    Station* v = findStation(s);
    Station* sink = findStation(t);
    v->setVisited(true);
    v->setPath(nullptr);
    std::queue<Station* > q;
    q.push(v);

    while(!q.empty()){
        Station* u = q.front();
        q.pop();

        for(auto e: u->getAdj()){
            Station* w = e->getDest();
            if(!w->isVisited() && (e->getCapacity() - e->getFlow()) > 0) {
                if(w->getName() == sink->getName()){
                    w->setPath(e);
                    return true;
                }
                q.push(w);
                w->setPath(e);
                w->setVisited(true);
            }
        }
        for(auto edge : u->getIncoming()){
            Station* w = edge->getOrig();
            if(!w->isVisited() && edge->getFlow()>0){
                w->setVisited(true);
                w->setPath(edge);
                edge->setSelected(true);
                q.push(w);
                if(w->getName()==sink->getName()){
                    return true;
                }
            }
        }
    }
    return false;
}

int Graph::edmondsKarp(string source, string target){
    for(Station* station : StationSet){
        for(Segment *edge : station->getAdj()){
            edge->setFlow(0.0);
        }
    }
    double maxFlow = 0;

    while(edmondsKarpBFS(source, target)){
        double bottleneck = INF;

        Station* currentVertex = findStation(target);
        while (currentVertex->getPath() != nullptr) {
            Segment* e = currentVertex->getPath();

            if(e->isSelected()){
                bottleneck = std::min(bottleneck, e->getFlow());
                currentVertex = e->getDest();
            }
            else{
                bottleneck = std::min(bottleneck, e->getCapacity() - e->getFlow());
                currentVertex = e->getOrig();
            }

        }

        currentVertex = findStation(target);
        while (currentVertex->getPath() != nullptr) {
            Segment* e = currentVertex->getPath();
            if(e->isSelected()){
                e->setFlow(e->getFlow() - bottleneck);
                currentVertex = e->getDest();
            }
            else{
                e->setFlow(e->getFlow() + bottleneck);
                currentVertex = e->getOrig();
            }
        }
        maxFlow+=bottleneck;
    }
    return maxFlow;
}

/*
 *  Adds a Station with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a Station with that content already exists.
 */
bool Graph::addStation(const string &name, const string &district, const string &municipality, const string &township, const string &line) {
    if (findStation(name) != nullptr)
        return false;
    StationSet.push_back(new Station(name,district,municipality,township,line));
    return true;
}

/*
 * Adds a Segment to a graph (this), given the contents of the source and
 * destination vertices and the Segment weight (w).
 * Returns true if successful, and false if the source or destination Station does not exist.
 */
bool Graph::addSegment(const string &sourc, const string &dest, double w, int serv) {
    auto v1 = findStation(sourc);
    auto v2 = findStation(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addSegment(v2, w, serv);
    return true;
}

bool Graph::addBidirectionalSegment(const string &sourc, const string &dest, double w, int serv) {
    auto v1 = findStation(sourc);
    auto v2 = findStation(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addSegment(v2, w, serv);
    auto e2 = v2->addSegment(v1, w, serv);
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

void Graph::sinks(){
    for(auto s : StationSet)   {
        if(s->getAdj().size()==0){
            cout << s->getName() << " is a sink\n";
        }
        if(s->getIncoming().size()==0){
            cout << s->getName() << " is a source\n";
        }
    }
}

void Graph::pairs(){
    double max =0;
    stack<pair<string,string>> s;

    for(int i = 0; i < StationSet.size(); i++){
        for(int j = i+1; j < StationSet.size(); j++){
            Station* source = StationSet[i];
            Station* sink = StationSet[j];
            
            double flow = edmondsKarp(source->getName(),sink->getName());
            pair<string,string> cur = pair<string, string> (source->getName(), sink->getName());
            if(flow == max){
                s.push(cur);
            }
            if(flow > max){
               while(!s.empty()){
                   s.pop();
               }
               max = flow;
               s.push(cur);
            }
        }
    }
    while(!s.empty()){
        pair<string, string> top = s.top();
        s.pop();
        cout << top.first << " and " << top.second  << " Flow : " << max << "\n";
    }
}

void Graph::printTopK(string filter, int k) const {
    unordered_map<string, int> map;

    for(auto station : StationSet){
        for(auto s : station->getAdj()){
            if(filter == "municipality"){
                string name = station->getMunicipality();
                if(map.find(name)==map.end()){
                    map.insert(pair<string,int>(name,s->getFlow() * s->getService()));
                }
                else{
                    map[station->getMunicipality()] += s->getFlow() * s->getService();
                }
            }
        }
    }
}