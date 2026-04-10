#include <iostream>
#include <conio.h>
#include "matplotlibcpp.h"
#include "Algorithms.cpp"

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
 *     graphs
 */

using namespace std;

void SingleMode();
void CompareMode();

void printMainMenu() {
    cout << "Welcome to Algorithm Analizer!\n------------------------------\n";
    cout << "What do you want to do?\n";
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
        cout << "Press Enter to continue...";
        getch();
        cout << "\n\n\n";
    }
}


void SingleMode() {
    cout << "\n--- SINGLE MODE ---\n";
    cout << "\nWhich algorithm do you want to analyze?\n";

    for (int i = 1; i < Algorithm::AlgorithmNames::COUNT; i++) {
        cout << i << ". " << Algorithm::GetAlgorithmName(static_cast<Algorithm::AlgorithmNames>(i)) << endl;
    }

    int choice;
    bool validInput = false;

    do {
        cin >> choice;

        if (choice < 1 || choice >= Algorithm::COUNT) {
            cin.clear();
            cout << "Invalid choice. Try again.\n";
        } else {
            validInput = true;
        }
    } while (!validInput);

    int TestsCount = 20;

    int totalIterations = 0;
    int totalSwaps = 0;
    int totalTime = 0;

    int size = 10000;

    for (int t = 0; t < TestsCount; t++) {
        vector<int> data;

        for (int i = 0; i < size; i++) {
            data.push_back(rand() % 1000);
        }

        auto stats = Algorithm::CallAlgorithmByName(
            (Algorithm::AlgorithmNames)(choice),
            data
        );

        totalIterations += stats[0];
        totalSwaps += stats[1];
        totalTime += stats[2];
    }

    cout << "\n----- AVERAGE STATS (" << TestsCount << " runs) -----\n";
    cout << "Input size: " << size << "\n";
    cout << "-------------\n";
    cout << "Iterations: " << totalIterations / TestsCount << endl;
    cout << "Swaps:      " << totalSwaps / TestsCount << endl;
    cout << "Time (ms):  " << totalTime / TestsCount << endl;

    // Graph

    vector<int> sizes;
    vector<double> iterData;
    vector<double> swapData;
    vector<double> timeData;

    int maxSize = 10000;
    int step = 500;

    for (int s = 500; s <= maxSize; s += step) {
        vector<int> data;

        for (int i = 0; i < s; i++) {
            data.push_back(rand() % 1000);
        }
        auto stats = Algorithm::CallAlgorithmByName(static_cast<Algorithm::AlgorithmNames>(choice),data);

        double timeScale = 10000.0; // to make the value similar to the others and readable
        sizes.push_back(s);
        iterData.push_back((double)stats[0]); // iterations
        swapData.push_back((double)stats[1]); // swaps
        timeData.push_back((double)stats[2] * timeScale); // time
    }

    matplotlibcpp::figure_size(900, 600);

    matplotlibcpp::named_plot("Iterations", sizes, iterData);
    matplotlibcpp::named_plot("Swaps", sizes, swapData);
    matplotlibcpp::named_plot("Time (10E-4 ms)", sizes, timeData);

    matplotlibcpp::title("Algorithm Performance");
    matplotlibcpp::xlabel("Input Size");
    matplotlibcpp::ylabel("Value");

    matplotlibcpp::legend();
    matplotlibcpp::show();
}

void CompareMode() {
    cout << "\n--- COMPARE MODE ---\n";

    // First Algorithm
    cout << "Choose first algorithm:\n";
    for (int i = 1; i < Algorithm::COUNT; i++) {
        cout << i << ". " << Algorithm::GetAlgorithmName((Algorithm::AlgorithmNames)i) << endl;
    }

    int a;
    bool validInput = false;

    do {
        cin >> a;

        if (a < 1 || a >= Algorithm::COUNT) {
            cout << "Invalid choice. Try again.\n";
        } else {
            validInput = true;
        }
    } while (!validInput);

    // Second Algorithm
    cout << "Choose second algorithm:\n";
    for (int i = 1; i < Algorithm::COUNT; i++) {
        cout << i << ". " << Algorithm::GetAlgorithmName((Algorithm::AlgorithmNames)i) << endl;
    }

    int b;
    validInput = false;

    do {
        cin >> b;

        if (b < 1 || b >= Algorithm::COUNT) {
            cout << "Invalid choice. Try again.\n";
        } else {
            validInput = true;
        }
    } while (!validInput);

    // Stat selection
    cout << "\nWhich stat do you want to compare?\n";
    cout << "1. iterations\n2. swaps\n3. time\n";

    int stat;
    validInput = false;

    do {
        cin >> stat;

        if (stat < 1 || stat > 3) {
            cout << "Invalid stat. Try again.\n";
        } else {
            validInput = true;
        }
    } while (!validInput);

    int statIndex = stat - 1;

    // Graphs data
    vector<int> sizes;
    vector<double> dataA;
    vector<double> dataB;

    int maxSize = 10000;
    int step = 500;

    for (int s = 0; s <= maxSize; s += step) {
        vector<int> arr1, arr2;

        for (int i = 0; i < s; i++) {
            int val = rand() % 1000;
            arr1.push_back(val);
            arr2.push_back(val);
        }

        auto resA = Algorithm::CallAlgorithmByName((Algorithm::AlgorithmNames)a, arr1);
        auto resB = Algorithm::CallAlgorithmByName((Algorithm::AlgorithmNames)b, arr2);

        sizes.push_back(s);
        dataA.push_back(resA[statIndex]);
        dataB.push_back(resB[statIndex]);
    }

    // Graphs
    matplotlibcpp::figure_size(900, 600);

    matplotlibcpp::named_plot(Algorithm::GetAlgorithmName((Algorithm::AlgorithmNames)a), sizes, dataA);

    matplotlibcpp::named_plot(Algorithm::GetAlgorithmName((Algorithm::AlgorithmNames)b), sizes, dataB);

    string statName;
    if (stat == 1) statName = "iterations";
    if (stat == 2) statName = "swaps";
    if (stat == 3) statName = "time";

    matplotlibcpp::title("Algorithm Comparison (" + statName + ")");
    matplotlibcpp::xlabel("Input Size");
    matplotlibcpp::ylabel(statName);

    matplotlibcpp::legend();
    matplotlibcpp::show();
}