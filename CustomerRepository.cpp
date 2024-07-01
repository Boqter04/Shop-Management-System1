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
    virtual void addCustomer(const std::string& name, int id, const std::string& phone, const std::string& address, int type) = 0;
    virtual void editCustomer(int id) = 0;
    virtual void deleteCustomer(int id) = 0;
    virtual void viewCustomers() = 0;
    virtual void searchCustomerByPhone(const std::string& phone) = 0;
    virtual ~CustomerRepository() = default;
};