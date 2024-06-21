
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "OldCustomer.cpp"
#include "NewCustomer.cpp"
#include "CustomerManager.cpp"
#include "DataValidInput.cpp"

// Class to run the customer management application
class CustomerApplication {
private:
    // Display the menu for customer management
    void displayMenu() {
        DataValidInput::SetColor(10);
        std::cout << "\n\t||- *************************** -||\n";
        std::cout << "\t       Customer Manager Menu\n";
        std::cout << "\t||- *************************** -||\n";
        std::cout << "\n1. Add Customer\n";
        std::cout << "2. Edit Customer\n";
        std::cout << "3. Delete Customer\n";
        std::cout << "4. View Customers\n";
        std::cout << "5. Search Customers\n";
        std::cout << "6. Back to Main Menu\n";
        std::cout << std::endl;
    }
public:

    // Run the customer management application
    void run() {

        CustomerManager manager;
        int choice;

        bool done = false;
        while (!done) {
            displayMenu();
            choice = DataValidInput::getIntInput("Enter your choice: ");
            try {
                switch (choice) {
                    case 1: {
                        std::string name, phone;
                        //std::string phone;
                        int address;
                        int type;

                        name = DataValidInput::getStringInput("Enter customer name: ");
                        address = DataValidInput::getIntInput("Enter customer address: ");                       
                        phone = DataValidInput::getStringInput("Enter customer phone number: ");
                        DataValidInput::validateAddress(address);
                        type = DataValidInput::getIntInput("Enter 1 for Old Customer, 2 for New Customer: ");
                        manager.addCustomer(address, name, phone, type);
                        break;
                    }
                    case 2: {
                        int address;
                        address = DataValidInput::getIntInput("Enter customer address: ");
                        DataValidInput::validateAddress(address);

                        manager.editCustomer(address);
                        break;
                    }
                    case 3: {
                        int address;
                        address = DataValidInput::getIntInput("Enter customer address: ");
                        DataValidInput::validateAddress(address);
                        manager.deleteCustomer(address);
                        break;
                    }
                    case 4:
                        DataValidInput::SetColor(3);
                        manager.viewCustomers();
                        break;
                    case 5: {
                        std::string phone;
                        phone = DataValidInput::getStringInput("Enter customer phone: ");
                        manager.searchCustomerByPhone(phone);
                        break;
                    }
                    case 6:
                        done = true;
                        break;
                    default:
                    DataValidInput::SetColor(12);
                        std::cout << "Invalid choice. Please try again.\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    }
};