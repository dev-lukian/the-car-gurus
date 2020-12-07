#include <string>

#pragma once

using namespace std;

struct Vehicle{
    string make;
    string model;
    string transmission;
    string color;
    string engine_type;
    string body_type;
    int Odometer;
    int Year;
    int Price;
    int Reliability;
    int Rank;

    Vehicle();
    Vehicle(const string &make, const string &model, const string &transmission, const string &color,
            const string &engineType, const string &bodyType, int odometer, int year, int price, int reliability);
};
