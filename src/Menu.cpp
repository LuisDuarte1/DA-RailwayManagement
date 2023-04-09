#include "Menu.h"
#include "LineFailures.h"

using namespace std;

Graph* graph;
string networkPath = DEFAULT_NETWORK_PATH;
string stationsPath = DEFAULT_STATIONS_PATH;
bool stayInMenu;

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
    << "2.Pair of stations requiring the most amount of trains\n"
    << "3.Top-k stations requiring larger budgets\n"
    << "4.Maximum number of trains that can simultaneously arrive at a station\n"
    <<  "0.Return to main menu\n" << endl;
    cout << "Choose an option: ";
    return auxMenu(4,0);

}

int Menu::ocoMenu(){
    cout << endl << "OPERATION COST OPTIMIZATION MENU\n";
    cout << endl << "1.Choose station \n";
    cout << "0.Return to main menu\n";
    return auxMenu(1,0);
}

int Menu::rsMenu(){
    cout << endl << "RELIABILITY AND SENSITIVITY TO FAILURES MENU\n";
    cout << endl << "1.Maximum number of trains that can simultaneously travel between two stations in a reduced connectivity network\n";
    cout << "2.Most affected stations by segment failure\n";
    cout << "0.Return to main menu\n";
    cout << endl << "Choose an option: ";
    return auxMenu(2,0);
}

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

                            case 1: {
                                cout << endl;
                                Vertex * src = getValidStationv2("first");
                                Vertex * dst = getValidStationv2("second");
                                int result = graph->edmondsKarp(src, dst);
                                cout << "The max amount of trains travelling simultaneously between " << src->getStation().getName() << " and " << dst->getStation().getName() << " is " << result << endl;
                                stayInMenu = getBooleanInputFromUser("Do you wish to stay on this menu (y/n) ?", true);
                                if (stayInMenu){
                                    temp = 1;
                                    control = 0;
                                    break;
                                }
                                else{
                                    control = 0;
                                    temp = 0;
                                    break;
                                }
                            }

                            case 2: {
                                std::cout << std::endl;
                                std::pair<std::vector<std::pair<Vertex *, Vertex *>>, int> result;
                                result = graph->moreDemandingPairOfStations();
                                cout << "The most demanding pair of stations is " << result.first[0].first->getStation().getName() << " and " << result.first[0].second->getStation().getName() << " with " << result.second << " trains \n";
                                stayInMenu = getBooleanInputFromUser("Do you wish to stay on this menu (y/n) ?", true);
                                if (stayInMenu){
                                    temp = 1;
                                    control = 0;
                                    break;
                                }
                                else{
                                    control = 0;
                                    temp = 0;
                                    break;
                                }

                            }

                            case 3: {
                                std::cout << std::endl;
                                int k = getIntegerInputFromUser("Choose the value for k: ");
                                cout << endl;
                                bool useDistrict = getBooleanInputFromUser("Do you wish to see the result district-wise or municipality-wise (d or m respectively) ?", true);
                                std::cout << std::endl;
                                displayTopK(k, useDistrict);
                                stayInMenu = getBooleanInputFromUser("Do you wish to stay on this menu and alter the settings ?", true);
                                if (stayInMenu){
                                    break;
                                }
                                else{
                                    control = 0;
                                    temp = 0;
                                    break;
                                }
                            }

                            case 4:{
                                cout << endl;
                                Vertex * st = getValidStationv2("desired");
                                int result = graph->edmondsKarpSinkOnly(st);
                                cout << "The maximum amount of trains that can arrive at " << st->getStation().getName() << " is " << result << endl;
                                stayInMenu = getBooleanInputFromUser("Do you wish to stay on this menu and alter the station ?", true);
                                if (stayInMenu){
                                    break;
                                }
                                else{
                                    control = 0;
                                    temp = 0;
                                    break;
                                }
                            }

                            case 0 : {
                                temp = 0;
                            }

                            default: break;

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

                            case 1 : {
                                maximumTrainsReducedConnectivityMenu();
                                stayInMenu = getBooleanInputFromUser("Do you wish to continue on this menu ?", true);
                                if (stayInMenu){
                                    break;
                                }
                                else{
                                    control = 0;
                                    temp = 0;
                                    break;
                                }
                            }

                            case 2: {
                                cout << endl;
                                Edge* segment = getValidSegment("desired segment");
                                std::vector<std::pair<Vertex *, std::pair<int,int>>> result;
                                result = mostAffectedStationsOnSegmentFailure(graph, segment);
                                cout << "The most affected station on the removal of the chosen segment is " << result[0].first->getStation().getName() << " changing from " << result[0].second.second << " to " << result[0].second.first << endl;
                                stayInMenu = getBooleanInputFromUser("Do you wish to stay on this menu and alter the segment ?", true);
                                if (stayInMenu){
                                    break;
                                }
                                else{
                                    control = 0;
                                    temp = 0;
                                    break;
                                }

                            }

                            case 0 : {
                                temp = 0;
                            }

                            default:break;
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

                default: break;

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

Vertex* Menu::getValidStation(std::string displayQuery) {
    std::cin.sync();
    Vertex* v;
    do {
        std::cout << "Please select a " << displayQuery << " station: ";
        std::string station;
        std::getline(std::cin, station);
        std::cout << "\n";
        v = graph->findVertex(station);
        if(v == nullptr) std::cout << "Invalid station name... please try again..\n\n";
    } while(v == nullptr);
    return v;
}

Vertex* Menu::getValidStationv2(std::string displayQuery) {
    std::cin.sync();
    Vertex* v;
    do {
        std::cout << "Please select the " << displayQuery << " station: ";
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
        cin.clear();
        cin.sync();
        std::cout << displayString;
        char choice = 0;
        std::cin >> choice;
        if(choice == 0 || choice == 10 ){
            return defaultEnter;
        } else if(choice == 'y' || choice == 'Y'){
            return true;
        } else if ( choice == 'n' || choice == 'N'){
            return false;
        } else if ( choice == 'd' || choice == 'D'){
            return true;
        } else if ( choice == 'm' || choice == 'M'){
            return false;
        }

        std::cout << "\n Option not valid... try again...\n";
    }
}

int Menu::getIntegerInputFromUser(std::string displayString) {
    while (true) {
        int r = 0;
        std::cout << displayString;
        if((std::cin >> r).good() && r < graph->getNumVertex()){
            return r;
        }
        std::cout << "Invalid input... only a number is accepted... try again...\n";
    }
}

void Menu::displayTopK(int k, bool useDistricts){
    std::vector<std::pair<std::string, float>> municipalitiesHighestAverage;
    std::vector<std::pair<std::string, int>> municipalitiesHighestBottleneck;
    std::vector<std::pair<std::string, int>> municipalitiesMoreStations;
    graph->findTopK(municipalitiesHighestAverage, municipalitiesHighestBottleneck, municipalitiesMoreStations, k, useDistricts);


    const int tableWidth = 80;

    std::cout << std::setfill(' ') << std::left << std::setw(50) << "Municipalities with highest weighted average (stations with higher flow are more important to calculate the mean): \n"
              << std::setfill('=') << std::right << std::setw(tableWidth) << "" << std::endl;
    std::cout << std::setfill(' ') << std::left << std::setw(50) << "Municipality"
              << std::setfill(' ') << std::right << std::setw(30) << "Value" << std::endl;
    std::cout << std::setfill('-') << std::setw(tableWidth) << "" << std::endl;
    for (auto el: municipalitiesHighestAverage) {
        std::cout << std::setfill(' ') << std::left << std::setw(50) << el.first
                  << std::setfill(' ') << std::right << std::setw(30) << el.second << std::endl;
    }
    std::cout << std::setfill('=') << std::setw(tableWidth) << "" << std::endl;

    std::cout << std::endl;

    std::cout << std::setfill(' ') << std::left << std::setw(50) << "Municipalities with highest bottleneck: "
              << std::setfill(' ') << std::right << std::setw(30) << "" << std::endl;
    std::cout << std::setfill('=') << std::setw(tableWidth) << "" << std::endl;
    std::cout << std::setfill(' ') << std::left << std::setw(50) << "Municipality"
              << std::setfill(' ') << std::right << std::setw(30) << "Value" << std::endl;
    std::cout << std::setfill('-') << std::setw(tableWidth) << "" << std::endl;
    for (auto el: municipalitiesHighestBottleneck) {
        std::cout << std::setfill(' ') << std::left << std::setw(50) << el.first
                  << std::setfill(' ') << std::right << std::setw(30) << el.second << std::endl;
    }
    std::cout << std::setfill('=') << std::setw(tableWidth) << "" << std::endl;

    std::cout << std::endl;

    std::cout << std::setfill(' ') << std::left << std::setw(50) << "Municipalities with more stations: "
              << std::setfill(' ') << std::right << std::setw(30) << "" << std::endl;
    std::cout << std::setfill('=') << std::setw(tableWidth) << "" << std::endl;
    std::cout << std::setfill(' ') << std::left << std::setw(50) << "Municipality"
              << std::setfill(' ') << std::right << std::setw(30) << "Value" << std::endl;
    std::cout << std::setfill('-') << std::setw(tableWidth) << "" << std::endl;
    for (auto el: municipalitiesMoreStations) {
        std::cout << std::setfill(' ') << std::left << std::setw(50) << el.first
                  << std::setfill(' ') << std::right << std::setw(30) << el.second << std::endl;
    }
    std::cout << std::setfill('=') << std::setw(tableWidth) << "" << std::endl;
}

