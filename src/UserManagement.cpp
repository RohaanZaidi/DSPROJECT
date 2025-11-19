#include "UserManagement.h"
#include <iostream>

bool UserManagement::registerUser(const string& username, const string& password, const string& role) {
    if (users.find(username) != users.end()) {
        return false; // error if the user already exists
    }

    User newUser;
    newUser.username = username;
    newUser.password = password;
    newUser.role = role;

    users[username] = newUser;
    return true;
}

bool UserManagement::loginUser(const string& username, const string& password) {
    if (users.find(username) == users.end())
        return false;

    return users[username].password == password;
}

bool UserManagement::userExists(const string& username) {
    return users.find(username) != users.end();
}

string UserManagement::getUserRole(const string& username) {
    if (!userExists(username)) return "";
    return users[username].role;
}
