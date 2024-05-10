#include "ferry.hpp"



Ferry::Ferry(int travelTime, int maxWaitTime, int capacity): ferryIsFullTo0(this), ferryIsAvailableTo0(this), letsLeaveTo0(this), ferryIsFullTo1(this), ferryIsAvailableTo1(this), letsLeaveTo1(this) , trafficController(this) {
    this->travelTime = travelTime;
    this->maxWaitTime = maxWaitTime;
    this->capacity = capacity;
    // initialize ferryIsFull as false
    this->counter0 = 0;
    this->counter1 = 0;
}




                /*
                You can assume that loading and unloading cars from the Ferry is done instantly. Every
                car is unloaded at the same time.
                • You can assume there are an infinite number of ferries. All cars coming to the ferry will
                be loaded on a new one once the current ferry departs. Cars will not wait for ferries to
                arrive.
                • Maximum wait time is not triggered by a car thread. It should trigger automatically
                once the time limit is reached.
                */




int Ferry::GetTravelTime() const {
    return this->travelTime;
}

int Ferry::GetMaxWaitTime() const {
    return this->maxWaitTime;
}

int Ferry::GetCapacity() const {
    return this->capacity;
}   

void Ferry::PrintFerry() const {
    std::cout << "Ferry Travel Time: " << this->travelTime << std::endl;
    std::cout << "Ferry Max Wait Time: " << this->maxWaitTime << std::endl;
    std::cout << "Ferry Capacity: " << this->capacity << std::endl;
}

bool Ferry::UpdateBridgeVector(Car* car, UPDATE_FERRY_QUEUE action) {
        __synchronized__;

    if (action == ENTERF) {
    if (car->pathSegments[car->currentPathSegment].GetToDirection() == 0) {
        if(counter0 == capacity) {
            ferryIsFullTo0.notifyAll();
    
        }
        else {
            ferryIsFullTo0.timedwait(maxWaitTime);
        }


        WriteOutput(car->id, car->pathSegments[car->currentPathSegment].GetType(), car->pathSegments[car->currentPathSegment].GetID(), START_PASSING);
        
        
        return true;
    } 
    else if (car->pathSegments[car->currentPathSegment].GetToDirection() == 1) {
        if(counter1 == capacity) {
            ferryIsFullTo1.notifyAll();
    
        }
        else {
            ferryIsFullTo1.timedwait(maxWaitTime);
        }
        WriteOutput(car->id, car->pathSegments[car->currentPathSegment].GetType(), car->pathSegments[car->currentPathSegment].GetID(), START_PASSING);
        return true;
    }
    else {
        return false; // there was an error
    }
    }
    else if (action == LEAVEF) {
            if ((car->pathSegments[car->currentPathSegment].GetToDirection() == 0)) {
        if (counter0==0 ) {
            letsLeaveTo0.notifyAll();
            
            
        }
        else if (counter0 > 0 ) {
            letsLeaveTo0.wait();
            
        }
        WriteOutput(car->id, car->pathSegments[car->currentPathSegment].GetType(), car->pathSegments[car->currentPathSegment].GetID(), FINISH_PASSING);
        ferryIsAvailableTo0.notifyAll();
        return true;
    }
    else if ((car->pathSegments[car->currentPathSegment].GetToDirection() == 1)) {
        if (counter1==0 ) {
            letsLeaveTo1.notifyAll();
            
        }
        else if (counter1 > 0 ) {
            letsLeaveTo1.wait();
            
        }
        WriteOutput(car->id, car->pathSegments[car->currentPathSegment].GetType(), car->pathSegments[car->currentPathSegment].GetID(), FINISH_PASSING);
        ferryIsAvailableTo1.notifyAll();
        return true;
    }
    else {
        return false; // there was an error
    }
    }
    else {
        return false;
    }

}


bool Ferry::EnterOrLeaveAllowed(Car* car, UPDATE_FERRY_QUEUE action) {
     __synchronized__;

    if (action == ENTERF) {
            if (counter0 < capacity && car->pathSegments[car->currentPathSegment].GetToDirection() == 0) {
                counter0++;

                return true;
            }
            else if (counter0 == capacity && car->pathSegments[car->currentPathSegment].GetToDirection() == 0) {
                ferryIsAvailableTo0.wait();
                counter0++;
                return true;
            
            }
            else if (counter1 < capacity && car->pathSegments[car->currentPathSegment].GetToDirection() == 1) {
                counter1++;
                return true;
            }
            else if (counter1 == capacity && car->pathSegments[car->currentPathSegment].GetToDirection() == 1) {
                ferryIsAvailableTo1.wait();
                counter1++;
                return true;
            }
            else {
                return false;
            }
    }
    else if (action == LEAVEF) {
            if (car->pathSegments[car->currentPathSegment].GetToDirection() == 0) {
                counter0--;
                return true;
            }
            else if (car->pathSegments[car->currentPathSegment].GetToDirection() == 1) {
                counter1--;
                return true;
            }
            else {
                return false;
            }
    }
    else {
        return false;
    }
}








// Ferry: ferry.hpp