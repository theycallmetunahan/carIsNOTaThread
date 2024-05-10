#ifndef CROSSROAD_HPP
#define CROSSROAD_HPP

#include "monitor.h"

#include <iostream>

#include "car.hpp"
#include <queue>
#include <chrono>
#include "WriteOutput.h"
#include "helper.h"


enum UPDATE_CROSS_QUEUE {
    ENTERC,
    LEAVEC
};


class Crossroad: public Monitor {



    
public:
    int travelTime;
    int maxWaitTime;
    int currentDirection;
    int carsOnBridge;
    int carsLeft;
    int calculatedTime;
    bool noOneWaiting;

    std::queue<Car*> carsOnBridgeVector;
    std::queue<Car*> carsOnBridgeQueue[2];
    Condition directionChange;
    Condition trafficController0;
    Condition trafficController1;
    Condition trafficController2;
    Condition trafficController3;
    std::vector<Condition*> trafficController;
    
    bool hasCarsWaiting[4];




    Crossroad(int travelTime, int maxWaitTime);


    int GetTravelTime() const;
    int GetMaxWaitTime() const;

    void PrintCrossroad() const;

    bool UpdateBridgeVector(Car* car, UPDATE_CROSS_QUEUE action);
    bool EnterOrLeaveAllowed(Car* car, UPDATE_CROSS_QUEUE action);

    void Sleep(int time);
    
};

#endif