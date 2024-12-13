
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Constants for admin credentials and customer file path
const string ADMIN_EMAIL = "anees78@gmail.com";
const string ADMIN_PASSWORD = "anees123";
const string CUSTOMER_FILE = "customers.txt";

// Login function for the user
bool login(string& log) {
    string email, password;
    while (true) {
        cout << "Login to the user \n";

        //  user for email and password
        cout << "Enter email: ";
        cin >> email;

        cout << "Enter password: ";
        cin >> password;

        // Check if the user is an admin
        if (email == ADMIN_EMAIL && password == ADMIN_PASSWORD) {
            log = "admin";
            cout << "Admin logged in successfully.\n";
            return true;
        }
        else {
            // Open the customer file for reading
            ifstream file(CUSTOMER_FILE);
            if (!file.is_open()) { // Check if the file opens successfully
                cout << "Error: Could not open customer file.\n";
                return false;
            }

            // Variables to hold stored email and password
            string storedEmail, storedPassword;

            // Read customer details from the file
            while (file >> storedEmail >> storedPassword) {
                // Check if the entered  details match any stored 
                if (email == storedEmail && password == storedPassword) {
                    log = "customer";
                    cout << "Customer logged in successfully.\n";
                    file.close();
                    return true;
                }
            }

            // If no match is found, login fails
            cout << "Invalid email or password. Please try again.\n";
            file.close();
            
        }
    }

}



//#ifndef USER_H
//#define USER_H
//
//#include <iostream>
//#include <fstream>
//#include <string>
//using namespace std;
//
//// Constants for admin credentials and customer file path
//const string ADMIN_EMAIL = "anees78@gmail.com";
//const string ADMIN_PASSWORD = "anees123";
//const string CUSTOMER_FILE = "customers.txt";
//
//// Login function for the user
//bool login(string& log) {
//    string email, password;
//    while (true) {
//        cout << "Login to the user \n";
//
//        // User for email and password
//        cout << "Enter email: ";
//        cin >> email;
//
//        cout << "Enter password: ";
//        cin >> password;
//
//        // Check if the user is an admin
//        if (email == ADMIN_EMAIL && password == ADMIN_PASSWORD) {
//            log = "admin";
//            cout << "Admin logged in successfully.\n";
//            return true;
//        }
//        else {
//            // Open the customer file for reading
//            ifstream file(CUSTOMER_FILE);
//            if (!file.is_open()) { // Check if the file opens successfully
//                cout << "Error: Could not open customer file.\n";
//                return false;
//            }
//
//            // Variables to hold stored email and password
//            string storedEmail, storedPassword;
//
//            // Read customer details from the file
//            while (file >> storedEmail >> storedPassword) {
//                // Check if the entered details match any stored customer
//                if (email == storedEmail && password == storedPassword) {
//                    log = "customer";
//                    cout << "Customer logged in successfully.\n";
//                    file.close();
//                    return true;
//                }
//            }
//
//            // If no match is found, login fails
//            cout << "Invalid email or password. Please try again.\n";
//            file.close();
//        }
//    }
//}
//
//#endif
