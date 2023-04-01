#ifndef DA_RAILWAYMANAGEMENT_MENU_H
#define DA_RAILWAYMANAGEMENT_MENU_H


#include <vector>

class Menu {
public:
    Menu();
    void mainMenu();
    void clearScreen();
private:

    void printOptions(std::vector<std::string> options);

    bool validOption(char option, int max);
};


#endif //DA_RAILWAYMANAGEMENT_MENU_H
