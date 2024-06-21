#pragma once
#include "Customer.cpp"

class NewCustomer : public Customer {
private:
    double price;

public:
    NewCustomer() : Customer("", 0, ""), price(0) {}

    NewCustomer(const std::string& name, int address, const std::string& phone, double price)
        : Customer(name, address, phone), price(price) {
            applyDiscount(10); // Applying a 10% discount to the price
        }

    // Method to apply a discount to the price
    void applyDiscount(double discountPercentage) {
        price -= price * (discountPercentage / 100.0);
    }

    double getPrice() const {
        return price;
    }

    std::string getType() const override {
        return "NewCustomer";
    }

    void display() const override {
        Customer::display();  
         std::cout << std::right << std::setw(20)
                  << std::setw(0) << price << "$" << " Discount 10%" << std::endl;
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
