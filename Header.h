#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <exception>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class FileNotFoundException : public exception {
    string msg;
public:
    FileNotFoundException(const string& file) {
        msg = "File not found: " + file;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

struct User {
    int id;
    string name;
    string email;
};

vector<User> readUsers(const string& filename);
void saveUsersToJson(const vector<User>& users, const string& out_filename);