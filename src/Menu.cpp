#include "Menu.h"

using namespace std;

Graph* graph;
string networkPath = DEFAULT_NETWORK_PATH;
string stationsPath = DEFAULT_STATIONS_PATH;

int Menu::auxMenu(int maxOption, int minOption) {
    int op;
    while (true) {
        std::cin >> op;
        if (std::cin.fail() || (op > maxOption || op < minOption)) {  // input is not an integer
            std::cout << "Please enter a valid integer: ";
            std::cin.clear();  // clear the error flag
            std::cin.ignore(10000, '\n');  // ignore the invalid input
        } else {
            break;  // input is valid, break the loop
        }
    }
    return op;
}

void Menu::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

int Menu::dataLoaderMenu() {
    cout << endl << "DATA MANAGEMENT MENU \n" << endl;
    cout << "1.Use default data (PT network)" << endl;
    cout << "2.Use new data" << endl;
    cout << "0.Return to main menu" << endl;
    cout << "Choose an option: ";
    return auxMenu(2,0);

}

int Menu::mainMenu() {
    cout << "\n";
    cout << "MAIN MENU\n\n";
    cout << "1.Basic Service Metrics" << '\n' << "2.Operation Cost Optimization" << '\n' << "3.Reliability and Sensitivity to Line Failures" << '\n' << "4.Change dataset" << '\n' << "5.About us" << '\n' << "0.Quit" << "\n";
    cout << "Choose an option: ";

    //reportFailureSegmentMenu();
    //maximumTrainsReducedConnectivityMenu();
    minCostMenu();

    Vertex *src = graph->findVertex("Porto Campanhã");
    Vertex *dst = graph->findVertex("Coimbra B");
    std::cout << "Max flow to sink node is " << graph->edmondsKarpSinkOnly(dst) << std::endl;
    char option;
    /*
    auto pair = graph->moreDemandingPairOfStations();
    for (auto el : pair.first) {
        std::cout << el.first->getStation().getName() << " " << el.second->getStation().getName() << " " << pair.second << std::endl;
    }
    */
    std::vector<std::pair<std::string, float>> municipalitiesHighestAverage;
    std::vector<std::pair<std::string, int>> municipalitiesHighestBottleneck;
    std::vector<std::pair<std::string, int>> municipalitesMoreStations;
    graph->findTopK(municipalitiesHighestAverage, municipalitiesHighestBottleneck, municipalitesMoreStations, 5, false);

    std::cout
            << "Municipalities with highest weighted average (stations with higher flow are more important to calculate the mean): "
            << std::endl;
    for (auto el: municipalitiesHighestAverage) {
        std::cout << el.first << " " << el.second << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Municipalities with highest bottleneck: " << std::endl;
    for (auto el: municipalitiesHighestBottleneck) {
        std::cout << el.first << " " << el.second << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Municipalities with more stations: " << std::endl;
    for (auto el: municipalitesMoreStations) {
        std::cout << el.first << " " << el.second << std::endl;
    }

    return auxMenu(5, 0);
}


int Menu::AboutUsMenu(){
    cout << "\nHelp platform for the management of railway transports created in favor of the Design of Algorithms course\n" << endl;
    cout << "Meet the team: \n";
    cout << left << setw(30) <<  "Student Name\t" << setw(18) << "Student number" << setw(9) << endl;
    cout << left << setw(30) <<  "Hélder Costa\t" << setw(18) << "202108719" << endl;
    cout << left << setw(30)  << "Luís Duarte\t"  << setw(18) << " 202108734" << endl;
    cout << left << setw(30)  << "Luís Jesus\t" << setw(18) << " 202108683" << endl;
    cout << endl << "0.Return to main menu \n";
    cout << "Choose an option: ";
    return auxMenu(0,0);
}

int Menu::bsmMenu(){
    cout << endl << "BASIC SERVICE METRICS MENU\n" << endl;
    cout << "1.Maximum trains travelling simultaneously between two stations\n"
    << "2.Pairs of stations requiring the most amount of trains\n"
    << "3.Stations requiring larger budgets\n"
    << "4.Maximum number of trains that can simultaneously arrive at a station\n"
    <<  "0.Return to main menu\n" << endl;
    cout << "Choose an option: ";
    return auxMenu(4,0);

}

int Menu::ocoMenu(){
    cout << endl << "OPERATION COST OPTIMIZATION MENU\n";
    cout << endl << "1.choose station \n";
    cout << "0.Return to main menu\n";
    return auxMenu(1,0);
}

int Menu::rsMenu(){
    cout << endl << "RELIABILITY AND SENSITIVITY TO FAILURES MENU\n";
    cout << endl << "1.Maximum number of trains that can simultaneously travel between two stations in a reduced connectivity network\n";
    cout << "2.Top-k most affected stations by segment failure\n";
    cout << "0.Return to main menu\n";
    cout << endl << "Choose an option: ";
    return auxMenu(2,0);
}

/*
int Menu::choiceK(){
    cout << endl << "Type a value for k: ";
    return auxMenu(3019,1);
}
*/

void Menu::menuController() {
    int op;
    graph = loadDataset(networkPath, stationsPath);
    cout << endl << "Welcome to the support platform for the management of railway transports!\n";
    do {
        int temp;
        op = mainMenu();
        do {
            switch (op) {
                case 1:{
                    int control = bsmMenu();
                    do{
                        switch (control) {
                            case 0 : {
                                temp = 0;
                            }

                        }
                    }while(control != 0);
                    break;
                }

                case 2:{
                    int control = ocoMenu();
                    do {
                        switch (control) {
                            case 0 : {
                                 temp = 0;
                            }
                        }
                    } while(control != 0);
                    break;
                }

                case 3:{
                    int control = rsMenu();
                    do{
                        switch (control) {
                            case 0 : {
                                temp = 0;
                            }
                        }
                    }while(control != 0);
                    break;
                }

                case 4:{
                    int control = dataLoaderMenu();
                    do {
                        switch (control) {
                            case 1:{
                                networkPath = DEFAULT_NETWORK_PATH;
                                stationsPath = DEFAULT_STATIONS_PATH;
                                graph = loadDataset(networkPath, stationsPath);
                                control = 0;
                                temp = 0;
                                break;
                            }

                            case 2: {
                                while (true) {
                                    cout << "\nInsert the paths for new data: " << "\n" << "Path for network file: ";
                                    cin >> networkPath;
                                    cout << endl;

                                    if (networkPath == "q" || networkPath == "Q"){
                                        control = 1;
                                        break;
                                    }

                                    cout << "Path for the stations file:";
                                    cin >> stationsPath;
                                    cout << endl;

                                    if (stationsPath == "q" || stationsPath == "Q"){
                                        control = 1;
                                        break;
                                    }

                                    graph = loadDataset(networkPath, stationsPath);

                                    if (graph != nullptr) break;

                                    cout << "Make sure you entered the correct paths, write 'q' to revert to default data and go to main menu\n";
                                }
                                control = 0;
                                temp = 0;
                                break;
                            }

                            case 0:{
                                temp = 0;
                                break;
                            }

                        }

                    }while(control != 0);
                    break;
                }

                case 5:{
                    temp = AboutUsMenu();
                    break;
                }


                case 0:{
                    temp = 0;
                    break;
                }

            }

        } while (temp != 0);

    } while (op != 0);
    cout << "\n";
    cout << "Thank you for using our platform!" << endl;
}

void Menu::maximumTrainsReducedConnectivityMenu() {
    std::cout << "======================================================" << std::endl << std::endl;
    Vertex * src = getValidStation("source");
    Vertex * dst = getValidStation("destination");
    std::vector<Edge*> segmentsToExclude;
    while(true){
        Edge * edge = getValidSegment("broken segment");
        segmentsToExclude.push_back(edge);
        if(!getBooleanInputFromUser("Do you wish to insert more segments (y/N): ", false)) break;
    }
    int normalFlow = graph->edmondsKarp(src, dst);
    int result = maximumTrainsReducedConnectivity(graph, segmentsToExclude, src, dst);
    std::cout << "Results: \n";
    std::cout << "With reduced connectivity: \t Flow:" << result << "\n";
    std::cout << "Normal Network: \t Flow:" << normalFlow << "\n";
}



void Menu::minCostMenu() {
    std::cout << "======================================================" << std::endl << std::endl;
    Vertex * src = getValidStation("source");
    Vertex * dst = getValidStation("dst");
    //Vertex * src = graph->findVertex("Lisboa Santa Apolónia");
    //Vertex * dst = graph->findVertex("Coimbra B");

    auto answers = getMinCostPaths(graph, src, dst);
    std::cout << "The optimal solution contains " << answers.size() << " paths...\n";
    for(auto path : answers){
        graph->resetFlow();
        graph->resetVisited();
        int cost = calculateCostOfPath(path);
        reconstructPath(path);
        int numberOfTrains = graph->findMinResidualAlongPath(src, dst);
        std::cout << "This path should be done with " << numberOfTrains << " trains.\n";
        std::cout << "The total cost per train is: " << cost << "€.\n\n";
        std::cout << "The total cost is: " << cost*numberOfTrains << "€.\n\n";
        std::cout << "\t" << path[0]->getDest()->getStation().getName() << "\n";
        std::cout << "\t^\n";
        std::cout << "\t|\n"; 
        std::cout << "\t|\n"; 
        for(auto it = path.begin(); it != (--path.end()); it++){
            std::cout << "\t" << (*it)->getOrigin()->getStation().getName() << "\n";
            std::cout << "\t^\n";
            std::cout << "\t|\n"; 
            std::cout << "\t|\n"; 
        }
        std::cout << "\t" << path[path.size()-1]->getOrigin()->getStation().getName() << "\n";
        std::cout << "===================" << std::endl << std::endl;

    }
}

void Menu::reportFailureSegmentMenu() {
    std::cout << "======================================================" << std::endl << std::endl;
    Edge * edge = getValidSegment("segment to fail");
    auto mostAffectedStations = mostAffectedStationsOnSegmentFailure(graph, edge);
    int topK = getIntegerInputFromUser("How many results do you want to display (top-k): ");
    for(int i = 0; i < mostAffectedStations.size() && i < topK; i++){
        std::cout << mostAffectedStations[i].first->getStation().getName() << " :\t" <<
                  abs(mostAffectedStations[i].second.first - mostAffectedStations[i].second.second) << "\n";
    }
}

Vertex * Menu::getValidStation(std::string displayQuery) {
    Vertex * v;
    do{
        std::cout << "Please select a " << displayQuery << " station: ";
        std::string station;
        std::getline(std::cin, station);
        std::cout << "\n";
        v = graph->findVertex(station);
        if(v == nullptr) std::cout << "Invalid station name... please try again..\n\n";
    } while(v == nullptr);
    return v;
}

Edge * Menu::getValidSegment(std::string displayQuery) {
    std::cout << "Please select the " << displayQuery << "\n";
    while(true){
        Vertex * src = getValidStation("segment start");
        Vertex * dst = getValidStation("segment end");
        for(auto edge : src->getEdges()){
            if(edge->getDest() == dst){
                std::cout << "========================\n\n";
                return edge;
            }
        }
        std::cout << src->getStation().getName() << " is not adjancent to " << dst->getStation().getName()
                  << "... try again\n";
    }
}

bool Menu::getBooleanInputFromUser(std::string displayString, bool defaultEnter) {
    while(true){
        std::cout << displayString;
        char choice = 0;
        std::cin >> choice;
        if(choice == 0 || choice == 10 ){
            return defaultEnter;
        } else if(choice == 'y' || choice == 'Y'){
            return true;
        } else if ( choice == 'n' || choice == 'N'){
            return false;
        }
        std::cout << "\n Option not valid... try again...\n";
    }
}

int Menu::getIntegerInputFromUser(std::string displayString) {
    while (true) {
        int r = 0;
        std::cout << displayString;
        if((std::cin >> r).good()){
            return r;
        }
        std::cout << "Invalid input... only a number is accepted... try again...\n";
    }
}

