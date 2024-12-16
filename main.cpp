#include <iostream>
#include "menu.h"
#include "user.h"
#include "reservation.h"

using namespace std;

int main() {
    loadReservationsFromFile();

    string log, email;
    if (!login(log, email)) {
        cout << "Login failed. Exiting...\n";
        return 1;
    }

    int choice;
    do {
        // Show menu based on the role
        if (log == "admin") {
            showAdminMenu();
        }
        else if (log == "customer") {
            showCustomerMenu();
        }

        cout << "Enter your choice: ";
        cin >> choice;

        // Handle admin menu choices
        if (log == "admin") {
            switch (choice) {
            case 1: bookReservation(); break;
            case 2: cancelReservation(); break;
            case 3: searchReservation("admin"); break;
            case 4: updateReservation(); break;
            case 5: displayAllReservations(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n"; break;
            }
        }
        // Handle customer menu choices
        else if (log == "customer") {
            switch (choice) {
            case 1: searchReservation(email); break;
            case 2: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n"; break;
            }
        }
    } while ((log == "admin" && choice != 6) || (log == "customer" && choice != 2));

    saveReservationsToFile();  // Save data before exiting
    return 0;
}


