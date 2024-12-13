#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

const string RESERVATION_FILE = "reservations.txt";

// Struct for reservation details
struct Reservation {
    string id;
    string name, email;
    int age;
    int seatNumber;
};

map<string, Reservation> reservations; // Stores reservations
map<string, string> customer; // Stores customer email-password 
void loadCustomer() {
    ifstream file(CUSTOMER_FILE);
    if (!file) return;

    string email, password;
    while (file >> email >> password) {
        customer[email] = password;
    }

    file.close();
}

// Function to save customer (append)
void appendCustomer(const string& email, const string& password) {
    ofstream file(CUSTOMER_FILE, ios::app);
    if (file.is_open()) {
        file << email << " " << password << "\n";
        file.close();
    }
    else {
        cerr << "Error: Unable to open customer file for appending.\n";
    }
}

// Function to save customer
void saveCustomer() {
    for (const auto& pair : customer) {
        appendCustomer(pair.first, pair.second);
    }
}

// Function to load reservations from file
void loadReservationsFromFile() {
    ifstream file(RESERVATION_FILE);
    if (!file) return;

    while (file) {
        Reservation res;
        file >> res.id;
        if (res.id.empty()) break;
        file >> res.email >> res.name >> res.age >> res.seatNumber;
        reservations[res.id] = res;
    }
    file.close();
}

// Function to save reservations to file (append)
void appendReservation(const Reservation& res) {
    ofstream file(RESERVATION_FILE, ios::app);
    if (file.is_open()) {
        file << "ID: " << res.id << "\n"
            << "Email: " << res.email << "\n"
            << "Name: " << res.name << "\n"
            << "Age: " << res.age << "\n"
            << "Seat number: " << res.seatNumber << "\n\n";
        file.close();
    }
    else {
        cerr << "Error: Unable to open reservation file for appending.\n";
    }
}

// Function to save reservations to file
void saveReservationsToFile() {
    for (const auto& pair : reservations) {
        appendReservation(pair.second);
    }
}

// Function to book a reservation
void bookReservation() {
    Reservation res;
    cout << "Enter email: ";
    cin >> res.email;

    if (customer.find(res.email) == customer.end()) {
        customer[res.email] = "password123"; // Default password for new customers
        saveCustomer();
        cout << "Customer email saved with default password.\n";
    }

    cout << "Enter reservation ID: ";
    cin >> res.id;

    if (reservations.find(res.id) != reservations.end()) {
        cout << "Reservation with this ID already exists.\n";
        return;
    }
    cout << "Enter passenger name: ";
    cin.ignore();
    getline(cin, res.name);
    cout << "Enter age: ";
    cin >> res.age;
    cout << "Enter seat number: ";
    cin >> res.seatNumber;

    reservations[res.id] = res;
    appendReservation(res);
    cout << "Reservation booked successfully!\n";
}

// Function to cancel a reservation
void cancelReservation() {
    string id;
    cout << "Enter the reservation ID to cancel: ";
    cin >> id;

    if (reservations.erase(id)) {
        saveReservationsToFile();
        cout << "Reservation canceled successfully!\n";
    }
    else {
        cout << "Reservation not found.\n";
    }
}

// Function to search for a reservation
void searchReservation(const string& customerEmail) {
    string id;
    cout << "Enter the reservation ID to search: ";
        cin >> id;
        for (const auto& pair : reservations) {
            const auto& res = pair.second;
            if (res.email == customerEmail) {
                cout << "ID: " << res.id << "\n"
                    << "Email: " << res.email << "\n"
                    << "Name: " << res.name << "\n"
                    << "Age: " << res.age << "\n"
                    << "Seat Number: " << res.seatNumber << "\n\n";
            }
            else {
                cout << "Reservation not found.\n";
            }
        }
}

// Function to update a reservation
void updateReservation() {
    string id;
    cout << "Enter the reservation ID to update: ";
    cin >> id;

    auto it = reservations.find(id);
    if (it != reservations.end()) {
        auto& res = it->second;

        cout << "Enter new email: ";
        cin >> res.email;

        cout << "Enter new passenger name: ";
        cin.ignore();
        getline(cin, res.name);

        cout << "Enter new age: ";
        cin >> res.age;

        cout << "Enter new seat number: ";
        cin >> res.seatNumber;

        saveReservationsToFile();
        cout << "Reservation updated successfully!\n";
    }
    else {
        cout << "Reservation not found.\n";
    }
}

// Function to display all reservations
void displayAllReservations() {
    cout << "\n--- Reservations ---\n";
    for (const auto& pair : reservations) {
        const auto& res = pair.second;
        cout << "ID: " << res.id << "\n"
            << "Email: " << res.email << "\n"
            << "Name: " << res.name << "\n"
            << "Age: " << res.age << "\n"
            << "Seat Number: " << res.seatNumber << "\n\n";
    }
}

#endif

//// Function to load customer details
//void loadCustomer() {
//    ifstream file(CUSTOMER_FILE);
//    if (!file) return;
//
//   string email, password;
//    while (file >> email >> password) {
//        customer[email] = password;
//    }
//    
//    file.close();
//}
//
//// Function to save customer 
//void saveCustomer() {
//    ofstream file(CUSTOMER_FILE, ios::app);
//    for (const auto& pair : customer) {
//        file << pair.first << " " << pair.second << "\n";
//    }
//   
//    file.close();
//}
//
//// Function to load reservations from a file
//void loadReservationsFromFile() {
//    ifstream file(RESERVATION_FILE);
//    if (!file) return;
//
//    while (file) {
//        Reservation res;
//        file >> res.id;
//        if (res.id.empty()) break;
//        file >> res.email >> res.name >> res.age >> res.seatNumber;
//        reservations[res.id] = res;
//    }
//    file.close();
//}
//
//
//
//// Function to save reservations to a file
//void saveReservationsToFile() {
//    ofstream file(RESERVATION_FILE, ios::app);
//    for (const auto& pair : reservations) {
//        const auto& res = pair.second;
//        file
//        <<"ID:" << res.id << "\n"
//        <<"Email: " << res.email << "\n"
//        <<"Name: " << res.name << "\n"
//        <<"Age: " << res.age << "\n"
//        <<"Seat number: " << res.seatNumber << "\n";
//            
//   
//        
//    }
//    
//    file.close();
//}
//
//// Function to book a reservation
//void bookReservation() {
//    Reservation res;
//    cout << "Enter email: ";
//    cin >> res.email;
//
//    if (customer.find(res.email) == customer.end()) {
//        customer[res.email] = "password123";
//        saveCustomer();
//        cout << "Customer email saved with default password.\n";
//    }
//
//    cout << "Enter reservation ID: ";
//    cin >> res.id;
//
//    if (reservations.find(res.id) != reservations.end()) {
//        cout << "Reservation with this ID already exists.\n";
//        return;
//    }
//
//    cout << "Enter passenger name: ";
//    cin.ignore();
//    getline(cin, res.name);
//
//    cout << "Enter age: ";
//    cin >> res.age;
//
//    cout << "Enter seat number: ";
//    cin >> res.seatNumber;
//
//    reservations[res.id] = res;
//    saveReservationsToFile();
//    cout << "Reservation booked successfully!\n";
//}
//
//// Function to cancel a reservation
//void cancelReservation() {
//    string id;
//    cout << "Enter the reservation ID to cancel: ";
//    cin >> id;
//
//    if (reservations.erase(id)) {
//        saveReservationsToFile();
//        cout << "Reservation canceled successfully!\n";
//    }
//    else {
//        cout << "Reservation not found.\n";
//    }
//}
//
//// Function to search for a reservation
//void searchReservation() {
//    string id;
//    cout << "Enter the reservation ID to search: ";
//    cin >> id;
//
//    auto it = reservations.find(id);
//    if (it != reservations.end()) {
//        const auto& res = it->second;
//        cout << "Reservation found:\n"
//            << "ID: " << res.id << "\n"
//            << "Email: " << res.email << "\n"
//            << "Name: " << res.name << "\n"
//            << "Age: " << res.age << "\n"
//            << "Seat Number: " << res.seatNumber << "\n";
//    }
//    else {
//        cout << "Reservation not found.\n";
//    }
//}



//// Function to update a reservation
//void updateReservation() {
//    string id;
//    cout << "Enter the reservation ID to update: ";
//    cin >> id;
//
//    auto it = reservations.find(id);
//    if (it != reservations.end()) {
//      //it->second pairs of value and key
//        auto& res = it->second;
//
//        cout << "Enter new email: ";
//        cin >> res.email;
//
//        cout << "Enter new passenger name: ";
//        cin.ignore();
//        getline(cin, res.name);
//
//        cout << "Enter new age: ";
//        cin >> res.age;
//
//        cout << "Enter new seat number: ";
//        cin >> res.seatNumber;
//
//        saveReservationsToFile();
//        cout << "Reservation updated successfully!\n";
//    }
//    else {
//        cout << "Reservation not found.\n";
//    }
//}
//
//// Function to display all reservations
//void displayAllReservations() {
//    cout << "\n--- Reservations ---\n";
//    for (const auto& pair : reservations) {
//        const auto& res = pair.second;
//        cout << "ID: " << res.id << "\n"
//            << "Email: " << res.email << "\n"
//            << "Name: " << res.name << "\n"
//            << "Age: " << res.age << "\n"
//            << "Seat Number: " << res.seatNumber << "\n\n";
//    }
//}
//
//#endif
//






