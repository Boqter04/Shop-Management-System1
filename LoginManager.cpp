#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "CustomerApplication.cpp"
#include "ProductApplication.cpp"
#include "CustomerManager.cpp"
#include "ProductManager.cpp"
#include "DataValidInput.cpp"
#include "User.cpp"
#include <cstdlib> 

using namespace std;

class LoginManager {
    CustomerManager customermanager;
    ProductManager productmanager;

private:
    vector<User> users;
    string usersFile = "users.dat";

public:
    LoginManager() {
        loadUsers();
    }
     
    void loadUsers() {
        ifstream file(usersFile, ios::binary);
        if (file.is_open()) {
            User user;
            while (file.read((char*)&user, sizeof(User))) {
                users.push_back(user);
            }
            file.close();
        }  
    }

    void saveUsers() {
        ofstream file(usersFile, ios::binary | ios::trunc);
        if (file.is_open()) {
            for (const auto& user : users) {
                file.write((char*)&user, sizeof(User));
            }
            file.close();
        } else {
            DataValidInput::SetColor(12);
            cerr << "Could not open file " << usersFile << " for writing." << endl;
        }
    }

    void addUser() {
        string username, password, role;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter role (admin/user): ";
        cin >> role;

        users.push_back(User(username, password, role));
        saveUsers();
        cout << "User added successfully!" << endl;
    }

    bool authenticate(const string& username, const string& password, User& authenticatedUser) {
        for (const auto& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                authenticatedUser = user;
                return true;
            }
        }
        return false;
    }

    void login() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        User authenticatedUser;
        if (authenticate(username, password, authenticatedUser)) {
            cout << "Login successful! Role: " << authenticatedUser.getRole() << endl;
            if (authenticatedUser.getRole() == "admin") {
                 system("cls");
                adminMenu();
            } else {
                system("cls");
                userMenu();
            }
        } else {
            DataValidInput::SetColor(12);
            cout << "Invalid username or password." << endl;
        }
    }

    void regis() {
        string username, password, role;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter role (admin/user): ";
        cin >> role;

        users.push_back(User(username, password, role));
        saveUsers();
        cout << "User added successfully!" << endl;
    }

    void adminMenu() {
        enum MainMenu {EXIT, CUSTOMER, PRODUCT};
        int choice;
        cout.setf(ios::fixed | ios::showpoint);
        cout << setprecision(2);

        do {
            system("cls");
            DataValidInput::SetColor(11);
            cout << "\t||- **************** -||\n";
            cout << "\t       Admin Menu\n";
            cout << "\t||- **************** -||\n";
            cout << "\n1. Customer Management\n";
            cout << "2. Product Management\n";
            cout << "3. Logout\n";
            choice = DataValidInput::getIntInput("Enter your choice: ");
            switch (choice) {
                case CUSTOMER: {
                    CustomerApplication customerApp;
                    customerApp.run();
                    break;
                }
                case PRODUCT:
                    ProductApplication productApp;
                    productApp.run();
                    break;
                case EXIT:
                    menu();
                    break;
                default:
                    cout << "Invalid input" << endl;
                    cout << "\a";
            }
        } while (choice != EXIT);
    }

    void userMenu() {
        int choice;
        do {
            DataValidInput::SetColor(15);
            cout << "\t||- *************** -||\n";
            cout << "\t       User Menu\n";
            cout << "\t||- *************** -||\n";
            cout << "\n1. View Customer\n";
            cout << "2. View Product\n";
            cout << "3. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    customermanager.viewCustomers();
                    system("cls");
                    break;
                case 2:
                    productmanager.viewProducts();
                    system("cls");
                    break;
                case 3:
                    menu();
                    break;
                default:
                    DataValidInput::SetColor(12);
                    cout << "Invalid choice, please try again." << endl;
            }
        } while (choice != 2);
    }

    void viewUsers() {
        cout << "\nRegistered Users:\n";
        for (const auto& user : users) {
            cout << "Username: " << user.getUsername() << ", Role: " << user.getRole() << endl;
        }
    }

    void menu() {
        int choice;
        do {
            DataValidInput::SetColor(2);
            cout << "\n\t||- *************** -||\n";
            cout << "\t       Main Menu\n";
            cout << "\t||- *************** -||\n";
            cout << "\n1. Login\n";
            cout << "2. Register\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    login();  
                    break;
                case 2:
                    regis();
                    break;
                case 0:
                    cout << "Exiting program." << endl;
                    break;
                default:
                    DataValidInput::SetColor(12);
                    cout << "Invalid choice, please try again." << endl;
            }
        } while (choice != 0);
    }
};