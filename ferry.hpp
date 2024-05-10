#ifndef FERRY_HPP
#define FERRY_HPP

#include "monitor.h"

#include <iostream>

#include "car.hpp"
#include <queue>
#include <chrono>
#include "WriteOutput.h"
#include "helper.h"


enum UPDATE_FERRY_QUEUE {
    ENTERF,
    LEAVEF
};

class Ferry: public Monitor {

    
public:
    int travelTime;
    int maxWaitTime;
    int capacity;

    int counter0;
    int counter1;
    Condition ferryIsFullTo1;
    Condition ferryIsAvailableTo1;
    Condition letsLeaveTo1;
    Condition ferryIsFullTo0;
    Condition ferryIsAvailableTo0;
    Condition letsLeaveTo0;

    Condition trafficController;

    Ferry(int travelTime, int maxWaitTime, int capacity);


    int GetTravelTime() const;
    int GetMaxWaitTime() const;
    int GetCapacity() const;

    void PrintFerry() const;


    bool UpdateBridgeVector(Car* car, UPDATE_FERRY_QUEUE action);

    bool EnterOrLeaveAllowed(Car* car, UPDATE_FERRY_QUEUE action);


    
};

#endif