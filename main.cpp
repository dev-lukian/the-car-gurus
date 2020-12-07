#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Vehicle{
    Vehicle(const string &make, const string &model, const string &transmission, const string &color,
            const string &engineType, const string &bodyTape, int odometer, int productionYear, int price);

    string make;
    string model;
    string transmission;
    string color;
    string engine_type;
    string body_tape;
    int Odometer;
    int Year;
    int Price;
    int Rank = 0;

};

Vehicle::Vehicle(const string &make, const string &model, const string &transmission, const string &color, const string &engineType, const string &bodyTape, int Odometer, int Year, int price):
make(make), model(model), transmission(transmission), color(color), engine_type(engineType), body_tape(bodyTape), Odometer(Odometer),Year(Year),Price(Price) {}

void merge(vector<Vehicle> listings, int size, int low, int middle, int high, string criteria)
{
    {
        vector<Vehicle> temp(size);
        for(int i = low; i <= high; i++){
            temp[i] = listings[i];
        }
        int i = low;
        int j = middle+1;
        int k = low;
        if(criteria == "Price") {
            while (i <= middle && j <= high){
                if(temp[i].Price <= temp[j].Price){
                    listings[k] = temp[i];
                    ++i;
                }
                else {
                    listings[k] = temp[j];
                    ++j;
                }
                ++k;
            }
            while (i <= middle){
                listings[k] = temp[i];
                ++k;
                ++i;
            }
        }
        if(criteria == "Odometer") {
            while (i <= middle && j <= high){
                if(temp[i].Odometer <= temp[j].Odometer){
                    listings[k] = temp[i];
                    ++i;
                }
                else {
                    listings[k] = temp[j];
                    ++j;
                }
                ++k;
            }
            while (i <= middle){
                listings[k] = temp[i];
                ++k;
                ++i;
            }
        }
        if(criteria == "Year") {
            while (i <= middle && j <= high){
                if(temp[i].Year <= temp[j].Year){
                    listings[k] = temp[i];
                    ++i;
                }
                else {
                    listings[k] = temp[j];
                    ++j;
                }
                ++k;
            }
            while (i <= middle){
                listings[k] = temp[i];
                ++k;
                ++i;
            }
        }
        if(criteria == "Rank") {
            while (i <= middle && j <= high){
                if(temp[i].Rank <= temp[j].Rank){
                    listings[k] = temp[i];
                    ++i;
                }
                else {
                    listings[k] = temp[j];
                    ++j;
                }
                ++k;
            }
            while (i <= middle){
                listings[k] = temp[i];
                ++k;
                ++i;
            }
        }


    }
}
void swap(Vehicle* a, Vehicle* b){
    Vehicle temp = *a;
    *a = *b;
    *b = temp;
}
int pivotSwap (vector<Vehicle> listings, int low, int high, string criteria){

    Vehicle pivot = listings[high];
    int x = low -1;
    for(int i = low; i<= high -1; i++){
            if(criteria == "Price") {
                if (listings[i].Price < pivot.Price) {
                    x++;
                    swap(&listings[x], &listings[i]);
                }
            }
            if(criteria == "Odometer")
                if (listings[i].Odometer < pivot.Odometer) {
                    x++;
                    swap(&listings[x], &listings[i]);
                }
            if(criteria == "Year")
                if (listings[i].Year < pivot.Year) {
                    x++;
                    swap(&listings[x], &listings[i]);
                }
            if(criteria == "Rank")
                if (listings[i].Rank < pivot.Rank) {
                    x++;
                    swap(&listings[x], &listings[i]);
                }
        }
    swap(&listings[x+1],&listings[high]);
    return x+1;
}
void quickSort(vector<Vehicle> listings, int low, int high, string criteria){
    if(low<high){
        int indx = pivotSwap(listings, low, high, criteria);
        quickSort(listings,low,indx-1,criteria);
        quickSort(listings,indx+1,high,criteria);
    }
}
void mergeSort(vector<Vehicle> listings, int size, int low, int high, string criteria){
    if( low < high){
        int middle = (low + high)/ 2;
        mergeSort(listings, size, low, middle, criteria);
        mergeSort(listings,size, middle+1, high, criteria);
       // merge(listings, size,low,middle,high, criteria);
    }
}
void updateRank(vector<Vehicle> listings, int multiplier){
    int rank;
    int size = listings.size();
    for(int i = 0; i < size; i++){
        if(i < size*0.01){
            listings[i].Rank  += 5 * multiplier;
        }
        else if(i > size*0.01 && i <  size*0.05){
            listings[i].Rank  += 4 * multiplier;
        }
        else if(i > size*0.05 && i <  size*0.1){
            listings[i].Rank  += 3 * multiplier;
        }
        else if(i > size*0.1 && i <  size*0.25){
            listings[i].Rank  += 2 * multiplier;
        }
        else {
            listings[i].Rank += 1 * multiplier;
        }
    }
}
vector<Vehicle> readFile(string outFile, Vehicle &data)
{
    ifstream file;
    file.open(outFile);
    vector<Vehicle> listings;
    if(file.is_open())
    {
        string make = getline(file, make, ',');
        string model = getline(file, model, ',');
        string transmission = getline(file, transmission, ',');
        string color = getline(file, color, ',');
        string odometer = getline(file, odometer, ',');
        string year = getline(file, year, ',');
        string temp = getline(file, temp, ','); //engine type is in the file twice so this is eating up the extra one, won't get used
        string engine_type = getline(file, engine_type, ',');
        string body_type = getline(file, body_type, ',');
        string temp2 = getline(file, temp2, ','); //same thing as before, but for drivetrain
        string price = getline(file, price, ',');
        string temp3 getline(file, temp3); //again for the reliability rating + end line
        
        Vehicle car = Vehicle(make, model, transmission, color, engine_type, body_type, stoi(odometer), stoi(year), stoi(price));
        listings.push_back(car);
    }
    file.close();
    return listings;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
