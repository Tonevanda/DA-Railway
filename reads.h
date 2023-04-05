//
// Created by tiago on 11/03/2023.
//
#ifndef PROJETO_DA_1_READS
#define PROJETO_DA_1_READS

#include "Graph.h"
#include <fstream>
#include <sstream>

vector<string> read(const string line){
    vector<string> info;
    string word;
    bool inQuotes = false;
    for(char c : line){
        if(c == '"'){
            inQuotes = !inQuotes;
        }
        else if(c == ',' && !inQuotes){
            info.push_back(word);
            word.clear();
        }
        else {
            word += c;
        }
    }
    info.push_back(word);
    return info;
}

void readStations(Graph* graph, string file){
    ifstream fout;
    file= "../" +file;
    fout.open(file);
    if(!fout.is_open()){
        cout << "Error when opening file " << file << endl;
        return;
    }
    string tempstream,Name,District,Municipality,Township,Line;
    getline(fout, tempstream);
    while (getline (fout, tempstream)) {
        vector<string> info = read(tempstream);
        Name = info[0];
        District = info[1];
        Municipality = info[2];
        Township = info[3];
        Line = info[4];
        graph->addStation(Name,District,Municipality,Township,Line);
    }
    fout.close();
}

void readNetwork(Graph* graph, string file){
    ifstream fout;
    file="../"+file;
    fout.open(file);
    if(!fout.is_open()){
        cout << "Error when opening file " << file << endl;
        return;
    }
    string tempstream,Station_A,Station_B,Capacity,Service;
    getline (fout, tempstream);
    while (getline (fout, tempstream)) {
        vector<string> info = read(tempstream);
        int serv;
        stringstream it_stream(tempstream);
        Station_A = info[0];
        Station_B = info[1];
        Capacity = info[2];
        Service = info[3];
        double cap = stod(Capacity);
        if(Service == "ALFA PENDULAR"){
            serv = 4;
        }
        else{
            serv = 2;
        }
        graph->addBidirectionalSegment(Station_A,Station_B,cap,serv);
    }
    fout.close();
}

#endif //PROJETO_DA_1_READS
