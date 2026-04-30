#include "Header2.h"


vector<User> readUsers(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        throw FileNotFoundException(filename);
    }

    vector<User> users;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue; 

        stringstream ss(line);
        string id_str, name, email;

        getline(ss, id_str, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');

        if (id_str == "id" || id_str == "ID") continue;

        User u;
        u.id = stoi(id_str); 
        u.name = name;
        u.email = email;

        users.push_back(u); 
    }

    file.close();
    return users;
}

void saveUsersToJson(const vector<User>& users, const string& out_filename) {
    json j_array = json::array(); // Створюємо порожній масив JSON

    
    for (int i = 0; i < users.size(); i++) {
        json j_user; 
        j_user["id"] = users[i].id;
        j_user["name"] = users[i].name;
        j_user["email"] = users[i].email;

        j_array.push_back(j_user); 
    }

    ofstream file(out_filename);
    if (file.is_open()) {
        file << j_array.dump(4);
        file.close();
    }
    else {
        cout << "Error: Cannot open file for writing." << endl;
    }
}