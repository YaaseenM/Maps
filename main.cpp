#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;
using std::map;

std::mt19937 random_mt;

int Random(int min, int max) {
    uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);
}

void RollDice(int numberOfRolls, int numberOfSides) {
    map<int, int> Dice;
    for (int i = 1; i <= numberOfSides; i++) {
        Dice.emplace(i, 0);
    }
    for (int i = 1; i <= numberOfRolls; i++) {
        int rng = Random(1, numberOfSides);
        int tempValue = Dice[rng];
        Dice[rng] = tempValue + 1;
    }
    for (int i = 1; i <= numberOfSides; i++) {
        cout << i << ": " << Dice[i] << endl;
    }
}

int main() {
    cout << "1. Random Numbers\n";
    cout << "2. State Info\n";

    int option;
    cin >> option;

    if (option == 1) {
        int randomSeed;
        cout << "Random seed value: ";
        cin >> randomSeed;
        random_mt.seed(randomSeed);


        cout << "Number of times to roll the die: ";
        // user input
        int numRolls;
        cin >> numRolls;

        cout << "Number of sides on this die: ";
        // user input
        int numSides;
        cin >> numSides;

        // Roll Dice
        RollDice(numRolls, numSides);
    } else if (option == 2) {
        // Load the states
        ifstream File("states.csv");
        map<string, vector<unsigned int>> stateInfo;

        if (File.is_open()) {
            string lineFromFile;
            getline(File, lineFromFile);

            while (getline(File, lineFromFile)) {

                istringstream stream(lineFromFile);

                string State;
                string tempPCap;
                string tempPop;
                string tempMedianIncome;
                string tempNumHouseholds;
                unsigned int pCap;
                unsigned int Pop;
                unsigned int medianIncome;
                unsigned int numHouseholds;

                getline(stream, State, ',');
                getline(stream, tempPCap, ',');
                getline(stream, tempPop, ',');
                getline(stream, tempMedianIncome, ',');
                getline(stream, tempNumHouseholds, ',');
                pCap = stoi(tempPCap);
                Pop = stoi(tempPop);
                medianIncome = stoi(tempMedianIncome);
                numHouseholds = stof(tempNumHouseholds);
                if(State == "United States") {
                    numHouseholds = numHouseholds + 3;
                }
                vector<unsigned int> data{Pop, pCap, medianIncome, numHouseholds};
                stateInfo.emplace(State, data);
            }
        } else {
            cout << "File not opened." << endl;
        }
        // Get input for option 1 (show all states) or 2 (do a search for a particular state)
        cout << "1. Print all states" << endl;
        cout << "2. Search for a state" << endl;
        short choice;
        cin >> choice;

        if (choice == 1) {
            map<string, vector<unsigned int>>::iterator iter = stateInfo.begin();
            for (; iter != stateInfo.end(); ++iter) {
                vector<unsigned int> stateNums;
                stateNums = iter->second;
                cout << iter->first << endl;
                for (unsigned int i = 0; i < stateNums.size(); i++) {
                    if (i == 0) {
                        cout << "Population: " << stateNums[i] << endl;
                    } else if (i == 1) {
                        cout << "Per Capita Income: " << stateNums[i] << endl;
                    } else if (i == 2) {
                        cout << "Median Household Income: " << stateNums[i] << endl;
                    } else if (i == 3) {
                        cout << "Number of Households: " << stateNums[i] << endl;
                    }
                }
            }
        } else if (choice == 2) {
            string searchState;
            cin >> searchState;
            if (stateInfo.find(searchState) != stateInfo.end()) {
                vector<unsigned int> stateNums;
                stateNums = stateInfo[searchState];
                cout << searchState << endl;
                for (unsigned int i = 0; i < stateNums.size(); i++) {
                    if (i == 0) {
                        cout << "Population: " << stateNums[i] << endl;
                    } else if (i == 1) {
                        cout << "Per Capita Income: " << stateNums[i] << endl;
                    } else if (i == 2) {
                        cout << "Median Household Income: " << stateNums[i] << endl;
                    } else if (i == 3) {
                        cout << "Number of Households: " << stateNums[i] << endl;
                    }
                }
            } else {
                cout << "No match found for " << searchState << endl;
            }

        }

    }
}