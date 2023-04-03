// By: Gonçalo Leão

#include "Graph.h"
#include "UFDS.h"
#include <iostream>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <utility>

using namespace std;


Graph::Graph(const Graph &graph){
    this->StationSet=graph.StationSet;
}   

Graph::~Graph() {
    deleteMatrix(distMatrix, StationSet.size());
    deleteMatrix(pathMatrix, StationSet.size());
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

/*
 * Finds the index of the Station with a given content.
 */
int Graph::findStationIdx(const string &name) const {
    for (unsigned i = 0; i < StationSet.size(); i++)
        if (StationSet[i]->getName() == name)
            return i;
    return -1;
}

int Graph::getNumStation() const {
    return StationSet.size();
}

std::vector<Station *> Graph::getStationSet() const {
    return StationSet;
}

int Graph::getSegmentCapacity(string source, string target) const {
    auto sourceStation = findStation(source);
    int capacity = 0;
    for(auto segment : sourceStation->getAdj()){
        if(segment->getDest()->getName() == target)
            capacity = segment->getCapacity();
    }
    return capacity;
}

int Graph::getSegmentService(string source, string target) const {
    auto sourceStation = findStation(source);
    int service = 0;
    for(auto segment : sourceStation->getAdj()){
        if(segment->getDest()->getName() == target)
            service = segment->getService();
    }
    return service;
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

bool Graph::removeBidirectionalSegment(const string &source, const string &dest) {
    auto v1 = findStation(source);
    auto v2 = findStation(dest);
    if(v1 == nullptr || v2 == nullptr) return false;
    v1->removeSegment(dest);
    v2->removeSegment(source);
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


double Graph::edmondsKarp(string source, string target){
    for(Station* station : StationSet){
        for(Segment *edge : station->getAdj()){
            edge->setFlow(0.0);
        }
    }
    double maxFlow = 0;
    Station* s = findStation(source);
    Station* t = findStation(target);
    if (s == nullptr || t == nullptr || s == t) {
        cout << "Invalid source and/or target station!\n";
        return 0.0;
    }

    while(edmondsKarpBFS(s, t)){
        double bottleneck = findMinResidual(s, t);
        updateFlow(s, t, bottleneck);
        maxFlow+=bottleneck;
    }

    //can possibly be done inside the edmondsKarp algorithm and become more efficient
    for(auto station : StationSet){
        int flow = 0;
        for(auto segment : station->getIncoming()){
            flow += segment->getFlow();
        }
        station->setFlow(flow);
    }

    return maxFlow;
}
bool Graph::edmondsKarpBFS(Station* v, Station* sink){
    for(auto st : StationSet){
        st->setVisited(false);
    }
    v->setVisited(true);
    v->setPath(nullptr);
    std::queue<Station* > q;
    q.push(v);

    while(!q.empty() && !sink->isVisited()){
        Station* u = q.front();
        q.pop();

        for(auto e: u->getAdj()){
            testVisit(q, e, e->getDest(), sink, e->getCapacity() - e->getFlow());
        }
        for(auto edge : u->getIncoming()){
            testVisit(q, edge, edge->getOrig(), sink, edge->getFlow());
        }
    }
    return sink->isVisited();
}

void Graph::updateFlow(Station* source, Station* target, double bottleneck){
    Station* currentVertex = target;
    while (currentVertex != source) {
        Segment* e = currentVertex->getPath();

        if(e->getDest()==currentVertex){
            e->setFlow(e->getFlow() + bottleneck);
            currentVertex = e->getOrig();
        }
        else{
            e->setFlow(e->getFlow() - bottleneck);
            currentVertex = e->getDest();
        }
    }
}

double Graph::edmondsKarpMoney(string source, string target){
    for(Station* station : StationSet){
        for(Segment *edge : station->getAdj()){
            edge->setFlow(0.0);
        }
    }
    double maxFlow = 0;
    Station* s = findStation(source);
    Station* t = findStation(target);
    if (s == nullptr || t == nullptr || s == t) {
        cout << "Invalid source and/or target station!\n";
        return 0.0;
    }

    while(edmondsKarpBFS(s, t)){
        double bottleneck = findMinResidual(s, t);
        updateFlowMoney(s, t, bottleneck);
        maxFlow+=bottleneck;
    }
    return maxFlow;
}

void Graph::updateFlowMoney(Station* source, Station* target, double bottleneck){
    Station* currentVertex = target;
    while (currentVertex != source) {
        Segment* e = currentVertex->getPath();

        if(e->getDest()==currentVertex){
            e->setFlow(e->getFlow() + bottleneck);
            e->setCost((e->getFlow() + bottleneck)*e->getService());
            currentVertex = e->getOrig();
        }
        else{
            e->setFlow(e->getFlow() - bottleneck);
            e->setCost((e->getFlow() - bottleneck)*e->getService());
            currentVertex = e->getDest();
        }
    }
}


double Graph::findMinResidual(Station* source, Station* target){
    double bottleneck = INF;
    Station* currentVertex = target;
    while (currentVertex != source) {
        Segment* e = currentVertex->getPath();

        if(e->getDest()==currentVertex){
            bottleneck = std::min(bottleneck, e->getCapacity() - e->getFlow());
            currentVertex = e->getOrig();
        }
        else{
            bottleneck = std::min(bottleneck, e->getFlow());
            currentVertex = e->getDest();
        }

    }
    return bottleneck;
}

void Graph::testVisit(std::queue<Station*> &q, Segment* e, Station* w, Station* sink, double residual){
    if(!w->isVisited() && (residual) > 0){
        w->setPath(e);
        w->setVisited(true);
        q.push(w);
    }
}

//para que é que isto servia mesmo??
vector<Station*> Graph::kruskal(){ // talvez fique melhor se trocarmos de int id no UFDS para string name? mas tou demasiado cansado para pensar em como fazer isso
    for (auto v : StationSet) {
        for (auto e : v->getAdj()) {
            e->setSelected(false);
        }
    }

    UFDS ufds(StationSet.size());
    std::vector<Segment*> sortedEdges;

    for (auto v : StationSet) {
        for (auto e : v->getAdj()) {
            if(!e->isSelected()){
                sortedEdges.push_back(e);
                e->setSelected(true);
                Segment* e2 = e->getReverse();
                e2->setSelected(true);
            }
        }
    }

    std::sort(sortedEdges.begin(), sortedEdges.end(), [](const Segment* e1, const Segment* e2) {
        return e1->getCost() < e2->getCost();
    });

    for(auto e :sortedEdges){
        if(!ufds.isSameSet(findStationIdx(e->getDest()->getName()), findStationIdx(e->getOrig()->getName()))){
            Station* v = e->getDest();
            Station* u = e->getOrig();
            v->setPath(e);
            ufds.linkSets(findStationIdx(u->getName()), findStationIdx(v->getName()));
        }
    }
    return StationSet;
}

///TODO
vector<Station*> Graph::dijkstra(string source, string dest) {
    Station* s = findStation(source);
    Station* t = findStation(dest);
    for(auto &temp:StationSet){
        temp->setVisited(false);
    }
    s->setVisited(true);
    s->setCost(0);
    vector<Station *> optimalPath;
    optimalPath.push_back(s);
    int min;
    priority_queue<Station*> q;
    q.push(s);
    while(!q.empty()){
        Station* current = q.top();
        q.pop();
        for(auto seg : current->getAdj()){
            Station* next = seg->getDest();
            int cost = (seg->getFlow())*(seg->getService());
            if(cost==0){continue;}
            if(!next->isVisited()){
                next->setCost(current->getCost()+cost);
                next->setVisited(true);
                q.push(next);
            }
            else if(current->getCost()+cost < next->getCost()){
                next->setCost(current->getCost()+cost);
                q.push(next);
            }
        }
    }
    cout << "The path with the minimum cost for the company has a cost of " << t->getCost() << " moner €";
    return optimalPath;
}


void Graph::maxTrains(string source, string target) {
    int flow = edmondsKarp(source, target);
    cout << "The maximum numbers of trains that can simultaneously travel between " << source << " and " << target << " is " << flow << endl;
}

void Graph::stationPairs(){
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

void Graph::printTopKHigherBudget(const string &filter, int k) {
    unordered_map<string, int> map;
    edmondsKarp("Valongo", "Trofa");
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
            else if(filter == "district"){
                string name = station->getDistrict();
                if(map.find(name) == map.end()){
                    map.insert(pair<string, int>(name,s->getFlow() * s->getService()));
                }
                else{
                    map[station->getDistrict()] += s->getFlow() * s->getService();
                }
            }
        }
    }
    vector<pair<string, int>> top(map.begin(), map.end());
    sort(top.begin(), top.end(), [](const pair<string, int>& a, const pair<string, int>& b) {return a.second > b.second;});
    for(int i = 0; i < k; i++){
        if(i >= StationSet.size()){
            break;
        }
        cout << top[i].first << ": " << top[i].second << "\n";
    }
}

int Graph::maxTrainsInStation(string station) {
    int trainCount = 0;
    auto incoming = findStation(station)->getIncoming();
    for(auto segment : incoming){
        trainCount += segment->getCapacity();
    }
    return trainCount;
}

void Graph::maxTrainsMinCost(string source, string target){
    edmondsKarpMoney(source, target);
    vector<Station*> res = dijkstra(source, target);
    stringstream ss;
    ss << "This is the following path:\n";
    for(const auto v : res) {
        ss << v->getName();
        if ( v->getPath() != nullptr ) {
            ss << " -> " << v->getPath()->getDest()->getName();
        }
    }
    ss << " | Arrived at destination.";
    cout << ss.str() <<endl;
}


void Graph::maxTrainsFailure(string source, string target, stack<pair<string, string>> failedSegments) {
    stack<pair<string, string>> reallocateSegments; //copy failedSegments before removing them from the graph to add them later
    stack<pair<int, int>> values; //vector to keep track of the values of the segments we remove

    while(!failedSegments.empty()){
        auto segment = failedSegments.top();
        failedSegments.pop();
        int capacity = getSegmentCapacity(segment.first, segment.second);
        int service = getSegmentService(segment.first, segment.second);
        values.push(make_pair(capacity, service));
        reallocateSegments.push(segment);
        removeBidirectionalSegment(segment.first,segment.second);
    }

    int flow = edmondsKarp(source, target);

    while(!reallocateSegments.empty()){
        auto segment = reallocateSegments.top();
        reallocateSegments.pop();
        auto value = values.top();
        values.pop();
        addBidirectionalSegment(segment.first,segment.second,value.first,value.second);
    }

    cout << "The maximum numbers of trains that can simultaneously travel between " << source << " and " << target << ", in a network of reduced connectivity, is " << flow << endl;
}

bool compare(Station s1, Station s2){
    return s1.getFlow() > s2.getFlow();
}

void Graph::printTopKMostAffected(string source, string target, stack<pair<string, string>> failedSegments, int k) {
    edmondsKarp(source, target);
    vector<Station> mostAffected;

    mostAffected.reserve(StationSet.size());
    for(auto & i : StationSet){
        mostAffected.push_back(*i);
    }

    maxTrainsFailure(source, target, failedSegments);

    for(int i = 0; i<StationSet.size();i++){ //get the difference between before and after the failed segments
        mostAffected[i].setFlow(abs(mostAffected[i].getFlow() - StationSet[i]->getFlow()));
    }

    sort(mostAffected.begin(), mostAffected.end(), compare);

    cout << "The top k most affected stations with the provided segment failures are:\n";
    for(int i = 1; i<k+1;i++){
        cout << i << ": " << mostAffected[i-1].getName() << " with a difference in flow of " << mostAffected[i-1].getFlow() << endl;
    }
}




bool compare2(pair<string, int> p1,pair<string, int> p2){
    return p1.second > p2.second;
}

void Graph::topKIncoming(int k){
    int before = 0;
    vector<pair<string, int>> top;
    for(auto station : StationSet){
        int incoming = maxTrainsInStation(station->getName());
        top.push_back(make_pair(station->getName(), incoming));
    }
    sort(top.begin(), top.end(), compare2);
    for(int i = 1; i < k+1; i++){
        cout << i << ": " << top[i-1].first << " | Capacity: " << top[i-1].second << endl;
    }
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

/*Isto vai retornar todas as estações com 1 de adj ig para dps fazermos edmonds karp*/
vector<Station*> Graph::oneGetAdj(){
    vector<Station*> nascentes;
    for(auto st : StationSet){
        int count = 0;
        for(auto adj : st->getAdj()){
            if(adj->getDest()->getLine()==st->getLine() && st->getLine()=="Linha do Norte"){
                count++;
            }
        }
        if(count==1){
            nascentes.push_back(st);
            cout << st->getName() << " ------- " << st->getLine() << endl;
        }
    }
    return nascentes;
}

/*cria uma supersource chamada SuperSource, cap=INF, serv=0*/
void Graph::createSuperSource(vector<Station*> nascentes){
    this->addStation("SuperSource","", "","","");
    for(auto source : nascentes){
        this->addSegment("SuperSource", source->getName(),INF, 0);
    }

}