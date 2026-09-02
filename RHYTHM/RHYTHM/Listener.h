#pragma once
#include <string>
#include <vector>

class Listener {
public:
    Listener();
    bool login(const std::string& username, const std::string& password);

private:
    bool loadCredentials();
    // A vector of pairs, where first = username, second = password
    std::vector<std::pair<std::string, std::string>> credentials;
};
