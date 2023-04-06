#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H

#include <iomanip>
#include <iostream>
#include "DatasetLoader.h"

class Menu {
public:

    int auxMenu(int maxOption, int minOption);

    static std::string toLowerString;

    void clearScreen();

    int mainMenu();

    int AboutUsMenu();

    int bsmMenu();

    int ocoMenu();

    int rsMenu();

    void menuController();

    //int choiceK();

    int dataLoaderMenu();

};


#endif //UNTITLED_MENU_H