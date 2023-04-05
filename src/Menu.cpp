#include <iostream>
#include "Menu.h"
#include "DatasetLoader.h"

Menu::Menu() {
    graph = loadDataset(DEFAULT_NETWORK_PATH, DEFAULT_STATIONS_PATH);
    mainMenu();
}

void Menu::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void Menu::printOptions(std::vector<std::string> options) {
    for (int i = 0; i < options.size(); i++) {
        std::cout << options[i] << std::endl;
    }
}

bool Menu::validOption(char option, int max) {
    if (option < '0' || option > max + '0') {
        std::cout << "Invalid option. Please try again." << std::endl;
        return false;
    }
    return true;
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
        std::cout << mostAffectedStations[i].first->getStation().getName() << " : " << 
            mostAffectedStations[i].second << "\n";
    }

}

Vertex * Menu::getValidStation(std::string displayQuery)
{
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

Edge * Menu::getValidSegment(std::string displayQuery)
{
    "========================\n\n";
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

int Menu::getIntegerInputFromUser(std::string displayString)
{
    while (true)
    {
        int r = 0;
        std::cout << displayString;
        if((std::cin >> r).good()){
            return r;
        }
        std::cout << "Invalid input... only a number is accepted... try again...\n";
    }
    
}

void Menu::mainMenu() {
    clearScreen();
    // WE WILL NEED THESE OPTIONS IN MENU 3:
    // 1. With less cost for the company
    // 2. Despite the cost
    // 3. In a network with reduced connectivity
    std::vector<std::string> options = {"\t1. Stations' Info",
                                        "\t2. Max Flow Between Stations",
                                        "\t3. Pair of Stations requiring the most amount of trains",
                                        "\t4. Max Flow that can reach a Station",
                                        "\t5. Maintenance - More needed locations",
                                        "\t6. More affected stations for each segment"};
    std::cout << "======================================================" << std::endl << std::endl;
    std::cout << "\t  Portuguese Railway Analysis System  " << std::endl << std::endl;
    std::cout << "======================================================" << std::endl;
    std::cout << "0. EXIT" << std::endl;
    printOptions(options);
    
    reportFailureSegmentMenu();
    //maximumTrainsReducedConnectivityMenu();

    Vertex* src = graph->findVertex("Porto Campanhã");
    Vertex* dst = graph->findVertex("Coimbra B");
    std::cout << "Max flow to sink node is "  << graph->edmondsKarpSinkOnly(dst) << std::endl;
    char option;
    auto pair = graph->moreDemandingPairOfStations();
    for (auto el : pair.first) {
        std::cout << el.first->getStation().getName() << " " << el.second->getStation().getName() << " " << pair.second << std::endl;
    }
    std::vector<std::string> municipalities;
    graph->findTopKMunicipalities(municipalities, 6);
    for (auto el : municipalities) {
        std::cout << el << std::endl;
    }

    do {
        std::cout << "\nChoose an option: ";
        std::cin >> option;

    } while (!validOption(option, options.size()));

}