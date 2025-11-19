#ifndef BOOKING_SYSTEM_H
#define BOOKING_SYSTEM_H

#include <queue>
#include <vector>
#include "CabManagement.h"
#include "TripHistory.h"
#include "FareCalculator.h"

struct BookingRequest {
    string riderName;
    double riderX, riderY;
};

class BookingSystem {
private:
    CabManagement &cabManager;
    TripHistory &tripHistory;
    FareCalculator &fareCalc;

public:
    BookingSystem(CabManagement &c, TripHistory &t, FareCalculator &f);

    string requestCab(const string& riderName, double x, double y);
};

#endif
