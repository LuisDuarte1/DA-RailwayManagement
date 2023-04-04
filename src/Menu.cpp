#include <iostream>
#include "Menu.h"
#include "DatasetLoader.h"

Graph * graph;
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