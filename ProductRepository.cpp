#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "NewCustomer.cpp"
#include "OldCustomer.cpp"
#include "Customer.cpp"
#include "DataValidInput.cpp"

class ProductRepository {
public:
    virtual void addProduct(int sku, const std::string& name, const std::string& model, int year, int type) = 0;
    virtual void editProduct(int address) = 0;
    virtual void deleteProduct(int address) = 0;
    virtual void viewProducts() = 0;
    virtual void searchProductByName(const std::string& name) = 0;
    virtual ~ProductRepository() = default;
};