#include "Menu.h"
#include "LineFailures.h"
#include <cstdlib>
using namespace std;

Graph *graph;
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
    #ifdef _WIN32   // Windows
        system("cls");
    #else          // Linux
        std::cout << "\033[2J\033[1;1H";
    #endif
}

int Menu::dataLoaderMenu() {
    clearScreen();
    cout << endl << "DATA MANAGEMENT MENU \n" << endl;
    cout << "\t1. Use default data (PT network)" << endl;
    cout << "\t2. Use new data" << endl;
    cout << "\t0. Return to main menu" << endl;
    cout << "\nChoose an option: ";
    return auxMenu(2, 0);

}

int Menu::mainMenu() {
    //clearScreen();
    cout << "MAIN MENU\n\n";
    cout << "\t1. Basic Service Metrics" << endl
         << "\t2. Operation Cost Optimization" << endl
         << "\t3. Reliability and Sensitivity to Line Failures" << endl
         << "\t4. Change dataset" << endl
         << "\t5. About us" << endl << endl
         << "\t0. Quit" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "Choose an option: ";
    return auxMenu(5, 0);
}


int Menu::AboutUsMenu() {
    clearScreen();
    cout
            << "\nHelp platform for the management of railway transports created in favor of the Design of Algorithms course\n"
            << endl;
    cout << "Meet the team: \n\n";
    cout << left << setw(30) << "STUDENT NAME" << right << setw(18) << "STUDENT NUMBER" << setw(9) << endl << endl;
    cout << left << setw(30) << "Hélder Costa" << setfill(' ') << right << setw(18) << "202108719" << endl;
    cout << left << setw(30) << "Luís Duarte" << setfill(' ') << right << setw(18) << " 202108734" << endl;
    cout << left << setw(30) << "Luís Jesus" << setfill(' ') << right << setw(18) << " 202108683" << endl;
    cout << endl << "0.Return to main menu \n" << endl;
    cout << "Choose an option: ";
    return auxMenu(0, 0);
}

int Menu::bsmMenu() {
    clearScreen();
    cout << endl << "BASIC SERVICE METRICS MENU\n" << endl;
    cout << "\t1. Maximum trains travelling simultaneously between two stations" << endl
         << "\t2. Pair of stations requiring the most amount of trains" << endl
         << "\t3. Top-k stations requiring larger budgets" << endl
         << "\t4. Maximum number of trains that can simultaneously arrive at a station" << endl
         << "\t0. Return to main menu" << endl << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "Choose an option: ";
    return auxMenu(4, 0);

}

int Menu::ocoMenu() {
    clearScreen();
    cout << endl << "OPERATION COST OPTIMIZATION MENU\n";
    cout << endl << "\t1. Choose source and destination stations \n";
    cout << "\t0.Return to main menu\n";
    cout << endl << "Choose an option: ";
    return auxMenu(1, 0);
}

int Menu::rsMenu() {
    clearScreen();
    cout << endl << "RELIABILITY AND SENSITIVITY TO FAILURES MENU\n";
    cout << endl
         << "\t1. Max Number of trains that can simultaneously travel between 2 stations (reduced connectivity network)\n";
    cout << "\t2. Most affected stations by segment failure\n";
    cout << "\t0. Return to main menu\n";
    cout << endl << "Choose an option: ";
    return auxMenu(2, 0);
}

void Menu::menuController() {
    int op;
    graph = loadDataset(networkPath, stationsPath);
    clearScreen();
    cout << endl << "Welcome to the support platform for the management of railway transports!" << endl << endl;
    cout << "--------------------RAILWAY ANALYSIS SYSTEM--------------------" << endl;
    do {
        int temp;
        op = mainMenu();
        do {
            switch (op) {
                case 1: {
                    int control = bsmMenu();
                    do {
                        switch (control) {
                            case 1: {
                                clearScreen();
                                Vertex *src = getValidStationv2("origin/source");
                                Vertex *dst = getValidStationv2("sink/destination");
                                int result = graph->edmondsKarp(src, dst);
                                cout << "The max amount of trains travelling simultaneously between "
                                     << src->getStation().getName() << " and " << dst->getStation().getName() << " is "
                                     << result << "." << endl << endl;
                                stayInMenu = getBooleanInputFromUser("Do you wish to stay on this menu (y/n)? ", true);
                                if (stayInMenu) {
                                    temp = 1;
                                    control = 0;
                                    break;
                                } else {
                                    clearScreen();
                                    control = 0;
                                    temp = 0;
                                    break;
                                }
                            }

                            case 2: {
                                clearScreen();
                                std::cout << std::endl;
                                std::pair<std::vector<std::pair<Vertex *, Vertex *>>, int> result;
                                std::cout << "\n\t\tCalculating..." << std::endl << std::endl,
                                        result = graph->moreDemandingPairOfStations();
                                clearScreen();
                                cout << "The most demanding pair(s) of stations are: " << endl << endl;
                                for (auto &i: result.first) {
                                    cout << "- " << i.first->getStation().getName() << " and "
                                         << i.second->getStation().getName() << endl;
                                }
                                cout << endl << "The amount of trains that can travel simultaneously is "
                                     << result.second << "." << endl << endl;
                                stayInMenu = getBooleanInputFromUser("Do you wish to stay on this menu (y/n) ?", true);
                                if (stayInMenu) {
                                    temp = 1;
                                    control = 0;
                                    break;
                                } else {
                                    clearScreen();
                                    control = 0;
                                    temp = 0;
                                    break;
                                }

                            }

                            case 3: {
                                clearScreen();
                                int k = getIntegerInputFromUser("Choose the value for K (number of locations): ");
                                cout << endl;
                                bool useDistrict = getBooleanInputFromUser(
                                        "Do you wish to see the result district-wise or municipality-wise (d or m respectively)? ",
                                        true);
                                std::cout << std::endl;
                                displayTopK(k, useDistrict);
                                stayInMenu = getBooleanInputFromUser(
                                        "Do you wish to stay on this menu and change the settings? ", true);
                                if (stayInMenu) {
                                    break;
                                } else {
                                    clearScreen();
                                    control = 0;
                                    temp = 0;
                                    break;
                                }
                            }

                            case 4: {
                                clearScreen();
                                cout << endl;
                                Vertex *st = getValidStationv2("desired");
                                int result = graph->edmondsKarpSinkOnly(st);
                                cout << "The maximum amount of trains that can arrive at " << st->getStation().getName()
                                     << " is " << result << endl;
                                stayInMenu = getBooleanInputFromUser(
                                        "\nDo you wish to stay on this menu and change the station? ", true);
                                if (stayInMenu) {
                                    break;
                                } else {
                                    clearScreen();
                                    control = 0;
                                    temp = 0;
                                    break;
                                }
                            }

                            case 0 : {
                                temp = 0;
                            }

                            default:
                                break;

                        }
                    } while (control != 0);
                    break;
                }

                case 2: {
                    int control = ocoMenu();
                    do {
                        switch (control) {
                            case 1 : {
                                clearScreen();
                                Vertex *src = getValidStationv2("origin/source");
                                Vertex *dst = getValidStationv2("sink/destination");
                                if (stayInMenu) {
                                    break;
                                } else {
                                    clearScreen();
                                    control = 0;
                                    temp = 0;
                                    break;
                                }
                            }
                            case 0 : {
                                temp = 0;
                            }
                        }
                    } while (control != 0);
                    break;
                }

                case 3: {
                    int control = rsMenu();
                    do {
                        switch (control) {
                            case 1 : {
                                clearScreen();
                                maximumTrainsReducedConnectivityMenu();
                                stayInMenu = getBooleanInputFromUser("\nDo you wish to continue on this menu? ", true);
                                if (stayInMenu) {
                                    break;
                                } else {
                                    clearScreen();
                                    control = 0;
                                    temp = 0;
                                    break;
                                }
                            }

                            case 2: {
                                clearScreen();
                                int k = getIntegerInputFromUser("Choose the number of entries to display: ");
                                clearScreen();
                                Edge *segment = getValidSegment("desired segment");
                                std::vector<std::pair<Vertex *, std::pair<int, int>>> result;
                                result = mostAffectedStationsOnSegmentFailure(graph, segment);
                                clearScreen();
                                cout << "The most affected stations on the removal of the chosen segment are: " << endl
                                     << endl;
                                for (int i = 0; i < k; i++) {
                                    cout << "- " << result[i].first->getStation().getName()
                                         << " with an initial maximum amount of trains of " << result[i].second.first
                                         << " and a final maximum amount of trains of " << result[i].second.second
                                         << endl;
                                }

                                stayInMenu = getBooleanInputFromUser(
                                        "\nDo you wish to stay on this menu and change the segment? ", true);
                                if (stayInMenu) {
                                    break;
                                } else {
                                    control = 0;
                                    temp = 0;
                                    break;
                                }

                            }

                            case 0 : {
                                temp = 0;
                            }

                            default:
                                break;
                        }
                    } while (control != 0);
                    break;
                }

                case 4: {
                    int control = dataLoaderMenu();
                    do {
                        switch (control) {
                            case 1: {
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

                                    if (networkPath == "q" || networkPath == "Q") {
                                        control = 1;
                                        break;
                                    }

                                    cout << "Path for the stations file:";
                                    cin >> stationsPath;
                                    cout << endl;

                                    if (stationsPath == "q" || stationsPath == "Q") {
                                        control = 1;
                                        break;
                                    }

                                    graph = loadDataset(networkPath, stationsPath);

                                    if (graph != nullptr) break;

                                    cout
                                            << "Make sure you entered the correct paths, write 'q' to revert to default data and go to main menu\n";
                                }
                                control = 0;
                                temp = 0;
                                break;
                            }

                            case 0: {
                                temp = 0;
                                break;
                            }

                        }

                    } while (control != 0);
                    break;
                }

                case 5: {
                    temp = AboutUsMenu();
                    break;
                }


                case 0: {
                    temp = 0;
                    break;
                }

                default:
                    break;

            }

        } while (temp != 0);
        clearScreen();

    } while (op != 0);
    cout << "\n";
    cout << "Thank you for using our platform!" << endl;
}

void Menu::maximumTrainsReducedConnectivityMenu() {
    std::cout << "======================================================" << std::endl << std::endl;
    Vertex *src = getValidStation("source");
    Vertex *dst = getValidStation("destination");
    std::vector<Edge *> segmentsToExclude;
    clearScreen();
    while (true) {
        Edge *edge = getValidSegment("BROKEN SEGMENT (the segment that will be removed from the network)");
        segmentsToExclude.push_back(edge);
        clearScreen();
        if (!getBooleanInputFromUser("Do you wish to insert more segments (y/n): ", false)) break;
    }
    int normalFlow = graph->edmondsKarp(src, dst);
    int result = maximumTrainsReducedConnectivity(graph, segmentsToExclude, src, dst);
    std::cout << "\nRESULTS: " << std::endl;
    std::cout << "- With reduced connectivity: \t Max-Flow:" << result << "\n";
    std::cout << "- Normal Network: \t Max-Flow:" << normalFlow << "\n";
}

void Menu::reportFailureSegmentMenu() {
    std::cout << "======================================================" << std::endl << std::endl;
    Edge *edge = getValidSegment("segment to fail");
    auto mostAffectedStations = mostAffectedStationsOnSegmentFailure(graph, edge);
    int topK = getIntegerInputFromUser("How many results do you want to display (top-k): ");
    for (int i = 0; i < mostAffectedStations.size() && i < topK; i++) {
        std::cout << mostAffectedStations[i].first->getStation().getName() << " :\t" <<
                  abs(mostAffectedStations[i].second.first - mostAffectedStations[i].second.second) << "\n";
    }
}

Vertex *Menu::getValidStation(std::string displayQuery) {
    Vertex *v;
    do {
        std::cout << "Please select a " << displayQuery << " station: ";
        std::string station;
        do {
            std::getline(std::cin, station);
        } while (station.empty());
        v = graph->findVertex(station);
        std::cout << endl;
        if (v == nullptr) std::cout << "Invalid station name... please try again..\n\n";
    } while (v == nullptr);
    return v;
}

Vertex *Menu::getValidStationv2(std::string displayQuery) {
    Vertex *v;
    do {
        std::cout << "Please select the " << displayQuery << " station: ";
        std::cin.clear(); // clear any error flags on the cin stream
        std::string station;
        do {
            std::getline(std::cin, station);
        } while (station.empty());
        v = graph->findVertex(station);
        std::cout << endl;
        if (v == nullptr) std::cout << "Invalid station name... please try again..\n\n";
    } while (v == nullptr);
    return v;
}

Edge *Menu::getValidSegment(std::string displayQuery) {
    std::cout << "PLEASE SELECT THE " << displayQuery << std::endl << std::endl;
    while (true) {
        Vertex *src = getValidStation("segment start");
        Vertex *dst = getValidStation("segment end");
        for (auto edge: src->getEdges()) {
            if (edge->getDest() == dst) {
                std::cout << "========================\n\n";
                return edge;
            }
        }
        clearScreen();
        std::cout << src->getStation().getName() << " is not adjacent to " << dst->getStation().getName()
                  << "... try again\n";

    }
}

bool Menu::getBooleanInputFromUser(std::string displayString, bool defaultEnter) {
    while (true) {
        cin.clear();
        cin.sync();
        std::cout << displayString;
        char choice = 0;
        std::cin >> choice;
        if (choice == 0 || choice == 10) {
            return defaultEnter;
        } else if (choice == 'y' || choice == 'Y') {
            return true;
        } else if (choice == 'n' || choice == 'N') {
            return false;
        } else if (choice == 'd' || choice == 'D') {
            return true;
        } else if (choice == 'm' || choice == 'M') {
            return false;
        }

        std::cout << "\n Option not valid... try again...\n";
    }
}

int Menu::getIntegerInputFromUser(std::string displayString) {
    while (true) {
        std::cin.clear();
        int r = 0;
        std::cout << displayString;
        if ((std::cin >> r).good() && r < graph->getNumVertex()) {
            return r;
        }
        std::cout << "Invalid input... only a number is accepted... try again...\n";
    }
}

void Menu::displayTopK(int k, bool useDistricts) {
    std::vector<std::pair<std::string, float>> municipalitiesHighestAverage;
    std::vector<std::pair<std::string, int>> municipalitiesHighestBottleneck;
    std::vector<std::pair<std::string, int>> municipalitiesMoreStations;
    graph->findTopK(municipalitiesHighestAverage, municipalitiesHighestBottleneck, municipalitiesMoreStations, k,
                    useDistricts);


    const int tableWidth = 80;

    std::cout << std::setfill('=') << std::right << std::setw(tableWidth) << "" << std::endl;
    std::cout << std::setfill(' ') << std::left << std::setw(42) << "Municipality"
              << std::setfill(' ') << std::right << std::setw(20) << "Weighted Average Of Stations' Max-Flow"
              << std::endl;
    std::cout << std::setfill('-') << std::setw(tableWidth) << "" << std::endl;
    for (auto el: municipalitiesHighestAverage) {
        std::cout << std::setw(50) << std::setfill(' ') << std::left << el.first
                  << std::setw(30) << std::setfill(' ') << std::right << std::fixed << std::setprecision(2) << el.second
                  << std::endl;
    }
    std::cout << std::setfill('=') << std::setw(tableWidth) << "" << std::endl;

    std::cout << std::endl;

    std::cout << std::setfill(' ') << std::right << std::setw(30) << "" << std::endl;
    std::cout << std::setfill('=') << std::setw(tableWidth) << "" << std::endl;
    std::cout << std::setfill(' ') << std::left << std::setw(50) << "Municipality"
              << std::setfill(' ') << std::right << std::setw(30) << "Highest Bottleneck" << std::endl;
    std::cout << std::setfill('-') << std::setw(tableWidth) << "" << std::endl;
    for (auto el: municipalitiesHighestBottleneck) {
        std::cout << std::setfill(' ') << std::left << std::setw(50) << el.first
                  << std::setfill(' ') << std::right << std::setw(30) << el.second << std::endl;
    }
    std::cout << std::setfill('=') << std::setw(tableWidth) << "" << std::endl;

    std::cout << std::endl;

    std::cout << std::setfill(' ') << std::right << std::setw(30) << "" << std::endl;
    std::cout << std::setfill('=') << std::setw(tableWidth) << "" << std::endl;
    std::cout << std::setfill(' ') << std::left << std::setw(45) << "Municipality"
              << std::setfill(' ') << std::right << std::setw(30) << "Number Of Stations" << std::endl;
    std::cout << std::setfill('-') << std::setw(tableWidth) << "" << std::endl;
    for (auto el: municipalitiesMoreStations) {
        std::cout << std::setfill(' ') << std::left << std::setw(50) << el.first
                  << std::setfill(' ') << std::right << std::setw(30) << el.second << std::endl;
    }
    std::cout << std::setfill('=') << std::setw(tableWidth) << "" << std::endl;
}

