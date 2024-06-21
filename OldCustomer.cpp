#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "Customer.cpp"

// Derived class  
class OldCustomer : public Customer {
private:
    double price;

public:
    OldCustomer() : Customer("", 0, ""), price(0) {}

    OldCustomer(const std::string& name, int address, const std::string& phone, double price)
        : Customer(name, address, phone), price(price) {
             applyDiscount(40); // Applying a 40% discount to the price
        }

    // Method to apply a discount to the price
    void applyDiscount(double discountPercentage) {
        price -= price * (discountPercentage / 100.0);
    }

    double getPrice() const {
        return price;
    }

    std::string getType() const override {
        return "OldCustomer";
    }

    void display() const override {
        Customer::display(); 
        std::cout << std::right << std::setw(20)
                  << std::setw(0) << price << "$" << " Discount 40%" << std::endl;
    }

    virtual void saveToFile(std::ofstream& ofs) const override {
        Customer::saveToFile(ofs);
        ofs.write(reinterpret_cast<const char*>(&price), sizeof(price));
    }

    virtual void loadFromFile(std::ifstream& ifs) override {
        Customer::loadFromFile(ifs);
        ifs.read(reinterpret_cast<char*>(&price), sizeof(price));
    }
};
