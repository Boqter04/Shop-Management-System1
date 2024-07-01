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
    enum MenuChoice {
        ADD_CUSTOMER = 1,
        EDIT_CUSTOMER,
        DELETE_CUSTOMER,
        VIEW_CUSTOMERS,
        SEARCH_CUSTOMER,
        EXIT
    };

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
                    case ADD_CUSTOMER: {
                        std::string name, phone, address;
                        int id;
                        int type;

                        name = DataValidInput::getStringInput("Enter customer name: ");
                        id = DataValidInput::getIntInput("Enter customer id: ");                 
                        phone = DataValidInput::getStringInput("Enter customer phone number: ");
                        address = DataValidInput::getStringInput("Enter customer address: ");
                        DataValidInput::validateId(id);
                        type = DataValidInput::getIntInput("Enter 1 for Old Customer, 2 for New Customer: ");
                        manager.addCustomer(name, id, phone, address, type);
                        break;
                    }
                    case EDIT_CUSTOMER: {
                        int id;
                        id = DataValidInput::getIntInput("Enter customer id: ");
                        DataValidInput::validateId(id);

                        manager.editCustomer(id);
                        break;
                    }
                    case DELETE_CUSTOMER: {
                        int id;
                        id = DataValidInput::getIntInput("Enter customer id: ");
                        DataValidInput::validateId(id);
                        manager.deleteCustomer(id);
                        break;
                    }
                    case VIEW_CUSTOMERS:
                        DataValidInput::SetColor(3);
                        manager.viewCustomers();
                        break;
                    case SEARCH_CUSTOMER: {
                        std::string phone;
                        phone = DataValidInput::getStringInput("Enter customer phone: ");
                        manager.searchCustomerByPhone(phone);
                        break;
                    }
                    case EXIT:
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