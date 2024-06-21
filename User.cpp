#pragma once
#include <iostream>

using namespace std;

class User {
    private:
    string username;
    string password;
    string role; // e.g., "admin", "user"
    public:
    User() {}
    User(string u, string p, string r) : username(u), password(p), role(r) {}
    
    //setters and getters method
    string getUsername() const{
        return username;
    }
    string getPassword() const{
        return password; 
    }
    string getRole() const{
        return role;
    }
    void setUsername(string user){
        username=user;
    }
    void setPassword(string pass){
        password=pass;
    }
    void setRole(string r){
        role=r;
    }
};