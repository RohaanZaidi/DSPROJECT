#include "TripHistory.h"

void TripHistory::addTrip(const Trip& t) {
    riderTrips[t.rider].push_back(t);
    driverTrips[t.driver].push_back(t);
}

vector<Trip> TripHistory::getRiderHistory(const string& rider) {
    if (riderTrips.find(rider) == riderTrips.end())
        return {};
    return riderTrips[rider];
}

vector<Trip> TripHistory::getDriverHistory(const string& driver) {
    if (driverTrips.find(driver) == driverTrips.end())
        return {};
    return driverTrips[driver];
}
