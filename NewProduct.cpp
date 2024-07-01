#pragma once
#include "Product.cpp"

class NewProduct : public Product {
private:
    double discount; // Discount percentage for the new product

public:
    NewProduct(int sku, const std::string& name, const std::string& model, int year, double discount)
        : Product(sku, name, model, year), discount(discount) {}

    NewProduct() : Product(0,"", "", 0), discount(0) {}

    // Getter function for discount
    double getdiscount() const {
        return discount;
    }

    // Setter function for discount
      void setDiscount(double discount){
        this->discount = discount;
      }

    // Override the getType function to return the type of product
    std::string getType() const override {
        return "NewProduct";
    }

    // Override the display function to include discount information
    void display() const override {
        Product::display();  
         std::cout << std::right << std::setw(20)
                  << std::setw(0) << discount << "%" << std::endl;
    }

    // Override the saveToFile function to include discount information
    void saveToFile(std::ofstream& ofs) const override {
        Product::saveToFile(ofs); // Call the base class saveToFile function
        ofs << "Discount: " << discount << "%" << "\n";
    }

    // Override the loadFromFile function to load discount information
    void loadFromFile(std::ifstream& ifs) override {
        Product::loadFromFile(ifs); // Call the base class loadFromFile function
        ifs >> discount;
        ifs.ignore();
    }
};
