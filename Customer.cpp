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
    int address;
    std::string phone;

public:
    Customer(){}

    Customer(const std::string& name, int address, const std::string& phone)
        : name(name), address(address), phone(phone) {}

    virtual ~Customer() {}

    virtual std::string getType() const = 0;

    // Getter functions
    int getAddress(){
        return address;
    }
    std::string getName(){
        return name;
    }
    std::string getPhone(){
        return phone;
    }

   // Setter functions
    void setAddress(int address){
        this->address = address;
    }
    void setName(std::string name){
        this->name = name;
    }
    void setPhone(std::string phone){
        this->phone = phone;
    }

    static void displayHeader() {
        std::cout << std::left << std::setw(20) << "Type"
                  << std::setw(15) << "Name"
                  << std::setw(15) << "Address"
                  << std::setw(15) << "Phone" 
                  << std::setw(15) << "Total" << std::endl;
        std::cout << std::string(75, '-') << std::endl;
    }

    virtual void display() const {
        std::cout << std::left << std::setw(20) << getType()
                  << std::setw(15) << name
                  << std::setw(15) << address
                  << std::setw(15) << phone ;
    }
    
    virtual void saveToFile(std::ofstream& ofs) const {
        size_t nameSize = name.size();
        ofs.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        ofs.write(name.c_str(), nameSize);
        ofs.write(reinterpret_cast<const char*>(&address), sizeof(address));
        size_t phoneSize = phone.size();
        ofs.write(reinterpret_cast<const char*>(&phoneSize), sizeof(phoneSize));
        ofs.write(phone.c_str(), phoneSize);
    }

    virtual void loadFromFile(std::ifstream& ifs) {
        size_t nameSize;
        ifs.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        name.resize(nameSize);
        ifs.read(&name[0], nameSize);

        ifs.read(reinterpret_cast<char*>(&address), sizeof(address));

        size_t phoneSize;
        ifs.read(reinterpret_cast<char*>(&phoneSize), sizeof(phoneSize));
        phone.resize(phoneSize);
        ifs.read(&phone[0], phoneSize);
    }

};