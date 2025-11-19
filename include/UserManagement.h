#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <string>
#include <unordered_map>

using namespace std;

struct User {
    string username;
    string password;
    string role; // "rider" or "driver"
};

class UserManagement {
private:
    unordered_map<string, User> users;   // username → User

public:
    bool registerUser(const string& username, const string& password, const string& role);
    bool loginUser(const string& username, const string& password);
    bool userExists(const string& username);
    string getUserRole(const string& username);
};

#endif
