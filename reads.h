//
// Created by tiago on 11/03/2023.
//
#ifndef PROJETO_DA_1_READS
#define PROJETO_DA_1_READS

#include "Graph.h"
#include <fstream>
#include <sstream>

void readStations(Graph* graph, string file){
    ifstream fout;
    file= "../" +file;
    fout.open(file);
    string tempstream,Name,District,Municipality,Township,Line;
    getline(fout, tempstream);
    while (getline (fout, tempstream)) {
        stringstream it_stream(tempstream);
        getline(it_stream,Name,',');
        getline(it_stream,District,',');
        getline(it_stream,Municipality,',');
        getline(it_stream,Township,',');
        getline(it_stream,Line,'\r');
        graph->addStation(Name,District,Municipality,Township,Line);
    }
    fout.close();
}

void readNetwork(Graph* graph, string file){
    ifstream fout;
    file="../"+file;
    fout.open(file);
    string tempstream,Station_A,Station_B,Capacity,Service;
    getline (fout, tempstream);
    while (getline (fout, tempstream)) {
        int serv;
        stringstream it_stream(tempstream);
        getline(it_stream,Station_A,',');
        getline(it_stream,Station_B,',');
        getline(it_stream,Capacity,',');
        getline(it_stream,Service,'\r');
        double cap = stod(Capacity);
        if(Service == "ALFA PENDULAR"){
            serv = 4;
        }
        else{
            serv = 2;
        }
        graph->addSegment(Station_A,Station_B,cap,serv);
    }
    fout.close();
}

#endif //PROJETO_DA_1_READS
