#include "Header.h"

set<string> getUniqueAuthors(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        throw FileNotFoundException(filename);
    }

    set<string> unique_authors;
    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;
        if (line.empty()) continue;

        try {
            stringstream ss(line);
            string title, author, year, isbn;

            if (getline(ss, title, ',') &&
                getline(ss, author, ',') &&
                getline(ss, year, ',') &&
                getline(ss, isbn, ',')) {

                if (author != "author" && author != "Author") {
                    unique_authors.insert(author);
                }
            }
            else {
                // Якщо колонок менше
                throw RowFormatException(line);
            }
        }
        catch (const RowFormatException& e) {
            cerr << "Warning at line " << lineNumber << " -> " << e.what() << endl;
        }
    }

    file.close();
    return unique_authors;
}

void saveAuthorsToJson(const set<string>& authors, const string& out_filename) {
    json j_array = json::array();

    for (set<string>::const_iterator it = authors.begin(); it != authors.end(); ++it) {
        j_array.push_back(*it);
    }

    ofstream file(out_filename);
    if (file.is_open()) {
        file << j_array.dump(4);
        file.close();
    }
    else {
        cerr << "Error: Could not open file for writing!" << endl;
    }
}