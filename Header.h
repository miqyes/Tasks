#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <exception>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class FileNotFoundException : public exception {
    string msg;
public:
    FileNotFoundException(const string& file) : msg("File not found: " + file) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class RowFormatException : public exception {
    string msg;
public:
    RowFormatException(const string& row) : msg("Invalid row format: " + row) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

// Ôóíêö³¿
set<string> getUniqueAuthors(const string& filename);
void saveAuthorsToJson(const set<string>& authors, const string& out_filename);