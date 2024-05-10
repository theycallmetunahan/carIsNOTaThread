#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>
#include "path.hpp"



class Car {
private:


    
public:
    int travelTime;
    int pathLength;
    int id;
    Path* pathSegments;
    int currentPathSegment;
    // hold a static id and initialize it to 0
    static int lastId;
    
    Car();
    Car(int travelTime, int pathLength, Path* pathSegments);
    Car(const Car& rhs);
    ~Car();

    int GetTravelTime() const;
    int GetPathLength() const;
    Path* GetPathSegments() const;
    
    void PrintCar() const;
    int GetCurrentPathSegment() const;
    int getDirection() const;

    

    
};

#endif