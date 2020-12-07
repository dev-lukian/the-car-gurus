#include "Vehicle.h"

Vehicle::Vehicle() {
    Rank = 0;
};

Vehicle::Vehicle(const string &make, const string &model, const string &transmission, const string &color,
                 const string &engineType, const string &bodyType, int odometer, int year, int price, double reliability)
        : make(make), model(model), transmission(transmission), color(color), engine_type(engineType),
          body_type(bodyType), Odometer(odometer), Year(year), Price(price), Reliability(reliability), Rank(0) {}
