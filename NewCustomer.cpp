#pragma once
#include "Customer.cpp"

class NewCustomer : public Customer {
private:
    double price;

public:
    NewCustomer() : Customer("", 0, "", ""), price(0) {}

    NewCustomer(const std::string& name, int id, const std::string& phone, const std::string& address, double price)
        : Customer(name, id, phone, address), price(price) {
             applyDiscount(40); // Applying a 40% discount to the price
        }

    // Method to apply a discount to the price
    void applyDiscount(double discountPercentage) {
        price -= price * (discountPercentage / 100.0);
    }

    // Getter function for price
    double getPrice() const {
        return price;
    }
    
    // Override the getType function to return the type of customer
    std::string getType() const override {
        return "NewCustomer";
    }

    // Override the display function to include price and discount information
    void display() const override {
        Customer::display();  // Call the base class display function
         std::cout << std::right << std::setw(20)
                  << std::setw(0) << price << "$" << " Discount 10%" << std::endl;
    }

    // Override the saveToFile function to include price information
    virtual void saveToFile(std::ofstream& ofs) const override {
        Customer::saveToFile(ofs); // Call the base class saveToFile function
        ofs.write(reinterpret_cast<const char*>(&price), sizeof(price));
    }

    // Override the loadFromFile function to load price information
    virtual void loadFromFile(std::ifstream& ifs) override {
        Customer::loadFromFile(ifs); // Call the base class loadFromFile function
        ifs.read(reinterpret_cast<char*>(&price), sizeof(price));
    }
};
