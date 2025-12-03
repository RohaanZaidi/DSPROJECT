#include "UserModule.h"

//------------------------------------------------------------
// USER CONSTRUCTOR
//------------------------------------------------------------
User::User(int ID, string name, int phoneNO, string password) {
    this->ID = ID;
    this->name = name;
    this->phoneNO = phoneNO;
    this->password = password;
    next = NULL;
}

//------------------------------------------------------------
// HASH FUNCTION
//------------------------------------------------------------
int UserList::hashFunction(int key) {
    return key % TABLE_SIZE;
}

//------------------------------------------------------------
// CONSTRUCTOR
//------------------------------------------------------------
UserList::UserList() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
        table2[i] = NULL;
    }
}

//------------------------------------------------------------
// REGISTER PASSENGER
//------------------------------------------------------------
void UserList::registerUser(int id, string n, int phone, string pass) {
    int index = hashFunction(id);
    User* newUser = new User(id, n, phone, pass);

    if (table[index] == NULL) {
        table[index] = newUser;
    }
    else {
        User* temp = table[index];
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newUser;
    }
    cout << "User Registered: " << n << endl;
}

//------------------------------------------------------------
// LOGIN PASSENGER
//------------------------------------------------------------
bool UserList::loginUser(int id, string pass) {
    int index = hashFunction(id);
    User* temp = table[index];

    while (temp != NULL) {
        if (temp->ID == id) {
            if (temp->password == pass) {
                cout << "✔ Login successful! Welcome, " << temp->name << "\n";
                return true;
            }
            else {
                cout << "✖ Incorrect password!\n";
                return false;
            }
        }
        temp = temp->next;
    }

    cout << "✖ ID not found!\n";
    return false;
}

//------------------------------------------------------------
// REGISTER DRIVER
//------------------------------------------------------------
void UserList::registerDriver(int id, string n, int phone, string pass) {
    int index = hashFunction(id);
    User* newDriver = new User(id, n, phone, pass);

    if (table2[index] == NULL) {
        table2[index] = newDriver;
    }
    else {
        User* temp = table2[index];
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newDriver;
    }

    cout << "Driver Registered: " << n << endl;
}

//------------------------------------------------------------
// LOGIN DRIVER
//------------------------------------------------------------
bool UserList::loginDriver(int id, string pass) {
    int index = hashFunction(id);
    User* temp = table2[index];

    while (temp != NULL) {
        if (temp->ID == id) {
            if (temp->password == pass) {
                cout << "✔ Login successful! Welcome, " << temp->name << "\n";
                return true;
            }
            else {
                cout << "✖ Incorrect password!\n";
                return false;
            }
        }
        temp = temp->next;
    }

    cout << "✖ Driver ID not found!\n";
    return false;
}

//------------------------------------------------------------
// CHANGE USER PASSWORD
//------------------------------------------------------------
void UserList::changeUserPassword(int id, string newPass) {
    int index = hashFunction(id);
    User* temp = table[index];

    while (temp != NULL) {
        if (temp->ID == id) {
            temp->password = newPass;
            cout << "✔ User password changed successfully!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "✖ ID not found.\n";
}

//------------------------------------------------------------
// CHANGE DRIVER PASSWORD
//------------------------------------------------------------
void UserList::changeDriverPassword(int id, string newPass) {
    int index = hashFunction(id);
    User* temp = table2[index];

    while (temp != NULL) {
        if (temp->ID == id) {
            temp->password = newPass;
            cout << "✔ Driver password changed successfully!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "✖ Driver ID not found.\n";
}

//------------------------------------------------------------
// DISPLAY ALL USERS & DRIVERS
//------------------------------------------------------------
void UserList::displayAll() {
    cout << "\n===== Registered Passengers =====\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "[" << i << "] ";
        User* temp = table[i];
        while (temp != NULL) {
            cout << temp->name << "(" << temp->ID << ") -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    cout << "\n===== Registered Drivers =====\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "[" << i << "] ";
        User* temp = table2[i];
        while (temp != NULL) {
            cout << temp->name << "(" << temp->ID << ") -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}

