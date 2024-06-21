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

class CustomerRepository {
public:
    virtual void addCustomer(int address, const std::string& name, const std::string& phone, int type) = 0;
    virtual void editCustomer(int address) = 0;
    virtual void deleteCustomer(int address) = 0;
    virtual void viewCustomers() = 0;
    virtual void searchCustomerByPhone(const std::string& phone) = 0;
    virtual ~CustomerRepository() = default;
};