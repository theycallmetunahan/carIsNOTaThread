#include "car.hpp"

int Car::lastId = 0;

Car::Car() {
    
}

Car::Car(int travelTime, int pathLength, Path* pathSegments) {
    this->travelTime = travelTime;
    this->pathLength = pathLength;
    this->pathSegments = pathSegments;
    this->currentPathSegment = 0;
    this->id = Car::lastId++;
    
}

Car::Car(const Car& rhs) {
    this->travelTime = rhs.travelTime;
    this->pathLength = rhs.pathLength;
    this->pathSegments = rhs.pathSegments;
    this->currentPathSegment = rhs.currentPathSegment;
    this->id = rhs.id;
}

Car::~Car() {
    
}

int Car::GetTravelTime() const {
    return this->travelTime;
}

int Car::GetPathLength() const {
    return this->pathLength;
}

Path* Car::GetPathSegments() const {
    return this->pathSegments;
}

int Car::GetCurrentPathSegment() const {
    return this->currentPathSegment;
}

void Car::PrintCar() const {
    std::cout << "Car Travel Time: " << this->travelTime << std::endl;
    std::cout << "Car Path Length: " << this->pathLength << std::endl;
    for (int i = 0; i < this->pathLength; i++) {
        this->pathSegments[i].PrintPath();
    }
}

int Car::getDirection() const {
    return this->pathSegments[this->currentPathSegment].GetToDirection();
}

// Car: car.hpp