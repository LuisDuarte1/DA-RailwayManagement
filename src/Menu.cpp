#include "Menu.h"

using namespace std;

Graph* graph;
string networkPath = DEFAULT_NETWORK_PATH;
string stationsPath = DEFAULT_STATIONS_PATH;

int Menu::auxMenu(int maxOption, int minOption){
    int op;
    while (true) {
        std::cin >> op;
        if (std::cin.fail() || (op > maxOption || op < minOption)) {  // input is not an integer
            std::cout << "Please enter a valid integer: " ;
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

int Menu::dataLoaderMenu(){
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
                    do{
                        switch (control) {

                            case 0 : {
                                 temp = 0;
                            }

                        }
                    }while(control != 0);
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
