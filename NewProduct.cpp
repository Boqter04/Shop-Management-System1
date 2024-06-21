#pragma once
#include "Product.cpp"

class NewProduct : public Product {
private:
    double discount;

public:
    NewProduct(int sku, const std::string& name, const std::string& model, int year, double discount)
        : Product(sku, name, model, year), discount(discount) {}

    NewProduct() : Product(0,"", "", 0), discount(0) {}

    double getdiscount() const {
        return discount;
    }

      void setDiscount(double discount){
        this->discount = discount;
      }

    std::string getType() const override {
        return "NewProduct";
    }

    void display() const override {
        Product::display();  
         std::cout << std::right << std::setw(20)
                  << std::setw(0) << discount << "%" << std::endl;
    }

    void saveToFile(std::ofstream& ofs) const override {
        Product::saveToFile(ofs);
        ofs << "Discount: " << discount << "%" << "\n";
    }

    void loadFromFile(std::ifstream& ifs) override {
        Product::loadFromFile(ifs);
        ifs >> discount;
        ifs.ignore();
    }
};