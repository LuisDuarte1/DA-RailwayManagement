#ifndef DA_RAILWAYMANAGEMENT_MENU_H
#define DA_RAILWAYMANAGEMENT_MENU_H


#include <vector>
#include "graph/Graph.h"
#include "LineFailures.h"

class Menu {
public:
    Menu();
    void mainMenu();
    void clearScreen();
private:
    Graph * graph;

    void printOptions(std::vector<std::string> options);

    bool validOption(char option, int max);
    void maximumTrainsReducedConnectivityMenu();
    void reportFailureSegmentMenu();
    Vertex * getValidStation(std::string displayQuery);
    Edge * getValidSegment(std::string displayQuery);
    bool getBooleanInputFromUser(std::string displayString, bool defaultEnter);
    int getIntegerInputFromUser(std::string displayString);
};


#endif //DA_RAILWAYMANAGEMENT_MENU_H
