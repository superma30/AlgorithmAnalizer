#include <iostream>
#include "matplotlibcpp.h"

/* mathplotlib-cpp
 * stats:
 * iterations
 * swaps
 * time
 *
 * - SINGLE
 *     stats
 *     graphs
 *
 * - COMPARE
 *     stats
 */

using namespace std;

void SingleMode();
void CompareMode();

void printMainMenu() {
    cout << "Welcome to Algorithm Analizer!\n------------------------------";
    cout << "What do you want to do?";
    cout << "1. Single - Get statistics and graphs for a single algorithm"<<endl;
    cout << "2. Compare - Compare statistics of two algorithms"<<endl;
    cout << "3. Exit"<<endl;
}

int main() {
    while (true) {
        printMainMenu();
        string input;
        bool validInput = false;
        do {
            cin >> input;
            if (input.length() == 1) {
                if (input == "1" || input == "2" || input == "3") {
                    validInput = true;
                }
            }
        }while (!validInput);
        if (input == "1") {
            SingleMode();
        }
        else if (input == "2") {
            CompareMode();
        }
        else if (input == "3") {
            return 0;
        }
    }
}




void SingleMode() {

}

void CompareMode() {

}