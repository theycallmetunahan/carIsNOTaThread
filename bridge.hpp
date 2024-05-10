#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "monitor.h"

#include <iostream>

#include "car.hpp"
#include <queue>
#include <chrono>
#include "WriteOutput.h"
#include "helper.h"


enum Direction { ONE, ZERO};

enum UPDATE_BRIDGE_QUEUE {
    ENTER,
    LEAVE
};


class Bridge: public Monitor {
    


    
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
    std::vector<Condition*> trafficControllerArray;

    bool hasCarsWaiting[2];
    
    bool checkAndReverseTraffic();
    
    Bridge(int travelTime, int maxWaitTime);
    void Sleep(int time);
   
    

    int GetTravelTime() const;
    int GetMaxWaitTime() const;



    bool UpdateBridgeVector(Car* car, UPDATE_BRIDGE_QUEUE action);
    bool EnterOrLeaveAllowed(Car* car, UPDATE_BRIDGE_QUEUE action);

    

    void PrintBridge() const;
    

    
};

#endif