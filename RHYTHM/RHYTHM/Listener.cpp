#include "Listener.h"
#include <fstream>
#include <iostream>

Listener::Listener() {
    // Constructor can remain empty
}

bool Listener::loadCredentials() {
    credentials.clear(); // Clear any previous data
    std::ifstream inFile("jammer.dat");
    if (!inFile) {
        std::cerr << "Error: Could not open jammer.dat\n";
        return false;
    }

    std::string user, pass;
    while (inFile >> user >> pass) {
        // For each line, store username and password
        credentials.emplace_back(user, pass);
    }

    return !credentials.empty();
}

bool Listener::login(const std::string& username, const std::string& password) {
    if (!loadCredentials()) {
        return false; // If no credentials loaded, no login possible
    }

    // Check all stored credentials
    for (const auto& cred : credentials) {
        if (cred.first == username && cred.second == password) {
            return true; // Found a match
        }
    }

    return false; // No matching username/password found
}
