#include "monitor.h"
#include "car.hpp"
#include "ferry.hpp"
#include "path.hpp"
#include "bridge.hpp"
#include "crossroad.hpp"
#include "WriteOutput.h"
#include "helper.h"


#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <climits>

int NN, FN, CN, CAN;
int i, j;

std::vector<Car*> carVector;
std::vector<Bridge*> bridgeVector;
std::vector<Ferry*> ferryVector;
std::vector<Crossroad*> crossroadVector;




void* CarThread(void* car) {
    Car* carObj = (Car*)car;
    int pathLength = carObj->GetPathLength();
    Path* pathSegments = carObj->GetPathSegments();

    for (int i = 0; i < pathLength; i++) {
        Path path = pathSegments[i];
        char type = path.GetType();
        int id = path.GetID();
        carObj->currentPathSegment = i;
        

        if (type=='N') {
                Bridge* bridge = bridgeVector.at(id);
                if (i==0) {
                    WriteOutput(carObj->id, pathSegments[carObj->currentPathSegment].GetType(), pathSegments[carObj->currentPathSegment].GetID(), TRAVEL);
                    sleep_milli(carObj->travelTime);  // Simulating travel time on the path
                    WriteOutput(carObj->id, pathSegments[carObj->currentPathSegment].GetType(), pathSegments[carObj->currentPathSegment].GetID(), ARRIVE);
                }
                
                // if the object can enter the bridge, attain the lock
               
                if(!bridge->EnterOrLeaveAllowed(carObj, ENTER)) {;}
                 
               
                 if(!(bridge->UpdateBridgeVector(carObj, ENTER))) {
;                }
                
                sleep_milli(bridge->GetTravelTime());

                if(!(bridge->EnterOrLeaveAllowed(carObj, LEAVE))) {
;                }
                 if(!(bridge->UpdateBridgeVector(carObj, LEAVE))) {
;                }
       
       
                if (i == pathLength - 1) {
                    return nullptr;
                }
                // checkAndReverseTraffic
                

                WriteOutput(carObj->id, pathSegments[carObj->currentPathSegment].GetType(), pathSegments[carObj->currentPathSegment].GetID(), TRAVEL);
                sleep_milli(carObj->travelTime);
                WriteOutput(carObj->id, pathSegments[carObj->currentPathSegment].GetType(), pathSegments[carObj->currentPathSegment].GetID(), ARRIVE);
                
            } 
    
            
            
           else if (type=='F') {
                Ferry* ferry = ferryVector.at(id);
                /*
                You can assume that loading and unloading cars from the Ferry is done instantly. Every
                car is unloaded at the same time.
                • You can assume there are an infinite number of ferries. All cars coming to the ferry will
                be loaded on a new one once the current ferry departs. Cars will not wait for ferries to
                arrive.
                • Maximum wait time is not triggered by a car thread. It should trigger automatically
                once the time limit is reached.
                */
               if (i==0) {
                    WriteOutput(carObj->id, pathSegments[carObj->currentPathSegment].GetType(), pathSegments[carObj->currentPathSegment].GetID(), TRAVEL);
                    sleep_milli(carObj->travelTime);  // Simulating travel time on the path
                    WriteOutput(carObj->id, pathSegments[carObj->currentPathSegment].GetType(), pathSegments[carObj->currentPathSegment].GetID(), ARRIVE);
                }
                
                
                
                ferry->EnterOrLeaveAllowed(carObj, ENTERF);
                ferry->UpdateBridgeVector(carObj, ENTERF);
                sleep_milli(ferry->GetTravelTime());
                ferry->EnterOrLeaveAllowed(carObj, LEAVEF);
                ferry->UpdateBridgeVector(carObj, LEAVEF);
                
                if (i == pathLength - 1) {
                    return nullptr;
                }
                WriteOutput(carObj->id, pathSegments[carObj->currentPathSegment].GetType(), pathSegments[carObj->currentPathSegment].GetID(), TRAVEL);
                sleep_milli(carObj->travelTime);
                WriteOutput(carObj->id, pathSegments[carObj->currentPathSegment].GetType(), pathSegments[carObj->currentPathSegment].GetID(), ARRIVE);

            }
        else if (type=='C') {
                Crossroad* crossroad = crossroadVector.at(id);
                if (i==0) {
                    WriteOutput(carObj->id, pathSegments[carObj->currentPathSegment].GetType(), pathSegments[carObj->currentPathSegment].GetID(), TRAVEL);
                    sleep_milli(carObj->travelTime);  // Simulating travel time on the path
                    WriteOutput(carObj->id, pathSegments[carObj->currentPathSegment].GetType(), pathSegments[carObj->currentPathSegment].GetID(), ARRIVE);
                }
                else {
                    ;
                }
                
                // if the object can enter the bridge, attain the lock
               
                if(!crossroad->EnterOrLeaveAllowed(carObj, ENTERC)) {
                    std::cout << "Error in entering the crossroad" << std::endl; }
               
                 if(!(crossroad->UpdateBridgeVector(carObj, ENTERC))) {
                     std::cout << "Error in entering the crossroad" << std::endl;
                }
                
                sleep_milli(crossroad->GetTravelTime());

                if(!crossroad->EnterOrLeaveAllowed(carObj, LEAVEC)) {
                    std::cout << "Error in leaving the crossroad" << std::endl;
                }
                
                 if(!(crossroad->UpdateBridgeVector(carObj, LEAVEC))) {
                    std::cout << "Error in leaving the crossroad" << std::endl;
                }
       
       
                if (i == pathLength - 1) {
                    return nullptr;
                }
                // checkAndReverseTraffic
                

                WriteOutput(carObj->id, pathSegments[carObj->currentPathSegment].GetType(), pathSegments[carObj->currentPathSegment].GetID(), TRAVEL);
                sleep_milli(carObj->travelTime);
                WriteOutput(carObj->id, pathSegments[carObj->currentPathSegment].GetType(), pathSegments[carObj->currentPathSegment].GetID(), ARRIVE);
                
            } 
            else {
                std::cout << "Error in path type" << std::endl;
            }  
    }
    return nullptr;
    }
    



int parser() {
    std::cin >> NN;
    for (i = 0; i < NN; i++) {
        int travelTime, maxWaitTime;
        std::cin >> travelTime >> maxWaitTime;
        Bridge* bmon =  new Bridge(travelTime, maxWaitTime);
        bridgeVector.push_back(bmon);
    }

    std::cin >> FN;
    for (i = 0; i < FN; i++) {
        int travelTime, maxWaitTime, capacity;
        std::cin >> travelTime >> maxWaitTime >> capacity;
        Ferry* ferry = new Ferry(travelTime, maxWaitTime, capacity);
        ferryVector.push_back(ferry);
    }


    std::cin >> CN;
    for (i = 0; i < CN; i++) {
        int travelTime, maxWaitTime;
        std::cin >> travelTime >> maxWaitTime;
        Crossroad* crossroad = new Crossroad(travelTime, maxWaitTime);
        crossroadVector.push_back(crossroad);
    }

    std::cin >> CAN;


    for (i = 0; i < CAN; i++) {
        int travelTime, pathLength;
        std::cin >> travelTime >> pathLength;
        Path *pathSegments = new Path[pathLength];
        for (j = 0; j < pathLength; j++) {
            char type;
            int id, fromDirection, toDirection;
            std::cin >> type >> id >> fromDirection >> toDirection;
            pathSegments[j] = Path(type, id, fromDirection, toDirection);
        }
        Car* car = new Car(travelTime, pathLength, pathSegments);
        carVector.push_back(car);
    }
    return 0;






}

int freer() {
    for (i = 0; i < NN; i++) {
        delete bridgeVector[i];
    }

    for (i = 0; i < FN; i++) {
        delete ferryVector[i];
    }

    for (i = 0; i < CN; i++) {
        delete crossroadVector[i];
    }

    for (i = 0; i < CAN; i++) {
        delete carVector[i];
    }
    return 0;

}


int printer() {
    for (i = 0; i < NN; i++) {
        bridgeVector[i]->PrintBridge();
    }

    for (i = 0; i < FN; i++) {
        ferryVector[i]->PrintFerry();
    }

    for (i = 0; i < CN; i++) {
        crossroadVector[i]->PrintCrossroad();
    }

    for (i = 0; i < CAN; i++) {
        carVector[i]->PrintCar();
    }
    return 0;
}

int main() 
{
    parser();
    //printer();
    InitWriteOutput();
    

    std::vector<pthread_t> carThreads(CAN);

    for (size_t i = 0; i < carVector.size(); i++) {
        pthread_create(&carThreads[i], NULL, CarThread, (void*)carVector[i]);
    }



    for (auto& th : carThreads) {
        pthread_join(th, NULL);
    }


    //freer();

    return 0;
}