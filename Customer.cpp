#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <fstream>

// Base class representing a customer
class Customer {
protected:
    std::string name;
    int id; // Customer's id (represented as an integer)
    std::string phone;
    std::string address;

public:
    Customer(){}

    Customer(const std::string& name, int id, const std::string& phone, const std::string& address)
        : name(name), id(id), phone(phone), address(address) {}

     // Virtual destructor
    virtual ~Customer() {}

    // Pure virtual function to get the type of customer
    virtual std::string getType() const = 0;

    // Getter functions
    int getId(){
        return id;
    }
    std::string getName(){
        return name;
    }
    std::string getPhone(){
        return phone;
    }
    std::string getAddress(){
        return address;
    }

   // Setter functions
    void setId(int id){
        this->id = id;
    }
    void setName(std::string name){
        this->name = name;
    }
    void setPhone(std::string phone){
        this->phone = phone;
    }
    void setAddress(std::string address){
        this->address = address;
    }

    // Static function to display the header for customer information
    static void displayHeader() {
        std::cout << "\n";
        std::cout << std::left << std::setw(20) << "Type"
                  << std::setw(15) << "Name"
                  << std::setw(15) << "Id"
                  << std::setw(15) << "Phone" 
                  << std::setw(15) << "Address" 
                  << std::setw(15) << "Total" << std::endl;
        std::cout << std::string(90, '-') << std::endl;
    }

    // Virtual function to display customer information
    virtual void display() const {
        std::cout << std::left << std::setw(20) << getType()
                  << std::setw(15) << name
                  << std::setw(15) << id
                  << std::setw(15) << phone
                  << std::setw(15) << address;
    }
    
      // Virtual function to save customer information to a file
    virtual void saveToFile(std::ofstream& ofs) const {
        size_t nameSize = name.size();
        ofs.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        ofs.write(name.c_str(), nameSize);
        ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
        size_t phoneSize = phone.size();
        ofs.write(reinterpret_cast<const char*>(&phoneSize), sizeof(phoneSize));
        ofs.write(phone.c_str(), phoneSize);
        size_t addressSize = address.size();
        ofs.write(reinterpret_cast<const char*>(&addressSize), sizeof(addressSize));
        ofs.write(address.c_str(), addressSize);
    }

    // Virtual function to load customer information from a file
    virtual void loadFromFile(std::ifstream& ifs) {
        size_t nameSize;
        ifs.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        name.resize(nameSize);
        ifs.read(&name[0], nameSize);

        ifs.read(reinterpret_cast<char*>(&id), sizeof(id));

        size_t phoneSize;
        ifs.read(reinterpret_cast<char*>(&phoneSize), sizeof(phoneSize));
        phone.resize(phoneSize);
        ifs.read(&phone[0], phoneSize);

        size_t addressSize;
        ifs.read(reinterpret_cast<char*>(&addressSize), sizeof(addressSize));
        address.resize(addressSize);
        ifs.read(&address[0], addressSize);
    }
};