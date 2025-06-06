#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Ticket.h"
#include "Flight.h"

class Customer {
private:
    int id;
    string name;
    string email;
    list<Ticket> bookedTickets;

public:
    Customer(int id, const string& name, const string& email);
    void bookFlight(const vector<Flight>& flights, int flightId);
    void cancelFlight(int flightID);
    void displayCustomer() const;
    int getId() const { return id; }
    string getName() const { return name; }
    void displayBookedFlights() const {
        for (const Ticket& t : bookedTickets) {
            cout << t.getFlightNumber() << " ";
        }
        cout << endl;
    }
};

#endif
