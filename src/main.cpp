#include <iostream>
#include "UserManagement.h"
#include "CabManagement.h"
#include "BookingSystem.h"
#include "TripHistory.h"
#include "FareCalculator.h"

using namespace std;

int main() {
    UserManagement userManager;
    CabManagement cabManager;
    TripHistory tripHistory;
    FareCalculator fareCalc;

    BookingSystem booking(cabManager, tripHistory, fareCalc);

    // Example usage:
    userManager.registerUser("rider1", "pass", "rider");
    userManager.registerUser("driver1", "pass", "driver");

    cabManager.addCab("CAB101", "driver1", 0, 0);
    cabManager.setAvailability("CAB101", true);

    cout << booking.requestCab("rider1", 5, 5) << endl;

    return 0;
}
