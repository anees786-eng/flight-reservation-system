#ifndef RESERVATION_H
#define RESERVATION_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct Reservation {
    int reservationID;
    string email;
    string passengerName;
    int age;
    int seatNumber;

    void display() const {
        cout << "Reservation ID: " << reservationID
            << ", Email: " << email
            << ", Passenger Name: " << passengerName
            << ", Age: " << age
            << ", Seat Number: " << seatNumber << endl;
    }
};

map<int, Reservation> reservations;
map<string, string> customer;
int nextReservationID = 1;

// Load reservations from file
void loadReservationsFromFile(const string& filename = "reservations.txt") {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "File not found: " << filename << "\n";
        return;
    }

    int id, age, seatNumber;
    string email, name;

    while (inFile >> id) {
        inFile.ignore(); // Ignore the delimiter '|'
        getline(inFile, email);
        getline(inFile, name);
        inFile >> age;
        inFile.ignore(); // Ignore the delimiter '|'
        inFile >> seatNumber;
        inFile.ignore(); // Ignore the newline or any delimiter

        Reservation res{ id, email, name, age, seatNumber };
        reservations[id] = res;

        if (id >= nextReservationID) {
            nextReservationID = id + 1;
        }
    }

    inFile.close();
}

// Save reservations to a file
void saveReservationsToFile(const string& filename = "reservations.txt") {
    ofstream outFile(filename);
    for (const auto& pair : reservations) {
        const Reservation& res = pair.second;
        outFile
     << res.reservationID << "\n" 
    << res.email << "\n"
   << res.passengerName << "\n"
    << res.age << "\n"
   << res.seatNumber << "\n";
    }
    outFile.close();
}

// Book reservation (admin function)

void bookReservation() {

    char choice;

    Reservation res;

    cout << "Enter email: ";
    cin >> res.email;

    // Check if the customer email is already stored
    if (customer.find(res.email) == customer.end()) {
        customer[res.email] = "password123"; // Assign default password for new customers
        cout << "Customer email saved with default password.\n";
    }
    do {

        // Input and validate reservation details
        cout << "Enter reservation ID: ";
        cin >> res.reservationID;

        // Check if the reservation ID already exists
        if (reservations.find(res.reservationID) != reservations.end()) {
            cout << "Error: Reservation with this ID already exists. Try again.\n";
           return ; // Restart the current iteration
        }

        cout << "Enter passenger name: ";
        cin.ignore(); // Clear input buffer
        getline(cin, res.passengerName);

        cout << "Enter age: ";
        cin >> res.age;

        cout << "Enter seat number: ";
        cin >> res.seatNumber;

        // Check if email is stored in customers.txt
        ifstream customerFile(CUSTOMER_FILE);
        bool emailExists = false;
        string storedEmail;
        while (customerFile >> storedEmail) {
            if (storedEmail == res.email) {
                emailExists = true;
                break;
            }
        }
        customerFile.close();

        if (!emailExists) {
            ofstream customerFileOut(CUSTOMER_FILE, ios::app);
            customerFileOut << res.email << endl; // Save the email in customers.txt
            customerFileOut.close();
        }

        // Save the reservation
        reservations[res.reservationID] = res;
        cout << "Reservation booked successfully! ID: " << res.reservationID << "\n";

        // Save all reservations to file
        saveReservationsToFile();

        // Ask user if they want to add another reservation
        cout << "Do you want to add another reservation? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Returning to the main menu...\n";
}

// Update reservation (admin function)
void updateReservation() {
    int id;
    cout << "Enter reservation ID to update: ";
    cin >> id;

    auto it = reservations.find(id);
    if (it != reservations.end()) {
        Reservation& res = it->second;

        // Ask user for updated details
        cout << "Current passenger name: " << res.passengerName << "\n";
        cout << "Enter new passenger name: ";
        cin.ignore(); // Clear input buffer
        string newName;
        getline(cin, newName);
        if (!newName.empty()) {
            res.passengerName = newName;
        }

        cout << "Current age: " << res.age << "\n";
        cout << "Enter new age: ";
        int newAge;
        cin >> newAge;
        if (newAge != 0) {
            res.age = newAge;
        }

        cout << "Current seat number: " << res.seatNumber << "\n";
        cout << "Enter new seat number: ";
        int newSeatNumber;
        cin >> newSeatNumber;
        if (newSeatNumber != 0) {
            res.seatNumber = newSeatNumber;
        }

        // Save all reservations to file
        saveReservationsToFile();
        cout << "Reservation updated successfully!\n";
    }
    else {
        cout << "Reservation not found.\n";
    }
}

// Cancel reservation (admin function)
void cancelReservation() {
    int id;
    cout << "Enter reservation ID to cancel: ";
    cin >> id;
    if (reservations.erase(id)) {
        cout << "Reservation cancelled.\n";
    }
    else {
        cout << "Reservation not found.\n";
    }
}

// Search reservation (customer/admin function)
void searchReservation(const string& email) {
    int id;
    cout << "Enter reservation ID to search: ";
    cin >> id;

    auto it = reservations.find(id);
    if (it != reservations.end()) {
        if (it->second.email == email || email == "admin") { // Admin can search any, customer can only see theirs
            it->second.display();
        }
        else {
            cout << "Reservation ID found, but it does not belong to this email.\n";
        }
    }
    else {
        cout << "Reservation ID not found.\n";
    }
}



// Display all reservations (admin function)
void displayAllReservations() {
    for (const auto& pair : reservations) {
        pair.second.display();
    }
}

#endif


