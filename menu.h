#ifndef MENU_H
#define MENU_H
#include <iostream>
using namespace std;

void showAdminMenu() {
    cout << "\n--- Admin Menu ---\n";
    cout << "1. Book Reservation\n";
    cout << "2. Cancel Reservation\n";
    cout << "3. Search Reservation\n";
    cout << "4. Update Reservation\n";
    cout << "5. Display All Reservations\n";
    cout << "6. Exit\n";
}

void showCustomerMenu() {
    cout << "\n--- Customer Menu ---\n";
    cout << "1. Search Reservation\n";
    cout << "2. Exit\n";
   
}

#endif

