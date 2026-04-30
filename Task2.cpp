#include "Header.h"

int main() {
    try {
        cout << " Processing CSV File " << endl;

        vector<User> users = readUsers("users.csv");
        saveUsersToJson(users, "users_report.json");

        cout << "Done! Saved to users_report.json" << endl;
    }
    catch (const FileNotFoundException& e) {
        cout << "CRITICAL ERROR: " << e.what() << endl;
    }

    return 0;
}