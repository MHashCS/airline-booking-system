#include "Flight.h"

Flight::Flight(int id, const string& src, const string& dest, const string& depart, const string& arrive, int seats)
    : flightID(id), source(src), destination(dest), departureTime(depart), arrivalTime(arrive), availableSeats(seats), totalSeats(seats) {
    flightStatus = "On Time";
}

int Flight::getFlightID() const {
    return flightID;
}

int Flight::getAvailableSeats() const {
    return availableSeats;
}

string Flight::getSource() const {
    return source;
}

string Flight::getDestination() const {
    return destination;
}

void Flight::displayFlight() const {
    cout << "Flight ID: " << flightID << ", From: " << source << ", To: " << destination
        << ", Departure: " << departureTime << ", Arrival: " << arrivalTime
        << ", Available Seats: " << availableSeats << endl << ",Flight Status: " << flightStatus << endl;
}

void Flight::bookSeat() {
    if (availableSeats > 0) {
        availableSeats--;
    }
    else {
        cout << "No seats available!" << endl;
    }
}

void Flight::cancelSeat() {
    availableSeats++;
}
void Flight::delayFlight()
{
    flightStatus = "Flight Delayed";
}

int Flight::getNextAvailableSeat() const {
    // Assuming seats are numbered from 1 to totalSeats
    // and we track available seats with a simple counter
    return totalSeats - availableSeats + 1;
}

