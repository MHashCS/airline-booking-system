#include <string>
#include <ctime>
#include "ticket.h"
using namespace std;

string generateTicketId() {
    // Generate a ticket ID using current time
    time_t now = time(0);

    // Use time to create a pseudo-random number
    int random = (now % 8999) + 1000;  // Generates number between 1000-9999

    return "TKT" + to_string(now) + to_string(random);
}

void Ticket::display_ticket() {
    cout << "Ticket ID: " << ticketId << endl;
    cout << "User ID: " << userId << endl;
    cout << "Flight Number: " << flightNumber << endl;
    cout << "Seat Number: " << seatNumber << endl;
    cout << "Price: " << price << endl;
    cout << "Status: " << (isActive ? "Active" : "Cancelled") << endl;
}

Ticket::Ticket(const string& userId, const Flight& flight, int seatNum)
    : userId(userId),
    flightNumber(to_string(flight.getFlightID())), // Set flightNumber as flight ID
    seatNumber(seatNum),
    price(calculatePrice(flight)),
    isActive(true) {
    ticketId = generateTicketId();
}

double Ticket::calculatePrice(const Flight& flight) {
    int a = rand()%49;
    return 100.00*a;  // Should implement actual pricing logic
}

void Ticket::cancelTicket() {
    isActive = false;
}
