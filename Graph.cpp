// By: Gonçalo Leão

#include "Graph.h"
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
    for(auto segment : sourceStation->getAdj()){
        if(segment->getDest()->getName() == target)
            return segment->getCapacity();
    }
    return -1;
}

int Graph::getSegmentService(string source, string target) const {
    auto sourceStation = findStation(source);
    for(auto segment : sourceStation->getAdj()){
        if(segment->getDest()->getName() == target)
            return segment->getService();
    }
    return -1;
}

/*
 *  Adds a Station with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a Station with that content already exists.
 */
bool Graph::addStation(const string &name, const string &district, const string &municipality, const string &township, const string &line) {
    if (findStation(name) != nullptr)
        return false;
    StationSet.push_back(new Station(name,district,municipality,township,line));
    lines.insert(line);
    return true;
}

bool Graph::removeStation(const string &name){
    int idx = findStationIdx(name);
    if(idx == -1) return false;
    StationSet.erase(StationSet.begin()+idx);
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

bool Graph::removeSegment(const string &sourc, const string &dest){
    auto v1 = findStation(sourc);
    auto v2 = findStation(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->removeSegment(dest);
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
            testVisit(q, e, e->getDest(), e->getCapacity() - e->getFlow());
        }
        for(auto edge : u->getIncoming()){
            testVisit(q, edge, edge->getOrig(), edge->getFlow());
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
    if(target==source){
        return 0;
    }
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

void Graph::testVisit(std::queue<Station*> &q, Segment* e, Station* w, double residual){
    if(!w->isVisited() && (residual) > 0){
        w->setPath(e);
        w->setVisited(true);
        q.push(w);
    }
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
    s->setPath(nullptr);
    vector<Station *> optimalPath;
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
                current->setPath(seg);
                q.push(next);
            }
            else if(current->getCost()+cost < next->getCost()){
                next->setCost(current->getCost()+cost);
                current->setPath(seg);
                q.push(next);
            }
        }
    }
    cout << "The path with the minimum cost for the company has a cost of " << t->getCost() << "€\n";
    Station* temp=s;
    optimalPath.push_back(s);
    while(temp!=t){
        optimalPath.push_back(temp->getPath()->getDest());
        temp=temp->getPath()->getDest();
    }
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


void Graph::printTopKHigherBudget(string filter, int k) {

    transform(filter.begin(),filter.end(),filter.begin(), ::tolower); //make input lowercase
    if(districtBudget.empty() || municipalityBudget.empty() || townshipBudget.empty()) {
        for (Station *station: StationSet) {
            for (Segment *edge: station->getAdj()) {
                edge->setFlow(0.0);
            }
        }


        vector<Station *> sourceStations;

        for (string line: lines) {
            sourceStations = oneGetAdjLine(line);
            for (auto st: sourceStations) {
                edmondsKarpMultipleSources(st);
            }
        }


        unordered_map<string, int> districtMap;
        unordered_map<string, int> municipalityMap;
        unordered_map<string, int> townshipMap;


        for (auto station: StationSet) {
            for (auto s: station->getIncoming()) {
                string district = station->getDistrict();
                if (districtMap.find(district) == districtMap.end()) {
                    districtMap.insert(pair<string, int>(district, s->getFlow() * s->getService()));
                } else {
                    districtMap[s->getDest()->getDistrict()] += s->getFlow() * s->getService();
                }

                string municipality = station->getMunicipality();
                if (municipalityMap.find(municipality) == municipalityMap.end()) {
                    municipalityMap.insert(pair<string, int>(municipality, s->getFlow() * s->getService()));
                } else {
                    municipalityMap[s->getDest()->getMunicipality()] += s->getFlow() * s->getService();
                }

                string township = station->getTownship();
                if (townshipMap.find(township) == townshipMap.end()) {
                    townshipMap.insert(pair<string, int>(township, s->getFlow() * s->getService()));
                } else {
                    townshipMap[s->getDest()->getTownship()] += s->getFlow() * s->getService();
                }
            }
        }

        vector<pair<string, int>> topDistricts(districtMap.begin(), districtMap.end());
        sort(topDistricts.begin(), topDistricts.end(),
             [](const pair<string, int> &a, const pair<string, int> &b) { return a.second > b.second; });
        districtBudget = topDistricts;

        vector<pair<string, int>> topMunicipalities(municipalityMap.begin(), municipalityMap.end());
        sort(topMunicipalities.begin(), topMunicipalities.end(),
             [](const pair<string, int> &a, const pair<string, int> &b) { return a.second > b.second; });
        municipalityBudget = topMunicipalities;

        vector<pair<string, int>> topTownships(townshipMap.begin(), townshipMap.end());
        sort(topTownships.begin(), topTownships.end(),
             [](const pair<string, int> &a, const pair<string, int> &b) { return a.second > b.second; });
        townshipBudget = topTownships;
    }

    if(filter == "district"){
        cout << "The top " << k << " districts are:\n";
        int count = 1;
        for(auto district : districtBudget){
            cout << count << ": " << district.first << " | Budget = " << district.second << endl;
            if(count == k) return;
            count++;
        }
        return;
    }
    else if(filter == "municipality"){
        cout << "The top " << k << " municipalities are:\n";
        int count = 1;
        for(auto municipality : municipalityBudget){
            cout << count << ": " << municipality.first << " | Budget = " << municipality.second << endl;
            if(count == k) return;
            count++;
        }
        return;
    }
    else if(filter == "township"){
        cout << "The top " << k << " township are:\n";
        int count = 1;
        for(auto township : townshipBudget){
            cout << count << ": " << township.first << " | Budget = " << township.second << endl;
            if(count == k) return;
            count++;
        }
        return;
    }
}

int Graph::maxTrainsInStation(string station) {
    for(Station* station : StationSet){
        for(Segment *edge : station->getAdj()){
            edge->setFlow(0.0);
        }
    }
    vector<string> linhas;
    for(string line : lines) linhas.push_back(line);

    vector<Station*> sourceStations;

    for(string line:linhas){
        sourceStations = oneGetAdjLine(line);
        for(auto st : sourceStations){
            edmondsKarpMultipleSources(st);
        }
    }

    int trainCount = 0;
    auto incoming = findStation(station)->getIncoming();
    for(auto segment : incoming){
        trainCount += segment->getFlow();
    }
    cout << trainCount << " trains can arrive simultaneously in station " << station << endl;
    return trainCount;
}

void Graph::maxTrainsMinCost(string source, string target){
    edmondsKarpMoney(source, target);
    vector<Station*> res = dijkstra(source, target);
    stringstream ss;
    ss << "This is the following path:\n";
    for(const auto v : res) {
        ss << v->getName() << " - ";
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

    for(Station* station : StationSet) {
        for (Segment *edge: station->getAdj()) {
            edge->setFlow(0.0);
        }
    }

    vector<Station*> sourceStations;

    for(string line:lines){
        sourceStations = oneGetAdjLine(line);
        for(auto st : sourceStations){
            edmondsKarpMultipleSources(st);
        }
    }

    for(auto station : StationSet){
        int flow = 0;
        for(auto segment : station->getIncoming()){
            flow += segment->getFlow();
        }
        station->setFlow(flow);
    }

    /* Preservar o flow num vetor diferente para uma futura comparação*/
    vector<Station> mostAffected;
    mostAffected.reserve(StationSet.size());
    for(auto & i : StationSet){
        mostAffected.push_back(*i);
    }

    /*Retirar os segmentos especificados do graph*/
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

     /*Refazer o Edmonds-Karp geral, desta vez com o graph sem os segmentos especificados*/

    for(Station* station : StationSet){
        for(Segment *edge : station->getAdj()){
            edge->setFlow(0.0);
        }
    }

    for(string line:lines){
        sourceStations = oneGetAdjLine(line);
        for(auto st : sourceStations){
            edmondsKarpMultipleSources(st);
        }
    }

    for(auto station : StationSet){
        int flow = 0;
        for(auto segment : station->getIncoming()){
            flow += segment->getFlow();
        }
        station->setFlow(flow);
    }

    /*Realocar os segmentos anteriormente retirados do graph de volta*/
    while(!reallocateSegments.empty()){
        auto segment = reallocateSegments.top();
        reallocateSegments.pop();
        auto value = values.top();
        values.pop();
        addBidirectionalSegment(segment.first,segment.second,value.first,value.second);
    }

    /*Comparar o flow de cada estação antes de retirar os segmentos e depois*/
    for(int i = 0; i<StationSet.size();i++){ //get the difference between before and after the failed segments
        mostAffected[i].setFlow(abs(mostAffected[i].getFlow() - StationSet[i]->getFlow()));
    }
    /*Printar por ordem decrescente de flow*/
    sort(mostAffected.begin(), mostAffected.end(), compare);

    cout << "The top k most affected stations with the provided segment failures are:\n";
    int count = 1;
    for(auto station : mostAffected){
        cout << count << ": " << station.getName() << " with a difference in flow of " << station.getFlow() << endl;
        if(count == k) return;
        count++;
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



vector<Station*> Graph::oneGetAdjLine(string line){
    vector<Station*> sources;
    for(auto st : StationSet){
        if(st->getLine()!=line) continue;
        int count = 0;
        for(auto adj : st->getAdj()){
            if(adj->getDest()->getLine()==st->getLine()){
                count++;
            }
        }
        if(count==1 || count == 0){
            sources.push_back(st);
        }
    }
    return sources;
}

bool Graph::edmondsKarpBFSArea(Station* source, string* target){
    for(auto st : StationSet){
        st->setVisited(false);
    }
    source->setVisited(true);
    source->setPath(nullptr);
    std::queue<Station* > q;
    q.push(source);
    Station* tempTarget;
    if(*target != ""){
        tempTarget = findStation(*target);
    }
    if(source->getAdj().size()==0&&source->getIncoming().size()==0){
        *target = source->getName();
        return false;
    }

    while(!q.empty()){
        bool isEnd = true;
        Station* u = q.front();
        q.pop();
        for(auto e: u->getAdj()){
            //if(e->getDest()->getLine()!=source->getLine())continue;
            testVisit(q, e, e->getDest(), e->getCapacity() - e->getFlow());
        }
        for(auto edge : u->getIncoming()){
            //if(edge->getOrig()->getLine()!=source->getLine())continue;
            testVisit(q, edge, edge->getOrig(), edge->getFlow());
        }
        if(q.empty() && *target==""){
            *target = u->getName();
            tempTarget = findStation(*target);
        }
    }
    return tempTarget->isVisited();
}

void Graph::edmondsKarpMultipleSources(Station* s){
    if (s == nullptr) {
        cout << "Invalid source and/or target station!\n";
        return;
    }
    string t;
    while(edmondsKarpBFSArea(s, &t)){
        Station* target = findStation(t);
        double bottleneck = findMinResidual(s, target);
        updateFlow(s, target, bottleneck);
    }
}
