#include "bridge.hpp"


Bridge::Bridge(int travelTime, int maxWaitTime) : directionChange(this), trafficController0(this), trafficController1(this) {
    this->travelTime = travelTime;
    this->maxWaitTime = maxWaitTime;
    this->currentDirection = 0;
    this->carsOnBridge = 0;
    this->carsLeft = 0;
    this->noOneWaiting = true;
    trafficControllerArray.push_back(&trafficController0);  
    trafficControllerArray.push_back(&trafficController1);
    hasCarsWaiting[0] = false;
    hasCarsWaiting[1] = false;

    // initialize empty mutex as true

}




int Bridge::GetTravelTime() const {
    return this->travelTime;
}

int Bridge::GetMaxWaitTime() const {
    return this->maxWaitTime;
}

void Bridge::PrintBridge() const {
    std::cout << "Bridge Travel Time: " << this->travelTime << std::endl;
    std::cout << "Bridge Max Wait Time: " << this->maxWaitTime << std::endl;
}


void Bridge::Sleep(int time) {
    sleep_milli(time);
    return; 
}



bool Bridge::UpdateBridgeVector(Car* car, UPDATE_BRIDGE_QUEUE action) {
    __synchronized__;
    if (action == ENTER) {
        try {
            carsOnBridgeVector.push(car);
            WriteOutput(car->id, car->pathSegments[car->currentPathSegment].GetType(), car->pathSegments[car->currentPathSegment].GetID(), START_PASSING);
            return true;
        }
        catch (std::exception& e) {
            std::cout << "Error in pushing the car to the bridge" << std::endl;
            return false;
        }
    }
    else if (action == LEAVE) {
        try {
            carsOnBridgeVector.pop();
            WriteOutput(car->id, car->pathSegments[car->currentPathSegment].GetType(), car->pathSegments[car->currentPathSegment].GetID(), FINISH_PASSING);
            return true;
        }
        catch (std::exception& e) {
            std::cout << "Error in popping the car from the bridge" << std::endl;
            return false;
        }


    }
}


bool Bridge::EnterOrLeaveAllowed(Car* car, UPDATE_BRIDGE_QUEUE action) {
    __synchronized__;
    if (action == ENTER) {
        while(true) {
        if (car->pathSegments[car->currentPathSegment].GetToDirection() == currentDirection || (noOneWaiting&&carsOnBridge==0)) {
            if(carsOnBridge!=0) {
                //sleep_milli(PASS_DELAY);
                Sleep(PASS_DELAY);
            }
            currentDirection = car->pathSegments[car->currentPathSegment].GetToDirection();
            noOneWaiting = false;
            carsOnBridge++;
            calculatedTime += this->travelTime;
            return true;
        }
        else if (car->pathSegments[car->currentPathSegment].GetToDirection() == 0) {
            hasCarsWaiting[0] = true;
            trafficControllerArray.at(0)->timedwait(maxWaitTime);
            if(car->pathSegments[car->currentPathSegment].GetToDirection() != currentDirection) {
                currentDirection = 0;
                carsLeft = 0;
                hasCarsWaiting[1] = false;
            }
        }
        else if (car->pathSegments[car->currentPathSegment].GetToDirection() == 1) {
            hasCarsWaiting[1] = true;
            trafficControllerArray.at(1)->timedwait(maxWaitTime);
            if(car->pathSegments[car->currentPathSegment].GetToDirection() != currentDirection) {
                currentDirection = 1 ;
                carsLeft = 0;
                hasCarsWaiting[0] = false;
            }
        }
        else {
            return false;
        }
        }
    }
    else if (action == LEAVE) {
        if (car->pathSegments[car->currentPathSegment].GetToDirection() != currentDirection) {
            return false;
        }
        if (car->pathSegments[car->currentPathSegment].GetToDirection() == currentDirection) {
            carsLeft++;
            carsOnBridge--;
            noOneWaiting = false;


            if (carsOnBridge == 0) {
                int temp = currentDirection;
                hasCarsWaiting[currentDirection] = false;
                
                // we will do (temp + 1) % 4 to get the next direction until we find a direction with cars
                int counter = 0;

                while(!hasCarsWaiting[(temp + 1) % 2] && counter < 3) {
                    temp = (temp + 1) % 2;
                    counter++;
                }
                if (counter == 3) {
                    currentDirection = (currentDirection + 1) % 2;  
                    noOneWaiting = true;
                    carsLeft = 0;
                }
                else {
                    currentDirection = (temp + 1) % 2;
                    noOneWaiting = false;
                    trafficControllerArray.at(currentDirection)->notifyAll();
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





bool Bridge::checkAndReverseTraffic() {
    __synchronized__;
    ;
}




// Bridge: bridge.hpp