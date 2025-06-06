#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

class Flight {
private:
    int flightID;
    string source;
    string destination;
    string departureTime;
    string arrivalTime;
    int availableSeats;
    int totalSeats;
    string flightStatus = "on-time flight";
    vector<bool> seatMap;  // To track occupied seats

public:
    Flight(int id, const string& src, const string& dest, const string& depart, const string& arrive, int seats);
    int getFlightID() const;
    int getAvailableSeats() const;
    string getSource() const;
    string getDestination() const;
    void displayFlight() const;
    void bookSeat();
    void cancelSeat();
    void delayFlight();
    int getNextAvailableSeat() const;
};

#endif
