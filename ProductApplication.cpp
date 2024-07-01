#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "OldProduct.cpp"
#include "NewProduct.cpp"
#include "ProductManager.cpp"
#include "DataValidInput.cpp"

// Class to run the customer management application
class ProductApplication {
private:
    // Display the menu for customer management
    void displayMenu() {
        DataValidInput::SetColor(10);
        std::cout << "\n\t||- ************************** -||\n";
        std::cout << "\t       Product Manager Menu\n";
        std::cout << "\t||- ************************** -||\n";
        std::cout << "\n1. Add Product\n";
        std::cout << "2. Edit Product\n";
        std::cout << "3. Delete Product\n";
        std::cout << "4. View Product\n";
        std::cout << "5. Search Product\n";
        std::cout << "6. Back to Main Menu\n";
        std::cout << std::endl;
    }
public:
    enum MenuChoice {
        ADD_PRODUCT = 1,
        EDIT_PRODUCT,
        DELETE_PRODUCT,
        VIEW_PRODUCTS,
        SEARCH_PRODUCT,
        EXIT
    };
    
    // Run the Product management application
    void run() {
        ProductManager manager;
        int choice;

        bool done = false;
        while (!done) {
            displayMenu();
            choice = DataValidInput::getIntInput("Enter your choice: ");
            try {
                switch (choice) {
                    case ADD_PRODUCT: {
                        std::string name, model;
                        int year, sku;
                        int type;

                        sku = DataValidInput::getIntInput("Enter product SKU: ");
                        name = DataValidInput::getStringInput("Enter product name: ");                      
                        model = DataValidInput::getStringInput("Enter product model: ");
                        year = DataValidInput::getIntInput("Enter product year: "); 
                        DataValidInput::validateSku(sku);
                        type = DataValidInput::getIntInput("Enter 1 for Old Product, 2 for New Product: ");
                        manager.addProduct(sku, name, model, year, type);
                        break;
                    }
                    case EDIT_PRODUCT: {
                        int sku;
                        sku = DataValidInput::getIntInput("Enter product SKU: ");
                        DataValidInput::validateSku(sku);

                        manager.editProduct(sku);
                        break;
                    }
                    case DELETE_PRODUCT: {
                        int sku;
                        sku = DataValidInput::getIntInput("Enter Product SKU: ");
                        DataValidInput::validateSku(sku);
                        manager.deleteProduct(sku);
                        break;
                    }
                    case VIEW_PRODUCTS:
                        DataValidInput::SetColor(3);
                        manager.viewProducts();
                        break;
                    case SEARCH_PRODUCT: {
                        std::string name;
                        name = DataValidInput::getStringInput("Enter Product name: ");
                        manager.searchProductByName(name);
                        break;
                    }
                    case EXIT:
                        done = true;
                        break;
                    default:
                    DataValidInput::SetColor(12);
                        std::cout << "Invalid choice. Please try again.\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    }
};