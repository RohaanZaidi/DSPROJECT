#include <iostream>
using namespace std;

class FareCalculator {
private:
    float baseFare;        // base charge
    float perKmRate;       // rate per km
    float waitingCharge;   // per minute
    float surgeMultiplier; // surge multiplier

public:
    // Constructor with default values
    FareCalculator() {
        baseFare = 50.0;          // Rs 50 base fare
        perKmRate = 20.0;         // Rs 20 per km
        waitingCharge = 2.0;      // Rs 2 per minute waiting
        surgeMultiplier = 1.0;    // no surge by default
    }

    // Set custom rates if needed
    void setRates(float base, float perKm, float wait) {
        baseFare = base;
        perKmRate = perKm;
        waitingCharge = wait;
    }

    // Enable surge pricing
    void applySurge(float multiplier) {
        if (multiplier >= 1.0)
            surgeMultiplier = multiplier;
        else
            surgeMultiplier = 1.0;
    }

    // Calculate total fare
    float calculateFare(float distanceKm, int waitingMinutes) {
        float fare = baseFare 
                     + (distanceKm * perKmRate)
                     + (waitingMinutes * waitingCharge);

        // Apply surge
        fare = fare * surgeMultiplier;

        return fare;
    }

    // Display fare breakdown
    void printFareBreakdown(float distanceKm, int waitingMinutes) {
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
};
