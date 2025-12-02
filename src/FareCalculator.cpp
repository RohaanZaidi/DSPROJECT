#include <iostream>
#include "FareCalculator.h"
using namespace std;

//---------------------------------------
// Constructor sets default values
//---------------------------------------
FareCalculator::FareCalculator() {
    baseFare = 50.0;          // Rs 50
    perKmRate = 20.0;         // Rs 20 per KM
    waitingCharge = 2.0;      // Rs 2 per minute waiting
    surgeMultiplier = 1.0;    // No surge by default
}

//---------------------------------------
// Set custom fare parameters
//---------------------------------------
void FareCalculator::setRates(float base, float perKm, float waiting) {
    baseFare = base;
    perKmRate = perKm;
    waitingCharge = waiting;
}

//---------------------------------------
// Apply surge pricing
//---------------------------------------
void FareCalculator::applySurge(float multiplier) {
    if (multiplier >= 1.0)
        surgeMultiplier = multiplier;
    else
        surgeMultiplier = 1.0;
}

//---------------------------------------
// Calculate final fare amount
//---------------------------------------
float FareCalculator::calculateFare(float distanceKm, int waitingMinutes) {
    float fare = baseFare
        + (distanceKm * perKmRate)
        + (waitingMinutes * waitingCharge);

    fare *= surgeMultiplier;

    return fare;
}

//---------------------------------------
// Print detailed fare breakdown
//---------------------------------------
void FareCalculator::printFareBreakdown(float distanceKm, int waitingMinutes) {
    cout << "\n---- Fare Breakdown ----\n";
    cout << "Base Fare: Rs " << baseFare << endl;
    cout << "Distance (" << distanceKm << " km): Rs "
         << distanceKm * perKmRate << endl;
    cout << "Waiting (" << waitingMinutes << " min): Rs "
         << waitingMinutes * waitingCharge << endl;
    cout << "Surge Multiplier: x" << surgeMultiplier << endl;

    cout << "--------------------------\n";
    cout << "Total Fare: Rs "
         << calculateFare(distanceKm, waitingMinutes) << endl;
}
