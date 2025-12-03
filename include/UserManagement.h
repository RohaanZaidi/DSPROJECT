#ifndef USER_MODULE_H
#define USER_MODULE_H

#include <iostream>
using namespace std;

//------------------------------------------------------------
// USER NODE
//------------------------------------------------------------
class User {
public:
    int ID;
    string name;
    int phoneNO;
    string password;
    User* next;

    User(int ID, string name, int phoneNO, string password);
};

//------------------------------------------------------------
// USER HASH TABLE (for Riders + Drivers)
//------------------------------------------------------------
class UserList {
private:
    static const int TABLE_SIZE = 10;
    User* table[TABLE_SIZE];   // Passengers
    User* table2[TABLE_SIZE];  // Drivers

    int hashFunction(int key);

public:
    UserList();

    // USER (PASSENGER)
    void registerUser(int id, string name, int phone, string pass);
    bool loginUser(int id, string pass);
    void changeUserPassword(int id, string newPass);

    // DRIVER
    void registerDriver(int id, string name, int phone, string pass);
    bool loginDriver(int id, string pass);
    void changeDriverPassword(int id, string newPass);

    // Display everything
    void displayAll();
};

#endif



