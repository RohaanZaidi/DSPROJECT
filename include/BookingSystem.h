#ifndef SMART_CAB_SYSTEM_H
#define SMART_CAB_SYSTEM_H

//------------------------------------------------------------
// RIDER CLASS
//------------------------------------------------------------
class Rider {
public:
    int RiderID;
    int PickupLocation;

    Rider();
    Rider(int riderID, int pickup);
};

//------------------------------------------------------------
// RIDER QUEUE (ARRAY-BASED)
//------------------------------------------------------------
class RiderQueue {
public:
    Rider arr[50];
    int front;
    int rear;

    RiderQueue();

    bool isFULL();
    bool isEmpty();

    void insert(int riderID, int pickupLocation);
    void dequeue();
};

//------------------------------------------------------------
// DRIVER CLASS
//------------------------------------------------------------
class Driver {
public:
    int id;
    char name[20];
    int location;
    bool available;

    Driver();
};

//------------------------------------------------------------
// MIN-HEAP PRIORITY QUEUE FOR NEAREST DRIVER
//------------------------------------------------------------
class DriverMinHeap {
private:
    Driver* heap[50];
    int distanceArr[50];
    int size;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    DriverMinHeap();

    bool isEmpty();
    void push(Driver* d, int riderPickup);
    Driver* pop();
};

//------------------------------------------------------------
// DRIVER HASH MAP (LINEAR PROBING)
//------------------------------------------------------------
#define TABLE_SIZE 50

class DriverHashMap {
private:
    Driver* table[TABLE_SIZE];

public:
    DriverHashMap();

    int hashFunction(int key);
    void insertDriver(Driver* d);
    Driver* getDriver(int driverID);
    void setAvailability(int driverID, bool status);
    void printDrivers();
};

//------------------------------------------------------------
// TRIP CLASS
//------------------------------------------------------------
class Trip {
public:
    int tripID;
    int riderID;
    int driverID;
    int pickup;
    int drop;

    Trip* next;

    Trip(int tID, int rID, int dID, int pick, int drp);
};

//------------------------------------------------------------
// LINKED LIST FOR ACTIVE TRIPS
//------------------------------------------------------------
class TripList {
private:
    Trip* head;

public:
    TripList();

    void addTrip(int tripID, int riderID, int driverID, int pickup, int drop);
    void completeTrip(int tripID);
    void displayTrips();
};

#endif

