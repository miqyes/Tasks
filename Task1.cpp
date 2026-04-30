#include "Header.h"

int main() {
    
    try {
        cout << "Reading books.csv " << endl;

        set<string> authors = getUniqueAuthors("books.csv");

        saveAuthorsToJson(authors, "authors.json");
        cout << "Success! Unique authors saved to authors.json" << endl;

    }
    catch (const FileNotFoundException& e) {
        cerr << "CRITICAL ERROR: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "GENERAL ERROR: " << e.what() << endl;
    }

    return 0;
}