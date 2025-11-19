#ifndef TRIP_HISTORY_H
#define TRIP_HISTORY_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Trip {
    string rider;
    string driver;
    string cabId;
    double distance;
    double fare;
};

class TripHistory {
private:
    unordered_map<string, vector<Trip>> riderTrips;   // rider → trips
    unordered_map<string, vector<Trip>> driverTrips;  // driver → trips

public:
    void addTrip(const Trip& t);

    vector<Trip> getRiderHistory(const string& rider);
    vector<Trip> getDriverHistory(const string& driver);
};

#endif
