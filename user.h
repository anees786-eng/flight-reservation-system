#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Constants for admin credentials and customer file path
const string ADMIN_EMAIL = "anees78@gmail.com";
const string ADMIN_PASSWORD = "anees123";
const string CUSTOMER_FILE = "customers.txt";

// Login function for the user
bool login(string& rol, string& email) {
    string password;

    while (true) {
        cout << "Login to the system\n";

        // Prompt user for email and password
        cout << "Enter email: ";
        cin >> email;

        cout << "Enter password: ";
        cin >> password;

        // Check if the user is an admin
        if (email == ADMIN_EMAIL && password == ADMIN_PASSWORD) {
            rol = "admin";
            cout << "Admin logged in successfully.\n";
            return true;
        }
        // Check if the user is a customer
        else {
            // Open the customer file for reading
            ifstream file(CUSTOMER_FILE);
            if (!file.is_open()) { // Check if the file opens successfully
                cout << "Error: Could not open customer file.\n";
                return false;
            }

            string storedEmail;
            bool bin = false;  //If a match is bin( the input email matches one from the file), bin is set to true.
           
            // Read customer emails from the file
            while (file >> storedEmail) {
                // Check if the entered email matches a customer email and the password is correct
                if (email == storedEmail && password == "password123") {  // Default password for customers
                    rol = "customer";
                    bin = true;
                    break;
                }
            }
            // The login success (bin) is checked.
            if (bin) {
                cout << "Customer logged in successfully.\n";
                file.close();
                return true;
            }
            else {
                cout << "Invalid email or password. Please try again.\n";
                file.close();
            }
        }
    }


}

#endif



