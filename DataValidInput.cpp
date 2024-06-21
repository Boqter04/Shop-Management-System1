

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "OldCustomer.cpp"
#include "NewCustomer.cpp"
#include "Customer.cpp"
#include <windows.h>

// Utility class for data validation and input
class DataValidInput {
public:
    // Validate the address to ensure it's positive
    static void validateAddress(int address) {
        if (address <= 0) {
            throw std::invalid_argument("Address must be a positive integer.");
        }
    }
    // Validate the sku to ensure it's positive
    static void validateSku(int sku) {
        if (sku <= 0) {
            throw std::invalid_argument("SKU must be a positive integer.");
        }
    }

    // Get a string input from the user
    static std::string getStringInput(const std::string& prompt) {
        std::string input;
        std::cout << prompt;
        std::getline(std::cin, input);
        return input;
    }
    
    // Get an integer input from the user
    static int getIntInput(const std::string& prompt) {
        int input;
        std::cout << prompt;
        while (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }

    // Get an Double input from the user
    static double getDoubleInput(const std::string& prompt) {
        double input;
        std::cout << prompt;
        while (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }

    //Set Color
    static void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    }
};