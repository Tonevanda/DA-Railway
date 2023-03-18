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

double Graph::dinicMaxFlow(const string& source, const string& sink) {
    /*// Initialize the flow network
    for(auto st : StationSet){
        for(auto seg: st->getAdj()){
            seg->setFlow(0);
        }
    }

    // Initialize the residual graph
    Graph residualGraph;
    for (auto& station : StationSet) {
        residualGraph.addStation(station->getName(), station->getDistrict(), station->getMunicipality(), station->getTownship(),station->getLine());
        for(auto seg: station->getAdj()){
            residualGraph.addBidirectionalSegment(station->getName(), seg->getDest()->getName(), seg->getCapacity(), seg->getService());
        }
    }

    // Compute the maximum flow using the Dinic's algorithm
    double maxFlow = 0;
    while (true) {
        // Compute the level graph using BFS
        unordered_map<string, int> level;
        queue<string> q;
        level[source] = 0;
        q.push(source);
        while (!q.empty()) {
            string front = q.front();
            Station* u = findStation(front);
            q.pop();
            for(auto seg : u->getAdj()){

            }
            for (auto& edge : residualGraph.getAdj(u)) {
                string v = edge->getSink()->getName();
                if (edge->getResidualCapacity(u) > 0 && !level.count(v)) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }

        // If the sink is not reachable, stop
        if (!level.count(sink)) {
            break;
        }

        // Compute the blocking flow using DFS
        unordered_map<string, int> ptr;
        function<double(string, double)> dfs = [&](string u, double bottleneck) {
            if (u == sink) {
                return bottleneck;
            }
            for (int& i = ptr[u]; i < residualGraph.getOutgoingEdges(u).size(); i++) {
                auto& edge = residualGraph.getOutgoingEdges(u)[i];
                string v = edge->getSink()->getName();
                if (level[v] == level[u] + 1 && edge->getResidualCapacity(u) > 0) {
                    double residualCapacity = edge->getResidualCapacity(u);
                    double flow = dfs(v, min(bottleneck, residualCapacity));
                    if (flow > 0) {
                        edge->addFlow(u, flow);
                        return flow;
                    }
                }
            }
            return 0.0;
        };
        while (true) {
            double bottleneck = dfs(source, INFINITY);
            if (bottleneck == 0) {
                break;
            }
            maxFlow += bottleneck;
        }
    }

    return maxFlow;*/
}

void Graph::pairs(){
    double max =0;
    stack<pair<string,string>> s;

    for(int i = 0; i < StationSet.size(); i++){
        for(int j = i+1; j < StationSet.size(); j++){
            Station* source = StationSet[i];
            Station* sink = StationSet[j];
            
            double flow = edmondsKarpStor(source->getName(),sink->getName());
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
/* TEST FUNCTIONS */
double Graph::edmondsKarpStor(string source, string target) {
    Station* s = findStation(source);
    Station* t = findStation(target);
    double count = 0;
    if (s == nullptr || t == nullptr || s == t)
        cout << "Invalid source and/or target vertex";

    // Reset the flows
    for (auto v : StationSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    // Loop to find augmentation paths
    while(findAugmentingPath(s, t)) {
        double f = findMinResidualAlongPath(s, t);
        count+=f;
        augmentFlowAlongPath(s, t, f);
    }
    return count;
}

void Graph::augmentFlowAlongPath(Station *s, Station *t, double f) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

double Graph::findMinResidualAlongPath(Station *s, Station *t) {
    double f = INF;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = min(f, e->getCapacity() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

bool Graph::findAugmentingPath(Station *s, Station *t) {
    for(auto v : StationSet) {
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Station *> q;
    q.push(s);
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getCapacity() - e->getFlow());
        }
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}

void Graph::testAndVisit(std::queue<Station*> &q, Segment *e, Station *w, double residual) {
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}
