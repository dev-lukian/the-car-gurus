#include <curses.h>
#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Vehicle.h"

using namespace std;

// Read CSV File and creates a vector of Vehicle object pointers
void readFile(string outFile, vector<Vehicle*>& listings);

// Helper functions for sorting algos
void merge(vector<Vehicle*>& listings, int size, int low, int middle, int high, string criteria);
void swap(Vehicle* a, Vehicle* b);
int pivotSwap (vector<Vehicle*>& listings, int low, int high, string criteria);

// Sorting algos
void quickSort(vector<Vehicle*>& listings, int low, int high, string criteria);
void mergeSort(vector<Vehicle*>& listings, int size, int low, int high, string criteria);

// Assign car guru rating to eacg vehicle objects
void updateRank(vector<Vehicle*>& listings, int multiplier);

// UI functions
int displayMenu(vector<string>& choices, int highlight, int y, WINDOW* window);

int main() {
    // Curses initialization
    WINDOW *main = initscr();
    keypad(main, TRUE);
    cbreak();

    // Get screen size
    int yMax, xMax;
    getmaxyx(main, yMax, xMax);

    // Creates 2nd window
    WINDOW *inputWin = newwin(8, 80, 11, 0);
    keypad(inputWin, TRUE);
    scrollok(main, TRUE);

    vector<string> choices;
    vector<string> priority;
    vector<Vehicle*> listings;
    readFile("./cars.csv", listings);
    int numOfCars = listings.size();
    int numOfPrintedCars;
    bool prioritySet = false;
    int userOption = 0;

    attron(A_STANDOUT);
    printw("THE CAR GURUS\n");
    attroff(A_STANDOUT);
    printw("You might not know what you want, but we can help you.\n");
    printw("Click any key to start the process of finding your next dream car...");
    getch();
    clear();

    while(true) {
        while (!prioritySet) {
            choices.emplace_back("Price");
            choices.emplace_back("Year");
            choices.emplace_back("Odometer");
            choices.emplace_back("Reliability");

            while (priority.size() != 4) {
                printw("Rank these criterias from most important to least important\n");
                userOption = displayMenu(choices, userOption, 1, main);
                priority.emplace_back(choices[userOption]);
                choices.erase(choices.begin() + userOption);
                clear();
            }

            // Confirmation screen for ranks that user set
            printw("Your Ranking\n");
            string line;
            for (int i = 0; i < 4; i++) {
                line = to_string(i + 1) + ". " + priority[i];
                mvwprintw(main, i + 1, 0, line.c_str());
            }

            mvwprintw(main, 7, 0, "Does this ranking look right?");
            choices.emplace_back("1. Yes");
            choices.emplace_back("2. No");
            userOption = displayMenu(choices, userOption, 8, main);
            choices.clear();
            clear();

            if (userOption == 0) {
                prioritySet = true;
            } else if (userOption == 1) {
                priority.clear();
            }
        }

        // User has option to choose which algo to run
        printw("Which sorting algorithm would you like to run?");
        choices.emplace_back("1. Merge Sort");
        choices.emplace_back("2. Quick Sort");
        userOption = displayMenu(choices, userOption, 1, main);
        choices.clear();

        while (true) {
            // Asks user how many of the top cars do they want returned
            try {
                mvprintw(4, 0, "What is the number of potential cars you want to return (Max 50)? ");
                char input[2];
                clrtoeol();
                getnstr(input, 2);
                numOfPrintedCars = stoi(input);
                if (numOfPrintedCars < 1 || numOfPrintedCars > 50) {
                    throw invalid_argument("That is an invalid number. Please try again.");
                } else {
                    clear();
                    printw("Processing has begun...");
                    wrefresh(main);
                    break;
                }
            }
            catch (invalid_argument &error) {
                attron(A_BOLD);
                clrtobot();
                mvprintw(5, 0, error.what());
                attroff(A_BOLD);
            }
        }

        // MERGE SORT
        if (userOption == 0) {
            auto start = std::chrono::high_resolution_clock::now();

            // Sorting algorithm is run 4 times, once for each priority, and ranks are updated after each go
            for (int i = 0; i < 4; i++) {
                mergeSort(listings, numOfCars, 0, numOfCars - 1, priority[i]);
                updateRank(listings, 4 - i);
                string percentageComplete = to_string((i + 1) * 20) + " Percent Complete....";
                mvprintw(0, 0, percentageComplete.c_str());
                wrefresh(main);
            }

            // Vehicle vector is sorted last by their calculated "Car Guru" rank
            mergeSort(listings, numOfCars, 0, numOfCars - 1, "Rank");
            mvprintw(0, 0, "100 Percent Complete....");
            wrefresh(main);

            // Time it took to run algorithm is calculated
            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = finish - start;
            clear();

            // Priority list set by user is reminded
            string priorityList =
                    "Your priority list (from most important to least): " + priority[0] + ", " + priority[1] + ", " +
                    priority[2] + ", " + priority[3] + "\n";
            // Time it took is printed
            string time = "Using the merge sort alogirthm, your list of potential cars was generated in " +
                          to_string(elapsed.count()) + " seconds";
            printw(priorityList.c_str());
            printw(time.c_str());
        }
        // QUICK SORT
        else if (userOption == 1) {
            auto start = std::chrono::high_resolution_clock::now();

            // Sorting algorithm is run 4 times, once for each priority, and ranks are updated after each go
            for (int i = 0; i < 4; i++) {
                quickSort(listings, 0, numOfCars - 1, priority[i]);
                updateRank(listings, 4 - i);
                string percentageComplete = to_string((i + 1) * 20) + " Percent Complete....";
                mvprintw(0, 0, percentageComplete.c_str());
                wrefresh(main);
            }

            // Vehicle vector is sorted last by their calculated "Car Guru" rank
            quickSort(listings, 0, numOfCars - 1, "Rank");
            mvprintw(0, 0, "100 Percent Complete....");
            wrefresh(main);

            // Time it took to run algorithm is calculated
            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = finish - start;
            clear();

            // Priority list set by user is reminded
            string priorityList =
                    "Your priority list (from most important to least): " + priority[0] + ", " + priority[1] + ", " +
                    priority[2] + ", " + priority[3] + "\n";
            // Time it took is printed
            string time = "Using the quick sort alogirthm, your list of potential cars was generated in " +
                          to_string(elapsed.count()) + " seconds";
            printw(priorityList.c_str());
            printw(time.c_str());
        }

        // List of top "n" cars is printed with their important info highlighted
        for (int i = 0; i < numOfPrintedCars; i++) {
            Vehicle *car = listings[i];
            ostringstream stream;
            stream << std::fixed << std::setprecision(2) << car->Reliability;
            string place =  to_string(i + 1) + ".";
            string rank = "Rank(Out of 50): " + to_string(car->Rank);
            string year = "Year: " + to_string(car->Year);
            string make = "Make: " + car->make;
            string model = "Model: " + car->model;
            string odo = "Odometer: " + to_string(car->Odometer);
            string price = "Price: $" + to_string(car->Price);
            string reliability = "Reliability(Out of 5): " + stream.str();
            // Table set-up
            mvprintw(i + 3, 0, "%-5s%-23s%-14s%-23s%-20s%-20s%-20s%-25s\n", place.c_str(), rank.c_str(), year.c_str(), make.c_str(), model.c_str(), odo.c_str(), price.c_str(), reliability.c_str());
        }

        getch();
        clear();
        
        printw("Do you want to run another search?");
        choices.emplace_back("1. Yes");
        choices.emplace_back("2. No");
        userOption = displayMenu(choices, userOption, 1, main);
        choices.clear();

        if(userOption == 0) {
            clear();
            prioritySet = false;
            priority.clear();
            continue;
        }
        else if(userOption == 1) {
            clear();
            break;
        }
    }

    endwin();
}


//FUNCTION DEFINITIONS

void readFile(string outFile, vector<Vehicle*>& listings) {
    ifstream file;

    string make;
    string model;
    string transmission;
    string color;
    string odometer;
    string year;
    string engine_type;
    string body_type;
    string price;
    string reliability;
    string temp;

    file.open(outFile);
    while(!file.eof()) {
        getline(file, make, ',');
        getline(file, model, ',');
        getline(file, transmission, ',');
        getline(file, color, ',');
        getline(file, odometer, ',');
        getline(file, year, ',');
        getline(file, temp, ',');
        getline(file, engine_type, ',');
        getline(file, body_type, ',');
        getline(file, temp, ',');
        getline(file, price, ',');
        getline(file, reliability,'\n');


        Vehicle* car = new Vehicle(make, model, transmission, color, engine_type, body_type, stoi(odometer), stoi(year), stoi(price), stod(reliability));
        listings.push_back(car);
    }
    file.close();
    return listings;
}
void merge(vector<Vehicle*>& listings, int size, int low, int middle, int high, string criteria) {
    vector<Vehicle*> temp(size);
    for (int i = low; i <= high; i++) {
        temp[i] = listings[i];
    }
    int i = low;
    int j = middle + 1;
    int k = low;
    if (criteria == "Price") {
        while (i <= middle && j <= high) {
            if (temp[i]->Price <= temp[j]->Price) {
                listings[k] = temp[i];
                ++i;
            } else {
                listings[k] = temp[j];
                ++j;
            }
            ++k;
        }
        while (i <= middle) {
            listings[k] = temp[i];
            ++k;
            ++i;
        }
    }
    if (criteria == "Odometer") {
        while (i <= middle && j <= high) {
            if (temp[i]->Odometer <= temp[j]->Odometer) {
                listings[k] = temp[i];
                ++i;
            } else {
                listings[k] = temp[j];
                ++j;
            }
            ++k;
        }
        while (i <= middle) {
            listings[k] = temp[i];
            ++k;
            ++i;
        }
    }
    if (criteria == "Year") {
        while (i <= middle && j <= high) {
            if (temp[i]->Year >= temp[j]->Year) {
                listings[k] = temp[i];
                ++i;
            } else {
                listings[k] = temp[j];
                ++j;
            }
            ++k;
        }
        while (i <= middle) {
            listings[k] = temp[i];
            ++k;
            ++i;
        }
    }
    if (criteria == "Reliability") {
        while (i <= middle && j <= high) {
            if (temp[i]->Reliability >= temp[j]->Reliability) {
                listings[k] = temp[i];
                ++i;
            } else {
                listings[k] = temp[j];
                ++j;
            }
            ++k;
        }
        while (i <= middle) {
            listings[k] = temp[i];
            ++k;
            ++i;
        }
    }
    if (criteria == "Rank") {
        while (i <= middle && j <= high) {
            if (temp[i]->Rank >= temp[j]->Rank) {
                listings[k] = temp[i];
                ++i;
            } else {
                listings[k] = temp[j];
                ++j;
            }
            ++k;
        }
        while (i <= middle) {
            listings[k] = temp[i];
            ++k;
            ++i;
        }
    }
}
void swap(Vehicle* a, Vehicle* b){
    Vehicle temp = *a;
    *a = *b;
    *b = temp;
}
int pivotSwap (vector<Vehicle*>& listings, int low, int high, string criteria){

    Vehicle* pivot = listings[high];
    int x = low -1;
    for(int i = low; i<= high -1; i++){
        if(criteria == "Price") {
            if (listings[i]->Price < pivot->Price) {
                x++;
                swap(listings[x], listings[i]);
            }
        }
        if(criteria == "Odometer")
            if (listings[i]->Odometer < pivot->Odometer) {
                x++;
                swap(listings[x], listings[i]);
            }
        if(criteria == "Year")
            if (listings[i]->Year > pivot->Year) {
                x++;
                swap(listings[x], listings[i]);
            }
        if(criteria == "Reliability")
            if (listings[i]->Reliability > pivot->Reliability) {
                x++;
                swap(listings[x], listings[i]);
            }
        if(criteria == "Rank")
            if (listings[i]->Rank > pivot->Rank) {
                x++;
                swap(listings[x], listings[i]);
            }
    }
    swap(listings[x+1],listings[high]);
    return x+1;
}
void quickSort(vector<Vehicle*>& listings, int low, int high, string criteria){
    if(low<high){
        int indx = pivotSwap(listings, low, high, criteria);
        quickSort(listings,low,indx-1,criteria);
        quickSort(listings,indx+1,high,criteria);
    }
}
void mergeSort(vector<Vehicle*>& listings, int size, int low, int high, string criteria){
    if( low < high){
        int middle = (low + high)/ 2;
        mergeSort(listings, size, low, middle, criteria);
        mergeSort(listings,size, middle+1, high, criteria);
        merge(listings, size,low,middle,high, criteria);
    }
}
void updateRank(vector<Vehicle*>& listings, int multiplier){
    int size = listings.size();
    for(int i = 0; i < size; i++){
        if(i <= size*0.01){
            listings[i]->Rank  += (5 * multiplier);
        }
        else if(i > size*0.01 && i <=  size*0.05){
            listings[i]->Rank  += (4 * multiplier);
        }
        else if(i > size*0.05 && i <= size*0.1){
            listings[i]->Rank  += (3 * multiplier);
        }
        else if(i > size*0.1 && i <= size*0.25){
            listings[i]->Rank  += (2 * multiplier);
        }
        else {
            listings[i]->Rank += (1 * multiplier);
        }
    }
}
int displayMenu(vector<string>& choices, int highlight, int y, WINDOW* window) {
    while(true) {
        int choice;
        for(int i = 0; i < choices.size(); i++) {
            if (i == highlight) {
                wattron(window, A_REVERSE);
            }
            mvwprintw(window, y+i, 0, choices[i].c_str());
            wattroff(window, A_REVERSE);
        }

        choice = wgetch(window);

        switch(choice) {
            case KEY_UP:
                highlight--;
                if(highlight == -1) {
                    highlight = 0;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == choices.size()) {
                    highlight = choices.size() - 1;
                }
                break;
        }

        if (choice == 10) {
            break;
        }
    }

    return highlight;
}


