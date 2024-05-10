#include "crossroad.hpp"



Crossroad::Crossroad(int travelTime, int maxWaitTime) :
directionChange(this), trafficController0(this), trafficController1(this), trafficController2(this), trafficController3(this) {
    this->travelTime = travelTime;
    this->maxWaitTime = maxWaitTime;
    this->currentDirection = 0;
    this->carsOnBridge = 0;
    this->carsLeft = 0;
    this->calculatedTime = 0;
    this->noOneWaiting = true;
    trafficController.push_back(&trafficController0);
    trafficController.push_back(&trafficController1);
    trafficController.push_back(&trafficController2);
    trafficController.push_back(&trafficController3);
    for (int i = 0; i < 4; i++) {
        hasCarsWaiting[i] = false;
    }   
    
}


void Crossroad::Sleep(int time) {
    sleep_milli(time);
    return; 
}



int Crossroad::GetTravelTime() const {
    return this->travelTime;
}

int Crossroad::GetMaxWaitTime() const {
    return this->maxWaitTime;
}

void Crossroad::PrintCrossroad() const {
    std::cout << "Crossroad Travel Time: " << this->travelTime << std::endl;
    std::cout << "Crossroad Max Wait Time: " << this->maxWaitTime << std::endl;
}




bool Crossroad::UpdateBridgeVector(Car* car, UPDATE_CROSS_QUEUE action) {
    __synchronized__;
    if (action == ENTERC) {
        try {
            carsOnBridgeVector.push(car);
            WriteOutput(car->id, car->pathSegments[car->currentPathSegment].GetType(), car->pathSegments[car->currentPathSegment].GetID(), START_PASSING);
            return true;
        }
        catch (std::exception& e) {
            return false;
        }
    }
    else if (action == LEAVEC) {
        try {
            carsOnBridgeVector.pop();
            WriteOutput(car->id, car->pathSegments[car->currentPathSegment].GetType(), car->pathSegments[car->currentPathSegment].GetID(), FINISH_PASSING);
            return true;
        }
        catch (std::exception& e) {
            return false;
        }


    }
    else {
        return false;
    }
}

bool Crossroad::EnterOrLeaveAllowed(Car* car, UPDATE_CROSS_QUEUE action) {
    __synchronized__;
    if (action == ENTERC) {
        while(true) {
            
        if (car->pathSegments[car->currentPathSegment].GetFromDirection() == currentDirection || (noOneWaiting&&carsOnBridge==0)) {
            if(carsOnBridge!=0) {
                //sleep_milli(PASS_DELAY);
                Sleep(PASS_DELAY);
            }
            currentDirection = car->pathSegments[car->currentPathSegment].GetFromDirection();
            noOneWaiting = false;
            carsOnBridge++;
            calculatedTime += this->travelTime;
            return true;
        }
        else if (car->pathSegments[car->currentPathSegment].GetFromDirection() == 0) {
            hasCarsWaiting[0] = true;

            trafficController.at(0)->timedwait(maxWaitTime);
            if(car->pathSegments[car->currentPathSegment].GetFromDirection() != currentDirection) {
                currentDirection = 0;
                carsLeft = 0;
            }
        }
        else if (car->pathSegments[car->currentPathSegment].GetFromDirection() == 1) {
            hasCarsWaiting[1] = true;
            trafficController.at(1)->timedwait(maxWaitTime);   
            if(car->pathSegments[car->currentPathSegment].GetFromDirection() != currentDirection) {
                currentDirection = 1;
                carsLeft = 0;
            }
        }
        else if (car->pathSegments[car->currentPathSegment].GetFromDirection() == 2) {
            hasCarsWaiting[2] = true;
            trafficController.at(2)->timedwait(maxWaitTime);
            if(car->pathSegments[car->currentPathSegment].GetFromDirection() != currentDirection) {
                currentDirection = 2;
                carsLeft = 0;
            }
        }
        else if (car->pathSegments[car->currentPathSegment].GetFromDirection() == 3) {
            hasCarsWaiting[3] = true;
            trafficController.at(3)->timedwait(maxWaitTime);
            if(car->pathSegments[car->currentPathSegment].GetFromDirection() != currentDirection) {
                currentDirection = 3;
                carsLeft = 0;
            }
        }
        else {
            return false;
        }
        }
        }
    
    else if (action == LEAVEC) {
        if (car->pathSegments[car->currentPathSegment].GetFromDirection() != currentDirection) {
            return false;
        }
        if (car->pathSegments[car->currentPathSegment].GetFromDirection() == currentDirection) {
            carsLeft++;
            carsOnBridge--;
            


            if (carsOnBridge == 0) {
                int temp = currentDirection;
                hasCarsWaiting[currentDirection] = false;
                
                // we will do (temp + 1) % 4 to get the next direction until we find a direction with cars
                int counter = 0;

                while(!hasCarsWaiting[(temp + 1) % 4] && counter < 6) {
                    temp = (temp + 1) % 4;
                    counter++;
                }
                if (counter == 6) {
                    currentDirection = (currentDirection + 1) % 4;  
                    noOneWaiting = true;
                    carsLeft = 0;
                }
                else {
                    currentDirection = (temp + 1) % 4;
                    noOneWaiting = false;
                    trafficController.at(currentDirection)->notifyAll();
                    carsLeft = 0;
                }
                
            }
            else {;}
            return true;
        }
        else {
            return false;
        }
    }
    
    
    return false;
}




// Crossroad: crossroad.hpp
