#include "CabManagement.h"

void CabManagement::addCab(const string& cabId, const string& driverName, double x, double y) {
    Cab cab;
    cab.cabId = cabId;
    cab.driverName = driverName;
    cab.available = true;
    cab.x = x;
    cab.y = y;

    cabs[cabId] = cab;
}

Cab* CabManagement::getCab(const string& cabId) {
    if (cabs.find(cabId) == cabs.end())
        return nullptr;
    return &cabs[cabId];
}

void CabManagement::updateCabLocation(const string& cabId, double x, double y) {
    if (cabs.find(cabId) == cabs.end()) return;
    cabs[cabId].x = x;
    cabs[cabId].y = y;
}

void CabManagement::setAvailability(const string& cabId, bool status) {
    if (cabs.find(cabId) == cabs.end()) return;
    cabs[cabId].available = status;
}

vector<Cab> CabManagement::getAvailableCabs() {
    vector<Cab> available;

    for (auto &entry : cabs) {
        if (entry.second.available) {
            available.push_back(entry.second);
        }
    }

    return available;
}
