#include "Customer.h"
#include "Ticket.h"
#include <vector>

// Simple constructor to initialize customer details
Customer::Customer(int id, const string& name, const string& email) : id(id), name(name), email(email) {}

// Book a flight for the customer
void Customer::bookFlight(const vector<Flight>& flights, int flightId) {
    // Find the flight and book if seats available
    for (const Flight& flight : flights) {
        if (flight.getFlightID() == flightId) {
            if (flight.getAvailableSeats() > 0) {
                // Create ticket using the correct constructor parameters
                Ticket ticket(to_string(this->id), flight, flight.getNextAvailableSeat());
                bookedTickets.push_back(ticket);
                return;
            }
            cout << "Sorry, flight " << flightId << " is full" << endl;
            return;
        }
    }
    cout << "Flight " << flightId << " not found" << endl;
}

// Cancel a booked flight
void Customer::cancelFlight(int flightID) {
    string flightStr = to_string(flightID);
    for (auto it = bookedTickets.begin(); it != bookedTickets.end(); ++it) {
        if (it->getFlightNumber() == flightStr) {
            it->cancelTicket();
            bookedTickets.erase(it);
            return;
        }
    }
}

// Show customer info and booked tickets
void Customer::displayCustomer() const {
    cout << "Customer Details:" << endl;
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Booked Flights: ";
    for (const Ticket& t : bookedTickets) {
        cout << t.getFlightNumber() << " ";
    }
    cout << endl;
}
