// CS321PaulAririHomework2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include "simulation.h"
using namespace std;
using namespace simulationspace;

void finishSim(int landTime, int takeOffTime, double arrivalProb, double departureProb, int fuelMaxTime, unsigned int totalTime);
bool crashedPlane(int arrivalTime, int departureTime, int fuelMax);

int main()
{
    int landTime, takeOffTime;
    double arrivalProb, departureProb;
    int avgLandTime, avgTakeOffTime;
    int fuelMaxTime; 
    unsigned int totalTime;

    cout << "*****************************************************************************" << endl;
    cout << "* Welcome to the Runway, answer the questions below to commence simulation! *" << endl;
    cout << "*****************************************************************************" << endl;
    cout << "The amount of time needed for one plane to land: " << endl;
    cin >> landTime;
    cout << endl;

    cout << "The amount of time needed for one plane to take off: " << endl;
    cin >> takeOffTime;
    cout << endl;

    cout << "The average amount of time between arrival of planes to the landing queue: " << endl;
    cin >> avgLandTime;
    arrivalProb = ((double)1 / avgLandTime);
    cout << endl;
    
    cout << "The average amount of time between arrival of planes to the takeoff queue: " << endl;
    cin >> avgTakeOffTime;
    departureProb = ((double)1 / avgTakeOffTime);
    cout << endl;
    
    cout << "The maximum amount of time that a plane can stay in the landing queue without running out of fuel and crashing: " << endl;
    cin >> fuelMaxTime;
    cout << endl;
    
    cout << "The total length of time to be simulated: " << endl;
    cin >> totalTime;
    cout << endl;

    cout << "********************************" << endl;
    cout << "* Runway Simulation Commences! *" << endl;
    cout << "********************************" << endl;

    finishSim(landTime, takeOffTime, arrivalProb, departureProb, fuelMaxTime, totalTime);
    return 0;
}

void finishSim(int landTime, int takeOffTime, double arrivalProb, double departureProb, int fuelMaxTime, unsigned int totalTime)
{
    queue<int> landingTimes;
    queue<int> takeOffTimes;

    int timeInLandingQueue = 0, timeInTakeOffQueue = 0;
    int crashedPlanesCount = 0;

    boolSource land(arrivalProb);
    boolSource takeOff(departureProb);

    averageTime landAve;
    averageTime takeOffAve;

    Runway landPlane(landTime);
    Runway takeOffPlane(takeOffTime);

    for (int t = 0; t <= totalTime; ++t)
    {
        //if plane arrived at landing queue
        if (land.queryCall())
            landingTimes.push(t);

        // If plane arrived at take off queue
        else if (takeOff.queryCall())
            takeOffTimes.push(t);

        //Priority to landing: no plane can takeoff unless landing queue is empty!
        if (!landPlane.isBusy() && !takeOffPlane.isBusy() && !landingTimes.empty())
        {
            int nextPlane = landingTimes.front();
            landingTimes.pop();
            timeInLandingQueue = (t - nextPlane);

            if (timeInLandingQueue < fuelMaxTime) {
                landAve.addNumber(timeInLandingQueue);
                landPlane.startActivity();
                cout << "Landing Plane " << landAve.numberCount() << " has successfully landed!" << endl;
            }
            if (timeInLandingQueue > fuelMaxTime) {
                crashedPlanesCount++;
                cout << "Plane has crashed!" << endl;
            }
        }

        else if (!landPlane.isBusy() && !takeOffPlane.isBusy() && !takeOffTimes.empty() && landingTimes.empty())
        {
            int nextPlane = takeOffTimes.front();
            takeOffTimes.pop();
            timeInTakeOffQueue = (t - nextPlane);

            takeOffAve.addNumber(timeInTakeOffQueue);
            takeOffPlane.startActivity();

            cout << "TakeOff Plane " << takeOffAve.numberCount()  << " has successfully departed!" << endl;
        }

        landPlane.oneMinute();
        takeOffPlane.oneMinute();
    }

    // Process the crashed planes after the simulation
    while (!landingTimes.empty() && crashedPlane(landingTimes.back(), totalTime, fuelMaxTime))
    {
        int nextPlane = landingTimes.front();
        landingTimes.pop();
        crashedPlanesCount++;

        cout << "Plane has crashed!" << endl;
    }

    cout << endl;
    cout << "The number of planes that took off in the simulated time: " << takeOffAve.numberCount() << endl;
    cout << "The number of planes that landed in the simulated time: " << landAve.numberCount() << endl;
    cout << "The number of planes that crashed because they ran out of fuel before they could land: " << crashedPlanesCount << endl;
    cout << "The average time that a plane spent in the takeoff queue: " << takeOffAve.average() << endl;
    cout << "The average time that a plane spent in the landing queue: " << landAve.average() << endl;
}

bool crashedPlane(int arrivalTime, int departureTime, int fuelMax)
{
    return (departureTime - arrivalTime) > fuelMax;
}
