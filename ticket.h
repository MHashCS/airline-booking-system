#ifndef TICKET_H
#define TICKET_H

#include <string>
#include "flight.h"

using namespace std;

class Ticket {
private:
    string ticketId;
    string userId;
    string flightNumber;
    int seatNumber;
    double price;
    bool isActive;
    double calculatePrice(const Flight& flight);

public:
    Ticket(const string& userId, const Flight& flight, int seatNum);

    // Getters
    string getTicketId() const { return ticketId; }
    string getUserId() const { return userId; }
    string getFlightNumber() const { return flightNumber; }
    int getSeatNumber() const { return seatNumber; }
    double getPrice() const { return price; }
    bool getIsActive() const { return isActive; }
    void display_ticket();
    // Operations
    void cancelTicket();
};

#endif 