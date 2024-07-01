#pragma once
#include "Product.cpp"

class OldProduct : public Product {
private:
    double discount; // Discount percentage for the old product

public:
    OldProduct(int sku, const std::string& name, const std::string& model, int year, double discount)
        : Product(sku, name, model, year), discount(discount) {}

    OldProduct() : Product(0, "", "", 0), discount(0) {}

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
        return "OldProduct";
    }

    // Override the display function
    void display() const override {
        Product::display();  
         std::cout << std::right << std::setw(20)
                  << std::setw(0) << discount << "%" << std::endl;
    }

    // Override the saveToFile to include discount information
    void saveToFile(std::ofstream& ofs) const override {
        Product::saveToFile(ofs); // Call the base class saveToFile function
        ofs <<"Discount: " << discount << "%" << "\n";
    }

    // Override the loadFromFile to load discount information
    void loadFromFile(std::ifstream& ifs) override {
        Product::loadFromFile(ifs); // Call the base class loadFromFile function
        ifs >> discount;
        ifs.ignore();
    }
};
