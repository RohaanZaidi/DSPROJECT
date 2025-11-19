#ifndef CAB_MANAGEMENT_H
#define CAB_MANAGEMENT_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Cab {
    string cabId;
    string driverName;
    bool available;
    double x, y; // location of cab
};

class CabManagement {
private:
    unordered_map<string, Cab> cabs; // cabId → Cab

public:
    void addCab(const string& cabId, const string& driverName, double x, double y);
    Cab* getCab(const string& cabId);
    void updateCabLocation(const string& cabId, double x, double y);
    void setAvailability(const string& cabId, bool status);
    vector<Cab> getAvailableCabs();
};

#endif

