#include <iostream>
#include <cstring>
#include <cmath>
#include "SmartCabSystem.h"
using namespace std;

//------------------------------------------------------------
// RIDER IMPLEMENTATION
//------------------------------------------------------------
Rider::Rider() {
    RiderID = -1;
    PickupLocation = 0;
}

Rider::Rider(int riderID, int pickup) {
    RiderID = riderID;
    PickupLocation = pickup;
}

//------------------------------------------------------------
// RIDER QUEUE IMPLEMENTATION
//------------------------------------------------------------
RiderQueue::RiderQueue() {
    front = rear = -1;
}

bool RiderQueue::isFULL() {
    return rear == 49;
}

bool RiderQueue::isEmpty() {
    return front == -1;
}

void RiderQueue::insert(int riderID, int pickupLocation) {
    if (isFULL()) {
        cout << "Cannot process more requests.\n";
        return;
    }

    if (front == -1)
        front = 0;

    rear++;
    arr[rear].RiderID = riderID;
    arr[rear].PickupLocation = pickupLocation;

    cout << "Ride request added to queue.\n";
}

void RiderQueue::dequeue() {
    if (isEmpty()) {
        cout << "No ride requests.\n";
        return;
    }

    if (front == rear)
        front = rear = -1;
    else
        front++;

    cout << "Ride request dequeued.\n";
}

//------------------------------------------------------------
// DRIVER IMPLEMENTATION
//------------------------------------------------------------
Driver::Driver() {
    id = -1;
    name[0] = '\0';
    location = 0;
    available = true;
}

//------------------------------------------------------------
// MIN-HEAP IMPLEMENTATION
//------------------------------------------------------------
DriverMinHeap::DriverMinHeap() {
    size = 0;
}

bool DriverMinHeap::isEmpty() {
    return size == 0;
}

void DriverMinHeap::push(Driver* d, int riderPickup) {
    if (size >= 50) {
        cout << "Heap full!\n";
        return;
    }

    int dist = abs(d->location - riderPickup);

    heap[size] = d;
    distanceArr[size] = dist;

    heapifyUp(size);
    size++;
}

Driver* DriverMinHeap::pop() {
    if (isEmpty()) {
        cout << "Heap empty!\n";
        return NULL;
    }

    Driver* minDriver = heap[0];

    heap[0] = heap[size - 1];
    distanceArr[0] = distanceArr[size - 1];
    size--;

    heapifyDown(0);

    return minDriver;
}

void DriverMinHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (distanceArr[index] < distanceArr[parent]) {
            swap(heap[index], heap[parent]);
            swap(distanceArr[index], distanceArr[parent]);
            index = parent;
        } else
            break;
    }
}

void DriverMinHeap::heapifyDown(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && distanceArr[left] < distanceArr[smallest])
            smallest = left;

        if (right < size && distanceArr[right] < distanceArr[smallest])
            smallest = right;

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            swap(distanceArr[index], distanceArr[smallest]);
            index = smallest;
        } else
            break;
    }
}

//------------------------------------------------------------
// DRIVER HASH MAP IMPLEMENTATION
//------------------------------------------------------------
DriverHashMap::DriverHashMap() {
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = NULL;
}

int DriverHashMap::hashFunction(int key) {
    return key % TABLE_SIZE;
}

void DriverHashMap::insertDriver(Driver* d) {
    int index = hashFunction(d->id);
    int start = index;

    while (table[index] != NULL) {
        index = (index + 1) % TABLE_SIZE;
        if (index == start) {
            cout << "Hash table full!\n";
            return;
        }
    }

    table[index] = d;
}

Driver* DriverHashMap::getDriver(int driverID) {
    int index = hashFunction(driverID);
    int start = index;

    while (table[index] != NULL) {
        if (table[index]->id == driverID)
            return table[index];

        index = (index + 1) % TABLE_SIZE;

        if (index == start)
            break;
    }

    return NULL;
}

void DriverHashMap::setAvailability(int driverID, bool status) {
    Driver* d = getDriver(driverID);

    if (d == NULL) {
        cout << "Driver not found!\n";
        return;
    }

    d->available = status;
}

void DriverHashMap::printDrivers() {
    cout << "\n--- DRIVER HASH TABLE ---\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL) {
            cout << "[ID: " << table[i]->id << "]  "
                 << table[i]->name
                 << " | Loc: " << table[i]->location
                 << " | Available: "
                 << (table[i]->available ? "Yes" : "No")
                 << "\n";
        }
    }
}

//------------------------------------------------------------
// TRIP IMPLEMENTATION
//------------------------------------------------------------
Trip::Trip(int tID, int rID, int dID, int pick, int drp) {
    tripID = tID;
    riderID = rID;
    driverID = dID;
    pickup = pick;
    drop = drp;
    next = NULL;
}

//------------------------------------------------------------
// TRIP LIST IMPLEMENTATION
//------------------------------------------------------------
TripList::TripList() {
    head = NULL;
}

void TripList::addTrip(int tripID, int riderID, int driverID, int pickup, int drop) {
    Trip* newTrip = new Trip(tripID, riderID, driverID, pickup, drop);

    if (head == NULL) {
        head = newTrip;
        return;
    }

    Trip* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newTrip;
}

void TripList::completeTrip(int tripID) {
    if (head == NULL) {
        cout << "No ongoing trips.\n";
        return;
    }

    if (head->tripID == tripID) {
        Trip* temp = head;
        head = head->next;
        delete temp;
        cout << "Trip " << tripID << " completed.\n";
        return;
    }

    Trip* prev = head;
    Trip* curr = head->next;

    while (curr != NULL) {
        if (curr->tripID == tripID) {
            prev->next = curr->next;
            delete curr;
            cout << "Trip " << tripID << " completed.\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "Trip not found.\n";
}

void TripList::displayTrips() {
    if (head == NULL) {
        cout << "No active trips.\n";
        return;
    }

    Trip* temp = head;
    cout << "\n--- ACTIVE TRIPS ---\n";
    while (temp != NULL) {
        cout << "TripID: " << temp->tripID
             << " | Rider: " << temp->riderID
             << " | Driver: " << temp->driverID
             << " | Pickup: " << temp->pickup
             << " | Drop: " << temp->drop << "\n";
        temp = temp->next;
    }
}
