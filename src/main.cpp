#include <iostream>
#include <string>
#include <cmath>
#include <limits>

#include "UserManagement.h"
#include "CabManagement.h"
#include "BookingSystem.h"
#include "TripHistory.h"
#include "FareCalculator.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    UserManagement userManager;
    CabManagement cabManager;
    TripHistory tripHistory;
    FareCalculator fareCalculator;

    BookingSystem bookingSystem(cabManager, tripHistory, fareCalculator);

    cout << "===== WELCOME TO CAB BOOKING SYSTEM =====\n";

    string currentUser = "";
    bool loggedIn = false;

    while (true) {
        cout << "\n===== MAIN MENU =====\n";

        if (!loggedIn) {
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "0. Exit\n";
            cout << "Choice: ";

            int choice;
            cin >> choice;

            if (choice == 0) break;

            string username, password, role;

            if (choice == 1) {
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                cout << "Role (rider/driver): ";
                cin >> role;

                if (role != "rider" && role != "driver") {
                    cout << "Invalid role.\n";
                    continue;
                }

                if (userManager.registerUser(username, password, role))
                    cout << "Registration successful!\n";
                else
                    cout << "Username already exists!\n";
            }
            else if (choice == 2) {
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (userManager.loginUser(username, password)) {
                    loggedIn = true;
                    currentUser = username;
                    cout << "Login successful!\n";
                } else {
                    cout << "Invalid username/password.\n";
                }
            }
            continue;
        }

        // USER IS LOGGED IN
        string role = userManager.getUserRole(currentUser);

        cout << "\nLogged in as: " << currentUser << " (" << role << ")\n";

        if (role == "rider") {
            cout << "1. Request Cab\n";
            cout << "2. View Trip History\n";
            cout << "3. Logout\n";
            cout << "0. Exit\n";
        } else if (role == "driver") {
            cout << "1. Add/Update Cab\n";
            cout << "2. Set Cab Availability\n";
            cout << "3. View Trip History\n";
            cout << "4. Logout\n";
            cout << "0. Exit\n";
        }

        int choice;
        cout << "Choice: ";
        cin >> choice;

        if (choice == 0) break;

        if (role == "rider") {
            if (choice == 1) {
                double x, y;
                cout << "Enter your current X location: ";
                cin >> x;
                cout << "Enter your current Y location: ";
                cin >> y;

                string result = bookingSystem.requestCab(currentUser, x, y);
                cout << result << endl;
            }
            else if (choice == 2) {
                auto trips = tripHistory.getRiderHistory(currentUser);

                if (trips.empty()) {
                    cout << "No trips found.\n";
                    continue;
                }

                cout << "\n===== YOUR TRIP HISTORY =====\n";
                for (auto &t : trips) {
                    cout << "Driver: " << t.driver
                         << ", Cab: " << t.cabId
                         << ", Distance: " << t.distance
                         << ", Fare: " << t.fare << "\n";
                }
            }
            else if (choice == 3) {
                loggedIn = false;
                currentUser = "";
            }
        }

        else if (role == "driver") {
            if (choice == 1) {
                string cabId;
                double x, y;

                cout << "Enter your Cab ID: ";
                cin >> cabId;

                cout << "Enter cab location (x y): ";
                cin >> x >> y;

                cabManager.addCab(cabId, currentUser, x, y);
                cabManager.setAvailability(cabId, true);

                cout << "Cab added/updated successfully!\n";
            }
            else if (choice == 2) {
                string cabId;
                cout << "Enter Cab ID: ";
                cin >> cabId;

                Cab* cab = cabManager.getCab(cabId);
                if (!cab) {
                    cout << "Cab not found!\n";
                    continue;
                }

                cout << "1. Set Available\n2. Set Unavailable\nChoice: ";
                int st;
                cin >> st;

                cabManager.setAvailability(cabId, st == 1);
                cout << "Availability updated.\n";
            }
            else if (choice == 3) {
                auto trips = tripHistory.getDriverHistory(currentUser);

                if (trips.empty()) {
                    cout << "No trips found.\n";
                    continue;
                }

                cout << "\n===== DRIVER TRIP HISTORY =====\n";
                for (auto &t : trips) {
                    cout << "Rider: " << t.rider
                         << ", Cab: " << t.cabId
                         << ", Distance: " << t.distance
                         << ", Fare: " << t.fare << "\n";
                }
            }
            else if (choice == 4) {
                loggedIn = false;
                currentUser = "";
            }
        }
    }

    cout << "Exiting system. Goodbye!\n";
    return 0;
}

