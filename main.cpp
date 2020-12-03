#include <iostream>
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
    int Rank;

};

Vehicle::Vehicle(const string &make, const string &model, const string &transmission, const string &color, const string &engineType, const string &bodyTape, int Odometer, int Year, int price):
make(make), model(model), transmission(transmission), color(color), engine_type(engineType), body_tape(bodyTape), Odometer(Odometer),Year(Year),Price(Price) {}

vector<Vehicle> merge(vector<Vehicle> left, vector<Vehicle> right)
{
    vector<Vehicle> result;

    return result;
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

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
