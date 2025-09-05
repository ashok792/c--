#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string name;
    int age;

    cout << "Enter your name: ";
    getline(cin, name);  // read full name with spaces

    cout << "Enter your age: ";
    cin >> age;

    // Open file to write
    ofstream file("student.txt");
    if (file.is_open()) {
        file << "Name: " << name << endl;
        file << "Age: " << age << endl;
        file.close();
        cout << "Data saved successfully in student.txt" << endl;
    } else {
        cout << "Error opening file!" << endl;
    }

    return 0;
}
