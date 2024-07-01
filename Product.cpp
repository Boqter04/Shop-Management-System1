#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <fstream>

// Base class representing a customer
class Product {
protected:
    int sku; //A unique identifier for the product.
    std::string name;
    std::string model;
    int year;

public:
    Product(){}
    
    Product(int sku, const std::string& name, const std::string& model, int year )
        : sku(sku), name(name), model(model), year(year) {}

    virtual ~Product() {}

    virtual std::string getType() const = 0;

    // Getter functions
    int getSku(){
        return sku;
    }
    int getYear(){
        return year;
    }
    std::string getName(){
        return name;
    }
    std::string getModel(){
        return model;
    }

   // Setter functions
    void setSku(int sku){
        this->sku = sku;
    }
    void setYear(int year){
        this->year = year;
    }
    void setName(std::string name){
        this->name = name;
    }
    void setModel(std::string model){
        this->model = model;
    }

    static void displayHeader() {
        std::cout << "\n";
        std::cout << std::left << std::setw(20) << "Type"
                  << std::setw(15) << "SKU"
                  << std::setw(15) << "NAME"
                  << std::setw(15) << "MODEL"
                  << std::setw(15) << "YEAR" 
                  << std::setw(15) << "DISCOUNT" << std::endl;
        std::cout << std::string(90, '-') << std::endl;
    }

    //virtual void display() const = 0;
    virtual void display() const {
        std::cout << std::left << std::setw(20) << getType()
                  << std::setw(15) << sku
                  << std::setw(15) << name
                  << std::setw(15) << model
                  << std::setw(15) << year;
    }
    
    virtual void saveToFile(std::ofstream& ofs) const {
        ofs << getType() << ": ";
        ofs << "SKU: " << sku << ", ";
        ofs << "NAME: " << name << ", ";
        ofs << "MODEL: " << model << ", ";
        ofs << "YEAR: " << year << ", ";
    }

    virtual void loadFromFile(std::ifstream& ifs) {
        ifs >> sku;
        ifs.ignore();
        std::getline(ifs, name);
        std::getline(ifs, model);
        ifs >> year;
        ifs.ignore();
    }
};