#include <iostream>
#include "Graph.h"
#include "Flight.h"
#include "Customer.h"
#include "Ticket.h"
using namespace std;

static int nextUserId = 1;
static list<Customer> allCustomers;  // Add this to track all customers and their bookings

void adminMenu(Graph& graph, list<Flight>& flights);
void userMenu(Graph& graph, list<Flight>& flights, Customer& customer);


int main() {
    Graph graph(5);
    // Add some initial cities
    graph.addCity("New York");
    graph.addCity("London");
    graph.addCity("Paris");
    graph.addCity("Tokyo");
    graph.addCity("Dubai");

    list<Flight> flights;
    // Add hardcoded flights
    flights.push_back(Flight(101, "New York", "London", "10:00", "22:00", 150));
    flights.push_back(Flight(102, "London", "Paris", "08:30", "10:30", 100));
    flights.push_back(Flight(103, "Paris", "Dubai", "14:00", "23:00", 200));
    flights.push_back(Flight(104, "Dubai", "Tokyo", "01:00", "15:00", 180));
    flights.push_back(Flight(105, "Tokyo", "New York", "11:00", "22:00", 160));
    flights.push_back(Flight(106, "New York", "Dubai", "09:00", "23:00", 190));

    // Add corresponding routes for the flights
    graph.addRoute(0, 1);  // New York to London
    graph.addRoute(1, 2);  // London to Paris
    graph.addRoute(2, 4);  // Paris to Dubai
    graph.addRoute(4, 3);  // Dubai to Tokyo
    graph.addRoute(3, 0);  // Tokyo to New York
    graph.addRoute(0, 4);  // New York to Dubai

    // Add two hardcoded customers with some bookings
    Customer customer1(nextUserId++, "Ali Raza", "ali@gmail.com");
    Customer customer2(nextUserId++, "Hammad ", "Maddy@gmail.com");

    // Convert flights list to vector for booking
    vector<Flight> flightVector(flights.begin(), flights.end());

    // Book some flights for these customers
    for (Flight& flight : flights) {
        if (flight.getFlightID() == 101) {
            flight.bookSeat();  // Update seat count
            customer1.bookFlight(flightVector, 101);  // Books New York to London
        }
        if (flight.getFlightID() == 103) {
            flight.bookSeat();  // Update seat count
            customer2.bookFlight(flightVector, 103);  // Books Paris to Dubai
        }
    }

    // Add them to allCustomers list
    allCustomers.push_back(customer1);
    allCustomers.push_back(customer2);

    // Create customer variable for menu operations
    Customer customer(nextUserId++, "John Doe", "john.doe@example.com");

    // Hardcoded Admin Credentials
    string adminUsername = "admin";
    string adminPassword = "1234";

    while (true) {
        cout << "\n========================================\n";
        cout << "         AIRLINE BOOKING SYSTEM         \n";
        cout << "========================================\n";
        cout << "1. Admin Login\n";
        cout << "2. User Login\n";
        cout << "3. Exit\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            string username, password;
            cout << "Enter Admin Username: ";
            cin >> username;
            cout << "Enter Admin Password: ";
            cin >> password;

            if (username == adminUsername && password == adminPassword) {
                adminMenu(graph, flights);
            }
            else {
                cout << "Invalid credentials!" << endl;
            }
        }
        else if (choice == 2) {
            userMenu(graph, flights, customer);

        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid option! Try again.\n";
        }
    }

    return 0;
}

void adminMenu(Graph& graph, list<Flight>& flights) {
    while (true) {
        cout << "\n========================================\n";
        cout << "             ADMIN MENU                \n";
        cout << "========================================\n";
        cout << "1. Add Route\n";
        cout << "2. Create Flight\n";
        cout << "3. Remove Flight\n";
        cout << "4. Delay Flight\n";
        cout << "5. Display All Routes\n";
        cout << "6. Display All Flights\n";
        cout << "7. Display All Bookings\n";
        cout << "8. Back to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            string city1, city2;
            cout << "Enter first city: ";
            cin.ignore();
            getline(cin, city1);
            cout << "Enter second city: ";
            getline(cin, city2);

            int index1 = graph.findCityIndex(city1);
            int index2 = graph.findCityIndex(city2);

            if (index1 != -1 && index2 != -1) {
                graph.addRoute(index1, index2);
                cout << "Route added.\n";
            }
            else {
                cout << "One or both cities not found.\n";
            }
        }
        else if (choice == 2) {
            int id, seats;
            string src, dest, depart, arrive;

            cout << "Enter Flight ID: ";
            cin >> id;
            cout << "Enter Source City: ";
            cin.ignore();
            getline(cin, src);
            cout << "Enter Destination City: ";
            getline(cin, dest);

            // Check if route exists
            vector<string> route = graph.findRoute(src, dest);
            if (route.empty()) {
                cout << "No route exists between these cities. Please add a route first.\n";
                continue;
            }

            cout << "Enter Departure Time: ";
            cin >> depart;
            cout << "Enter Arrival Time: ";
            cin >> arrive;
            cout << "Enter Available Seats: ";
            cin >> seats;

            flights.push_back(Flight(id, src, dest, depart, arrive, seats));
            cout << "Flight created successfully.\n";
        }
        else if (choice == 3) {
            int flightID;
            cout << "Enter Flight ID to cancel: ";
            cin >> flightID;

            for (auto it = flights.begin(); it != flights.end(); ++it) {
                if (it->getFlightID() == flightID) {
                    flights.erase(it);
                    cout << "Flight canceled successfully.\n";
                    break;
                }
            }
        }
        else if (choice == 4) {
            int flightID;
            cout << "Enter Flight ID to Delay: ";
            cin >> flightID;

            for (auto it = flights.begin(); it != flights.end(); ++it) {
                if (it->getFlightID() == flightID) {
                    it->delayFlight(); // Delay the flight
                    cout << "Flight " << flightID << " delayed.\n";
                    break;
                }
            }
        }
        else if (choice == 5) {
            graph.displayConnections();
        }
        else if (choice == 6) {
            cout << "Available Flights:\n";
            for (const Flight& flight : flights) {
                flight.displayFlight();
            }
        }
        else if (choice == 7) {
            cout << "\n========================================\n";
            cout << "           ALL BOOKINGS                \n";
            cout << "========================================\n";
            if (allCustomers.empty()) {
                cout << "No bookings found in the system.\n";
            } else {
                for (const Customer& c : allCustomers) {
                    cout << "Customer ID: " << c.getId() << endl;
                    cout << "Name: " << c.getName() << endl;
                    cout << "Booked Flight Numbers: ";
                    c.displayBookedFlights();  // Just show flight numbers
                    cout << "----------------------------------------\n";
                }
            }
        }
        else if (choice == 8) {
            break;
        }
        else {
            cout << "Invalid option! Try again.\n";
        }
    }
}
void userMenu(Graph& graph, list<Flight>& flights, Customer& customer) {
    while (true) {
        cout << "\n========================================\n";
        cout << "             USER MENU                 \n";
        cout << "========================================\n";
        cout << "1. Book Flight\n";
        cout << "2. Cancel Booking\n";
        cout << "3. Check Available Flights\n";
        cout << "4. Check Route Between Cities\n";
        cout << "5. Back to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            string name, email;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter your email: ";
            getline(cin, email);
            
            customer = Customer(nextUserId++, name, email);  // Create new customer with details

            cout << "\nAvailable Flights:\n";
            cout << "----------------------------------------\n";
            for (const Flight& flight : flights) {
                flight.displayFlight();
                cout << "----------------------------------------\n";
            }

            cout << "Enter Flight ID to book: ";
            int flightID;
            cin >> flightID;

            for (Flight& flight : flights) {
                if (flight.getFlightID() == flightID) {
                    if (flight.getAvailableSeats() <= 0) {
                        cout << "Sorry, this flight is fully booked!\n";
                        break;
                    }

                    flight.bookSeat();
                    // Convert list to vector for booking
                    vector<Flight> flightVector(flights.begin(), flights.end());
                    customer.bookFlight(flightVector, flightID);

                    cout << "\n========================================\n";
                    cout << "       Flight booked successfully!       \n";
                    cout << "========================================\n";

                    cout << "Would you like to print your ticket? (y/n): ";
                    char printChoice;
                    cin >> printChoice;

                    if (printChoice == 'y' || printChoice == 'Y') {
                        cout << "\n========================================\n";
                        cout << "              TICKET                     \n";
                        cout << "========================================\n";
                        Ticket ticket(to_string(customer.getId()), flight, flight.getNextAvailableSeat());
                        ticket.display_ticket();
                        cout << "========================================\n";
                    }
                    break;
                }
            }
        }
        else if (choice == 2) {
            int flightID, userID;
            cout << "Enter User ID: ";
            cin >> userID;
            cout << "Enter Flight ID: ";
            cin >> flightID;

            bool found = false;
            for (Customer& c : allCustomers) {  // Search through all customers
                if (c.getId() == userID) {
                    for (Flight& flight : flights) {
                        if (flight.getFlightID() == flightID) {
                            flight.cancelSeat();
                            c.cancelFlight(flightID);
                            cout << "Booking canceled successfully.\n";
                            found = true;
                            break;
                        }
                    }
                    break;
                }
            }
            if (!found) {
                cout << "Invalid User ID or Flight ID!\n";
            }
        }
        else if (choice == 3) {
            cout << "\n========================================\n";
            cout << "         AVAILABLE FLIGHTS             \n";
            cout << "========================================\n";
            for (const Flight& flight : flights) {
                flight.displayFlight();
                cout << "----------------------------------------\n";
            }
        }
        else if (choice == 4) {
            string source, destination;
            cout << "Enter source city: ";
            cin >> source;
            cout << "Enter destination city: ";
            cin >> destination;

            vector<string> route = graph.findRoute(source, destination);
            if (route.empty()) {
                cout << "No route found between these cities.\n";
            }
            else {
                cout << "Route found: ";
                for (size_t i = 0; i < route.size(); i++) {
                    cout << route[i];
                    if (i < route.size() - 1) cout << " -> ";
                }
                cout << endl;

                // Display available flights along this route
                cout << "\nAvailable flights along this route:\n";
                for (size_t i = 0; i < route.size() - 1; i++) {
                    for (const Flight& flight : flights) {
                        if (flight.getSource() == route[i] &&
                            flight.getDestination() == route[i + 1]) {
                            flight.displayFlight();
                        }
                    }
                }
            }
        }
        else if (choice == 5) {
            break;
        }
        else {
            cout << "Invalid option! Try again.\n";
        }
    }
}
