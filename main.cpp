#include <iostream>
#include "Graph.h"
#include "reads.h"

using namespace std;
void menu(Graph& graph) {
    bool canRun = true;
    bool canRun1 = true;
    string start,end;
    while(canRun){
        int input;
        cout << "What areas do you wish to inspect?\n"
                "1: Number of trains\n"
                "2: Budget\n"
                "3: Failures\n"
                "0: End Program\n";
        while (!(cin >> input)) {
            cout << "Invalid input!\n\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "What areas do you wish to inspect?\n"
                    "1: Number of trains\n"
                    "2: Budget\n"
                    "3: Failures\n"
                    "0: End Program\n";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        canRun1= true;
        int input2;
        switch (input) {
            case 0:
                canRun = false;
                break;
            case 1:{
                while(canRun1){
                    cout << "What areas do you wish to inspect?\n"
                            "1: 2.1 Max number of trains that can travel between 2 stations\n"
                            "2: 2.2 The 2 stations with the highest number of trains that can travel between them\n"
                            "3: 2.4 Max number of trains that can arrive in 1 station simultaneously\n"
                            "9: Go back\n"
                            "0: End Program\n";
                    while (!(cin >> input2)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "What areas do you wish to inspect?\n"
                                "1: 2.1 Max number of trains that can travel between 2 stations\n"
                                "2: 2.2 The 2 stations with the highest number of trains that can travel between them\n"
                                "3: 2.4 Max number of trains that can arrive in 1 station simultaneously\n"
                                "9: Go back\n"
                                "0: End Program\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    switch (input2) {
                        case 0:
                            canRun = false;
                            canRun1 = false;
                            break;
                        case 1:{
                            cout << "Input First Station:\n";
                            getline(cin, start);
                            cin.clear();
                            while (graph.findStation(start)==nullptr) {
                                cout << "Invalid input!\n\n";
                                cout << "Input First Station:\n";
                                getline(cin, start);
                                cin.clear();
                            }
                            cout << "Input Second Station:\n";
                            getline(cin, end);
                            cin.clear();
                            while (graph.findStation(end)==nullptr) {
                                cout << "Invalid input!\n\n";
                                cout << "Input Second Station:\n";
                                getline(cin, end);
                                cin.clear();
                            }
                            graph.maxTrains(start, end);
                            break;
                        }
                        case 2:{
                            graph.stationPairs();
                            break;
                        }
                        case 3:{
                            cout << "Input Station:\n";
                            getline(cin, start);
                            cin.clear();
                            while (graph.findStation(start)==nullptr) {
                                cout << "Invalid input!\n\n";
                                cout << "Input Station:\n";
                                getline(cin, start);
                                cin.clear();
                            }
                            graph.maxTrainsInStation(start);
                            break;
                        }
                        case 9:{
                            canRun1= false;
                            break;
                        }
                    }
                }
                break;
            }
            case 2:{
                while(canRun1) {
                    cout << "What areas do you wish to inspect?\n"
                            "1: 2.3 top k municipality that requires a higher budget\n"
                            "2: 2.3 top k district that requires a higher budget\n"
                            "3: 2.3 top k township that requires a higher budget\n"
                            "4: 3.1 Max number of trains that can travel between 2 stations at a minimum cost\n"
                            "9: Go back\n"
                            "0: End Program\n";
                    while (!(cin >> input2)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "What areas do you wish to inspect?\n"
                                "1: 2.3 top k municipality that requires a higher budget\n"
                                "2: 2.3 top k district that requires a higher budget\n"
                                "3: 2.3 top k township that requires a higher budget\n"
                                "4: 3.1 Max number of trains that can travel between 2 stations at a minimum cost\n"
                                "9: Go back\n"
                                "0: End Program\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    switch (input2) {
                        case 0:
                            canRun1 = false;
                            canRun = false;
                            break;
                        case 1:{
                            int k;
                            cout << "Input K:\n";
                            while (!(cin >> k)) {
                                cout << "Invalid input!\n\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Input K:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            graph.printTopKHigherBudget("municipality", k);
                            break;
                        }
                        case 2:{
                            int k;
                            cout << "Input K:\n";
                            while (!(cin >> k)) {
                                cout << "Invalid input!\n\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Input K:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            graph.printTopKHigherBudget("district", k);
                            break;
                        }
                        case 3:{
                            int k;
                            cout << "Input K:\n";
                            while (!(cin >> k)) {
                                cout << "Invalid input!\n\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Input K:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            graph.printTopKHigherBudget("township", k);
                            break;
                        }
                        case 4:{
                            cout << "Input First Station:\n";
                            getline(cin, start);
                            cin.clear();
                            while (graph.findStation(start)==nullptr) {
                                cout << "Invalid input!\n\n";
                                cout << "Input First Station:\n";
                                getline(cin, start);
                                cin.clear();
                            }
                            cout << "Input Second Station:\n";
                            getline(cin, end);
                            cin.clear();
                            while (graph.findStation(end)==nullptr) {
                                cout << "Invalid input!\n\n";
                                cout << "Input Second Station:\n";
                                getline(cin, end);
                                cin.clear();
                            }
                            graph.maxTrainsMinCost(start, end);
                            break;
                        }
                        case 9:{
                            canRun1 = false;
                            break;
                        }
                    }
                }
                break;
            }
            case 3:{
                while(canRun1) {
                    cout << "What areas do you wish to inspect?\n"
                            "1: 4.1 Max number of trains that can travel between 2 stations in a network of reduced connectivity\n"
                            "2: 4.2 Top k most affected stations in a network of reduced connectivity\n"
                            "9: Go back\n"
                            "0: End Program\n";
                    while (!(cin >> input2)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "What areas do you wish to inspect?\n"
                                "1: 4.1 Max number of trains that can travel between 2 stations in a network of reduced connectivity\n"
                                "2: 4.2 Top k most affected stations in a network of reduced connectivity\n"
                                "9: Go back\n"
                                "0: End Program\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    switch (input2) {
                        case 0:
                            canRun1 = false;
                            canRun = false;
                            break;
                        case 1:{
                            cout << "Input First Station:\n";
                            getline(cin, start);
                            cin.clear();
                            while (graph.findStation(start)==nullptr) {
                                cout << "Invalid input!\n\n";
                                cout << "Input First Station:\n";
                                getline(cin, start);
                                cin.clear();
                            }
                            cout << "Input Second Station:\n";
                            getline(cin, end);
                            cin.clear();
                            while (graph.findStation(end)==nullptr) {
                                cout << "Invalid input!\n\n";
                                cout << "Input Second Station:\n";
                                getline(cin, end);
                                cin.clear();
                            }
                            string segment1,segment2;
                            stack<pair<string, string>> failedSegments;
                            bool flag=true;
                            cout << "Input the segment failures (write done when done):\n";
                            while(flag){
                                cout << "Input First Station:\n";
                                getline(cin, segment1);
                                cin.clear();
                                while (segment1 != "done" && graph.findStation(segment1)==nullptr) {
                                    cout << "Invalid input!\n\n";
                                    cout << "Input First Station:\n";
                                    getline(cin, segment1);
                                    cin.clear();
                                }
                                if(segment1=="done"){
                                    flag = false;
                                    break;
                                }
                                cout << "Input Second Station:\n";
                                getline(cin, segment2);
                                cin.clear();
                                while (segment2 != "done" && graph.findStation(segment2)==nullptr) {
                                    cout << "Invalid input!\n\n";
                                    cout << "Input Second Station:\n";
                                    getline(cin, segment2);
                                    cin.clear();
                                }
                                if(segment2=="done"){
                                    flag = false;
                                    break;
                                }
                                if(!graph.isValidSegment(segment1,segment2)){
                                    cout << "The segment you entered doesn't exist!\n";
                                    continue;
                                }
                                else{
                                    failedSegments.emplace(segment1, segment2);
                                }
                            }
                            graph.maxTrainsFailure(start, end,failedSegments);
                            break;
                        }

                        case 2:{
                            int k;
                            cout << "Input k:\n";
                            while (!(cin >> k)) {
                                cout << "Invalid input!\n\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Input k:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');

                            string segment1,segment2;
                            stack<pair<string, string>> failedSegments;
                            bool flag=true;
                            cout << "Input the segment failures (write done when done):\n";
                            while(flag){
                                cout << "Input First Station:\n";
                                getline(cin, segment1);
                                cin.clear();
                                while (segment1 != "done" && graph.findStation(segment1)==nullptr) {
                                    cout << "Invalid input!\n\n";
                                    cout << "Input First Station:\n";
                                    getline(cin, segment1);
                                    cin.clear();
                                }
                                if(segment1=="done"){
                                    flag = false;
                                    break;
                                }
                                cout << "Input Second Station:\n";
                                getline(cin, segment2);
                                cin.clear();
                                while (segment2 != "done" && graph.findStation(segment2)==nullptr) {
                                    cout << "Invalid input!\n\n";
                                    cout << "Input Second Station:\n";
                                    getline(cin, segment2);
                                    cin.clear();
                                }
                                if(segment2=="done"){
                                    flag = false;
                                    break;
                                }
                                if(!graph.isValidSegment(segment1,segment2)){
                                    cout << "The segment you entered doesn't exist!\n";
                                    continue;
                                }
                                else{
                                    failedSegments.emplace(segment1,segment2);
                                }
                            }
                            graph.printTopKMostAffected(failedSegments, k);
                            break;
                        }
                        case 9:{
                            canRun1 = false;
                            break;
                        }
                    }
                }
                break;
            }
            default:{
                cout << "Invalid input!\n\n";
                break;
            }
        }
    }
}

int main() {
    Graph graph;
    readStations(&graph, "dataset/stations.csv");
    readNetwork(&graph, "dataset/network.csv");
    menu(graph);
    return 0;
}
