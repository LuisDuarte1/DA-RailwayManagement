#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H

#include <iomanip>
#include <iostream>
#include "DatasetLoader.h"
#include <vector>
#include "graph/Graph.h"
#include "LineFailures.h"
#include <limits>

class Menu {
public:
    /**
     * Auxiliary menu to return a user's choice.
     * Complexity: O(1)
     * @param maxOption User's max option
     * @param minOption User's min option
     * @return
     */
    int auxMenu(int maxOption, int minOption);

    /**
     * Auxiliary function to clear the terminal's screen.
     * Complexity: O(1)
     */
    void clearScreen();

    /**
     * Simple menu used for facilitating the user's interaction with the program.
     * Complexity: O(1)
     * @return User's choice
     */
    int mainMenu();

    /**
    * Simple menu used for facilitating the user's interaction with the program.
    * Complexity: O(1)
    * @return User's choice
    */
    int AboutUsMenu();

    /**
    * Simple menu used for facilitating the user's interaction with the program.
    * Complexity: O(1)
    * @return User's choice
    */
    int bsmMenu();

    /**
    * Simple menu used for facilitating the user's interaction with the program.
    * Complexity: O(1)
    * @return User's choice
    */
    int ocoMenu();

    /**
    * Simple menu used for facilitating the user's interaction with the program.
    * Complexity: O(1)
    * @return User's choice
    */
    int rsMenu();

    void menuController();

    /**
    * Simple menu used for facilitating the user's interaction with the program.
    * Complexity: O(1)
    * @return User's choice
    */
    int dataLoaderMenu();

    void maximumTrainsReducedConnectivityMenu();

    void reportFailureSegmentMenu();

    Vertex * getValidStation(std::string displayQuery);

    Vertex* getValidStationv2(std::string displayQuery);

    Edge * getValidSegment(std::string displayQuery);

    bool getBooleanInputFromUser(std::string displayString, bool defaultEnter);

    int getIntegerInputFromUser(std::string displayString);

    void displayTopK(int k, bool useDistricts);
};


#endif //UNTITLED_MENU_H