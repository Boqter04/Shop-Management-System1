#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <fstream>
#include "OldCustomer.cpp"
#include "NewCustomer.cpp"
#include "Customer.cpp"
#include "DataValidInput.cpp"
#include "CustomerRepository.cpp"

// Class managing customer
class CustomerManager : public CustomerRepository {
private:
    std::vector<Customer*> customers;
    const std::string filename = "customers.dat";

    Customer* findCustomerById(int id) {
        auto it = std::find_if(customers.begin(), customers.end(), [id](Customer* customer) {
            return customer->getId() == id;
        });
        return (it != customers.end()) ? *it : nullptr;
    }

    Customer* findCustomerByPhone(const std::string& phone) {
        auto it = std::find_if(customers.begin(), customers.end(), [&phone](Customer* customer) {
            return customer->getPhone() == phone;
        });
        return (it != customers.end()) ? *it : nullptr;
    }

    // Function to save all customers to a file
    void saveAllCustomers() {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs) {
            DataValidInput::SetColor(12);
            std::cerr << "Error opening file for saving!" << std::endl;
            return;
        }
        for (const auto& customer : customers) {
            customer->saveToFile(ofs);
        }
    }

    // Function to load all customers from a file
    void loadAllCustomers() {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs) {
            return;
        }
        while (ifs.peek() != EOF) {
            std::string type;
            std::getline(ifs, type);
            Customer* customer = nullptr;
            if (type == "OldCustomer") {
                customer = new OldCustomer();
            } else if (type == "NewCustomer") {
                customer = new NewCustomer();
            }
            if (customer) {
                customer->loadFromFile(ifs);
                customers.push_back(customer);
            }
        }
    }

public:
    // Constructor to load customers from file on creation
    CustomerManager() {
        loadAllCustomers();
    }

    // Destructor to save customers to file and clean up memory
    ~CustomerManager() {
        saveAllCustomers();
        for (auto customer : customers) {
            delete customer;
        }
    }

    void addCustomer(const std::string& name, int id, const std::string& phone, const std::string& address, int type) override {
        if (type == 1) {
            double price = DataValidInput::getDoubleInput("Enter the total amount for the old customer: ");
            customers.push_back(new OldCustomer(name, id, phone, address, price));
        } else if (type == 2) {
            double price = DataValidInput::getDoubleInput("Enter the total amount for the new customer: ");
            customers.push_back(new NewCustomer(name, id, phone, address, price));
        } else {
            DataValidInput::SetColor(12);
            throw std::invalid_argument("Invalid customer type.");
        }
        saveAllCustomers();
        std::cout << "Customer added successfully.\n";
    }

    void editCustomer(int id) override {
        Customer* customer = findCustomerById(id);
        if (customer == nullptr) {
            DataValidInput::SetColor(12);
            throw std::invalid_argument("Customer not found");
        }

        std::string newName = DataValidInput::getStringInput("Enter new customer name: ");
        std::string newPhone = DataValidInput::getStringInput("Enter new customer phone number: ");
        std::string newAddress = DataValidInput::getStringInput("Enter new customer address: ");

        customer->setName(newName);
        customer->setPhone(newPhone);
        customer->setAddress(newAddress);
        saveAllCustomers();
        std::cout << "Customer updated successfully.\n";
    }

    void deleteCustomer(int id) override {
        auto it = std::find_if(customers.begin(), customers.end(), [id](Customer* customer) {
            return customer->getId() == id;
        });

        if (it != customers.end()) {
            char choice;
            do {
                std::cout << "Do you want to delete? (Y/N): ";
                std::cin >> choice;
                choice = toupper(choice);
                if (choice == 'Y') {
                    delete *it;
                    customers.erase(it);
                    saveAllCustomers();
                    std::cout << "Customer deleted successfully.\n";
                } else if (choice == 'N') {
                    std::cout << "Deletion canceled.\n";
                } else {
                    DataValidInput::SetColor(12);
                    std::cout << "Invalid input. Please enter 'Y' or 'N'.\n";
                }
            } while (choice != 'Y' && choice != 'N');
        } else {
            DataValidInput::SetColor(12);
            throw std::invalid_argument("Customer not found");
        }
    }

    void viewCustomers() override {
        if (customers.empty()) {
            DataValidInput::SetColor(12);
            throw std::invalid_argument("No customer available");
        }
        Customer::displayHeader();
        for (const auto& customer : customers) {
            customer->display();
            loadAllCustomers();
        }

        // Adding "press any key to continue" functionality
        std::cout << "\nPress any key to continue...";
        std::cin.get();  // Waits for user to press any key
    }

    void searchCustomerByPhone(const std::string& phone) override {
        Customer* customer = findCustomerByPhone(phone);
        if (customer == nullptr) {
            DataValidInput::SetColor(12);
            throw std::invalid_argument("Customer not found");
        } else {
            Customer::displayHeader();
            customer->display();
        }
        // Adding "press any key to continue" functionality
        std::cout << "\nPress any key to continue...";
        std::cin.get();  // Waits for user to press any key
    }
};
