#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int MAX_EMPLOYEES = 500;

struct Employee {
    int age;
    string gender;
    string educationLevel;
    string jobTitle;
    int yearsOfExperience;
    double salary;
};

struct Node {
    Employee employee;
    Node* next;
};

class HashTable {
private:
    static const int TABLE_SIZE = 100;
    Node* table[TABLE_SIZE];

    int hashFunction(const string& key) {
    int sum = 0;
    for (size_t i = 0; i < key.length(); i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}


public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = NULL;
        }
    }

    void insert(const Employee& employee) {
        int index = hashFunction(employee.jobTitle);
        Node* newNode = new Node;
        newNode->employee = employee;
        newNode->next = NULL;

        if (table[index] == NULL) {
            table[index] = newNode;
        } else {
            Node* current = table[index];
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* current = table[i];
            while (current != NULL) {
                cout << "Job Title: " << current->employee.jobTitle << endl;
                cout << "Employee Age: " << current->employee.age << endl;
                cout << "Employee Gender: " << current->employee.gender << endl;
                cout << "Education Level: " << current->employee.educationLevel << endl;
                cout << "Years of Experience: " << current->employee.yearsOfExperience << endl;
                cout << "Salary: " << current->employee.salary << endl;
                cout << endl;
                current = current->next;
            }
        }
    }
};

int main() {
    Employee employees[MAX_EMPLOYEES];

    // Read employee data from CSV file
    ifstream file("employee.csv");
    if (!file) {
        cout << "Failed to open file." << endl;
        return 1;
    }

    string line;
    int index = 0;
    while (getline(file, line) && index < MAX_EMPLOYEES) {
        stringstream ss(line);
        string cell;

        // Read each column of the CSV line into employee struct
        getline(ss, cell, ',');
        stringstream(cell) >> employees[index].age;

        getline(ss, cell, ',');
        employees[index].gender = cell;

        getline(ss, cell, ',');
        employees[index].educationLevel = cell;

        getline(ss, cell, ',');
        employees[index].jobTitle = cell;

        getline(ss, cell, ',');
        stringstream(cell) >> employees[index].yearsOfExperience;

        getline(ss, cell, ',');
        stringstream(cell) >> employees[index].salary;

        index++;
    }
    file.close();

    // Create and populate the hash table
    HashTable hashTable;
    for (int i = 0; i < index; i++) {
        hashTable.insert(employees[i]);
    }

    // Display the hash table data
    hashTable.display();

    return 0;
}
