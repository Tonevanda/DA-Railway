#include <iostream>
#include "Graph.h"
#include "reads.h"
#include <chrono>

using namespace std;
void menu(Graph graph) {
    bool canRun = true;
    bool canRun1 = true;
    string start,end;
    while(canRun){
        int input;
        cout << "What areas do you wish to inspect?\n"
                "1: Number of trains\n"
                "2: Budget\n"
                "3: failiures\n"
                "0: End Program\n";
        while (!(cin >> input)) {
            cout << "Invalid input!\n\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "What areas do you wish to inspect?\n"
                    "1: Number of trains\n"
                    "2: Budget\n"
                    "3: failiures\n"
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
                            "1: 2.1\n"
                            "2: 2.2\n"
                            "3: 2.4\n"
                            "4: 4.1\n"
                            "9: Go back\n"
                            "0: End Program\n";
                    while (!(cin >> input2)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "What areas do you wish to inspect?\n"
                                "1: 2.1\n"
                                "2: 2.2\n"
                                "3: 2.4\n"
                                "4: 4.1\n"
                                "9: Go back\n"
                                "0: End Program\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    switch (input) {
                        case 0:
                            canRun = false;
                            canRun1 = false;
                            break;
                        case 1:{
                            cout << "Input First Station:\n";
                            while (!(cin >> start)) {
                                cout << "Invalid input!\n\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Input First Station:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cout << "Input Second Station:\n";
                            while (!(cin >> end)) {
                                cout << "Invalid input!\n\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Input Second Station:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            double maxFlow = graph.edmondsKarp(start, end);
                            cout << "Máximo número de comboios simultâneos: " << maxFlow << "\n";
                            break;
                        }
                        case 2:{
                            //add 2.2
                            break;
                        }
                        case 3:{
                            cout << "Input Station:\n";
                            while (!(cin >> end)) {
                                cout << "Invalid input!\n\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Input Station:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            //add 2.4
                            break;
                        }
                        case 4:{
                            cout << "Input First Station:\n";
                            while (!(cin >> start)) {
                                cout << "Invalid input!\n\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Input First Station:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cout << "Input Second Station:\n";
                            while (!(cin >> end)) {
                                cout << "Invalid input!\n\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Input Second Station:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            //add 4.1
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
                            "1: 2.3\n"
                            "2: 3.1\n"
                            "9: Go back\n"
                            "0: End Program\n";
                    while (!(cin >> input2)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "What areas do you wish to inspect?\n"
                                "1: 2.3\n"
                                "2: 3.1\n"
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
                            graph.printTopK("municipality", 100);
                            break;
                        }
                        case 2:{
                            cout << "Input First Station:\n";
                            while (!(cin >> start)) {
                                cout << "Invalid input!\n\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Input First Station:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cout << "Input Second Station:\n";
                            while (!(cin >> end)) {
                                cout << "Invalid input!\n\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Input Second Station:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            //add 3.1
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
                            "1: 4.2\n"
                            "2: 5.1??????\n"
                            "9: Go back\n"
                            "0: End Program\n";
                    while (!(cin >> input2)) {
                        cout << "Invalid input!\n\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "What areas do you wish to inspect?\n"
                                "1: 4.2\n"
                                "2: 5.1??????\n"
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

                            //add 4.2
                            break;
                        }
                        case 2:{
                            //não faço a puta da minima ideia do que por aqui
                            //add 5.1
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
    auto start = chrono::steady_clock::now();
    Graph graph = Graph();
    readStations(&graph, "dataset/testStations.csv");
    readNetwork(&graph, "dataset/testNetwork.csv");
    menu(graph);
    //double maxFlow = graph.edmondsKarp("Porto Campanhã", "Estarreja");//2.1
    //cout << "Máximo número de comboios simultâneos: " << maxFlow << "\n";
    //graph.pairs();
    //graph.printTopK("municipality", 100);
    //graph.sinks();
    //graph
    //graph.printTopK("municipality", 5);
    auto end = chrono::steady_clock::now();
    double elapsed_time = double(chrono::duration_cast<chrono::milliseconds>(end - start).count());
    cout << "Took " << elapsed_time << " milliseconds to finish!\n";
    return 0;
}


/*Menu prototype
 *  Doesn't require extra input-2.2,4.2
 *  Requires extra user given input-2.1,2.3,2.4,3.1,4.1
 *
 *  From the input ones,
 *  The ones that require a number-2.3
 *  The ones that require 1 station-2.4
 *  The ones that require 2 stations-2.1,3.1,4.1
 * */

/*
 *  1.1-Menu
 *
 *  1.3-Doxygen
 *
 *  DONE 2.1-Calculate the maximum number of trains that can simultaneously travel between
    two specific stations. -> Max Flow ig -> graph.edmondsKarp("Porto Campanhã", "Estarreja"); - trains
 *
 *  DONE 2.2-Determine, from all pairs of stations, which ones (if more than one) require the
    most amount of trains when taking full advantage of the existing network capacity; -> graph.pairs(); - trains
 *
 *  2.3-Top-k municipalities and districts with higher budget; - budget -> Kinda done, mas tp, falta saber source e sink ig :thumbs_down:
 *
 *  2.4-Report the maximum number of trains that can simultaneously arrive at a given station, -trains
    taking into consideration the entire railway grid. // capacidade :thumbs_up:
 *
 *  3.1-Calculate the maximum amount of trains that can simultaneously travel between
    two specific stations with minimum cost for the company. Note that your system should also take any -budget
    valid source and destination stations as input;
 *
 *  4.1-Calculate the maximum number of trains that can simultaneously travel between
    two specific stations in a network of reduced connectivity. Reduced connectivity is understood as being - trains
    a subgraph (generated by your system) of the original railway network. Note that your system should
    also take any valid source and destination stations as input;
 *
 *  4.2-Provide a report on the stations that are the most affected by each segment failure, - failure
    i.e., the top-k most affected stations for each segment to be considered.
 *
 *  5.1-Use the (hopefully) user-friendly interface you have developed to illustrate the
    various algorithm results for a sample set of railway grids which you should develop specifically for the - failure
    purposes of this demo. For instance, you can develop a small set of very modest railway networks for
    contrived capacities so that you can highlight the “correctness” of your solution. For instance, a grid
    that has a “constricted” segment where all traffic must go through, will clearly have a segment very
    “sensitive” to failures.
 * */
