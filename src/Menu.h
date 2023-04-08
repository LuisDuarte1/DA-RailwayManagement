#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H

#include <iomanip>
#include <iostream>
#include "DatasetLoader.h"
#include <vector>
#include "graph/Graph.h"
#include "LineFailures.h"

class Menu {
public:
    int auxMenu(int maxOption, int minOption);
    void clearScreen();

    int mainMenu();

    int AboutUsMenu();

    int bsmMenu();

    int ocoMenu();

    int rsMenu();

    void menuController();

    //int choiceK();

    int dataLoaderMenu();
    void maximumTrainsReducedConnectivityMenu();
    void reportFailureSegmentMenu();
    Vertex * getValidStation(std::string displayQuery);
    Edge * getValidSegment(std::string displayQuery);
    bool getBooleanInputFromUser(std::string displayString, bool defaultEnter);
    int getIntegerInputFromUser(std::string displayString);
};


#endif //UNTITLED_MENU_H