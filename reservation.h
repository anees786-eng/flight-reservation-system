#ifndef RESERVATION_H
#define RESERVATION_H
#include<stdexcept>
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
    //Suitable for small to medium projects.
    void display()const{
        cout << "Reservation ID: " << reservationID
            << ", Email: " << email
            << ", Passenger Name: " << passengerName
            << ", Age: " << age
            << ", Seat Number: " << seatNumber << endl;
    }
};

//This is a map the key type is int, and the value type is Reservation
map<int, Reservation> reservations;
//This represents a mapping between two strings : 
map<string, string> customer; //This is the name of the map, which will store pairs of key-value strings.
//int nextReservationID = 1;
// Save reservations to a file


void saveReservationsToFile(const string& filename = "reservations.txt") {
    //ofstream Creates and writes to files 
    ofstream outFile(filename); // outFile is used to write data to a file.
    //all key - value pairs in the reservations map.
    for (const auto& pair : reservations) {
        const Reservation& res = pair.second;   // the value (Reservation object) from the pair and assigns it to the variable res.
        //This is an output file stream object used to write data to a file.
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
void bookReservation(const string& filename = "reservations.txt") {
    ifstream inFile(filename);
    int ID = 0;
    int nextReservationID = ID + 1;
    if (inFile) {
        int id, age, seatNumber;
        string email, passengerName;
        while (inFile >> id) {
            inFile.ignore(); // Ignore the value 
            getline(inFile, email); //infile read data(getline function use to read full line)
            getline(inFile, passengerName);
            inFile >> age;
            inFile.ignore(); // Ignore the value
            inFile >> seatNumber;
            inFile.ignore(); // Ignore the newline 
            ID = id; //get last id
            Reservation res{ id, email, passengerName, age, seatNumber };
            reservations[id] = res;

            if (id >= nextReservationID) {
                nextReservationID++;

            }
        }

    }

    // Increment for new reservation
    //int nextReservationID = ID + 1;
    //Create a new reservation
    Reservation res;
    res.reservationID = nextReservationID++;
    int age = 0;

    try {
        cout << "Enter email: ";
        cin >> res.email;
        //  Checks if the email (res.email) is already a key in the customer map.
        if (customer.find(res.email) == customer.end()) {  //Determines whether the email is missing from the map.
            customer[res.email] = "password123"; // Assign default password for new customers

            cout << "Customer email saved with default password.\n";

        }
        try {
            cout << "Enter passenger name: ";
            cin.ignore(); // Clear input buffer
            getline(cin, res.passengerName);

            if (res.passengerName.empty()) {
                throw invalid_argument("Passenger name must be charcter.");
            }
            //|| or opertaor(give value yes or no)
            cout << "Enter age: ";
            if (!(cin >> res.age) || res.age <= 0) {
                throw invalid_argument("Invalid input for age. Must be a  number.");
            }
            cout << "Enter seat number: ";
            if (!(cin >> res.seatNumber) || res.seatNumber <= 0) {
                throw invalid_argument("Invalid input for seat number. Must be a  number.");
            }
            // Check if email is stored in customers.txt
            ifstream customerFile(CUSTOMER_FILE);
            if (!customerFile) {
                throw runtime_error("Error opening customers.txt file.");
            }

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
                if (!customerFileOut) {
                    throw runtime_error("Error writing to customers.txt file.");
                }
                customerFileOut << res.email << endl; // Save the email in customers.txt
                customerFileOut.close();
            }

            // Save the reservation
            reservations[res.reservationID] = res;
            cout << "Reservation booked successfully! ID: " << res.reservationID << "\n";

            // Save all reservations to file
            saveReservationsToFile();
        }
        catch (const exception& a) {
            //what means (display value for user enter)
            cout << "Error: " << a.what() << "\n";
            cin.clear();  // Clear the input state
            //This represents the maximum number of characters
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cout << "Returning to the main menu...\n";
    }

    //& is refetence of e (e handel all exception)
    catch (const exception& e) {
        cout << "error unexpacted: " << e.what() << "\n";

    }

}
// Update reservation (admin function)
void updateReservation(const string& filename = "reservations.txt") {
    //int id;
  
    //Reservation res;
    //const string filename = "reservations.txt";
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error: File not found.\n";
    }
    int id, age, seatNumber;
    string storedEmail, name;
    Reservation res;
    while (inFile >> id) {
        inFile.ignore(); // Ignore newline after ID
        getline(inFile, storedEmail); // Read email
        getline(inFile, name);        // Read passenger name
        inFile >> age;
        inFile.ignore(); // Ignore newline after age
        inFile >> seatNumber;
        inFile.ignore(); // Ignore newline after seat number

        Reservation res{ id, storedEmail, name, age, seatNumber };
        reservations[id] = res;

    }

    inFile.close();
    
    cout << "Enter reservation ID to update: ";
    cin >> id;
    
    //it means iterator
    auto it = reservations.find(id);
    if (it != reservations.end())
    {
        //it-second(store elemnt in pair first and second)
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
void cancelReservation(const string& filename = "reservations.txt") {
    // Step 1: Load reservations from the file into the map
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error: File not found.\n";
        return;
    }

    reservations.clear(); // Clear any existing data in the map

    int id, age, seatNumber;
    string email, passengerName;

    while (inFile >> id) {
        inFile.ignore(); // Ignore newline after ID
        getline(inFile, email); // Read email
        getline(inFile, passengerName); // Read passenger name
        inFile >> age;
        inFile.ignore(); // Ignore newline after age
        inFile >> seatNumber;
        inFile.ignore(); // Ignore newline after seat number

        Reservation res{ id, email, passengerName, age, seatNumber };
        reservations[id] = res; // Add to the map
    }

    inFile.close();

    // Step 2: Prompt user for the reservation ID to cancel
    cout << "Enter reservation ID to cancel: ";
    cin >> id;

    // Step 3: Check if the reservation exists and remove it
    auto it = reservations.find(id);
    if (it != reservations.end()) {
        reservations.erase(it); // Remove from the map
        cout << "Reservation cancelled successfully.\n";

        // Step 4: Save updated reservations back to the file
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Error: Unable to write to file.\n";
            return;
        }

        for (const auto& pair : reservations) {
            const Reservation& res = pair.second;
            outFile << res.reservationID << "\n"
                << res.email << "\n"
                << res.passengerName << "\n"
                << res.age << "\n"
                << res.seatNumber << "\n";
        }

        outFile.close();
    }
    else {
        cout << "Reservation not found.\n";
    }
}


// Search reservation (customer/admin function)
void searchReservation(const string& email) {
    const string filename = "reservations.txt";
    ifstream inFile(filename);
     if (!inFile) {
        cout << "Error: File not found.\n";
        }
    int id, age, seatNumber;
    string storedEmail, name;
    Reservation res;
    while(inFile >> id) {
        inFile.ignore(); // Ignore newline after ID
        getline(inFile, storedEmail); // Read email
        getline(inFile, name);        // Read passenger name
        inFile >> age;
        inFile.ignore(); // Ignore newline after age
        inFile >> seatNumber;
        inFile.ignore(); // Ignore newline after seat number
        
        Reservation res{ id, storedEmail, name, age, seatNumber };
        reservations[id] = res;

    }

    inFile.close();

    //  user to enter reservation ID
    cout << "Enter reservation ID to search: ";
    cin >> id;

    // Search for the reservation
    auto it = reservations.find(id);
    if (it != reservations.end()) {
        // Check if the email matches or if the user is an admin
        if (it->second.email == email || email == "admin") {
            cout << "Reservation Details:\n";
            it->second.display(); // Display reservation details
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
void displayAllReservations(const string& filename = "reservations.txt") {
    //loadReservationsFromFile();
    ifstream inFile(filename);
    //The condition checks whether the file stream object inFile is in a failed state.
    if (!inFile) {
        cout << "File not found: " << filename << "\n";
    }
   int id, age, seatNumber;
    string email, name;
    
    while (inFile >> id) {
        inFile.ignore(); // Ignore the value 
        getline(inFile, email); //infile read data(getline function use to read full line)
        getline(inFile, name);
        inFile >> age;
        inFile.ignore(); // Ignore the value
        inFile >> seatNumber;
        inFile.ignore(); // Ignore the newline 

        Reservation res{ id, email, name, age, seatNumber };
        reservations[id] = res;
      }

    for (const auto& pair : reservations) {
        pair.second.display();

    }
}

#endif


