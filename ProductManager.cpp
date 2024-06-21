#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <fstream>
#include "OldProduct.cpp"
#include "NewProduct.cpp"
#include "Product.cpp"
#include "DataValidInput.cpp"
#include "ProductRepository.cpp"

// Class managing customer
class ProductManager : public ProductRepository {
private:
    std::vector<Product*> products;
    const std::string filename = "products.txt";

    Product* findProductBySku(int sku) {
        auto it = std::find_if(products.begin(), products.end(), [sku](Product* product) {
            return product->getSku() == sku;
        });
        return (it != products.end()) ? *it : nullptr;
    }

    Product* findProductByname(const std::string& name) {
        auto it = std::find_if(products.begin(), products.end(), [&name](Product* product) {
            return product->getName() == name;
        });
        return (it != products.end()) ? *it : nullptr;
    }

    // Function to save all customers to a file
    void saveAllProducts() {
        std::ofstream ofs(filename);
        if (!ofs) {
            DataValidInput::SetColor(12);
            std::cerr << "Error opening file for saving!" << std::endl;
            return;
        }
        for (const auto& product : products) {
            product->saveToFile(ofs);
        }
    }

    // Function to load all customers from a file
    void loadAllProducts() {
        std::ifstream ifs(filename);
        if (!ifs) {
            return;
        }
        while (ifs.peek() != EOF) {
            std::string type;
            std::getline(ifs, type);
            Product* product = nullptr;
            if (type == "OldProduct") {
                product = new OldProduct();
            } else if (type == "NewProduct") {
                product = new NewProduct();
            }
            if (product) {
                product->loadFromFile(ifs);
                products.push_back(product);
            }
        }
    }

public:
    // Constructor to load customers from file on creation
    ProductManager() {
        loadAllProducts();
    }

    // Destructor to save customers to file and clean up memory
    ~ProductManager() {
        saveAllProducts();
        for (auto product : products) {
            delete product;
        }
    }

    void addProduct(int sku, const std::string& name, const std::string& model, int year, int type) override {
        if (type == 1) {
            double price = DataValidInput::getDoubleInput("Enter Flash sale: [X]% off on [Product]: ");
            products.push_back(new OldProduct(sku, name, model, year, price));
        } else if (type == 2) {
            double price = DataValidInput::getDoubleInput("Enter Flash sale: [X]% off on [Product]: ");
            products.push_back(new NewProduct(sku, name, model, year, price));
        } else {
            DataValidInput::SetColor(12);
            throw std::invalid_argument("Invalid customer type.");
        }
        saveAllProducts();
        std::cout << "Product added successfully.\n";
    }

    void editProduct(int sku) override {
        Product* product = findProductBySku(sku);
        if (product == nullptr) {
            throw std::invalid_argument("Product not found");
        }

        std::string newName = DataValidInput::getStringInput("Enter new product name: ");
        std::string newModel = DataValidInput::getStringInput("Enter new product model: ");
        int newYear = DataValidInput::getIntInput("Enter new product year: ");
        product->setName(newName);
        product->setModel(newModel);
        product->setYear(newYear);
        saveAllProducts();
        std::cout << "Product updated successfully.\n";
    }

    void deleteProduct(int sku) override {
        auto it = std::find_if(products.begin(), products.end(), [sku](Product* product) {
            return product->getSku() == sku;
        });

        if (it != products.end()) {
            char choice;
            do {
                std::cout << "Do you want to delete? (Y/N): ";
                std::cin >> choice;
                choice = toupper(choice);
                if (choice == 'Y') {
                    delete *it;
                    products.erase(it);
                    saveAllProducts();
                    std::cout << "Product deleted successfully.\n";
                } else if (choice == 'N') {
                    std::cout << "Deletion canceled.\n";
                } else {
                    DataValidInput::SetColor(12);
                    std::cout << "Invalid input. Please enter 'Y' or 'N'.\n";
                }
            } while (choice != 'Y' && choice != 'N');
        } else {
            DataValidInput::SetColor(12);
            throw std::invalid_argument("Product not found");
        }
    }

    void viewProducts() override {
        if (products.empty()) {
            DataValidInput::SetColor(12);
            throw std::invalid_argument("No product available");
        }
        Product::displayHeader();
        for (const auto& product : products) {
            product->display();
        }
    }

    void searchProductByName(const std::string& phone) override {
        Product* product = findProductByname(phone);
        if (product == nullptr) {
            DataValidInput::SetColor(12);
            throw std::invalid_argument("Product not found");
        } else {
            Product::displayHeader();
            product->display();
        }
    }
};
