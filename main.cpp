
#include "user.h"
#include "reservation.h"
#include "menu.h"
#include <iostream>
using namespace std;


int main() {
    string log;

    loadReservationsFromFile();
    loadCustomer();

    // Attempt to log in
    if (!login(log)) {
        cout << "Login failed. Exiting...\n";
        return 1;

    }
    int choice;
    do {
        //Show menu 
        if (log == "admin") {
            showAdminMenu();
        }
        else if (log == "customer") {
            showCustomerMenu();
        }

        cout << "Enter your choice: ";
        cin >> choice;

        //Handle choices for the admin
        if (log == "admin") {
            switch (choice) {
            case 1: bookReservation(); break;
            case 2: cancelReservation(); break;
            case 3: searchReservation(log); break;
            case 4: updateReservation(); break;
            case 5: displayAllReservations(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n"; break;
            }
        }
        // Handle choices for the customer
        else if (log == "customer") {
            switch (choice) {
            case 1: searchReservation(log); break;

            case 2: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n"; break;
            }
        }
    } while ((log == "admin" && choice != 6) || (log == "customer" && choice != 2));

    return 0;
}






